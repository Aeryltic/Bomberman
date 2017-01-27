#ifndef REALOBJECT_H
#define REALOBJECT_H

#include <Object.h>
using namespace std;
class RealObject : public Object
{
    public:
        RealObject();
        virtual ~RealObject();
        ObjectType type() { return OBJECT_REAL; }
        Texture *texture() { return _tex; }
    protected:
        bool _static;
        bool _solid;
        Texture* _tex;

    private:

};

#endif // REALOBJECT_H
