#ifndef FSMSTATE_H
#define FSMSTATE_H

class FSM;

class FSMState
{
public:
    FSMState(FSM *fsm);
    virtual ~FSMState();

    virtual void update() = 0;

protected:
    FSM *fsm;
};

class IdleState : public FSMState
{
public:
    IdleState(FSM *fsm);
    virtual ~IdleState();

    void update();
};

class GotoState : public FSMState
{
public:
    GotoState(FSM *fsm);
    virtual ~GotoState();

    void update();
};

class PerformActionState : public FSMState
{
public:
    PerformActionState(FSM *fsm);
    virtual ~PerformActionState();

    void update();
};

#endif // FSMSTATE_H
