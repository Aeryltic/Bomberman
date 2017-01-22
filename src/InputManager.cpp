#include "InputManager.h"
#include <cstdio>
InputManager::InputManager()
{
    //SDL_Ena
}

InputManager::~InputManager()
{
    //dtor
}
void InputManager::update(StatusFlags &buttonStatus)
{
    while(SDL_PollEvent(&_event))
    {
        switch(_event.type)
        {
            case SDL_KEYDOWN:
            {
                _key[_event.key.keysym.sym] = KEY_PRESSED;
                printf("pressed: %s\n",SDL_GetKeyName(_event.key.keysym.sym));
                break;
            }
            case SDL_KEYUP:
            {
                _key[_event.key.keysym.sym] = KEY_RELEASED;
                printf("released: %s\n",SDL_GetKeyName(_event.key.keysym.sym));
                break;
            }
        }
        /* // obsolete
        switch(_event.type)
        {
            case SDL_KEYDOWN:
            {
                switch(_event.key.keysym.sym)
                {

                    case SDLK_LEFT:
                        buttonStatus._left = 1;
                        break;
                    case SDLK_RIGHT:
                        buttonStatus._right = 1;
                        break;
                    case SDLK_UP:
                        buttonStatus._up = 1;
                        break;
                    case SDLK_DOWN:
                        buttonStatus._down = 1;
                        break;
                    case SDLK_ESCAPE:
                        buttonStatus._escape = 1;
                        break;
                    default:
                        break;
                }
            }
            case SDL_KEYUP:
            {
                switch(_event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        buttonStatus._left = 0;
                        break;
                    case SDLK_RIGHT:
                        buttonStatus._right = 0;
                        break;
                    case SDLK_UP:
                        buttonStatus._up = 0;
                        break;
                    case SDLK_DOWN:
                        buttonStatus._down = 0;
                        break;
                    case SDLK_ESCAPE:
                        buttonStatus._escape = 0;
                        break;
                    default:
                        break;
                }
            }
        }
        */
    }
}

KeyStatus InputManager::keyStatus(SDL_Keycode keycode)
{
    return _key[keycode];
}
