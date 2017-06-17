#ifndef FSMSTATE_H
#define FSMSTATE_H

#include "Structures.h"

class Entity;
class FSM;

class FSMState
{
public:
    FSMState(FSM *fsm);
    virtual ~FSMState();

    virtual void update(int ms) = 0;
    Entity* get_owner();

protected:
    FSM *fsm;
};

class IdleState : public FSMState /// szukanie planu lub czekanie
{
public:
    IdleState(FSM *fsm);
    virtual ~IdleState();

    void update(int ms);
    unsigned wait_end;
};

class GotoState : public FSMState /// będzie korzystał z A* w przyszłości
{
public:
    GotoState(FSM *fsm, weak_ptr<Entity> dest, float min_range);
    virtual ~GotoState();

    void update(int ms);

    weak_ptr<Entity> dest;
    float min_range;

    bool is_in_range();
};

class PerformActionState : public FSMState
{
public:
    PerformActionState(FSM *fsm);
    virtual ~PerformActionState();

    void update(int ms);
    void set_target(weak_ptr<Entity> target);
};

#endif // FSMSTATE_H
