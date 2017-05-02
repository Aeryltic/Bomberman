#include "LogicManager.h"

LogicManager::LogicManager(EntityManager *entityManager)
{
    printf("new LogicManager\n");
    _entityManager = entityManager;
    _controlSystem = new ControllingSystem(_entityManager);
    _active = _controlSystem->isActive();
}

LogicManager::~LogicManager()
{
    printf("delete LogicManager\n");
    delete _controlSystem;
}

void LogicManager::update(int ms_passed)
{
    _entityManager->update(ms_passed);
    _controlSystem->update(ms_passed);
}
