#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include <Object.h>


class AbstractObject : public Object
{
    public:
        AbstractObject();
        virtual ~AbstractObject();
        ObjectType type() { return OBJECT_ABSTRACT; }
    protected:

    private:
};

#endif // ABSTRACTOBJECT_H
