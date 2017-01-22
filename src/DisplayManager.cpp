#include "DisplayManager.h"
#include <SDL.h>
#include <SDL_image.h>

DisplayManager::DisplayManager() : _window(WINDOW_WIDTH, WINDOW_HEIGHT)
{
    IMG_Init(IMG_INIT_PNG);
}

DisplayManager::~DisplayManager()
{
    IMG_Quit();
    //dtor
}

void DisplayManager::setup()
{

}
void DisplayManager::render(const ObjectInstanceContainer &instance, double interpolation)
{
   // for(auto ins : )
       //Clear screen
    SDL_RenderClear(_window._renderer);

    /** tworzy priority_queue
        dla kazdej instancji:
            jesli na ekranie
                oblicza pozycje
                wrzuca do kolejki
        dla kazdego w kolejce:
            wrzuca do renderera
    */
    //Render texture to screen
    //SDL_RenderCopy(_window._renderer, gTexture, NULL, NULL );

    //Update screen
    SDL_RenderPresent(_window._renderer);
}
