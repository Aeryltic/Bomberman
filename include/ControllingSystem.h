#ifndef CONTROLLINGSYSTEM_H
#define CONTROLLINGSYSTEM_H

#include "EntityManager.h"
#include "ObjectFactory.h"

class ControllingSystem
{
    public:
        ControllingSystem(ObjectFactory *objectFactory);
        virtual ~ControllingSystem();

        void update(EntityManager *entityManager, int ms);
        void collides(entity_ptr obj1, entity_ptr obj2, vector2d &normal);

        void plantBomb(int x, int y, BombPlanter *bombPlanter, World *world);
        void explosion(entity_ptr bomb, entity_ptr world_entity);

        bool itIsAGoodSpotToDropABomb(int x, int y, entity_ptr world, entity_ptr player);

        void setRunawayPath(int x, int y, AIController *controller, World *world);

       // Path pathToClosestSafePlace(int x, int y, World *world);

        Path pathFromTo(int_vector2d from, int_vector2d to, World *world, Path &path);
    protected:

    private:
        ObjectFactory *_objectFactory;
        /*
        template<class T>
        unordered_multimap<T,shared_ptr<T>> _component;
        */
};

#endif // CONTROLLINGSYSTEM_H
