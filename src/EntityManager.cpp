#include "EntityManager.h"

#include "Entity.h"

EntityManager::EntityManager()
{
    printf("new EntityManager\n");
    active = true;
    nextID = 0;
}

EntityManager::~EntityManager()
{
    printf("delete EntityManager\n");
}

void EntityManager::update(int ms)
{
    while(!toRemove.empty())
    {
        int id = toRemove.front();
        toRemove.pop();

        auto it = entities.find(id);
        if(it != entities.end()) entities.erase(it);
    }
    while(!toAdd.empty())
    {
        auto entity = toAdd.front();
        toAdd.pop();

        entity->setID(nextID);
        entities.insert({nextID++, entity});
    }
}

void EntityManager::removeRequest(int id)
{
    if(exists(id))
    {
        printf("to remove %d\n",id);
        toRemove.push(id);
//        entities[id]->deactivate();
    }
}

shared_ptr<Entity> EntityManager::make_entity()
{
    shared_ptr<Entity> e = make_shared<Entity>();
    entities[nextID++] = e;
    return e;
}

shared_ptr<Entity> EntityManager::make_object(string type, double x, double y)
{
    return factory.newObject(type, x, y, this);
}
