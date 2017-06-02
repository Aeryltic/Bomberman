#include "Entity.h"

#include "Component.h"
#include "EntityManager.h"

EntityManager* Entity::entityManager = nullptr;

Entity::Entity() { }

Entity::~Entity() { }

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
    printf("can't add component (already exists)\n"); /// lepsza ta wiadomosc mogla byc
    return false;
}

void Entity::receive_message(Message message) {
    for(auto &callback : callbacks[message.type]) {
        callback(message); /// tu raczej zapisanie wiadomości w kolejce, obsługa osobno: void process_messages();
    }
}

void Entity::register_listener(unsigned message_type, message_callback callback) {
    callbacks[message_type].push_back(callback);
}

void Entity::destroy_me() {
    printf("destroy me: %d\n", id);
    components = component_map();
    entityManager->request_entity_removal(id);
}

void Entity::set_manager(EntityManager *manager) {
    entityManager = manager;
}
