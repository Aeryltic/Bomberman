#include "FSMState.h"

#include "FSM.h"
#include "GoapPlanner.h"
#include "WorldState.h"
#include "GoapAgent.h"

FSMState::FSMState(FSM *fsm) : fsm(fsm)
{

}
FSMState::~FSMState()
{
    //dtor
}

IdleState::IdleState(FSM *fsm): FSMState(fsm) {wait_end = 0;}
IdleState::~IdleState() {}
void IdleState::update(int ms)
{
    if((wait_end == 0) || (wait_end <= SDL_GetTicks()))
    {
        wait_end = 0;
        GoapPlanner planner;
        GoapAgent* agent = fsm->get_agent();

        WorldState goal = agent->find_goal();

        agent->scan_world();
        agent->set_plan(planner.plan(agent, goal));

        if(!agent->has_plan()) /// jeśli nie znalazł planu czeka sekundę
        {
            //printf("plan was empty\n");
            wait_end = SDL_GetTicks() + 1000;
        }
        else
        {
            fsm->pop_state();
            fsm->push_state(make_unique<PerformActionState>(fsm));
        }
    }
}

GotoState::GotoState(FSM *fsm, vec3d dest, float min_range): FSMState(fsm), dest(dest), min_range(min_range) {}
GotoState::~GotoState() {}

bool GotoState::is_in_range()
{
    CPhysicalForm *pf = fsm->get_agent()->owner.lock()->get<CPhysicalForm>();
    return pf || pf->pos.dist(dest) <= min_range;
}

void GotoState::update(int ms)
{
    if(is_in_range())
    {
        fsm->pop_state(); /// ślisko
    }
}

PerformActionState::PerformActionState(FSM *fsm): FSMState(fsm) {}
PerformActionState::~PerformActionState() {}

void PerformActionState::update(int ms) /// tu potrzeba dużo pracy
{
    GoapAgent* agent = fsm->get_agent();
    if(agent->has_plan())
    {
        printf("acting: %s\n", agent->current_actions.front()->name.c_str());
        agent->ws = agent->current_actions.front()->act_on(agent->ws); /// trzeba dodać sprawdzenie, czy worldstate nadal spełnia warunki
        agent->current_actions.pop_front();
    }
    else
    {
//        printf("no plan\n");
        fsm->pop_state();
    }
}
