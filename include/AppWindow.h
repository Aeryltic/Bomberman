#ifndef APPWINDOW_H
#define APPWINDOW_H
#include <memory>
#include "SDL.h"
using namespace std;
class AppWindow
{
    public:
        AppWindow(int w, int h);
        virtual ~AppWindow();
        bool isReady();
    protected:

    private:
        SDL_Window* _window;
        SDL_Surface* _screenSurface;
};

#endif // APPWINDOW_H
