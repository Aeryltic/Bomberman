#include "FSM.h"

#include "FSMState.h"

FSM::FSM(GoapAgent *agent) : agent(agent) {
    push_state(std::make_unique<IdleState>(this));
}

FSM::~FSM() {
    //dtor
}

void FSM::update(int ms) {
    if(states.empty())
        push_state(make_unique<IdleState>(this));
    states.top()->update(ms);
}

void FSM::push_state(std::unique_ptr<FSMState> state) {
    states.push(std::move(state));
}

void FSM::pop_state() {
    states.pop();
}
