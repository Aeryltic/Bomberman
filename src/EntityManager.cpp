#include "EntityManager.h"

#include "Entity.h"
#include "Component.h"

EntityManager::EntityManager() : factory(this) {
    printf("new EntityManager\n");
    Entity::set_manager(this);
    Component::set_manager(this);
    active = true;
//    next_eid = 0;
//    next_cid = 0;
}

EntityManager::~EntityManager() {
    printf("delete EntityManager\n");
}

void EntityManager::update() {
    while(!entities_to_remove.empty()) {
        int id = entities_to_remove.front();
        entities_to_remove.pop();
        auto it = entities.find(id);
        if(it != entities.end())
            entities.erase(it);
    }
    while(!components_to_remove.empty()) {
        type_index t_index = components_to_remove.front().first;
        int id = components_to_remove.front().second;
        components_to_remove.pop();
        auto it = components[t_index].find(id);
        if(it != components[t_index].end())
            components[t_index].erase(it);
    }
}

void EntityManager::request_entity_removal(int id) {
    entities_to_remove.push(id);
}

void EntityManager::request_component_removal(type_index t_index, int id) { /// ta funkcja nie działa wywoływana ze środka ~Component destruktora
    components_to_remove.push(make_pair(t_index, id));
}

shared_ptr<Entity> EntityManager::make_entity() {
    shared_ptr<Entity> e = make_shared<Entity>();
    entities[e->get_id()] = e;
    return e;
}

shared_ptr<Entity> EntityManager::new_object(std::string type, double x, double y) {
    return factory.make_object(type, x, y);
}

void EntityManager::make_object(std::string type, double x, double y)
{
    new_object(type, x, y);
}

inline bool EntityManager::exists(int id) {
    return entities.find(id) != entities.end();
}

void EntityManager::delete_component(type_index t_index, int id) {
    auto it = components[t_index].find(id);
    if(it != components[t_index].end())
        components[t_index].erase(id);
}


