#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include "Object.h"
using namespace std;
class Object;
class Controller
{
    public:
        Controller();
        virtual ~Controller();
        virtual void control(Object *target) {}
    protected:

    private:
};

#endif // CONTROLLER_H
