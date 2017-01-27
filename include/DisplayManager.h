#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "AppWindow.h"
#include "GraphicsManager.h"
#include "ObjectContainer.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class DisplayManager
{
    struct ToRender
    {
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

        bool isVisible(const Object &obj);
    protected:

    private:
        AppWindow _window;
        GraphicsManager _graphicsManager;
        SDL_Rect _windowRect;
};

#endif // DISPLAYMANAGER_H
