#ifndef OBJECTCONTAINER_H
#define OBJECTCONTAINER_H

#include <deque>
#include "Object.h"
using namespace std;
class ObjectContainer
{
    public:
        ObjectContainer();
        virtual ~ObjectContainer();
        deque<Object> &obj(){return _obj;}
    protected:

    private:
        deque<Object> _obj;
};

#endif // OBJECTCONTAINER_H
