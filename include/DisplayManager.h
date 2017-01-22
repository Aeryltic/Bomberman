#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "AppWindow.h"
#include "GraphicsManager.h"
#include "ObjectInstanceContainer.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class DisplayManager
{
    public:
        DisplayManager();
        virtual ~DisplayManager();
        void setup();
        void render(const ObjectInstanceContainer &instance, double interpolation);
    protected:

    private:
        AppWindow _window;
        GraphicsManager _graphicsManager;
};

#endif // DISPLAYMANAGER_H
