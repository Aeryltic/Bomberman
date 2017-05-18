#ifndef GOAPAGENT_H
#define GOAPAGENT_H

#include <unordered_map>
#include <memory>
#include <queue>

#include "Components.h"
#include "FSM.h"
#include "Action.h"

class GoapAgent : public Component /// stworzyć system, który to obsłuży przynajmniej w jednym aspekcie
{
public:
    GoapAgent(std::weak_ptr<Entity> owner);
    virtual ~GoapAgent();

    void add_available_action(std::string name, Action a);
    void remove_available_action(std::string name);

    void set_variable(string name, bool value);

protected:
    FSM fsm;
    std::unordered_map<std::string, bool> world_state;
    std::unordered_map<std::string, Action> available_actions;
};

#endif // GOAPAGENT_H
