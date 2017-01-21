#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include <Object.h>


class AbstractObject : public Object
{
    public:
        AbstractObject();
        virtual ~AbstractObject();
        void update(int time_passed);
    protected:

    private:
};

#endif // ABSTRACTOBJECT_H
