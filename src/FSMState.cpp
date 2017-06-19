#include "FSMState.h"

#include <SDL.h>

#include "FSM.h"
#include "GoapPlanner.h"
#include "WorldState.h"
#include "GoapAgent.h"

#include "Components.h"

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
    if((wait_end == 0) || (wait_end <= SDL_GetTicks())) {
        wait_end = 0;
        GoapPlanner planner;
        GoapAgent* agent = fsm->get_agent();

        agent->scan_world();
        WorldState goal = agent->find_goal();
        agent->set_plan(planner.plan(agent, goal));

        if(!agent->has_plan()) { /// jeśli nie znalazł planu czeka sekundę
            unsigned wait_time = 1000 + rand() % 10000;
            wait_end = SDL_GetTicks() + wait_time;
            logs::log("no plan - waiting for: %d\n", wait_time);
            CMovement *mv = get_owner()->get<CMovement>();
            if(mv)mv->stop(); /// nie działa, bo kolizje
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
    CPhysicalForm* pf = get_owner()->get<CPhysicalForm>();
    CPhysicalForm* tpf = dest.lock()->get<CPhysicalForm>();
    return pf && tpf ? (pf->pos.dist(tpf->pos) <= (pf->vol.x + tpf->vol.x) / 2) : false;
}

void GotoState::update(int ms) {
    CPhysicalForm *pf = get_owner()->get<CPhysicalForm>();
    CMovement *mv = get_owner()->get<CMovement>();
    if(pf && mv) {
        if(!dest.expired() && dest.lock()->is_active()) {
            mv->speed = pf->pos.movement_step(dest.lock()->get<CPhysicalForm>()->pos, mv->max_speed * ms / 1000.0);
        } else {
            //mv->stop();
            fsm->pop_state();
            return;
        }
    }
    if(is_in_range()) {
        mv->stop();
        fsm->pop_state();
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------
PerformActionState::PerformActionState(FSM *fsm): FSMState(fsm), target_counter(0) {}
PerformActionState::~PerformActionState() {}

void PerformActionState::update(int ms) { /// tu potrzeba dużo pracy... to obrzydliwie wygląda
    /// można by po prostu licznik już wyszukanych celów dodać
    GoapAgent* agent = fsm->get_agent();
    if(agent->has_plan()) {
        Action* action = agent->current_actions.front();
        if(!action->is_performed()) {
            if(action->does_need_target() && !action->has_target()) {
                if(target_counter || !action->find_target(CActionTarget::targets)) { // nie można kontynuować, olać to
                    CMovement *mv = get_owner()->get<CMovement>();
                    if(mv)mv->stop(); /// nie działa, bo kolizje

                    fsm->pop_state();
                    return;
                }
                target_counter++;
            }
            if(!action->is_in_range()) {
                CPhysicalForm *tpf = action->get_target().lock()->get<CPhysicalForm>();
                if(tpf) {
                    //vec3d dest = tpf->pos;
                    fsm->push_state(make_unique<GotoState>(fsm, action->get_target(), 10));
                    return;
                } else {
                    logs::log("invalid target!\n");
                    fsm->pop_state();
                    return;
                }
            } else {
                action->start();
            }
        } else {
            if(action->does_need_target() && !action->has_target()) {
                //printf("target lost or sth!\n");
                fsm->pop_state();
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
