#include "LogicManager.h"

LogicManager::LogicManager()
{
    //ctor
}

LogicManager::~LogicManager()
{
    //dtor
}

void LogicManager::update(ObjectContainer &object, int time_passed)
{
    /* time_passed - milliseconds */
    for(auto obj : object.obj())
    {
      //  obj.update(time_passed);
    }
}
