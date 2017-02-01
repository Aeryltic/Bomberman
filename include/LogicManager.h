#ifndef LOGICMANAGER_H
#define LOGICMANAGER_H

//#include "ObjectContainer.h"
//#include "Structures.h"
#include "EntityManager.h"
#include "ControllingSystem.h"
#include "ObjectFactory.h"

class LogicManager
{
    public:
        LogicManager(ObjectFactory *objectFactory);
        virtual ~LogicManager();
        //void update(ObjectContainer &object, int time_passed);
        void update(EntityManager *entityManager, ObjectFactory *objectFactory, int ms_passed);
    protected:

    private:
        ControllingSystem _controlSystem;
};

#endif // LOGICMANAGER_H
