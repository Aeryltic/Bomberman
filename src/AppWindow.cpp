#include "AppWindow.h"

AppWindow::AppWindow(int w, int h) /* to nie powinno byc tak - raczej po prostu przekazac gotowe window i renderer */
{
    _window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
    _renderer = nullptr;
    if(_window)
    {
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
}

AppWindow::~AppWindow()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

bool AppWindow::isReady()
{
    return !((_window == 0) || (_renderer == 0));
}
