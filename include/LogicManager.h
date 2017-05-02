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
        LogicManager(EntityManager *entityManager);
        virtual ~LogicManager();
        void update(int ms_passed);

        bool isActive(){if(!_active)printf("LogicManager is not active\n");return _active;}
    protected:

    private:
        bool _active;
        ControllingSystem *_controlSystem;
        EntityManager *_entityManager;
};

#endif // LOGICMANAGER_H
