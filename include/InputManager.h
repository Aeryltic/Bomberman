#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include "Structures.h"
#include "Enumerations.h"
#include "Constants.h"
#include <unordered_map>

using namespace std;

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        void update();
        KeyStatus keyStatus(SDL_Keycode keycode);
    protected:

    private:
        //SDL_Event _event;
        unordered_map <SDL_Keycode,KeyStatus> _key;
};

#endif // INPUTMANAGER_H
