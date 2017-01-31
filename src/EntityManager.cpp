#include "EntityManager.h"

#include "Entity.h"
#include "GraphicsManager.h"

EntityManager::EntityManager()
{
    printf("new EntityManager\n");
    _nextID = 0;
}

EntityManager::~EntityManager()
{
    printf("delete EntityManager\n");
}

entity_ptr EntityManager::getWorld()
{
    if(!_world.lock())
    {
        for(auto w : _entity)
        {
            if(w->hasComponent<World>())
            {
                _world = w;
                break;
            }
        }
    }
    return _world.lock();
}

entity_ptr EntityManager::getPlayer()
{
    if(!_player.lock())
    {
        for(auto p : _entity)
        {
            if(p->hasComponent<PlayerControllerComponent_v2>())
            {
                _player = p;
                break;
            }
        }
    }
    return _player.lock();
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
    while(!_toRemove.empty())
    {
        removeEntity(_toRemove.top());
        _toRemove.pop();
    }
    while(!_toAdd.empty())
    {
        addEntity(_toAdd.top());
        _toAdd.pop();
    }
}

void EntityManager::removeEntity(int id)
{
    for(unsigned i=0; i<_entity.size(); i++)
    {
        if(_entity[i]->getID() == id)
        {
            printf("removing entity #%d\n",_entity[i]->getID());
            _entity.erase(_entity.begin()+i);
            printf("ok\n");
            break;
        }
    }
}

void EntityManager::removeEntity(entity_ptr entity)
{
    for(unsigned i=0; i<_entity.size(); i++)
    {
        if(_entity[i] == entity)
        {
            printf("removing entity #%d\n",_entity[i]->getID());
            _entity.erase(_entity.begin()+i);
            printf("ok\n");
            break;
        }
    }
}
