#ifndef LOGICMANAGER_H
#define LOGICMANAGER_H

//#include "ObjectContainer.h"
//#include "Structures.h"
#include "EntityManager.h"
#include "ControllingSystem.h"
#include "ObjectFactory.h"
#include "ScriptSystem.h"
class LogicManager
{
    public:
        LogicManager(GameInstance *gameInstance);
        virtual ~LogicManager();
        void update(int ms_passed);

        bool isActive(){if(!active)printf("LogicManager is not active\n");return active;}
    protected:

    private:
        bool active;
        ControllingSystem *controlSystem;
        EntityManager *entityManager;

        GameInstance *gameInstance;
};

#endif // LOGICMANAGER_H
