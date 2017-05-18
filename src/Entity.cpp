#include "Entity.h"

#include "Component.h"

Entity::Entity()
{
//    _active = true;
}

Entity::~Entity()
{

}

inline bool Entity::has(type_index key) const
{
    return components.find(key) != components.end();
}

bool Entity::add(shared_ptr<Component> component)
{
    type_index key = tindex(*component.get());
    if(!has(key))
    {
        components.insert(make_pair(key,component));
        component->owner = shared_from_this();
        return true;
    }
    printf("can't add component (already exists)\n"); /// lepsza ta wiadomosc mogla byc
    return false;
}

void Entity::receive_message(Message message)
{
    for(auto &callback : callbacks[message.type])
    {
        callback(message);
    }
}

void Entity::register_listener(unsigned message_type, message_callback callback)
{
    callbacks[message_type].push_back(callback);
}
