#include "FSM.h"

#include "FSMState.h"

FSM::FSM(GoapAgent *agent) : agent(agent)
{
    push_state(std::make_unique<IdleState>(this));
}

FSM::~FSM()
{
    //dtor
}

void FSM::update()
{
    if(!states.empty())
    {
        states.top()->update();
    }
}

void FSM::push_state(std::unique_ptr<FSMState> state)
{
    states.push(std::move(state));
}

void FSM::pop_state()
{
    states.pop();
}
