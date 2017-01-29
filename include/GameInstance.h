#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include "DisplayManager.h"
#include "InputManager.h"
#include "LogicManager.h"
#include "ObjectContainer.h"
#include "Structures.h"
/// v2 classes
#include "EntityManager.h"


class GameInstance
{
    public:
        GameInstance();
        virtual ~GameInstance();
        int run();
        int init(); /* 0 - ok , -1 - error */
        int startGame();
    protected:

    private:
        DisplayManager          _displayManager;
        InputManager            _inputManager;
        LogicManager            _logicManager;
        EntityManager           _entityManager;
        //shared_ptr<GraphicsManager> _graphicsManager;
        /*
        GraphicsManager _graphicsManager;
        InputManager _inputManager;
        LogicManager _logicManager;
        ObjectContainer _objectContainer;
        */
};

#endif // GAMEINSTANCE_H
