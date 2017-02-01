#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "InputManager.h"

class EventManager
{
    public:
        EventManager(InputManager *inputManager) : _inputManager(inputManager) {eventBeginningNum = SDL_RegisterEvents(NUMEVENTS);}
        virtual ~EventManager();

        void update();

        static void pushUserEvent(int eventcode, void *data1, void *data2);

        //template <class T>
      // void EventManager::pushEvent(int eventNum, int eventCode, shared_ptr<Entity> publisher, shared_ptr<Entity> subscriber);
    protected:

    private:
        InputManager *_inputManager;
        static Uint32 eventBeginningNum;
};

#endif // EVENTMANAGER_H
