#include "EventManager.h"

#include "GameInstance.h"
#include "Entity.h"
#include "Enumerations.h"

Uint32 EventManager::eventFirstNum = 0;
unordered_map<unsigned, vector<EventCallback>> EventManager::_registeredCallbacks;

EventManager::EventManager(GameInstance *gameInstance)
{
    this->gameInstance = gameInstance;

    // SDL_EventState(type, SDL_IGNORE); to disable event
    if((eventFirstNum = SDL_RegisterEvents(NUMEVENTS)) != (Uint32)-1)
    {
        _active = true;
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
/*
void EventManager::pushEntityEvent(Uint32 eventcode, shared_ptr<Entity> publisher, shared_ptr<Entity> subscriber)
{
    SDL_Event event;
    EntityEvent *e = reinterpret_cast<EntityEvent*>(&event);
    SDL_memset(&event, 0, sizeof(event));
    e->type = getUserEventType(eventcode);
    e->timestamp = SDL_GetTicks();
    e->publisher = publisher;
    e->subscriber = subscriber;


//    event.user.code = eventcode;
//    event.user.data1 = data1;
//    event.user.data2 = data2;

    SDL_PushEvent(&event);
}
*/
Uint32 EventManager::getUserEventType(Uint32 eventcode)
{
    return eventFirstNum + eventcode;
}
