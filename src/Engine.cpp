#include "Engine.h"

#include <SDL.h>
#include <stdio.h>

#include "Structures.h"

#include <ctime>
#include <cstdlib>

#include "DisplayManager.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "ScriptSystem.h"
#include "Console.h"
/// TEST
#include "ComponentSystem.h"
#include "GameInitializer.h"

#include "setups.h"
///

Engine* Engine::_instance = nullptr;

Engine::Engine() {
    logs::open("creating Engine instance...\n");

    scriptSystem = new ScriptSystem();

    displayManager = new DisplayManager();
    entityManager = new EntityManager();
    eventManager = new EventManager();
    console = new Console();
    componentSystem = new ComponentSystem();


    paused = false;
    working = true;

    logs::close("done\n");
}

Engine::~Engine() {
    //logs::open("delete GameInstance\n");

    //SDL_RemoveTimer(timerID);

    delete entityManager;
    delete componentSystem;
    delete displayManager;

    delete eventManager;
    delete console;

    delete scriptSystem;

    SDL_Quit();

    //logs::close("GAME is CLOSED!\n");
}

int Engine::run() {
    if(_instance) delete _instance;

    logs::open("starting engine...\n");
    _instance = new Engine();
    if(_instance->init() < 0) {
        return -1;
    }
    logs::close("engine ready\n");

    _instance->main_loop();

    logs::open("stopping engine...\n");
    if(_instance) delete _instance;
    logs::close("engine stopped\n");

    return 0;
}

void Engine::close() {

}

int Engine::init() {
    logs::open("initializing engine...\n");

    logs::open("initializing SDL...\n");
    logs::log("VIDEO...\n");
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        logs::log("SDL - could not initialize VIDEO! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    logs::log("AUDIO...\n");
    if(SDL_Init(SDL_INIT_AUDIO) < 0) {
        logs::log("SDL - could not initialize AUDIO! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
/// timer wywala wyjątki
//    logs::log("TIMER...\n");
//    if(SDL_Init(SDL_INIT_TIMER) < 0) {
//        logs::log("SDL - could not initialize TIMER! SDL_Error: %s\n", SDL_GetError());
//        return -1;
//    }
    logs::close("SDL initialized...\n");

    logs::open("initializing subsystems...\n");
    displayManager->init();
    componentSystem->init();
    entityManager->init();
    console->init();

    if(!(
                displayManager->isActive()    &&
                entityManager->isActive()     &&
                eventManager->isActive()      &&
                scriptSystem->isActive()
            )) {
        logs::close("some system(s) is(are) not active.\n");
        return -1;
    }
    logs::close("subsystems initialized and active.\n");

    logs::open("registering events...\n");
    EventManager::registerEventCallback(SDL_QUIT, [=](SDL_Event const& event) {
        quit();
    });

    EventManager::registerEventCallback(SDL_USEREVENT, [=](SDL_Event const& event) {
        SDL_Event pushed;
        switch (event.user.code) {
        case EVENT_LOST:
            logs::log("EVENT_LOST\n");
            SDL_memset(&pushed, 0, sizeof(pushed));
            pushed.type = SDL_QUIT;
            SDL_PushEvent(&pushed);
            break;
        case EVENT_WON:
            logs::log("EVENT_WON\n");
            SDL_memset(&pushed, 0, sizeof(pushed));
            pushed.type = SDL_QUIT;
            SDL_PushEvent(&pushed);
            break;
        case EVENT_PAUSE:
            tooglePause();
            break;
        }
    });

    EventManager::registerEventCallback(SDL_KEYDOWN, [=](SDL_Event const& event) {
        SDL_Keycode keycode = event.key.keysym.sym;
        switch (keycode) {
        case SDLK_ESCAPE:
            SDL_Event pushed;
            pushed.type = SDL_QUIT;
            SDL_PushEvent(&pushed);
            break;
//        case SDLK_p:
//            EventManager::pushUserEvent(EVENT_PAUSE,NULL,NULL);
//            break;
        case SDLK_BACKQUOTE:
            EventManager::pushUserEvent(EVENT_CONSOLE_TOGGLE,NULL,NULL);
            break;
        }
    });
    logs::close("events registered.\n");
    setups::register_all();

    GameInitializer().init_entities(entityManager);

    logs::close("engine initialized.\n");
    return 0;
}

int Engine::main_loop() {
    srand(time(NULL));

    unsigned last_check = SDL_GetTicks();
    unsigned frames = 0;
    unsigned previous = SDL_GetTicks();
    unsigned last_update = SDL_GetTicks();
    unsigned lag = 0.0;

    while(working) {
        unsigned current = SDL_GetTicks();
        unsigned elapsed = current - previous;

        previous = current;

        eventManager->handleEvents();
        console->run(); /// tu trzeba state'ów

        if(!paused) {
            lag += elapsed;
            while (lag >= TIMESTEP) {
                entityManager->update();
                componentSystem->update(TIMESTEP, entityManager);
                Engine::lua()->update(TIMESTEP);
                lag -= TIMESTEP;
                last_update = SDL_GetTicks();
            }
        }

        displayManager->render(entityManager, double(SDL_GetTicks() - last_update) / TIMESTEP);
        frames++;

        if(SDL_GetTicks() - last_check >= 1000) {
            logs::log("FPS: %d\n",frames);
            frames = 0;
            last_check = SDL_GetTicks();
        }

        SDL_Delay(1); /// tylko do testow
    }

    close();
    return 0;
}

void Engine::quit() {
    working = false;
}

DisplayManager* Engine::getDisplayManager() {
    return _instance->displayManager;
}
EntityManager* Engine::getEntityManager() {
    return _instance->entityManager;
}
//LogicManager    *GameInstance::getLogicManager(){return logicManager;}
Console* Engine::getConsole() {
    return _instance->console;
}
EventManager* Engine::getEventManager() {
    return _instance->eventManager;
}

ScriptSystem* Engine::lua() {
    return _instance->scriptSystem;
}
