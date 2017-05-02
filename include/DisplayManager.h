#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "AppWindow.h"
#include "GraphicsManager.h"

#include <memory>
#include <SDL.h>
#include "SDL_ttf.h"


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class EntityManager;
class ObjectContainer;

using namespace std;

class DisplayManager
{
    /// -----------------------------------
    struct ToRender
    {
        ToRender(SDL_Texture *texture, const SDL_Rect &rect, int z, double angle = 0) : texture(texture), rect(rect), z(z), angle(angle) {}

        SDL_Texture *texture;
        SDL_Rect rect;
        int z;
        double angle;

        friend bool operator<(const ToRender &a, const ToRender &b)
        {
            return a.z > b.z;
        }
    };
    /// -----------------------------------
    public:
        DisplayManager();
        virtual ~DisplayManager();

        void render(const EntityManager *entityManager, int ms);

        bool isVisible(const SDL_Rect &rect);

        GraphicsManager *getGraphicsManager(){return &_graphicsManager;}
        bool isActive(){if(!_active)printf("DisplayManager is not active\n");return _active;}

        void showDialog(const string &text);
        void drawRectangle(const SDL_Rect &rect, const SDL_Color &color);
        void drawText(const string &text, const SDL_Color &color);
    protected:

    private:
        bool _active;
        AppWindow _window;
        GraphicsManager _graphicsManager;
        SDL_Rect _windowRect;

        TTF_Font* consoleFont;
        int consoleFontSize;
        SDL_Color consoleFontColor;

        SDL_Color clearColor;
};

#endif // DISPLAYMANAGER_H
