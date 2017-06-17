#include "GoapAgent.h"

GoapAgent::GoapAgent() : fsm(this) { }

GoapAgent::~GoapAgent() { }

void GoapAgent::add_action(Action a) {
    a.set_agent(this);
    available_actions.insert({a.get_name(),a});
}

void GoapAgent::remove_action(std::string name) {
    available_actions.erase(name);
}

void GoapAgent::set_state(string name, bool value) {
    ws[name] = value;
}

WorldState& GoapAgent::get_world_state() {
    return ws;
}

std::unordered_map<std::string, Action>& GoapAgent::get_actions() {
    return available_actions;
}

bool GoapAgent::has_plan() const {
    return !current_actions.empty();
}

void GoapAgent::set_plan(std::list<Action*> plan) {
    current_actions = plan;
}

void GoapAgent::add_goal(std::string goal_name, bool goal_state, unsigned priority) {
    auto it = goals.begin();//std::lower_bound(open.begin(), open.end(), node);
    while(it != goals.end() && it->first <= priority)it++;
    goals.emplace(it, make_pair(priority, make_pair(goal_name, goal_state)));
}

WorldState GoapAgent::find_goal() {
    WorldState goal;
    for(auto p: goals) {
        if(p.second.second != ws[p.second.first]){
            goal.add(p.second.first, p.second.second); // to tylko na chwilę
            break;
        }
    }
    return goal;
    /*
    WorldState goal;
    goal
        .add("grain_delivered", true);
    return goal;
    */
}

void GoapAgent::scan_world() {
    //owner.lock()->receive_message(Message(MSG_SCANNING, owner));
    set_state("grain_delivered", false);    /// to tu nie może być
    set_state("enemy_killed", false);       /// tak samo to
                                            /// trzeba rozwinąć sensory
    for(auto a: available_actions){ /// to też nie jest dobre rozwiązanie
        a.second.scan();
    }
}
