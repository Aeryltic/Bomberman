#include "Entity.h"

#include "Component.h"
#include "EntityManager.h"

#include "ScriptSystem.h"

//#include "Components.h"

EntityManager* Entity::entityManager = nullptr;
int Entity::nextID = 0;

Entity::Entity() {
    active = true; // na pewno?
    id = nextID++;
}

Entity::~Entity() {
    //printf("del %d\n", id);
    if(entityManager) {
        //printf("removing components...");
        for(auto p: components) {
            //printf("%d ", p.second->get_id());
            entityManager->request_component_removal(p.first, p.second->get_id());
        }
        //printf(" done\n");
    }
}

inline bool Entity::has(type_index key) const {
    return components.find(key) != components.end();
}

bool Entity::add(shared_ptr<Component> component) {
    type_index key = tindex(*component.get());
    if(!has(key)) {
        component->set_owner(shared_from_this());
        components.insert(make_pair(key, component));
        return true;
    }
    logs::log("can't add component (already exists)\n"); /// lepsza ta wiadomosc mogla byc
    return false;
}
/*
void Entity::receive_message(Message message) {
    for(auto &callback : callbacks[message.type]) {
        callback(message); /// tu raczej zapisanie wiadomości w kolejce, obsługa osobno: void process_messages();
    }
}

void Entity::register_listener(unsigned message_type, message_callback callback) {
    callbacks[message_type].push_back(callback);
}
*/
void Entity::destroy_me() {
    //printf("destroy me: %d\n", id);
    active = false;
    entityManager->request_entity_removal(id);
}

void Entity::set_manager(EntityManager *manager) {
    entityManager = manager;
}
/*
void Entity::setup()
{
    lua_State* L = ScriptSystem::getInstance()->getLuaState();
    getGlobalNamespace(L)
            .beginClass<Entity>("Entity")
                .addConstructor<void(*)()>()
                .addFunction("destroy_me", &Entity::destroy_me)
                .addFunction("energy_store", &Entity::get<CEnergyStore>)
            .endClass();
}
*/
