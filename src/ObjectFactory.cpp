#include "ObjectFactory.h"
#include <fstream>
#include "Constants.h"
#include "Entity.h"
#include "EntityManager.h"
ObjectFactory::ObjectFactory(EntityManager *entityManager, GraphicsManager *graphicsManager) :
                _entityManager(entityManager), _graphicsManager(graphicsManager)
{
    if(_graphicsManager->isActive()) _active = true;
    else _active = false;
}
ObjectFactory::~ObjectFactory()
{
    printf("delete ObjectFactory\n");
}

entity_ptr ObjectFactory::createDefault()
{
    entity_ptr def = make_shared<Entity>();
    _entityManager->addRequest(def);
    return def;
}

inline bool ObjectFactory::addTo(shared_ptr<Component> component, shared_ptr<Entity> entity)
{
    if(entity->add(component))
    {
        _entityManager->add(weak_ptr<Component>(component));
        return true;
    }
    return false;
}

