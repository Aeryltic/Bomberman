#include "EventManager.h"

#include "GameInstance.h"
#include "Entity.h"
//#include "Component.h"
EventManager::EventManager(InputManager *inputManager) : _inputManager(inputManager)
{
    /// SDL_EventState(type, SDL_IGNORE); to disable event
    if((eventFirstNum = SDL_RegisterEvents(NUMEVENTS)) != (Uint32)-1)
    {
        _active = true;
        /// to tutaj NIE MOZE BYC (ale przynajmniej wiem ze dziala)
        registerStandardCallbacks();
    }
    else _active = false;
}
EventManager::~EventManager()
{
    //dtor
}
void EventManager::registerEventCallback(unsigned type, EventCallback callback)
{
    _registeredCallbacks[type].push_back(callback);
}
void EventManager::handleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        for (auto& cb : _registeredCallbacks[event.type])
        {
            cb(event);
        }
    }
}

Uint32 EventManager::eventFirstNum=0;
void EventManager::pushUserEvent(int eventcode, void *data1, void *data2)
{
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));
    event.type = eventFirstNum;
    event.user.code = eventcode;
    event.user.data1 = data1;
    event.user.data2 = data2;
    SDL_PushEvent(&event);
}
void EventManager::registerStandardCallbacks() /// to powinno byæ w plikach mo¿e poza standardowymi SLD_KEYDOWN, SDL_KEYUP i mo¿e kilkoma ktorych jeszcze nie ma tu
{
    registerEventCallback(SDL_KEYDOWN, [this](SDL_Event const& event)
    {
        SDL_Keycode keycode = event.key.keysym.sym;
        _inputManager->setKeyStatus(keycode,KEY_PRESSED);
    });
    registerEventCallback(SDL_KEYUP, [this](SDL_Event const& event)
    {
        SDL_Keycode keycode = event.key.keysym.sym;
        _inputManager->setKeyStatus(keycode,KEY_RELEASED);
    });
    registerEventCallback(SDL_KEYDOWN, [this](SDL_Event const& event)
    {
        SDL_Keycode keycode = event.key.keysym.sym;
        if(keycode == SDLK_ESCAPE)
        {
            SDL_Event pushed;
            pushed.type = SDL_QUIT;
            SDL_PushEvent(&pushed);
        }
        if(keycode == SDLK_p)
        {
            pushUserEvent(EVENT_PAUSE,NULL,NULL);
        }
    });
    registerEventCallback(SDL_QUIT, [this](SDL_Event const& event)
    {
        GameInstance::getInstance().quit();
    });
    registerEventCallback(SDL_USEREVENT, [this](SDL_Event const& event)
    {
        SDL_Event pushed;
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

           // case EVENT_DELETE:
           //     _entityManager->removeRequest(static_cast<Entity *>(data1)->getID());
           //     break;

            //case EVENT_ADD:
            //    _entityManager->addRequest(cos tam);
            //    break;

        }
//              if(event.user.data1)delete event.user.data1; /// to by trzeba jakos lepiej rozwiazac
//              if(event.user.data2)delete event.user.data2;
    });
    /* // for future use
    registerEventCallback(getUserEventType(EVENT_LOST),
        [this](SDL_Event const& event)
        {
            printf("PRZEGRALES\n");
            GameInstance::getInstance().quit();
        }
    );
    registerEventCallback(getUserEventType(EVENT_WON),
        [this](SDL_Event const& event)
        {
            printf("WYGRALES\n");
            GameInstance::getInstance().quit();
        }
    );
    registerEventCallback(getUserEventType(EVENT_KILLED),
        [this](SDL_Event const& event)
        {
            printf("ZGINALES\n");
            const EntityEvent *e = reinterpret_cast<const EntityEvent*>(&event);
            if(e->subscriber->hasComponent<Player>())
            {
                SDL_Event event;
                event.type = getUserEventType(EVENT_LOST);
                SDL_PushEvent(&event);
            }
        }
    );
    */
}
void EventManager::pushEntityEvent(Uint32 eventcode, shared_ptr<Entity> publisher, shared_ptr<Entity> subscriber)
{
    SDL_Event event;
    EntityEvent *e = reinterpret_cast<EntityEvent*>(&event);
    SDL_memset(&event, 0, sizeof(event));
    e->type = getUserEventType(eventcode);
    e->timestamp = SDL_GetTicks();
    e->publisher = publisher;
    e->subscriber = subscriber;

    /*
    event.user.code = eventcode;
    event.user.data1 = data1;
    event.user.data2 = data2;
    */
    SDL_PushEvent(&event);
}

Uint32 EventManager::getUserEventType(Uint32 eventcode)
{
    return eventFirstNum + eventcode;
}
