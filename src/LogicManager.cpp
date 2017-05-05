#include "LogicManager.h"

#include "GameInstance.h"

LogicManager::LogicManager(GameInstance *gameInstance)
{
    printf("new LogicManager\n");

    entityManager = gameInstance->getEntityManager();

    controlSystem = new ControllingSystem(entityManager);
    active = controlSystem->isActive();
}

LogicManager::~LogicManager()
{
    printf("delete LogicManager\n");
    delete controlSystem;
}

void LogicManager::update(int ms_passed)
{
    entityManager->update(ms_passed);
    controlSystem->update(ms_passed);
}
