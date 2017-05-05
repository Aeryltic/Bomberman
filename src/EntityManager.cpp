#include "EntityManager.h"

#include "Entity.h"
#include "GraphicsManager.h"
#include "GameInstance.h"
#include "DisplayManager.h"

EntityManager::EntityManager(GameInstance *gameInstance)
                            : objectFactory(this, gameInstance->getDisplayManager()->getGraphicsManager())
{
    printf("new EntityManager\n");
    if(objectFactory.isActive()) active = true;
    else active = false;

    nextID = 0;
}

EntityManager::~EntityManager()
{
    printf("delete EntityManager\n");
}

void EntityManager::update(int ms)
{
    for (auto it = entities.begin(); it != entities.end(); )
    {
        if (!it->second->isActive()) entities.erase(it++);
        else ++it;
    }

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
        entities[id]->deactivate();
    }
}
