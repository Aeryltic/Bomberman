#ifndef ANODE_H
#define ANODE_H

#include "WorldState.h"
class Action;
struct ANode {
    static int next_id;

    ANode(const WorldState& world_state, int g, int h, ANode *parent, Action *action);
    virtual ~ANode();

    int f() const {
        return g + h;
    }

    bool operator<(const ANode& other) {
        return f() < other.f();
    }

    WorldState ws;
    int g, h;
    ANode *parent;
    Action *action;
};

#endif // ANODE_H
