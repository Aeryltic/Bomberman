#ifndef GOAPPLANNER_H
#define GOAPPLANNER_H

#include <deque>
#include <list>

class ANode;
class Action;
class GoapAgent;
class WorldState;

class GoapPlanner
{
public:
    GoapPlanner();
    virtual ~GoapPlanner();
    std::list<Action*> plan(GoapAgent *agent, WorldState goal);

protected:

private:
    std::deque<ANode> nodes;

    std::deque<ANode*> closed;
    std::list<ANode*> open;

    void add_to_open(ANode *node);
    ANode* pop_and_close();

    bool is_closed(const WorldState& ws);
    std::list<ANode*>::iterator is_open(const WorldState& ws);
};

#endif // GOAPPLANNER_H
