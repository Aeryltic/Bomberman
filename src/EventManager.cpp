#include "EventManager.h"

#include "GameInstance.h"
//#include "Component.h"

EventManager::~EventManager()
{
    //dtor
}

void EventManager::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        SDL_Event pushed;
        switch(event.type)
        {
            case SDL_KEYDOWN:
            {
                SDL_Keycode keycode = event.key.keysym.sym;
                _inputManager->setKeyStatus(keycode,KEY_PRESSED);

                if(keycode == SDLK_ESCAPE)/// bez sensu, cale powinno byc oparte na eventach, albo _inputManager powinien wysylac wlasne, tak to mija sie z celem
                {
                    SDL_Event pushed;
                    pushed.type = SDL_QUIT;
                    SDL_PushEvent(&pushed);
                }
                if(keycode == SDLK_p)
                {
                    pushUserEvent(EVENT_PAUSE,NULL,NULL);
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
            case SDL_USEREVENT:
            {
                switch (event.user.code)
                {
                    case EVENT_LOST:
                        printf("EVENT_LOST\n");
                        SDL_memset(&pushed, 0, sizeof(pushed));
                        pushed.type = SDL_QUIT;
                        SDL_PushEvent(&pushed);
                        break;
                    case EVENT_WON:
                        printf("EVENT_WON\n");
                        SDL_memset(&pushed, 0, sizeof(pushed));
                        pushed.type = SDL_QUIT;
                        SDL_PushEvent(&pushed);
                        break;
                    case EVENT_PAUSE:
                        GameInstance::getInstance().pause();
                        /*
                    case EVENT_DELETE:
                        _entityManager->removeRequest(static_cast<Entity *>(data1)->getID());
                        break;
                        */
                    //case EVENT_ADD:
                    //    _entityManager->addRequest(/*eeehh*/);
                    //    break;

                }
                //if(data1)delete data1;
                //if(data2)delete data2;
            }
        }
    }
}

Uint32 EventManager::eventBeginningNum=0;
void EventManager::pushUserEvent(int eventcode, void *data1, void *data2)
{
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
    event.type = eventBeginningNum;
    event.user.code = eventcode;
    event.user.data1 = data1;
    event.user.data2 = data2;
    SDL_PushEvent(&event);
}
