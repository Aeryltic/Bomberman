#include "EventManager.h"

#include "GameInstance.h"

EventManager::~EventManager()
{
    //dtor
}

void EventManager::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
            {
                SDL_Keycode keycode = event.key.keysym.sym;
                _inputManager->setKeyStatus(keycode,KEY_PRESSED);

                if(keycode == SDLK_ESCAPE)
                {
                    SDL_Event pushed;
                    pushed.type = SDL_QUIT;
                    SDL_PushEvent(&pushed);
                }
                break;
            }
            case SDL_KEYUP:
            {
                SDL_Keycode keycode = event.key.keysym.sym;
                _inputManager->setKeyStatus(keycode,KEY_RELEASED);

                break;
            }
            case SDL_QUIT:
            {
                GameInstance::getInstance().quit();
                break;
            }
        }
    }

}
