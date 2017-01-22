#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include "DisplayManager.h"
#include "InputManager.h"
#include "LogicManager.h"
#include "ObjectContainer.h"
#include "Structures.h"
const int TICKS_PER_SECOND = 20;
const int TIMESTEP = 1000/TICKS_PER_SECOND;

class GameInstance
{
    public:
        GameInstance();
        virtual ~GameInstance();
        int run();
        int init(); /* 0 - ok , -1 - error */
    protected:

    private:

        /*
        GraphicsManager _graphicsManager;
        InputManager _inputManager;
        LogicManager _logicManager;
        ObjectContainer _objectContainer;
        */
};

#endif // GAMEINSTANCE_H
