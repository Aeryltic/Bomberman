#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

class Entity;
class EntityManager;

struct Component {
    Component();
    virtual ~Component();

    int get_id() { return id; }

    std::weak_ptr<Entity> get_owner(){return owner;}
    virtual void set_owner(std::weak_ptr<Entity> owner);

    static void set_manager(EntityManager* entity_manager);

protected:
    int id;
    std::weak_ptr<Entity> owner;

private:
    static EntityManager* entity_manager;
    static int nextID;
};

#endif // COMPONENT_H
