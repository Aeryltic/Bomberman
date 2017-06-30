#include "GoapPlanner.h"

#include <unordered_map>
#include <algorithm>

#include "ANode.h"
#include "Action.h"
#include "GoapAgent.h"
#include "WorldState.h"

GoapPlanner::GoapPlanner() {
    //ctor
}

GoapPlanner::~GoapPlanner() {
    //dtor
}

void GoapPlanner::add_to_open(ANode *node) {
    auto it = std::lower_bound(open.begin(), open.end(), node);
    open.emplace(it, node);
}

ANode* GoapPlanner::pop_and_close() {
    closed.push_back(std::move(open.front()));
    open.erase(open.begin());
    return closed.back();
}

bool GoapPlanner::is_closed(const WorldState& ws) {
    return std::find_if(closed.begin(), closed.end(), [&](const ANode* n) {
        return n->ws == ws;
    }) != closed.end();
}
std::list<ANode*>::iterator GoapPlanner::is_open(const WorldState& ws) {
    return std::find_if(open.begin(), open.end(), [&](const ANode* n) {
        return n->ws == ws;
    });
}

std::list<Action*> GoapPlanner::plan(GoapAgent *agent, WorldState goal) {
    WorldState &start = agent->get_world_state();

    open = std::list<ANode*>();
    closed.clear();
    nodes.clear();

    nodes.push_back(ANode(start, 0, start.distanceTo(goal), nullptr, nullptr));
    add_to_open(&nodes.back());

    while(!open.empty()) {
        ANode* current = pop_and_close();

        if(current->ws.fulfills(goal)) { /// jeśli dotarł do końca
            std::list<Action*> prepared_plan;
            while(current->parent != nullptr) {
                prepared_plan.push_back(current->action);
                current = current->parent;
            }
            prepared_plan.reverse();
            return prepared_plan;
        }

        for(auto& p : agent->get_actions()) {
            Action* potential_action = p.second;

            if(potential_action->is_doable(current->ws)) {
                WorldState outcome = potential_action->act_on(current->ws);
                if(is_closed(outcome)) {
                    continue;
                }

                auto p_outcome_node = is_open(outcome);
                if(p_outcome_node == open.end()) {
                    nodes.push_back(ANode(outcome, current->g + potential_action->get_cost(), outcome.distanceTo(goal), current, potential_action));
                    add_to_open(&nodes.back());
                } else {
                    if(current->g + potential_action->get_cost() < (*p_outcome_node)->g) {
                        (*p_outcome_node)->parent = current;
                        (*p_outcome_node)->g = current->g + potential_action->get_cost();
                        (*p_outcome_node)->h = outcome.distanceTo(goal);
                        (*p_outcome_node)->action = potential_action;

                        open.sort();
                    }
                }
            }
        }
    }
    logs::log("could not find a plan\n");
    return std::list<Action*>();
}

