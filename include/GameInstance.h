#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include <stdio.h>
#include <GameState.h>
#include <vector>

class DisplayManager;
class EntityManager;
//class LogicManager;
class ScriptSystem;
class Console;
class EventManager;
class ComponentSystem;

class GameInstance
{
public:

    virtual ~GameInstance();
    static GameInstance &getInstance();
    int run();

    DisplayManager  *getDisplayManager();
    EntityManager   *getEntityManager();
//         LogicManager    *getLogicManager();
    Console         *getConsole();
    EventManager    *getEventManager();

    static bool isPaused()
    {
        return paused;
    }
protected:

private:
    /// to w ogóle nie powinny być pointery
    DisplayManager  *displayManager;
    EntityManager   *entityManager;
    ComponentSystem *componentSystem;
//        LogicManager    *logicManager;
    Console         *console;
    EventManager    *eventManager;

//        std::vector<GameState*> gameStates;

    int timerID; // SDL_timer_ID

    GameInstance();
    bool working;
    static bool paused;

    int init();
    int startGame();

    void quit();
    void tooglePause()
    {
        paused = !paused;
    }
};

#endif // GAMEINSTANCE_H
