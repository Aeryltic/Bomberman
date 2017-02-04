#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "Constants.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "Typedefs.h"
class EntityManager;
class ObjectFactory
{
    public:
        ObjectFactory(EntityManager *entityManager, GraphicsManager *graphicsManager, InputManager *inputManager);
        virtual ~ObjectFactory();

        entity_ptr createDefault();
        //entity_ptr createPhysical(int x, int y,)

        entity_ptr createMan(int x, int y, string tex_path);
        entity_ptr createPlayer(int x, int y);
        entity_ptr createEnemy(int x, int y);

        entity_ptr createBomb(int x, int y, unsigned range);

        entity_ptr createExplosion(int x, int y);

        bool createWorld(string path); // laduje caly poziom uzywajac pliku pod sciezka: path
        entity_ptr createWorldCell(int x, int y, int t);

        bool isActive(){return _active;}
    protected:

    private:
        EntityManager *_entityManager;
        GraphicsManager *_graphicsManager;
        InputManager *_inputManager;
        bool _active;
};

#endif // OBJECTFACTORY_H
