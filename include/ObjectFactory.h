#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "Constants.h"
#include "EntityManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"

class ObjectFactory
{
    public:
        ObjectFactory(EntityManager *entityManager, GraphicsManager *graphicsManager, InputManager *inputManager) :
                _entityManager(entityManager), _graphicsManager(graphicsManager), _inputManager(inputManager) {}
        virtual ~ObjectFactory();

        entity_ptr createDefault();
        //entity_ptr createPhysical(int x, int y,)

        entity_ptr createMan(int x, int y);
        entity_ptr createPlayer(int x, int y);
        entity_ptr createEnemy(int x, int y);

        entity_ptr createBomb(int x, int y);

        bool createWorld(string path); // laduje caly poziom uzywajac pliku pod sciezka: path
        entity_ptr createWorldGrid(int x, int y, int t);
    protected:

    private:
        EntityManager *_entityManager;
        GraphicsManager *_graphicsManager;
        InputManager *_inputManager;
};

#endif // OBJECTFACTORY_H
