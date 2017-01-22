#ifndef OBJECTINSTANCECONTAINER_H
#define OBJECTINSTANCECONTAINER_H

#include "ObjectInstance.h"
#include <unordered_map>
using namespace std;

class ObjectInstanceContainer
{
    public:
        ObjectInstanceContainer();
        virtual ~ObjectInstanceContainer();

    protected:

    private:
        /*deque<ObjectInstance> _instance;*/
        unordered_map<int,ObjectInstance> _ins; /* Ref ID, instance */
};

#endif // OBJECTINSTANCECONTAINER_H
