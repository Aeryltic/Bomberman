#include "Action.h"

Action::Action(std::string name, int cost): name(name), cost(cost)
{

}
Action::~Action()
{
    //dtor
}

void Action::add_precondition(std::string name, bool value)
{
    preconditions.insert({name, value});
}
void Action::remove_precondition(std::string name)
{
    preconditions.erase(name);
}
void Action::add_effect(std::string name, bool value)
{
    effects.insert({name, value});
}
void Action::remove_effect(std::string name)
{
    effects.erase(name);
}
