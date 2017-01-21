#include "AppWindow.h"

AppWindow::AppWindow(int w, int h)
{
    _window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
    _screenSurface = 0;
    if(_window)_screenSurface = SDL_GetWindowSurface(_window);
}

AppWindow::~AppWindow()
{
    SDL_DestroyWindow(_window);
}

bool AppWindow::isReady()
{
    return !((_window == 0) || (_screenSurface == 0));
}
