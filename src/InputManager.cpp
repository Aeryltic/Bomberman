#include "InputManager.h"
#include <cstdio>
InputManager::InputManager()
{
    printf("new InputManager\n");
}

InputManager::~InputManager()
{
    printf("delete InputManager\n");
}
void InputManager::update()
{
    SDL_Event _event; /// powinien miec swoja osobna kolejke tylko z akcjami klawiatury i myszki
    for(auto &key : _key)
    {
        if(key.second == KEY_PRESSED) key.second = KEY_DOWN;//, printf("down: %s\n",SDL_GetKeyName(key.first));
        else if(key.second == KEY_RELEASED) key.second = KEY_UP;//, printf("up: %s\n",SDL_GetKeyName(key.first));
    }
    while(SDL_PollEvent(&_event))
    {
        switch(_event.type)
        {
            case SDL_KEYDOWN:
            {
                if(_key[_event.key.keysym.sym] != KEY_DOWN)
                {
                    _key[_event.key.keysym.sym] = KEY_PRESSED;
                    printf("pressed: %s\n",SDL_GetKeyName(_event.key.keysym.sym));
                }
                break;
            }
            case SDL_KEYUP:
            {
                if(_key[_event.key.keysym.sym] != KEY_UP) // even tho it's practically impossible
                {
                    _key[_event.key.keysym.sym] = KEY_RELEASED;
              //      printf("released: %s\n",SDL_GetKeyName(_event.key.keysym.sym));
                }
                break;
            }
        }
    }
}

KeyStatus InputManager::keyStatus(SDL_Keycode keycode)
{
    return _key[keycode];
}
