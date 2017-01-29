#include "LogicManager.h"

LogicManager::LogicManager()
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

void LogicManager::update(EntityManager *entityManager, int ms_passed)
{
    entityManager->update(ms_passed);
}
