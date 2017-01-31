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
/*
void EventManager::pushEvent(int eventNum, int eventCode, shared_ptr<Entity> publisher, shared_ptr<Entity> subscriber)
{
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));
    event.type = eventBeginningNum + eventNum;
    event.user.code = eventCode;
    event.user.data1 = publisher.get();
    event.user.data2 = subscriber.get();
    SDL_PushEvent(&event);
}
*/
