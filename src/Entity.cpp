#include "Entity.h"


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
