#ifndef FSMSTATE_H
#define FSMSTATE_H

#include "Structures.h"

class FSM;

class FSMState
{
public:
    FSMState(FSM *fsm);
    virtual ~FSMState();

    virtual void update(int ms) = 0;

protected:
    FSM *fsm;
};

class IdleState : public FSMState
{
public:
    IdleState(FSM *fsm);
    virtual ~IdleState();

    void update(int ms);
    unsigned wait_end;
};

class GotoState : public FSMState
{
public:
    GotoState(FSM *fsm, vec3d dest, float min_range);
    virtual ~GotoState();

    void update(int ms);

    vec3d dest; /// robi się zamieszanie, bo już jeden dest jest w CMovement
    float min_range;

    bool is_in_range();
};

class PerformActionState : public FSMState
{
public:
    PerformActionState(FSM *fsm);
    virtual ~PerformActionState();

    void update(int ms);
};

#endif // FSMSTATE_H
