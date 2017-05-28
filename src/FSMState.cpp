#include "FSMState.h"

#include "FSM.h"
#include "GoapPlanner.h"
#include "WorldState.h"
#include "GoapAgent.h"

FSMState::FSMState(FSM *fsm) : fsm(fsm) { }
FSMState::~FSMState() { }
//------------------------------------------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------------------------------------
GotoState::GotoState(FSM *fsm, vec3d dest, float min_range): FSMState(fsm), dest(dest), min_range(min_range) {}
GotoState::~GotoState() {}

bool GotoState::is_in_range()
{
    CPhysicalForm *pf = fsm->get_agent()->owner.lock()->get<CPhysicalForm>();
    return pf && (pf->pos.dist(dest) <= min_range);
}

void GotoState::update(int ms)
{
    CPhysicalForm *pf = fsm->get_agent()->owner.lock()->get<CPhysicalForm>();
    CMovement *mv = fsm->get_agent()->owner.lock()->get<CMovement>();
    if(pf && mv)
        pf->pos = pf->pos.moved_towards(dest, mv->max_speed * ms / 1000.0);
    if(is_in_range())
    {
        fsm->pop_state(); /// ślisko
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------
PerformActionState::PerformActionState(FSM *fsm): FSMState(fsm) {}
PerformActionState::~PerformActionState() {}

void PerformActionState::update(int ms) /// tu potrzeba dużo pracy
{
    GoapAgent* agent = fsm->get_agent();
    if(agent->has_plan())
    {
        //printf("acting: %s\n", agent->current_actions.front()->name.c_str());
        Action* action = agent->current_actions.front();
        if(action->does_need_target() && !action->has_target())
        {
            if(!action->find_target(CActionTarget::targets)) // nie można kontynuować, olać to
            {
                //printf("can't perform action - failure\n");
                fsm->pop_state();
                return;
            }
        }
        if(!action->is_in_range())
        {
            CPhysicalForm *tpf = action->get_target().lock()->get<CPhysicalForm>();
            if(tpf)
            {
                vec3d dest = tpf->pos;
                fsm->push_state(make_unique<GotoState>(fsm, dest, 10));
                return;
            }
            else
            {
                printf("invalid target!\n");
                fsm->pop_state();
                return;
            }
        }
        if(action->perform())
        {
            agent->ws = action->act_on(agent->ws); /// trzeba dodać sprawdzenie, czy worldstate nadal spełnia warunki
            agent->current_actions.pop_front();
        }
    }
    else
    {
//        printf("no plan\n");
        fsm->pop_state();
        return;
    }
}

void PerformActionState::set_target(weak_ptr<Entity> target)
{

}
