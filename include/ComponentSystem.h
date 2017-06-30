#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H

#include <functional>
#include <vector>
#include <stdio.h>
using namespace std;

class EntityManager;

class ComponentSystem {
    using update_function = function<void(int, EntityManager*)>;
public:
    ComponentSystem() {}
    virtual ~ComponentSystem() {}
    void update(int timestep, EntityManager *entityManager);
    void addUpdateFunction(int priority, update_function ufunction);
    bool init();
protected:
private:
    vector<pair<int, update_function>> ufunctions;
};
#endif // COMPONENTSYSTEM_H
