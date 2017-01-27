#ifndef LIVINGOBJECT_H
#define LIVINGOBJECT_H

#include <RealObject.h>

/// to chyba nie powinno istniec, sam nie wiem, wszystkie te rzeczy powinny byc cechami instancji a nie baz
class LivingObject : public RealObject
{
    public:
        LivingObject();
        virtual ~LivingObject();
        void die();
        ObjectType type() { return OBJECT_LIVING; }
        void setController(Controller *controller) {_controller = controller;}
    protected:

    private:
        char _direction;
        Controller *_controller;
};

#endif // LIVINGOBJECT_H
