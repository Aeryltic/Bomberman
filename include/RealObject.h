#ifndef REALOBJECT_H
#define REALOBJECT_H

#include <Object.h>


class RealObject : public Object
{
    public:
        RealObject();
        virtual ~RealObject();
    protected:

    private:
        bool _static;
        bool _solid;
};

#endif // REALOBJECT_H
