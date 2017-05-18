#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

class Entity;

struct Component
{
    Component(std::weak_ptr<Entity> owner)
    {
        this->owner = owner;
    }
    virtual ~Component() {}

    std::weak_ptr<Entity> owner;
};

#endif // COMPONENT_H
