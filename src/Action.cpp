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

const ActionExecutor::exec_fun ActionExecutor::fun0(ScriptSystem::getInstance()->getLuaState(), "do_nothing");// = [](Entity* doer, Entity* target) {return true;};

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

    for(auto a : j) { /// obsługa wyjątków!
        try {
            //std::string name = a["name"];
            //printf("adding action: %s...", name.c_str());
            Action action(a["name"], a["cost"], a["duration"], a["target"]);
            for(auto p: a["preconditions"]) {
                action.add_precondition(p[0],p[1]);
            }
            for(auto e: a["effects"]) {
                action.add_effect(e[0],e[1]);
            }
            lua_State* L  = ScriptSystem::getInstance()->getLuaState();
            std::string scr_name = a["script"];
            LuaRef script = getGlobal(L, scr_name.c_str());
            action.set_exec(script);
            actions.insert({action.name, std::move(action)});
            //printf(" done.\n");
        } catch(invalid_argument& e) {
            printf("error while loading from data/actions.json: %s\n", e.what());
        }

    }
/// to tak samo powinno nie być tu - ale w skryptach
    /*
        actions["pickup_grain"].set_exec([](Entity* doer, Entity* target) {
            target->destroy_me();
            return true;
        });
        actions["deliver_grain"].set_exec([](Entity* doer, Entity* target) {
            auto e = target->get<CEnergyStore>();
            if(e) e->amount += 100;
            return true;
        });
        actions["kill_enemy"].set_exec([](Entity* doer, Entity* target) {
            printf("killing: %d\n", target->get_id());
            target->destroy_me();
            return true;
        });
        */
}

Action Action::get_action(std::string name) {
    auto f = actions.find(name);
    if(f == actions.end()) {
        throw std::runtime_error("bad action name");
    }
    return f->second;
}
/// NIE-STATIC
Action::Action(std::string name, int cost, unsigned duration, std::string target_name): name(name), cost(cost), duration(duration), target_name(target_name) {
    needs_target = (target_name != "");
    start_tick = 0;
}

Action::~Action() {
    //dtor
}

Action& Action::add_precondition(std::string name, bool value) {
    precondition.add(name, value);
//    preconditions.insert({name, value});
    return *this;
}
Action& Action::remove_precondition(std::string name) {
    precondition.remove(name);
//    preconditions.erase(name);
    return *this;
}
Action& Action::add_effect(std::string name, bool value) {
    effect.add(name, value);
//    effects.insert({name, value});
    return *this;
}
Action& Action::remove_effect(std::string name) {
    effect.remove(name);
//    effects.erase(name);
    return *this;
}
void Action::set_agent(GoapAgent* agent) {
    this->agent = agent;
}
Entity* Action::get_owner() {
    //printf("Action::get_owner()... ");
    return agent->owner.lock().get();
}
bool Action::is_doable(const WorldState &ws) {
    //printf("\"%s\": checking doability on \n\tworldstate: %s\n\tneeded %s\n", name.c_str(), ws.repr().c_str(), precondition.repr().c_str());
    for(auto v : precondition.attrs) {
        auto f = ws.attrs.find(v.first);
        if(f == ws.attrs.end() || f->second != v.second) {
            //printf("  not passed\n");
            return false;
        }
    }
    //printf("  passed\n");
    return true;
}

WorldState Action::act_on(WorldState ws) {
    for(auto p : effect.attrs) {
        ws[p.first] = p.second;
    }
    return ws;
}

bool Action::find_target(std::unordered_map<std::string, std::vector<std::weak_ptr<Entity>>>& targets) {
    //printf("looking for targets\n");
    std::weak_ptr<Entity> closest;
    double dist = 0;
    //printf("trying owner... ");
    auto opf = get_owner()->get<CPhysicalForm>();
    //printf("-opf\n");
    if(opf) {
        for(auto target: targets[target_name]) {
            //printf("+");
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
            } //else printf("possible target expired!\n");
        }
        //printf("\n");
    }
    if(closest.expired()) {
//        printf("couldn't find a target...");
        return false;
    }
//    printf("target found!");
    target = closest;
    return true;
}

void Action::reset() {
    start_tick = 0;
    target.reset();
    execute.stop();
}

bool Action::perform(int ms_passed) {
    /*
    if(start_tick == 0) {
        start_tick = SDL_GetTicks();
    }
    if(SDL_GetTicks() >= start_tick + duration) { /// to jest zło - to skrypt powinien decydować
        // tu się odpali jakiś przypisany skrypt...
        execute(get_owner(), get_target().lock().get()); /// no ale co jeśli ta akcja jest ciągła?
        reset();
        return true;
    }
    */
    if(execute(get_owner(), get_target().lock().get(), ms_passed))
    {
        execute.stop();
        return true;
    }
    return false;
}

bool Action::is_in_range() {
    return needs_target ? (has_target() ? (get_owner()->get<CPhysicalForm>()->pos.dist(target.lock()->get<CPhysicalForm>()->pos) <= 10) : false) : true; // piękne
}

bool Action::has_target() {
    return !target.expired() && target.lock()->is_active();
}
