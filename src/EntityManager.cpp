#include "EntityManager.h"

#include "Entity.h"
#include "GraphicsManager.h"

EntityManager::EntityManager(GraphicsManager *graphicsManager, InputManager *inputManager)
                            : _objectFactory(this, graphicsManager, inputManager)
{
    printf("new EntityManager\n");
    if(_objectFactory.isActive()) _active = true;
    else _active = false;

    _nextID = 0;
}

EntityManager::~EntityManager()
{
    printf("delete EntityManager\n");
}

void EntityManager::update(int ms)
{
 //   printf("updating: %llu\n", _entity.size());
 /*
    for(auto &entity : _entity)
    {
        entity->update(ms);
    }
    */

    for (auto it = _entity.begin(); it != _entity.end(); )
    {
        if (!it->second->isActive()) _entity.erase(it++);
        else ++it;
    }

    /*
    for(auto entity_m : _entity)
    {
        entity_ptr entity = entity_m.second;
        if(!entity->isActive())
        {
            printf("%d is inactive -> to remove\n",entity->getID());
            removeRequest(entity->getID());
        }
    }
    */
    /*
    while(!_toRemove.empty())
    {
        removeEntity(_toRemove.front());
        _toRemove.pop();
    }
*/
    while(!_toAdd.empty())
    {
        addEntity(_toAdd.front());
        _toAdd.pop();
    }

}
/// dlaczego to usuwanie nie dziala?
/*
void EntityManager::removeEntity(int id)
{
    auto it = _entity.find(id);
    if(it != _entity.end()) _entity.erase(it);
}

void EntityManager::removeEntity(entity_ptr entity)
{
    removeEntity(entity->getID());
}
*/
