#include "Components.h"

unordered_map<string, vector<weak_ptr<Entity>>> CActionTarget::targets;

std::weak_ptr<Entity> CActionTarget::closest_target(std::string target_name, Entity* entity) {
    std::weak_ptr<Entity> closest;
    double dist = 0;
    auto opf = entity->get<CTransform>();
    if(opf) {
        for(auto target: targets[target_name]) {
            if(!target.expired()) {
                auto pf = target.lock()->get<CTransform>();
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
