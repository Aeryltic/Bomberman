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

void LogicManager::update(EntityManager *entityManager, ObjectFactory *objectFactory, int ms_passed)
{
    /*
    if(!entityManager->getPlayer())
    {
        SDL_Event pushed;
        pushed.type = SDL_QUIT;
        SDL_PushEvent(&pushed);
        printf("PLAYER DEAD\n");
    }
    */
    entityManager->update(ms_passed);
    _controlSystem.update(entityManager, objectFactory, ms_passed);
}
