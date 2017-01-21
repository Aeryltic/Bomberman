#include "InputManager.h"

InputManager::InputManager()
{
    //ctor
}

InputManager::~InputManager()
{
    //dtor
}
void InputManager::update()
{
/** PROPER MOVEMENT EXAMPLE

    int alien_x=0, alien_y=0;
    int alien_xvel=0, alien_yvel=0;

    while( SDL_PollEvent( &event ) ){
        switch( event.type ){

            case SDL_KEYDOWN:

                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        alien_xvel = -1;
                        break;
                    case SDLK_RIGHT:
                        alien_xvel =  1;
                        break;
                    case SDLK_UP:
                        alien_yvel = -1;
                        break;
                    case SDLK_DOWN:
                        alien_yvel =  1;
                        break;
                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:

                        if( alien_xvel < 0 )
                            alien_xvel = 0;
                        break;
                    case SDLK_RIGHT:
                        if( alien_xvel > 0 )
                            alien_xvel = 0;
                        break;
                    case SDLK_UP:
                        if( alien_yvel < 0 )
                            alien_yvel = 0;
                        break;
                    case SDLK_DOWN:
                        if( alien_yvel > 0 )
                            alien_yvel = 0;
                        break;
                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }

    alien_x += alien_xvel;
    alien_y += alien_yvel;

    */
}
