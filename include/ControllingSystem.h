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
        void collides(entity_ptr obj1, entity_ptr obj2, vector2d &normal);

        void explosion(entity_ptr bomb, entity_ptr world_entity, ObjectFactory *objectFactory);

        bool itIsAGoodSpotToDropABomb(int x, int y, entity_ptr world);

        Path pathFromTo(vector2d from, vector2d to);
    protected:

    private:
       // ObjectFactory *_objectFactory;
        /*
        template<class T>
        unordered_multimap<T,shared_ptr<T>> _component;
        */
};

#endif // CONTROLLINGSYSTEM_H
