#ifndef LOGICMANAGER_H
#define LOGICMANAGER_H

#include "ObjectContainer.h"
#include "Structures.h"
class LogicManager
{
    public:
        LogicManager();
        virtual ~LogicManager();
        void update(ObjectContainer &object, StatusFlags &buttonStatus, int time_passed);
    protected:

    private:
};

#endif // LOGICMANAGER_H
