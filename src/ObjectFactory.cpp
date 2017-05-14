#include "ObjectFactory.h"

#include "Entity.h"
#include "EntityManager.h"
#include "Components.h"

ObjectFactory::ObjectFactory()
{
    constructors["ant"] = ([](EntityManager *entityManager, double x, double y) -> shared_ptr<Entity>
    {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(e,x,y,0,15,15));
        e->add(entityManager->make_component<CAspect>(e,SDL_Color{.r=255,.g=0,.b=0,.a=255}));

        e->add(entityManager->make_component<CMovement>(e,100));

        e->add(entityManager->make_component<CSmell>(e));
        return e;
    });

    constructors["tree"] = ([](EntityManager *entityManager, double x, double y) -> shared_ptr<Entity>
    {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(e,x,y,0,30,30));
        e->add(entityManager->make_component<CAspect>(e,SDL_Color{.r=50,.g=155,.b=0,.a=155}));
        //e->add(entityManager->make_component<CMovement>(e,100));
        e->add(entityManager->make_component<CEnergyStore>(e, 100));
        e->add(entityManager->make_component<CBreeder>(e, "grain", 500, 1, 5));
        //e->add(entityManager->make_component<CSmell>(e));
        return e;
    });

    constructors["grain"] = ([](EntityManager *entityManager, double x, double y) -> shared_ptr<Entity>
    {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(e,x,y,0,10,10));
        e->add(entityManager->make_component<CAspect>(e,SDL_Color{.r=0,.g=155,.b=0,.a=255}));
        //e->add(entityManager->make_component<CMovement>(e,100));
        //e->add(entityManager->make_component<CEnergyStore>(e, 0));
        e->add(entityManager->make_component<CSmell>(e));
        return e;
    });
}

ObjectFactory::~ObjectFactory()
{
    //dtor
}

shared_ptr<Entity> ObjectFactory::newObject(string type, double x, double y, EntityManager *entityManager)
{
    shared_ptr<Entity> e = nullptr;
    if(constructors.find(type) != constructors.end())
    {
        e = constructors[type](entityManager, x, y);
    }
    return e;
}
