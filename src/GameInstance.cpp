#include "GameInstance.h"

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
#include "Enumerations.h"
#include "GameInitializer.h"
///
bool GameInstance::paused = false;

GameInstance &GameInstance::getInstance()
{
    static GameInstance instance;
    return instance;
}

GameInstance::GameInstance()
{
    printf("creating GameInstance...");
    working = true;

    printf("done\n");
}

GameInstance::~GameInstance()
{
    printf("delete GameInstance\n");

    SDL_RemoveTimer(timerID);

    delete eventManager;
    delete displayManager;
    delete componentSystem;
//    delete logicManager;
    delete entityManager;
    delete console;

    SDL_Quit();
}

int GameInstance::run()
{
    if(init() < 0)
    {
        return -1;
    }

    srand(time(NULL));

    unsigned last_check = SDL_GetTicks();
    unsigned frames = 0;
    unsigned previous = SDL_GetTicks();
    unsigned last_update = SDL_GetTicks();
    unsigned lag = 0.0;

    while(working)
    {
        unsigned current = SDL_GetTicks();
        unsigned elapsed = current - previous;

        previous = current;

        eventManager->handleEvents();
        console->run(); /// tu trzeba statów

        if(!paused)
        {
            lag += elapsed;
            while (lag >= TIMESTEP)
            {
                componentSystem->update(TIMESTEP, entityManager);
                ScriptSystem::getInstance()->update(TIMESTEP);
                lag -= TIMESTEP;
                last_update = SDL_GetTicks();
            }
        }

        displayManager->render(entityManager, SDL_GetTicks() - last_update);
        frames++;

        if(SDL_GetTicks() - last_check >= 1000)
        {
            printf("FPS: %d\n",frames);
            frames = 0;
            last_check = SDL_GetTicks();
        }

        SDL_Delay(1); /// tylko do testow
    }
	return 0;
}

/*
void GameInstance::run()
{
    gameStates.push_back(new MainMenuGS());

}
*/
int GameInstance::init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}
    /// rozdzielić konstrukcję i inicjalizację systemów, bo crashe przy innej kolejności konstrukcji

    //Uint32 delay = (33 / 10) * 10;  /* To round it down to the nearest 10 ms */
    //SDL_TimerID my_timer_id = SDL_AddTimer(delay, my_callbackfunc, my_callback_param);
    //timerID = SDL_AddTimer()

	displayManager = new DisplayManager(this);
    entityManager = new EntityManager();
    eventManager = new EventManager(this);
//    logicManager = new LogicManager(this);
    console = new Console(this);
    componentSystem = new ComponentSystem();

    console->init();
    displayManager->init();
    componentSystem->init();

    if(!(
         displayManager->isActive()    &&
         entityManager->isActive()     &&
//         logicManager->isActive()      &&
         eventManager->isActive()      &&
         ScriptSystem::getInstance()->isActive()
        ))
    {
        printf("some systems are not active\n");
        return -1;
    }

    EventManager::registerEventCallback(SDL_QUIT, [this](SDL_Event const& event)
    {
        quit();
    });

    EventManager::registerEventCallback(SDL_USEREVENT, [this](SDL_Event const& event)
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
                tooglePause();
                break;
        }
    });

    EventManager::registerEventCallback(SDL_KEYDOWN, [this](SDL_Event const& event)
    {
        SDL_Keycode keycode = event.key.keysym.sym;
        switch (keycode)
        {
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

    GameInitializer().initializeGame(entityManager);

    /// TEST TIMERA
    /*
    Uint32 delay = 1000;
    SDL_TimerID my_timer_id = SDL_AddTimer(delay,
        [this](Uint32 interval, void *param) -> int
        {
            EventManager::pushUserEvent(EVENT_CONSOLE_TOGGLE,NULL,NULL);

            return(interval);
        }, NULL);
    */
    return 0;
}

void GameInstance::quit()
{
    working = false;
}

DisplayManager  *GameInstance::getDisplayManager(){return displayManager;}
EntityManager   *GameInstance::getEntityManager(){return entityManager;}
//LogicManager    *GameInstance::getLogicManager(){return logicManager;}
Console         *GameInstance::getConsole(){return console;}
EventManager    *GameInstance::getEventManager(){return eventManager;}
