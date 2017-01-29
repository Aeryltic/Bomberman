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
        shared_ptr<EntityManager> _entityManager;
        shared_ptr<InputManager> _inputManager;
        /*
        GraphicsManager _graphicsManager;
        InputManager _inputManager;
        LogicManager _logicManager;
        ObjectContainer _objectContainer;
        */
};

#endif // GAMEINSTANCE_H
