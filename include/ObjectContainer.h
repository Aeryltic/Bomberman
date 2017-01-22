#ifndef OBJECTCONTAINER_H
#define OBJECTCONTAINER_H

#include <unordered_map>
#include "Object.h"
using namespace std;
class ObjectContainer
{
    public:
        ObjectContainer();
        virtual ~ObjectContainer();
        const unordered_map<unsigned,Object> &obj(){return _obj;}
    protected:

    private:
      //  deque<Object> _obj;
      unordered_map<unsigned,Object> _obj; /* Base ID, instance */
};

#endif // OBJECTCONTAINER_H
