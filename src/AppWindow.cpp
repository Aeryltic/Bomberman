#include "AppWindow.h"
#include <stdio.h>
#include "Logs.h"
AppWindow::AppWindow(int w, int h) /* to nie powinno byc tak - raczej po prostu przekazac gotowe window i renderer */
{
    logs::log("new AppWindow\n");
    _window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    _renderer = nullptr;
    if(_window)
    {
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
}

AppWindow::~AppWindow()
{
    logs::open("delete AppWindow\n");
    logs::log("SDL_DestroyRenderer\n");
    SDL_DestroyRenderer(_renderer);
    logs::log("destroyed\n");
    logs::log("SDL_DestroyWindow\n");
    SDL_DestroyWindow(_window);
    logs::close("destroyed\n");
}

bool AppWindow::isReady()
{
    return _window && _renderer;
}
