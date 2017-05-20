#include "GoapAgent.h"

GoapAgent::GoapAgent(weak_ptr<Entity> owner) : Component(owner), fsm(this)
{
    //ctor
}

GoapAgent::~GoapAgent()
{
    //dtor
}


void GoapAgent::add_action(Action a)
{
    available_actions.insert({a.name,a});
}
void GoapAgent::remove_action(std::string name)
{
    available_actions.erase(name);
}

void GoapAgent::set_state(string name, bool value)
{
    ws[name] = value;
}

WorldState& GoapAgent::get_world_state()
{
    return ws;
}

std::unordered_map<std::string, Action>& GoapAgent::get_actions()
{
    return available_actions;
}

bool GoapAgent::has_plan() const
{
    return !current_actions.empty();
}

void GoapAgent::set_plan(std::list<Action*> plan)
{
    current_actions = plan;
}

WorldState GoapAgent::find_goal()
{
    WorldState goal;
    goal
        .add("grain_delivered", true);
    return goal;
}

void GoapAgent::scan_world()
{
    set_state("grain_delivered", false);
}
