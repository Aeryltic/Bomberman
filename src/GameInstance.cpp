#include "GameInstance.h"

#include <SDL.h>
#include <stdio.h>

#include "DisplayManager.h"
#include "InputManager.h"
#include "LogicManager.h"
#include "EntityManager.h"
#include "ObjectFactory.h"
#include "EventManager.h"
#include "ScriptSystem.h"

#include "Structures.h"

#include <ctime>
#include <cstdlib>

GameInstance::GameInstance()
{
    printf("new GameInstance\n");
    _working = true;
    _paused = false;
}

GameInstance::~GameInstance()
{
    printf("delete GameInstance\n");
    SDL_Quit();
}

int GameInstance::run()
{
    if(init() < 0)
    {
        return -1;
    }
    //printf("%llu\n",sizeof(SDL_Event));
    shared_ptr<DisplayManager>  _displayManager = make_shared<DisplayManager>();
    shared_ptr<InputManager>    _inputManager = make_shared<InputManager>();
    shared_ptr<EntityManager>   _entityManager = make_shared<EntityManager>(_displayManager->getGraphicsManager(), _inputManager.get());
    shared_ptr<LogicManager>    _logicManager = make_shared<LogicManager>(_entityManager.get());
    shared_ptr<ScriptSystem>    _scriptSystem = make_shared<ScriptSystem>("scripts/script.lua", _displayManager.get());
    shared_ptr<Console>         _console = make_shared<Console>(_displayManager.get(), _scriptSystem.get());
    shared_ptr<EventManager>    _eventManager = make_shared<EventManager>(_inputManager.get(), _console.get());

    if(!(
         _displayManager->isActive()    &&
         _inputManager->isActive()      &&
         _entityManager->isActive()     &&
         _logicManager->isActive()      &&
         _eventManager->isActive()      &&
         _scriptSystem->isActive()
        ))
    {
        printf("some system(s) is(are) not active\n");
        return -1;
    }

    srand(time(NULL));

    unsigned last_check = SDL_GetTicks();
    unsigned frames = 0;
    unsigned previous = SDL_GetTicks();
    unsigned lag = 0.0;

   /// TEST
//    if(!_entityManager->getFactory()->createWorld("maps/lvl1")) return -1; /// przydaloby sie zeby lepiej sprawdzac czy gre faktycznie mozna zaczac
   /// KONIEC TESTU

    while(_working)
    {
        unsigned current = SDL_GetTicks();
        unsigned elapsed = current - previous;
        previous = current;

        _inputManager->update();
        _eventManager->handleEvents();

        if(!_paused)
        {
            lag += elapsed;
            while (lag >= TIMESTEP)
            {
                _logicManager->update(TIMESTEP);
                _scriptSystem->update(TIMESTEP);
                lag -= TIMESTEP;
            }
        }

        _displayManager->render(_entityManager.get(), lag);
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

int GameInstance::init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}
    return 0;
}

void GameInstance::quit()
{
    _working = false;
}

GameInstance &GameInstance::getInstance()
{
    static GameInstance instance;
    return instance;
}
