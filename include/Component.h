#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

class Entity;
class EntityManager;

struct Component {
    //const int id; // może później
    Component();
    virtual ~Component();

    virtual void set_owner(std::weak_ptr<Entity> owner);
    //void set_id(int id) { this->id = id; }
    int get_id() { return id; }

    std::weak_ptr<Entity> owner;

    static void set_manager(EntityManager* entity_manager);

private:
    int id;

    static EntityManager* entity_manager;
    static int nextID;
};

#endif // COMPONENT_H
