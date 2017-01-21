#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogicManager.h"

class GameInstance
{
    public:
        GameInstance();
        virtual ~GameInstance();
        void run();
    protected:

    private:
        GraphicsManager _graphicsManager;
        InputManager _inputManager;
        LogicManager _logicManager;
        ObjectContainer _objectContainer;
};

#endif // GAMEINSTANCE_H
