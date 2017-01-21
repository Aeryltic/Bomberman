#include "GameInstance.h"

#include <SDL.h>
#include <stdio.h>

GameInstance::GameInstance()
{
    /** INITIALIZE */ /* maybe not */

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
    DisplayManager      _displayManager;
    InputManager        _inputManager;
    LogicManager        _logicManager;
    ObjectContainer     _objectContainer;
    /// SCHEMAT
    /*  double previous = getCurrentTime();
        double lag = 0.0;
        while (true)
        {
            double current = getCurrentTime();
            double elapsed = current - previous;
            previous = current;
            lag += elapsed;

            processInput();

            while (lag >= MS_PER_UPDATE)
            {
                update();
                lag -= MS_PER_UPDATE;
            }

            render();
        }
        */
    double previous = SDL_GetTicks();
    double lag = 0.0;
    while(true)
    {
        double current = SDL_GetTicks();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        _inputManager.update(/* nie wiem co tu powinno byc */);
        while (lag >= TIMESTEP)
        {
            _logicManager.update(_objectContainer, TIMESTEP);
            lag -= TIMESTEP;
        }

        _displayManager.render(_objectContainer, lag / TIMESTEP);
    }
    SDL_Delay( 2000 );
    /*
    //The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;


	if(SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xAA, 0xFF, 0xFF));

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
