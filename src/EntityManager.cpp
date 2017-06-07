#include "EntityManager.h"

#include "Entity.h"
#include "Component.h"


#include "GoapAgent.h"

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
        //printf("deleting %d\n", id);
        auto it = entities.find(id);
        if(it != entities.end())
            entities.erase(it);
        //else printf("%d juz zostal usuniety!\n", id);
    }
    while(!components_to_remove.empty()) {
        type_index t_index = components_to_remove.front().first;
        int id = components_to_remove.front().second;
        components_to_remove.pop();
        //printf("deleting %d\n", id);
        auto it = components[t_index].find(id);
        if(it != components[t_index].end())
            components[t_index].erase(it);
        //else printf("%d juz zostal usuniety!\n", id);
    }
}

void EntityManager::request_entity_removal(int id) {
//    printf("request_entity_removal: ");
//    auto it = entities.find(id);
//    if(it != entities.end()) {
//        printf("remove %d...",id);
    entities_to_remove.push(id);
//    }
//    printf("ok\n");
}

void EntityManager::request_component_removal(type_index t_index, int id) { /// ta funkcja nie działa wywoływana ze środka ~Component destruktora
    //if(t_index == tindex(Component))printf("type index error while requesting component removal!\n");
    //if(t_index == tindex(GoapAgent))printf("GoapAgent removal!\n");
    components_to_remove.push(make_pair(t_index, id));
}

shared_ptr<Entity> EntityManager::make_entity() {
    shared_ptr<Entity> e = make_shared<Entity>();
//    int id = getNextEID();
    entities[e->get_id()] = e;
    //e->set_id(id);
    return e;
}

shared_ptr<Entity> EntityManager::make_object(unsigned type, double x, double y) {
    return factory.make_object(type, x, y);
}

inline bool EntityManager::exists(int id) {
    return entities.find(id) != entities.end();
}

void EntityManager::delete_component(type_index t_index, int id) {
    //if(components.find(t_index) == components.end())printf("usuwanie komponentow nie dziala!!!!!\n");
    auto it = components[t_index].find(id);
    if(it != components[t_index].end())
        components[t_index].erase(id);
}


