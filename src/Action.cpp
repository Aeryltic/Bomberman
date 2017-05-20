#include "Action.h"

#include <functional>

std::unordered_map<std::string, Action> Action::actions;

void Action::init_actions()
{
//-----------------------------------------------------------------------
    Action action("goto", 5); /// jakaś metaakcja
    action
        .add_precondition("in_range", false)
        .add_effect("in_range", true);
    actions.insert({action.name, action});
//-----------------------------------------------------------------------
    action = Action("deliver_grain", 10);
    action
        .add_precondition("have_grain", true)
        .add_precondition("grain_delivered", false)
        .add_effect("have_grain", false)
        .add_effect("grain_delivered", true);
    actions.insert({action.name, action});
//-----------------------------------------------------------------------
    action = Action("pickup_grain", 1);
    action
        .add_precondition("have_grain", false)
        .add_effect("have_grain", true);
    actions.insert({action.name, action});
//-----------------------------------------------------------------------
}

Action Action::get_action(std::string name)
{
    auto f = actions.find(name);
    if(f==actions.end())
    {
        throw std::runtime_error("bad action name");
    }
    return f->second;
}

Action::Action(std::string name, int cost): name(name), cost(cost)
{

}
Action::~Action()
{
    //dtor
}

Action& Action::add_precondition(std::string name, bool value)
{
    precondition.add(name, value);
//    preconditions.insert({name, value});
    return *this;
}
Action& Action::remove_precondition(std::string name)
{
    precondition.remove(name);
//    preconditions.erase(name);
    return *this;
}
Action& Action::add_effect(std::string name, bool value)
{
    effect.add(name, value);
//    effects.insert({name, value});
    return *this;
}
Action& Action::remove_effect(std::string name)
{
    effect.remove(name);
//    effects.erase(name);
    return *this;
}

bool Action::is_doable(const WorldState &ws)
{
    //printf("\"%s\": checking doability on \n\tworldstate: %s\n\tneeded %s\n", name.c_str(), ws.repr().c_str(), precondition.repr().c_str());
    for(auto v : precondition.attrs)
    {
        auto f = ws.attrs.find(v.first);
        if(f == ws.attrs.end() || f->second != v.second)
        {
            //printf("  not passed\n");
            return false;
        }
    }
    //printf("  passed\n");
    return true;
}

WorldState Action::act_on(WorldState ws)
{
    for(auto p : effect.attrs)
    {
        ws[p.first] = p.second;
    }
    return ws;
}
