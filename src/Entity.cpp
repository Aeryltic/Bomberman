#include "Entity.h"


Entity::Entity()
{
    _active = true;
}

Entity::~Entity()
{

}

inline bool Entity::has(type_index key) const
{
    return _component.find(key) != _component.end();
}

bool Entity::add(shared_ptr<Component> component)
{
    type_index key = tindex(component.get());
    if(!has(key))
    {
        _component.insert(make_pair(key,component));
        component->setTarget(shared_from_this());
        return true;
    }
    printf("can't add component (already exists)\n"); /// lepsza ta wiadomosc mogla byc
    return false;
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
    for(auto &component : _component)
    {
        component.second->setActive();
    }
    _active = true;
}
