#ifndef PCCONTROLLER_H
#define PCCONTROLLER_H

#include <Controller.h>


class PCController : public Controller
{
    public:
        PCController();
        virtual ~PCController();
        void setInputManager(InputManager *manager){_manager = manager;}
        void control(Player *player);
      //  void control()
    protected:

    private:
        InputManager *iManager;
};

#endif // PCCONTROLLER_H
