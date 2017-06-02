#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

class Entity;
class EntityManager;

struct Component {
    std::weak_ptr<Entity> owner;

    Component() {}
    virtual ~Component();

    virtual void set_owner(std::weak_ptr<Entity> owner) {
        this->owner = owner;
    }
    void set_id(int id) {this->id = id;}

    static void set_manager(EntityManager* entity_manager);
private:
    int id;
    static EntityManager* entity_manager;
};

#endif // COMPONENT_H
