#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "Constants.h"
#include "GraphicsManager.h"
#include "Typedefs.h"
class EntityManager;
class ObjectFactory
{
    public:
        ObjectFactory(EntityManager *entityManager, GraphicsManager *graphicsManager);
        virtual ~ObjectFactory();

        entity_ptr createDefault();
        inline bool addTo(shared_ptr<Component> component, shared_ptr<Entity> entity);

        bool isActive(){return _active;}
    protected:

    private:
        EntityManager *_entityManager;
        GraphicsManager *_graphicsManager;
        bool _active;
};

#endif // OBJECTFACTORY_H
