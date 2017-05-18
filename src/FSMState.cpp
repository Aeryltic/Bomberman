#include "FSMState.h"

#include "FSM.h"

FSMState::FSMState(FSM *fsm) : fsm(fsm)
{

}
FSMState::~FSMState()
{
    //dtor
}

IdleState::IdleState(FSM *fsm): FSMState(fsm) {}
IdleState::~IdleState() {}
void IdleState::update()
{
//        look_for_plan();
//        fsm->push_state(make_unique<PerformActionState>(fsm));

}

GotoState::GotoState(FSM *fsm): FSMState(fsm) {}
GotoState::~GotoState() {}
void GotoState::update()
{
//        if(is_in_range())
//        {
//            fsm->pop_state();
//        }
//        else
//        {
//
//        }
}

PerformActionState::PerformActionState(FSM *fsm): FSMState(fsm) {}
PerformActionState::~PerformActionState() {}
void PerformActionState::update()
{
//        if(!is_in_range())
//        {
//            fsm->push_state(make_unique<GotoState>(fsm));
//        }
//        else
//        {
//
//        }
}
