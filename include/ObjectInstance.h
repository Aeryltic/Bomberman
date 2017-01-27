#ifndef OBJECTINSTANCE_H
#define OBJECTINSTANCE_H

#include "Object.h"

class ObjectInstance
{
    public:
        ObjectInstance(const Object &base, int x, int y);
        virtual ~ObjectInstance();
        virtual void update(int time_passed);
        virtual void update_position(int time_passed);
        double posX();
        double posY();
    protected:
        const Object &_base;
        ObjectInstance *_parent;    /* jesli _parent != nullptr pozycja jest wzgledem niego, moze i inne pierdoly*/
                                    /* jakis mechanizm zeby sie wzajemnie nie oparentowali */

    private:

        // Controller *_controller; // do kontroli, ale w jakim zakresie?
};

#endif // OBJECTINSTANCE_H
