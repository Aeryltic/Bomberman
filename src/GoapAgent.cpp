#include "GoapAgent.h"

GoapAgent::GoapAgent(weak_ptr<Entity> owner) : Component(owner), fsm(this)
{
    //ctor
}

GoapAgent::~GoapAgent()
{
    //dtor
}

inline void GoapAgent::add_available_action(string name, Action a)
{
    available_actions.insert({name,a});
}

inline void GoapAgent::remove_available_action(string name)
{
    available_actions.erase(name);
}

inline void GoapAgent::set_variable(string name, bool value)
{
    world_state[name] = value;
}
