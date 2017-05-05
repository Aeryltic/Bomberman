#include "ControllingSystem.h"

#include "MiscFunctions.h"

ControllingSystem::ControllingSystem(EntityManager *entityManager)
{
    _entityManager = entityManager;
    _objectFactory = entityManager->getFactory(); // bo czesto z tego korzysta
    if(_entityManager->isActive())
    {
        _active = true;
    }
    else _active = false;
}

ControllingSystem::~ControllingSystem()
{
    //dtor
}
void ControllingSystem::update(int ms)
{

}
