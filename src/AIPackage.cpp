#include "AIPackage.h"

#include <algorithm>

AIPackage::AIPackage(std::string name) : name(name) {
    //ctor
}

AIPackage::~AIPackage() {
    //dtor
}

void AIPackage::add_action(std::string action) {
    printf("ai_pack: '%s' - adding action: '%s'\n", name.c_str(), action.c_str());
    actions.push_back(action);
}

void AIPackage::add_goal(std::string goal_name, bool state, int priority) {
    printf("ai_pack: '%s' - adding goal: '%s'\n", name.c_str(), goal_name.c_str());
    auto p = make_pair(priority, make_pair(goal_name, state));
    auto it = std::lower_bound(goals.begin(), goals.end(), p, [](AIPackage::Goal a, AIPackage::Goal b) -> bool{return a.first < b.first;});
    goals.emplace(it, p);
}
