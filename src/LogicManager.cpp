#include "LogicManager.h"

LogicManager::LogicManager(EntityManager *entityManager) : _controlSystem(entityManager)
{
    printf("new LogicManager\n");
    _entityManager = entityManager;
}

LogicManager::~LogicManager()
{
    printf("delete LogicManager\n");
}
/*
void LogicManager::update(ObjectContainer &object, int time_passed)
{
    for(auto obj : object.obj())
    {
      //  obj.update(time_passed);
    }
}
*/

void LogicManager::update(int ms_passed)
{
    _entityManager->update(ms_passed);
    _controlSystem.update(ms_passed);
}
