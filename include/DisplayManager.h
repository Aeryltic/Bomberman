#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "AppWindow.h"
#include "GraphicsManager.h"
//#include "ObjectContainer.h"


#include <memory>
#include <SDL.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class EntityManager;
//class GraphicsManager;
//class AppWindow;
class ObjectContainer;

using namespace std;

class DisplayManager
{
    struct ToRender
    {
        ToRender(SDL_Texture *texture, const SDL_Rect &rect, int h) : texture(texture), rect(rect), h(h) {}
        SDL_Texture *texture;
        SDL_Rect rect;
        int h;
        friend bool operator<(const ToRender &a, const ToRender &b)
        {
            return a.h < b.h;
        }

    };
    public:
        DisplayManager();
        virtual ~DisplayManager();
        void setup();

        void render(const ObjectContainer &obj, double interpolation);
        void render(const EntityManager *entityManager, int ms);

        GraphicsManager *getGraphicsManager(){return &_graphicsManager;}
        bool isVisible(const SDL_Rect &rect);

        void test();
    protected:

    private:
        AppWindow _window;
        GraphicsManager _graphicsManager; /// ani to
        SDL_Rect _windowRect; /// to nie powinno tu byc ^
};

#endif // DISPLAYMANAGER_H
