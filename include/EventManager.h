#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "InputManager.h"

class EventManager
{
    public:
        EventManager(InputManager *inputManager) : _inputManager(inputManager) {}
        virtual ~EventManager();

        void update();
    protected:

    private:
        InputManager *_inputManager;
};

#endif // EVENTMANAGER_H
