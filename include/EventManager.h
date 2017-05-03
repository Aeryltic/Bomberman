#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "InputManager.h"
#include <unordered_map>
#include <vector>
#include <functional>
#include <SDL.h>
#include "Console.h"

using namespace std;
class EventManager
{
    /// --------------------------------------------------------------------------
    public:
        using EventCallback = function<void(SDL_Event const&)>;

        void registerEventCallback(unsigned type, EventCallback callback);
        /// unregisterEventCallback?
        void handleEvents();

    private:
        unordered_map<unsigned, vector<EventCallback>> _registeredCallbacks;
                                        /// by Kolja from gamedev.stackexchange.com just formatted by me
    /// --------------------------------------------------------------------------
    public:
        EventManager(InputManager *inputManager, Console *console);
        virtual ~EventManager();

        static void pushUserEvent(int eventcode, void *data1, void *data2); /// nic nie wrzucac do data1 ani data2 poki co
        static void pushEntityEvent(Uint32 eventcode, shared_ptr<Entity> publisher, shared_ptr<Entity> subscriber);
        static Uint32 getUserEventType(Uint32 eventcode);

    //template <class T>
      // void EventManager::pushEvent(int eventNum, int eventCode, shared_ptr<Entity> publisher, shared_ptr<Entity> subscriber);
        bool isActive(){if(!_active)printf("EventManager is not active\n");return _active;}

        void registerStandardCallbacks();
    protected:

    private:
        bool _active;
        InputManager *_inputManager;
        static Uint32 eventFirstNum;
        Console *_console;
};
#endif // EVENTMANAGER_H
