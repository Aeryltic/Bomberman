#include "GameInstance.h"

#include <SDL.h>
#include <stdio.h>

GameInstance::GameInstance()
{
    /** INITIALIZE */ /* maybe not */
    /*
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	*/
	_entityManager = make_shared<EntityManager>();
	_inputManager = make_shared<InputManager>();
}

GameInstance::~GameInstance()
{
    /** DESTROY EVERYTHING */
    SDL_Quit();
}

int GameInstance::run()
{
    if(init() < 0)
    {
        return -1;
    }
    DisplayManager          _displayManager;
   // InputManager            _inputManager;
    LogicManager            _logicManager;
    ObjectContainer         _objectContainer;

//    Object::setGraphicsManager(_displayManager.getGraphicsManager());
//    ObjectInstanceContainer _objectInstanceContainer(_objectContainer);
    // load objects => load textures
    // load instances

    double last_check = SDL_GetTicks();
    int frames = 0;
//    bool quit = false;
    double previous = SDL_GetTicks();
    double lag = 0.0;
   // SDL_Scancode quit_key = SDL_SCANCODE_ESCAPE;
    startGame();
    while(!(_inputManager->keyStatus(SDLK_ESCAPE) & (KEY_PRESSED|KEY_DOWN)))
    {
        double current = SDL_GetTicks();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        _inputManager->update(); /// przy duzym delay przyciski moga nie wspolpracowac - zmieniaja stan zanim gra zereaguje
        while (lag >= TIMESTEP)
        {
            //_logicManager.update(_objectContainer, TIMESTEP);
            _logicManager.update(_entityManager, TIMESTEP);
            lag -= TIMESTEP;
        }

       // _displayManager.render(_objectContainer, lag / TIMESTEP);
        _displayManager.render(_objectContainer, lag);
        frames++;

        if(SDL_GetTicks() - last_check >= 1000)
        {
            printf("FPS: %d\n",frames);
            frames = 0;
            last_check = SDL_GetTicks();
        }

        SDL_Delay(20); /// tylko do testow
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

int GameInstance::startGame()
{
    _entityManager->createPlayer(320, 240, _inputManager);
    return 0;
}
