#include "LogicManager.h"

LogicManager::LogicManager(ObjectFactory *objectFactory) : _controlSystem(objectFactory)
{
    printf("new LogicManager\n");
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

void LogicManager::update(EntityManager *entityManager, ObjectFactory *objectFactory, int ms_passed)
{
    entityManager->update(ms_passed);
    _controlSystem.update(entityManager, ms_passed);
}
