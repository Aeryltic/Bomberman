#include "FSMState.h"

#include <SDL.h>

#include "FSM.h"
#include "WorldState.h"
#include "GoapAgent.h"

#include "Components.h"

FSMState::FSMState(GoapAgent* agent, FSMState* parent) : agent(agent), parent(parent) { }
FSMState::~FSMState() { }

Entity* FSMState::get_owner() {
    return agent->owner.lock().get();
}
//------------------------------------------------------------------------------------------------------------------------------------------------
IdleState::IdleState(GoapAgent *agent, FSMState* parent): FSMState(agent, parent) {
    wait_end = 0;
}
IdleState::~IdleState() {}
void IdleState::update(int ms) {
    if((wait_end == 0) || (wait_end <= SDL_GetTicks())) {
        wait_end = 0;

        agent->scan_world();
        WorldState goal = agent->find_goal();
        PlanExecutionState::ActionPlan plan = planner.plan(agent, goal);

        if(!plan.empty()) {
            agent->push_state<PlanExecutionState>(plan);
        } else {
            unsigned wait_time = 1000 + rand() % 4000; // 1-5s czekania
            wait_end = SDL_GetTicks() + wait_time;
            logs::log("no plan - waiting for: %d\n", wait_time);
            CMovement *mv = get_owner()->get<CMovement>();
            if(mv)mv->stop(); /// nie działa, bo kolizje... nie działa?
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------
PlanExecutionState::PlanExecutionState(GoapAgent* agent, FSMState* parent, ActionPlan plan) : FSMState(agent, parent), plan(plan) {

}

PlanExecutionState::~PlanExecutionState() {

}

void PlanExecutionState::update(int ms) {
    if(plan.empty()) {
        agent->pop_state();
        return;
    }
    if(action()->does_need_target()) {
        weak_ptr<Entity> target = find_target(action()->get_target_name(), CActionTarget::targets);
        if(!target.expired()) {
            agent->push_state<PerformActionState>(action(), target);
        } else {
            agent->pop_state();
            return;
        }
    } else {
        agent->push_state<PerformActionState>(action(), std::weak_ptr<Entity>());
    }
}

std::weak_ptr<Entity> PlanExecutionState::find_target(std::string target_name, std::unordered_map<std::string, std::vector<std::weak_ptr<Entity>>>& targets) {
    std::weak_ptr<Entity> closest;
    double dist = 0;
    auto opf = get_owner()->get<CPhysicalForm>();
    if(opf) {
        for(auto target: targets[target_name]) {
            if(!target.expired()) {
                auto pf = target.lock()->get<CPhysicalForm>();
                if(pf) {
                    if(closest.expired()) {
                        closest = target;
                        dist = opf->pos.dist(pf->pos);
                    } else {
                        double temp = opf->pos.dist(pf->pos);
                        if(temp < dist) {
                            closest = target;
                            dist = temp;
                        }
                    }
                }
            }
        }
    }
    return closest;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
PerformActionState::PerformActionState(GoapAgent *agent, FSMState* parent, Action* action, std::weak_ptr<Entity> target): FSMState(agent, parent), action(action), target(target), target_counter(0) {
    action_perform_time = 0;
}
PerformActionState::~PerformActionState() {}

void PerformActionState::update(int ms) {
    action_perform_time += ms;
    try {
        if(action->perform(get_owner(), target.expired() ? nullptr : target.lock().get(), ms)) {
            agent->ws = action->act_on(agent->ws); /// tego tu być nie winno
            static_cast<PlanExecutionState*>(parent)->next_action();
            agent->pop_state();
            return;
        }
    } catch (LuaException& ex) { /// błąd przy wykonaniu akcji - kończymy ją
        logs::log("action exception: %s\n", ex.what());
        agent->pop_state();
        return;
    }
}
