#include "Entity.h"

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    for(auto &component : _component)
    {
        delete component.second;
    }
}

template<class C>
bool Entity::hasComponent() const
{
    int key = typeid(C).hash_code();
    return _component.find(key) != _component.end();
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
        return 1;
    }
    printf("can't add component (already exists)\n"); /** lepsza ta wiadomosc mogla byc */
    return 0;
}

void Entity::update(int ms)
{
    for(auto &component : _component)
    {
        component.second->update(ms);
    }
}

void Entity::setAsTarget()
{
    for(auto &component : _component)
    {
        component.second->setTarget(shared_from_this());
    }
}
