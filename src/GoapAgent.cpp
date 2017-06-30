#include "GoapAgent.h"

GoapAgent::GoapAgent() {
    push_state<IdleState>();
}

GoapAgent::~GoapAgent() { }

void GoapAgent::add_action(Action *a) {
//    a.set_agent(this);
    available_actions.insert({a->get_name(), a});
}

void GoapAgent::remove_action(std::string name) {
    available_actions.erase(name);
}

void GoapAgent::set_state(std::string name, bool value) {
    ws[name] = value;
}

WorldState& GoapAgent::get_world_state() {
    return ws;
}

std::unordered_map<std::string, Action*>& GoapAgent::get_actions() {
    return available_actions;
}
int GoapAgent::get_action_perform_time() {
    try {
        return static_cast<PerformActionState*>(states.top().get())->get_time();
    } catch(...) { }
    return 0;
}
//bool GoapAgent::has_plan() const {
//    return !current_actions.empty();
//}
//
//void GoapAgent::set_plan(std::list<Action*> plan) {
//    current_actions = plan;
//}

void GoapAgent::add_goal(std::string goal_name, bool goal_state, unsigned priority) {
    auto it = goals.begin();//std::lower_bound(open.begin(), open.end(), node);
    while(it != goals.end() && it->first <= priority)it++;
    goals.emplace(it, make_pair(priority, make_pair(goal_name, goal_state)));
}

WorldState GoapAgent::find_goal() {
    WorldState goal;
    for(auto p: goals) {
        if(p.second.second != ws[p.second.first]) {
            goal.add(p.second.first, p.second.second); // to tylko na chwilę
            break;
        }
    }
    return goal;
}

void GoapAgent::scan_world() {
    /// trzeba rozwinąć sensory
    Entity* _owner = owner.lock().get();
    for(auto a: available_actions) { /// skrypty powinny być powiązane z celami, nie z akcjami - to jak jest teraz to nie jest goal-oriented
        try {
            a.second->scan(_owner);
        } catch(LuaException const& e) {
            logs::log("%s\n", e.what());
        }
    }
}

void GoapAgent::pop_state() {
    states.pop();

    if(states.empty())
        push_state<IdleState>();
}
