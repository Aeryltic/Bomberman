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
        SDL_Texture *texture() { return _tex; }
        int width() const {return _w;}
        int height()const {return _h;}
    protected:
        bool _static;
        bool _solid;
        SDL_Texture* _tex;
        int _w, _h, _z;
    private:

};

#endif // REALOBJECT_H
