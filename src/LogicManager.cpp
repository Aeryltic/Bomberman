#include "LogicManager.h"

LogicManager::LogicManager()
{
    //ctor
}

LogicManager::~LogicManager()
{
    //dtor
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

void LogicManager::update(shared_ptr<EntityManager> &entityManager, int ms_passed)
{
    entityManager->update(ms_passed);
}
