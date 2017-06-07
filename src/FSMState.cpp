#include "FSMState.h"

#include "FSM.h"
#include "GoapPlanner.h"
#include "WorldState.h"
#include "GoapAgent.h"

FSMState::FSMState(FSM *fsm) : fsm(fsm) { }
FSMState::~FSMState() { }

Entity* FSMState::get_owner() {
    return fsm->get_agent()->owner.lock().get();
}
//------------------------------------------------------------------------------------------------------------------------------------------------
IdleState::IdleState(FSM *fsm): FSMState(fsm) {
    wait_end = 0;
}
IdleState::~IdleState() {}
void IdleState::update(int ms) {
    //printf("IdleState::update\n");
    if((wait_end == 0) || (wait_end <= SDL_GetTicks())) {
        wait_end = 0;
        GoapPlanner planner;
        GoapAgent* agent = fsm->get_agent();

        WorldState goal = agent->find_goal();

        agent->scan_world();
        agent->set_plan(planner.plan(agent, goal));

        if(!agent->has_plan()) { /// jeśli nie znalazł planu czeka sekundę
            //printf("plan was empty\n");
            wait_end = SDL_GetTicks() + 1000;
        } else {
            fsm->pop_state();
            fsm->push_state(make_unique<PerformActionState>(fsm));
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------
GotoState::GotoState(FSM *fsm, weak_ptr<Entity> dest, float min_range): FSMState(fsm), dest(dest), min_range(min_range) {} /// dest to raczej powinien być ten ActionArea czy cuś
GotoState::~GotoState() {}

bool GotoState::is_in_range() {
    CPhysicalForm *pf = get_owner()->get<CPhysicalForm>();
    if(pf) {
        if(!dest.expired() && dest.lock()->is_active()) {
            auto d = pf->pos.dist(dest.lock()->get<CPhysicalForm>()->pos);
            //printf("pos: %s, dest: %s, distance: %.2f\n", pf->pos.repr().c_str(), dest.repr().c_str(), d);
            return d <= min_range;
        }
    }
    return false;
    //return pf && (pf->pos.dist(dest) <= min_range);
}

void GotoState::update(int ms) {
    //printf("GotoState::update\n");
    CPhysicalForm *pf = get_owner()->get<CPhysicalForm>();
    CMovement *mv = get_owner()->get<CMovement>();
    if(pf && mv) {
        if(!dest.expired() && dest.lock()->is_active()) {
            pf->pos = pf->pos.moved_towards(dest.lock()->get<CPhysicalForm>()->pos, mv->max_speed * ms / 1000.0);
        }
        else {
            fsm->pop_state(); // zamiast tego - szukaj nowego celu
            return;
        }
    }
    if(is_in_range()) {
        fsm->pop_state();
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------
PerformActionState::PerformActionState(FSM *fsm): FSMState(fsm) {}
PerformActionState::~PerformActionState() {}

void PerformActionState::update(int ms) { /// tu potrzeba dużo pracy... to obrzydliwie wygląda
    /// można by po prostu licznik już wyszukanych celów dodać
    //printf("PerformActionState::update\n");
    GoapAgent* agent = fsm->get_agent();
    if(agent->has_plan()) {
        Action* action = agent->current_actions.front();
        if(!action->is_being_performed()) {
            if(action->does_need_target() && !action->has_target()) {
                if(!action->find_target(CActionTarget::targets)) { // nie można kontynuować, olać to
                    fsm->pop_state();
                    return;
                }
            }
            if(!action->is_in_range()) {
                CPhysicalForm *tpf = action->get_target().lock()->get<CPhysicalForm>();
                if(tpf) {
                    //vec3d dest = tpf->pos;
                    fsm->push_state(make_unique<GotoState>(fsm, action->get_target(), 10));
                    return;
                } else {
                    printf("invalid target!\n");
                    fsm->pop_state();
                    return;
                }
            } else {
                action->start();
            }
        } else {
            if(action->does_need_target() && !action->has_target()) {
                //printf("target lost or sth!\n");
                fsm->pop_state(); /// to nie działa jak należy
                action->reset();
                return;
            }
        }
        if(action->perform(ms)) {
            agent->ws = action->act_on(agent->ws); /// trzeba dodać sprawdzenie, czy worldstate nadal spełnia warunki
            agent->current_actions.pop_front();
            return;
        }

    } else {
//        printf("no plan\n");
        fsm->pop_state();
        return;
    }
}
