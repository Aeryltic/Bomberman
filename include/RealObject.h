#ifndef REALOBJECT_H
#define REALOBJECT_H

#include <Object.h>


class RealObject : public Object
{
    public:
        RealObject();
        virtual ~RealObject();
        //void update(int time_passed);
    protected:

    private:
        bool _static;
        bool _solid;
};

#endif // REALOBJECT_H
