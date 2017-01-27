#ifndef OBJECTINSTANCECONTAINER_H
#define OBJECTINSTANCECONTAINER_H

#include "ObjectInstance.h"
#include "ObjectContainer.h"
#include <unordered_map>
using namespace std;

class ObjectInstanceContainer
{
    public:
        ObjectInstanceContainer(ObjectContainer &objContainer);
        virtual ~ObjectInstanceContainer();
        bool createInstance(string type, int x, int y);
    protected:

    private:
        /*deque<ObjectInstance> _instance;*/
        ObjectContainer &_objContainer;
        unordered_map<int,ObjectInstance> _ins; /* Ref ID, instance */
};

#endif // OBJECTINSTANCECONTAINER_H
