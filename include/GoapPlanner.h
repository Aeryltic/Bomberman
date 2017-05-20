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

    void addToOpenList(ANode *node);
    ANode* popAndClose();

    bool memberOfClosed(const WorldState& ws);
    std::list<ANode*>::iterator memberOfOpen(const WorldState& ws);
};

#endif // GOAPPLANNER_H
