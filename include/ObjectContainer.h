#ifndef OBJECTCONTAINER_H
#define OBJECTCONTAINER_H

#include <unordered_map>
#include "Object.h"
using namespace std;
class ObjectContainer
{
    typedef unordered_map<unsigned,Object>::iterator ObjIterator;
    public:
        ObjectContainer();
        virtual ~ObjectContainer();
        const unordered_map<unsigned,Object> &obj() const{return _obj;}
        const Object &getPlayer();
    protected:

    private:
      //  deque<Object> _obj;
      unordered_map<unsigned,Object> _obj; /* Base ID, instance */
};

#endif // OBJECTCONTAINER_H
