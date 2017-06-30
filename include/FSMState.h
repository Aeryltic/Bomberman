#ifndef FSMSTATE_H
#define FSMSTATE_H

#include <memory>
#include <list>
#include <unordered_map>
#include <vector>

#include "Structures.h"

#include "GoapPlanner.h"

class Entity;
class GoapAgent;
class Action;

class FSMState {
public:
    FSMState(GoapAgent* agent, FSMState* parent);
    virtual ~FSMState();

    virtual void update(int ms) = 0;
    Entity* get_owner();

protected:
    GoapAgent* agent;
    FSMState* parent;
};

class IdleState : public FSMState { /// szukanie planu lub czekanie
public:
    IdleState(GoapAgent* agent, FSMState* parent);
    virtual ~IdleState();

    void update(int ms);

private:
    unsigned wait_end;
    GoapPlanner planner;
};

class PlanExecutionState : public FSMState {
public:
    using ActionPlan = std::list<Action*>;

    PlanExecutionState(GoapAgent* agent, FSMState* parent, ActionPlan plan);
    virtual ~PlanExecutionState();

    void update(int ms);

    std::weak_ptr<Entity> find_target(std::string target_name, std::unordered_map<std::string, std::vector<std::weak_ptr<Entity>>>& targets); /// ta funkcja tutaj jakoś mi nie pasuje

    Action* action() {return plan.front();}
    void next_action() {plan.pop_front();}
private:
    ActionPlan plan;
};

class PerformActionState : public FSMState {
public:
    PerformActionState(GoapAgent* agent, FSMState* parent, Action* action, std::weak_ptr<Entity> target);
    virtual ~PerformActionState();

    void update(int ms);
    void set_target(std::weak_ptr<Entity> target);

    unsigned get_time() {return action_perform_time;}

private:
    Action* action;
    std::weak_ptr<Entity> target;
    unsigned target_counter;
    unsigned action_perform_time;
};

#endif // FSMSTATE_H
