#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include "Structures.h"
using namespace std;
class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        void update(StatusFlags &buttonStatus);
    protected:

    private:
        SDL_Event _event;
};

#endif // INPUTMANAGER_H
