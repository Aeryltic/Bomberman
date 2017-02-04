#ifndef CONTROLLINGSYSTEM_H
#define CONTROLLINGSYSTEM_H

#include "EntityManager.h"
#include "ObjectFactory.h"
/// te wszystkie funkcje powinny albo brac ca³e obiekty albo same komponenty, a nie raz to a raz to
class ControllingSystem
{
    public:
        ControllingSystem(EntityManager *entityManager);
        virtual ~ControllingSystem();

        void update(int ms);
        void collides(entity_ptr obj1, entity_ptr obj2, vector2d &normal);

        void plantBomb(int x, int y, BombPlanter *bombPlanter/*, World *world*/);
        void explosion(entity_ptr bomb/*, entity_ptr world_entity*/);

        bool itIsAGoodSpotToDropABomb(int x, int y/*, entity_ptr world, entity_ptr player*/);

        bool setRunawayPath(int x, int y, AIController *controller/*, World *world*/);

        bool isActive(){return _active;}

       // Path pathToClosestSafePlace(int x, int y, World *world);

        Path pathFromTo(int_vector2d from, int_vector2d to/*, World *world*/, Path &path);
    protected:

    private:
        bool _active;

        EntityManager *_entityManager;
        ObjectFactory *_objectFactory;

        /*
        template<class T>
        unordered_multimap<T,shared_ptr<T>> _component;
        */
};

#endif // CONTROLLINGSYSTEM_H
