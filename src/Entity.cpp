#include "Entity.h"

Entity::Entity() /// zmienic obsluge zeby moglobyc false
{
    _active = true;
}

Entity::~Entity()
{
    for(auto &component : _component)
    {
        delete component.second;
    }
    //printf("DELETING ENTITY #%d\n",_id);
}

inline bool Entity::hasComponent(int key) const
{
    return _component.find(key) != _component.end();
}

bool Entity::addComponent(Component *component)
{
    //int key = typeid(*component).hash_code();
    int key = typeid(*component).hash_code();
    if(!hasComponent(key))
    {
        _component.insert(make_pair(key,component));
        component->setTarget(shared_from_this());
        return 1;
    }
    printf("can't add component (already exists)\n"); /// lepsza ta wiadomosc mogla byc
    return 0;
}

void Entity::update(int ms)
{
    for(auto &component : _component)
    {
        component.second->update(ms);
    }
}

void Entity::activate()
{
    //printf("Entity::activate()\n");
    for(auto &component : _component)
    {
 //       component.second->setTarget(shared_from_this());
        component.second->setActive();
    }

}
