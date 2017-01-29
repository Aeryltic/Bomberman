#ifndef LOGICMANAGER_H
#define LOGICMANAGER_H

//#include "ObjectContainer.h"
//#include "Structures.h"
#include "EntityManager.h"
class LogicManager
{
    public:
        LogicManager();
        virtual ~LogicManager();
        //void update(ObjectContainer &object, int time_passed);
        void update(shared_ptr<EntityManager> &entityManager, int ms_passed);
    protected:

    private:
};

#endif // LOGICMANAGER_H
