#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include "GraphicsManager.h"
#include "InputManager.h"

class GameInstance
{
    public:
        GameInstance();
        virtual ~GameInstance();

    protected:

    private:
        GraphicsManager graphicsManager;
        InputManager inputManager;

};

#endif // GAMEINSTANCE_H
