#ifndef CONTROLLINGSYSTEM_H
#define CONTROLLINGSYSTEM_H

#include "EntityManager.h"
#include "ObjectFactory.h"

class ControllingSystem
{
    public:
        ControllingSystem();
        virtual ~ControllingSystem();

        void update(EntityManager *entityManager, ObjectFactory *objectFactory, int ms);
        void collides(entity_ptr obj1, entity_ptr obj2, Vector2D &normal);

        void explosion(int x, int y);

        bool itIsAGoodSpotToDropABomb(int x, int y, entity_ptr world);

        Path pathFromTo(Vector2D from, Vector2D to);
    protected:

    private:
       // ObjectFactory *_objectFactory;
        /*
        template<class T>
        unordered_multimap<T,shared_ptr<T>> _component;
        */
};

#endif // CONTROLLINGSYSTEM_H
