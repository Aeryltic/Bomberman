#include "Action.h"

#include "Engine.h"
#include "ScriptSystem.h"

#include "json.hpp"

#include "Entity.h"
#include "Components.h"
#include "GoapAgent.h"

#include "AIPackage.h"

#include "MiscFunctions.h"

///STATIC
using json = nlohmann::json;
std::unordered_map<std::string, Action> Action::actions;
std::unordered_map<std::string, AIPackage> Action::ai_packages;

void Action::init_actions() {
    logs::open("initializing actions...\n");

    std::string filename("data/actions.json");
    json j;
    file_to_json(j, filename);

    for(auto a : j) {
        //logs::open("next action\n");
        try {
            Action action(a["name"], a["cost"], a["target"]);

            try {
                for(auto p: a["preconditions"]) {
                    action.add_precondition(p[0],p[1]);
                }
            } catch(domain_error& e) {
                logs::log("no preconditions: %s\n", e.what());
            }

            try {
                for(auto e: a["effects"]) {
                    action.add_effect(e[0],e[1]);
                }
            } catch(domain_error& e) {
                logs::log("no effects: %s\n", e.what());
            }

            std::string scr_name = a["script"];
            action.set_exec(Engine::lua()->get(scr_name));
            try {
                std::string scanner_name = a["scanner"];
                action.set_scanner(Engine::lua()->get(scanner_name));
            } catch(domain_error& e) {
                logs::log("no scanner: %s\n", e.what());
                action.set_scanner(Engine::lua()->get("empty_scanner"));
            }

            actions.insert({action.name, std::move(action)});

            //logs::close("\n");
        } catch(invalid_argument& e) {
            logs::log("error while loading from %s: %s\n", filename.c_str(), e.what());
            //logs::close("error\n");
        }
    }
    logs::close("done!\n");
}
/// action packs
void Action::init_action_packs() {
    logs::open("initializing ai_packs...\n");

    std::string filename("data/ai_packages.json");
    json j;
    file_to_json(j, filename);

    for(auto p : j) {
        try {
            AIPackage ai_pack(p["name"].get<std::string>());
            for(auto g: p["goals"]) {
                try {
                    ai_pack.add_goal(g[0], g[1], g[2]);
                } catch(domain_error& e) {
                    logs::log("bad table: %s (%s)\n", e.what(), g.get<std::string>().c_str());
                }
            }
            for(auto a: p["actions"]) {
                try {
                    ai_pack.add_action(a);
                } catch(domain_error& e) {
                    logs::log("bad action: %s (%s)\n", e.what(), a.get<std::string>().c_str());
                }
            }
            ai_packages.insert({ai_pack.name, std::move(ai_pack)});
        } catch(invalid_argument& e) {
            logs::log("error while loading from %s: %s\n", filename.c_str(), e.what());
        } catch(domain_error& e) {
            logs::log("bad package: %s (%s)\n", e.what(), p.get<std::string>().c_str());
        }
    }
    logs::close("done!\n");
}

Action* Action::get_action(std::string name) {
    return &actions.at(name);
}

AIPackage Action::get_ai_package(std::string name) {
    return ai_packages.at(name);
}

void Action::clear(){
    ai_packages.clear();
    actions.clear();
}

/// NON-STATIC
Action::Action(std::string name, int cost, std::string target_name): name(name), cost(cost), target_name(target_name), scanner(Engine::lua()->state()) {
    logs::log("new action: %s\n", name.c_str());
    needs_target = (target_name != "");
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

bool Action::perform(Entity* agent, Entity* target, int ms_passed) {
    return execute(agent, target, ms_passed);
}

/*
bool Action::is_in_range() {
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
*/
