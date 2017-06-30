#include "ANode.h"

ANode::ANode(const WorldState& world_state, int g, int h, ANode *parent, Action *action)
    : ws(world_state), g(g), h(h), parent(parent), action(action) {
    //ctor
}

ANode::~ANode() {
    //dtor
}
