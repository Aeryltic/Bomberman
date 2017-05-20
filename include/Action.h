#ifndef ACTION_H
#define ACTION_H

#include <unordered_map>
#include <string>

#include "WorldState.h"

class Action
{
public:
    std::string name;

    Action(std::string name, int cost);
    virtual ~Action();

    Action& add_precondition(std::string name, bool value);
    Action& remove_precondition(std::string name);
    Action& add_effect(std::string name, bool value);
    Action& remove_effect(std::string name);

    bool is_doable(const WorldState &ws);

    WorldState act_on(WorldState ws);

    static void init_actions();
    static Action get_action(std::string name);

    int getCost(){return cost;}

protected:

    int cost;

    WorldState precondition;
    WorldState effect;

    static std::unordered_map<std::string, Action> actions;
};

#endif // ACTION_H
