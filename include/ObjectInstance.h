#ifndef OBJECTINSTANCE_H
#define OBJECTINSTANCE_H

#include "Object.h"

class ObjectInstance
{
    public:
        ObjectInstance(const Object &base);
        virtual ~ObjectInstance();
        virtual void update(int time_passed);
        virtual void update_position(int time_passed);
        double posX();
        double posY();
    protected:

    private:
        const Object &_base;
        ObjectInstance *_parent;    /* jesli _parent != nullptr pozycja jest wzgledem niego moze i inne pierdoly*/
                                    /* jakis mechanizm zeby sie wzajemnie nie oparentowali */
        double _posX, _posY, _vX, _vY; /* trzeba to przerobic na jakies wektorki zeby bylo ladnie */
                                    /* _vX/_vY w pikselach na sekunde */
};

#endif // OBJECTINSTANCE_H
