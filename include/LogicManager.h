#ifndef LOGICMANAGER_H
#define LOGICMANAGER_H

#include "ObjectContainer.h"

class LogicManager
{
    public:
        LogicManager();
        virtual ~LogicManager();
        void update(ObjectContainer &object, int time_passed);
    protected:

    private:
};

#endif // LOGICMANAGER_H
