#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "AppWindow.h"
#include "GraphicsManager.h"
#include "ObjectContainer.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class DisplayManager
{
    public:
        DisplayManager();
        virtual ~DisplayManager();
        void render(const ObjectContainer &object, double interpolation);
    protected:

    private:
        AppWindow _window;
        GraphicsManager _graphicsManager;
};

#endif // DISPLAYMANAGER_H
