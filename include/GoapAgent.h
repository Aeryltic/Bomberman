#ifndef GOAPAGENT_H
#define GOAPAGENT_H

#include <unordered_map>
#include <memory>
#include <list>

#include "Components.h"
#include "FSM.h"
#include "Action.h"
#include "WorldState.h"

class GoapAgent : public Component /// stworzyć system, który to obsłuży przynajmniej w jednym aspekcie
{
public:
    GoapAgent(std::weak_ptr<Entity> owner);
    virtual ~GoapAgent();

    void add_action(Action a);
    void remove_action(std::string name);

    void set_state(string name, bool value);
    WorldState& get_world_state();

    std::unordered_map<std::string, Action>& get_actions();
    bool has_plan() const;
    void set_plan(std::list<Action*> plan);

    WorldState find_goal();

    void scan_world();

    FSM* getFSM(){return &fsm;}

    void add_goal(std::string goal_name, bool goal_state, unsigned priority);

protected:
    FSM fsm;
    //std::unordered_map<std::string, bool> world_state;
    WorldState ws;
    std::unordered_map<std::string, Action> available_actions;
    std::list<std::pair<unsigned, std::pair<std::string, bool>>> goals; // <priority, <goal_name, goal_state>>

    friend class PerformActionState;
    std::list<Action*> current_actions;
};

#endif // GOAPAGENT_H
