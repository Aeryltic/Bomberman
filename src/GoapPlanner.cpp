#include "GoapPlanner.h"

#include <unordered_map>
#include <algorithm>

#include "ANode.h"
#include "Action.h"
#include "GoapAgent.h"
#include "WorldState.h"

GoapPlanner::GoapPlanner()
{
    //ctor
}

GoapPlanner::~GoapPlanner()
{
    //dtor
}

void GoapPlanner::add_to_open(ANode *node)
{
    //printf("--adding to open: %s\n", node->ws.repr().c_str());
    auto it = std::lower_bound(open.begin(), open.end(), node);
    open.emplace(it, node);
    ////printf("--added: %s\n", (*it)->ws.repr().c_str());
}

ANode* GoapPlanner::pop_and_close()
{
    //printf("--popping: %s\n", open.front()->ws.repr().c_str());

    closed.push_back(std::move(open.front()));
    open.erase(open.begin());

    //printf("--returning: %s\n", closed.back()->ws.repr().c_str());
    return closed.back();
}

bool GoapPlanner::is_closed(const WorldState& ws)
{
    return std::find_if(closed.begin(), closed.end(), [&](const ANode* n)
    {
        return n->ws == ws;
    }) != closed.end();
}
std::list<ANode*>::iterator GoapPlanner::is_open(const WorldState& ws)
{
    return std::find_if(open.begin(), open.end(), [&](const ANode* n)
    {
        return n->ws == ws;
    });
}

std::list<Action*> GoapPlanner::plan(GoapAgent *agent, WorldState goal)
{
    WorldState &start = agent->get_world_state();

    //printf("planner running for \n\tstart: %s\n\tgoal: %s\n", start.repr().c_str(), goal.repr().c_str());

    open = std::list<ANode*>();
    closed.clear();
    nodes.clear();

    nodes.push_back(ANode(start, 0, start.distanceTo(goal), nullptr, nullptr));
    //open.insert({"no_action", ANode(start, 0, start.distanceTo(goal), nullptr, nullptr)});
//    open.insert(nodes.front());
    add_to_open(&nodes.back());

    while(!open.empty())
    {
        ANode* current = pop_and_close();
        //printf("CURRENT_WORLD_STATE: %s\n", current->ws.repr().c_str());
        //std::min_element(open.begin(), open.end(), compNodes); /// biorę ten z najmniejszym f()

        if(current->ws.fulfills(goal)) /// jeśli dotarł do końca
        {
            //return action_queue(start, goal);
            list<Action*> prepared_plan;
            while(current->parent != nullptr)
            {
                prepared_plan.push_back(current->action);
                current = current->parent;
            }
            prepared_plan.reverse();
            printf("plan found\n");
//            if(prepared_plan.empty())
//                printf("PLAN is EMPTY\n");
//            else printf("PLAN FOUND\n");
            return prepared_plan;
        }
        //printf("CHECKING AVAILABLE ACTIONS\n");
        for(auto& p : agent->get_actions())
        {
            Action& potential_action = p.second;

            if(potential_action.is_doable(current->ws))
            {
                WorldState outcome = potential_action.act_on(current->ws);
                //printf("  outcome: %s\n", outcome.repr().c_str());
                if(is_closed(outcome))
                {
                    //printf("-already closed\n");
                    continue;
                }

                auto p_outcome_node = is_open(outcome);
                if(p_outcome_node == open.end())
                {
                    //printf("-adding node\n");
                    nodes.push_back(ANode(outcome, current->g + potential_action.get_cost(), outcome.distanceTo(goal), current, &potential_action));
                    //printf("-result: %s\n", nodes.back().ws.repr().c_str());
                    add_to_open(&nodes.back());
                    //printf("-just checking: %s\n", open.front()->ws.repr().c_str());
                }
                else
                {
                    //printf("-already opened\n");
                    if(current->g + potential_action.get_cost() < (*p_outcome_node)->g)
                    {
                        //printf("\tbetter\n");
                        (*p_outcome_node)->parent = current;
                        (*p_outcome_node)->g = current->g + potential_action.get_cost();
                        (*p_outcome_node)->h = outcome.distanceTo(goal);
                        (*p_outcome_node)->action = &potential_action;

                        open.sort();
                    }
                }
            }
        }
        //printf("CHECK FINISHED\n");
    }
    printf("could not find a plan\n\n");
    return list<Action*>();
    //throw std::runtime_error("A* planner could not find a path from start to goal");
}

