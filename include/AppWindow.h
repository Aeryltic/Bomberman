#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "SDL.h"

using namespace std;

class AppWindow
{
    public:
        AppWindow(int w, int h);
        virtual ~AppWindow();
        bool isReady();
        SDL_Renderer* getRenderer(){return _renderer;}
        SDL_Window* getWindow(){return _window;}
    protected:

    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
};

#endif // APPWINDOW_H
