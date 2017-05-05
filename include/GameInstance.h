#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include <stdio.h>
class DisplayManager;
class EntityManager;
class LogicManager;
class ScriptSystem;
class Console;
class EventManager;

class GameInstance
{
    public:

        virtual ~GameInstance();
        static GameInstance &getInstance();
        int run();

         DisplayManager  *getDisplayManager();
         EntityManager   *getEntityManager();
         LogicManager    *getLogicManager();
         ScriptSystem    *getScriptSystem();
         Console         *getConsole();
         EventManager    *getEventManager();

         static bool isPaused(){return paused;}
    protected:

    private:
        DisplayManager  *displayManager;
        EntityManager   *entityManager;
        LogicManager    *logicManager;
        ScriptSystem    *scriptSystem;
        Console         *console;
        EventManager    *eventManager;

        int timerID; // SDL_timer_ID

        GameInstance();
        bool working;
        static bool paused;

        int init();
        int startGame();

        void quit();
        void tooglePause(){paused = !paused;}
};

#endif // GAMEINSTANCE_H
