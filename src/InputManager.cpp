#include "InputManager.h"

InputManager::InputManager()
{
    //SDL_EnableUNICODE(1);
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
}
