#ifndef APPWINDOW_H
#define APPWINDOW_H
#include <memory>
#include "SDL.h"
using namespace std;
class DisplayManager;
class AppWindow
{
    friend DisplayManager;
    public:
        AppWindow(int w, int h);
        virtual ~AppWindow();
        bool isReady();
        SDL_Renderer* getRenderer(){return _renderer;}
    protected:

    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;
};

#endif // APPWINDOW_H
