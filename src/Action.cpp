#include "Action.h"

//#include <functional>
#include <string>
#include <fstream>
#include <streambuf>

#include "json.hpp"

#include "GoapAgent.h"
#include "Entity.h"
#include "Components.h"

///STATIC
using json = nlohmann::json;
std::unordered_map<std::string, Action> Action::actions;

void Action::init_actions() {
    std::ifstream t("data/actions.json");
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    json j;
    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    try {
        j = json::parse(str);
    } catch(runtime_error& e) {
        printf("runtime_error error while loading from data/actions.json: %s\n", e.what());
        return;
    } catch(invalid_argument& e) {
        printf("invalid_argument error while loading from data/actions.json: %s\n", e.what());
        return;
    }

    for(auto a : j) {
        try {
            Action action(a["name"], a["cost"], a["target"]);
            for(auto p: a["preconditions"]) {
                action.add_precondition(p[0],p[1]);
            }
            for(auto e: a["effects"]) {
                action.add_effect(e[0],e[1]);
            }
            lua_State* L  = ScriptSystem::instance()->state();
            std::string scr_name = a["script"];
            LuaRef script = getGlobal(L, scr_name.c_str());
            action.set_exec(script);
            try {
                std::string scanner_name = a["scanner"];
                action.set_scanner(getGlobal(L, scanner_name.c_str()));
            } catch(domain_error& e) {
                printf("no scanner: %s\n", e.what());
                action.set_scanner(getGlobal(L, "empty_scanner"));
            }

            actions.insert({action.name, std::move(action)});
        } catch(invalid_argument& e) {
            printf("error while loading from data/actions.json: %s\n", e.what());
        }

    }
}

Action Action::get_action(std::string name) {
    auto f = actions.find(name);
    if(f == actions.end()) {
        throw std::runtime_error("bad action name");
    }
    return f->second;
}

/// NIE-STATIC
Action::Action(std::string name, int cost, std::string target_name): name(name), cost(cost), target_name(target_name), scanner(ScriptSystem::state()) {
    needs_target = (target_name != "");
    //printf("%s needs target: %s\n", name.c_str(), needs_target ? "true" : "false");
}

Action::~Action() {
    //dtor
}

Action& Action::add_precondition(std::string name, bool value) {
    precondition.add(name, value);
    return *this;
}
Action& Action::remove_precondition(std::string name) {
    precondition.remove(name);
    return *this;
}
Action& Action::add_effect(std::string name, bool value) {
    effect.add(name, value);
    return *this;
}
Action& Action::remove_effect(std::string name) {
    effect.remove(name);
    return *this;
}
void Action::set_agent(GoapAgent* agent) {
    this->agent = agent;
}
Entity* Action::get_owner() {
    return agent->owner.lock().get();
}
bool Action::is_doable(const WorldState &ws) {
    for(auto v : precondition.attrs) {
        auto f = ws.attrs.find(v.first);
        if(f == ws.attrs.end() || f->second != v.second) {
            return false;
        }
    }
    return true;
}

WorldState Action::act_on(WorldState ws) {
    for(auto p : effect.attrs) {
        ws[p.first] = p.second;
    }
    return ws;
}

bool Action::find_target(std::unordered_map<std::string, std::vector<std::weak_ptr<Entity>>>& targets) {
    if(!needs_target) {
        target.reset();
        return true;
    }

    std::weak_ptr<Entity> closest;
    double dist = 0;
    auto opf = get_owner()->get<CPhysicalForm>();
    if(opf) {
        for(auto target: targets[target_name]) {
            if(!target.expired()) {
                auto pf = target.lock()->get<CPhysicalForm>();
                if(pf) {
                    if(closest.expired()) {
                        closest = target;
                        dist = opf->pos.dist(pf->pos);
                    } else {
                        double temp = opf->pos.dist(pf->pos);
                        if(temp < dist) {
                            closest = target;
                            dist = temp;
                        }
                    }
                }
            }
        }
    }
    if(closest.expired()) {
        return false;
    }
    target = closest;
    return true;
}

void Action::reset() {
    target.reset();
    execute.stop();
}

bool Action::perform(int ms_passed) { /// heavy

    if(execute(get_owner(), (get_target().expired() ? nullptr : get_target().lock().get()), ms_passed)) {
        execute.stop();
        return true;
    }
    return false;
}

bool Action::is_in_range() { /// to nie powinno mieć dwóch implementacji (druga jest w GotoState)
    if(needs_target) {
        if(target.expired()) return false;
        CPhysicalForm* pf = get_owner()->get<CPhysicalForm>();
        CPhysicalForm* tpf = target.lock()->get<CPhysicalForm>();
        return has_target() ? (pf->pos.dist(tpf->pos) <= (pf->vol.x + tpf->vol.x) / 2) : false;
    }
    return true;
}

bool Action::has_target() {
    return !target.expired() && target.lock()->is_active();
}
