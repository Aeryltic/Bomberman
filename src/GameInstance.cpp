#include "GameInstance.h"

#include <SDL.h>
#include <stdio.h>

#include "DisplayManager.h"
#include "InputManager.h"
#include "LogicManager.h"
#include "EntityManager.h"
#include "ObjectFactory.h"
#include "EventManager.h"

#include "Structures.h"

#include <ctime>
#include <cstdlib>

GameInstance::GameInstance()
{
    /** INITIALIZE */ /* maybe not */
    printf("new GameInstance\n");
    _working = true;
    /*

	*/
}

GameInstance::~GameInstance()
{
    /** DESTROY EVERYTHING */
    printf("delete GameInstance\n");
    SDL_Quit();
}

int GameInstance::run()
{
    if(init() < 0)
    {
        return -1;
    }
    shared_ptr<DisplayManager>  _displayManager = make_shared<DisplayManager>();
    shared_ptr<InputManager>    _inputManager = make_shared<InputManager>();
    shared_ptr<LogicManager>    _logicManager = make_shared<LogicManager>(); /// to jemu sie przypisze te "systemy"
    shared_ptr<EntityManager>   _entityManager = make_shared<EntityManager>();
    shared_ptr<EventManager>    _eventManager = make_shared<EventManager>(_inputManager.get());

    shared_ptr<ObjectFactory>   _objectFactory  = make_shared<ObjectFactory>(_entityManager.get(), _displayManager->getGraphicsManager(), _inputManager.get());

    srand(time(NULL));

    double last_check = SDL_GetTicks();
    int frames = 0;
//    bool quit = false;
    double previous = SDL_GetTicks();
    double lag = 0.0;

   /// TEST
    //_objectFactory.createPlayer(320, 240);
    if(!_objectFactory->createWorld("maps/lvl1")) return -1; /// przydaloby sie zeby sprawdzac czy gre faktycznie mozna zaczac
   /// KONIEC TESTU
 //   startGame(_entityManager);
    //while(!(_inputManager.keyStatus(SDLK_ESCAPE) & (KEY_PRESSED|KEY_DOWN)))
    while(_working)
    {
        double current = SDL_GetTicks();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        _inputManager->update(); /// przy duzym delay przyciski moga nie wspolpracowac - zmieniaja stan zanim gra zereaguje

        _eventManager->update();
        while (lag >= TIMESTEP)
        {
            //_logicManager.update(_objectContainer, TIMESTEP);
            _logicManager->update(_entityManager.get(), _objectFactory.get(), TIMESTEP);
            lag -= TIMESTEP;
        }

        //_displayManager.render(_objectContainer, lag);
        _displayManager->render(_entityManager.get(), lag);
        frames++;

        if(SDL_GetTicks() - last_check >= 1000)
        {
            printf("FPS: %d\n",frames);
            frames = 0;
            last_check = SDL_GetTicks();
        }

        SDL_Delay(10); /// tylko do testow
    }

    /*
    //The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screenSurface = nullptr;


	if(SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == nullptr )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xAA, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Wait two seconds
			SDL_Delay( 2000 );
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	SDL_Quit();
	*/
	return 0;
}

int GameInstance::init()
{

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}
	/*
    if(_graphicsManager.init() < 0)
    {
        return -1;
    }
    if(_inputManager.init() < 0)
    {
        return -1;
    }
    if(_logicManager.init() < 0)
    {
        return -1;
    }
    if(_objectContainer.init() < 0)
    {
        return -1;
    }
    */
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
/*
int GameInstance::startGame(shared_ptr<EntityManager> _entityManager, shared_ptr<InputManager> _inputManager, shared_ptr<DisplayManager> _displayManager)
{
    _entityManager->createPlayer(320, 240, _inputManager, _displayManager->getGraphicsManager());
    return 0;
}
*/
