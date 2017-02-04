#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "InputManager.h"

class EventManager
{
    public:
        EventManager(InputManager *inputManager);
        virtual ~EventManager();

        void update();

        static void pushUserEvent(int eventcode, void *data1, void *data2);

        //template <class T>
      // void EventManager::pushEvent(int eventNum, int eventCode, shared_ptr<Entity> publisher, shared_ptr<Entity> subscriber);
      bool isActive(){if(!_active)printf("EventManageris not active\n");return _active;}
    protected:

    private:
        bool _active;
        InputManager *_inputManager;
        static Uint32 eventBeginningNum;
};

#endif // EVENTMANAGER_H
