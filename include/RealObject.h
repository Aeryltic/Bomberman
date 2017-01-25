#ifndef REALOBJECT_H
#define REALOBJECT_H

#include <Object.h>


class RealObject : public Object
{
    public:
        RealObject();
        virtual ~RealObject();
        Texture* texture();
    protected:

    private:
        bool _static;
        bool _solid;
        Texture* _tex;
};

#endif // REALOBJECT_H
