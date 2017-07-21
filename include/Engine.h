#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <vector>

class DisplayManager;
class EntityManager;
class ScriptSystem;
class Console;
class EventManager;
class ComponentSystem;

class Engine {
public:
    virtual ~Engine();

    static int run();

    static DisplayManager  *getDisplayManager();
    static EntityManager   *getEntityManager();
    static ScriptSystem    *lua();
    static Console         *getConsole();
    static EventManager    *getEventManager();

    static bool isPaused() {
        return _instance->paused;
    }

protected:

private:
    static Engine *_instance;

    ScriptSystem    *scriptSystem;
    DisplayManager  *displayManager;
    EntityManager   *entityManager;
    ComponentSystem *componentSystem;
    Console         *console;
    EventManager    *eventManager;

//    int timerID; // SDL_timer_ID

    bool working;
    bool paused;

    Engine();
    int init();

    void quit();
    void tooglePause() {
        paused = !paused;
    }

    int main_loop();
    static void close();
};

#endif // ENGINE_H
