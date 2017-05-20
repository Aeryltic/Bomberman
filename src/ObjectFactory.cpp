#include "ObjectFactory.h"

#include "Entity.h"
#include "EntityManager.h"
#include "Components.h"
#include "GoapAgent.h"

ObjectFactory::ObjectFactory(EntityManager* entityManager) : entityManager(entityManager)
{
    Action::init_actions();

    constructors["nest"] = ([=](double x, double y) -> shared_ptr<Entity>
    {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(e,x,y,0,50,50));
        e->add(entityManager->make_component<CAspect>(e,SDL_Color{.r=100,.g=50,.b=50,.a=255}));
        //e->add(entityManager->make_component<CMovement>(e,100));
        e->add(entityManager->make_component<CEnergyStore>(e, 100));
        e->add(entityManager->make_component<CBreeder>(e, "ant", 500, 1, 2));

        e->add(entityManager->make_component<CScentSource>(e, 100, SCENT_NEST));
        //e->add(entityManager->make_component<CSmell>(e));
        return e;
    });

    constructors["ant"] = ([=](double x, double y) -> shared_ptr<Entity>
    {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(e,x,y,0,10,10));
        e->add(entityManager->make_component<CAspect>(e,SDL_Color{.r=255,.g=0,.b=0,.a=255}));

        e->add(entityManager->make_component<CMovement>(e,100));

        e->add(entityManager->make_component<CSmellSensor>(e));

        e->add(entityManager->make_component<CBackpack>(e));

        auto agent = entityManager->make_component<GoapAgent>(e);
        agent->set_state("have_grain", false);
        agent->set_state("grain_delivered", false);

        agent->add_action(Action::get_action("deliver_grain"));
        agent->add_action(Action::get_action("pickup_grain"));

        e->add(agent);

        return e;
    });

    constructors["tree"] = ([=](double x, double y) -> shared_ptr<Entity>
    {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(e,x,y,0,30,30));
        e->add(entityManager->make_component<CAspect>(e,SDL_Color{.r=50,.g=155,.b=0,.a=155}));
        //e->add(entityManager->make_component<CMovement>(e,100));
        e->add(entityManager->make_component<CEnergyStore>(e, 400));
        e->add(entityManager->make_component<CBreeder>(e, "grain", 500, 1, 5));
        //e->add(entityManager->make_component<CSmell>(e));
        return e;
    });

    constructors["grain"] = ([=](double x, double y) -> shared_ptr<Entity>
    {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(e,x,y,0,10,10));
        e->add(entityManager->make_component<CAspect>(e,SDL_Color{.r=0,.g=155,.b=0,.a=255}));
        //e->add(entityManager->make_component<CEnergyStore>(e, 0));
        e->add(entityManager->make_component<CScentSource>(e, 100, SCENT_FOOD));
        e->add(entityManager->make_component<CConsumable>(e, CONSUMABLE_FOOD, 100));

        e->add(entityManager->make_component<CCarryable>(e));
        return e;
    });
}

ObjectFactory::~ObjectFactory()
{
    //dtor
}

shared_ptr<Entity> ObjectFactory::make_object(string type, double x, double y)
{
    shared_ptr<Entity> e = nullptr;
    if(constructors.find(type) != constructors.end())
    {
        e = constructors[type](x, y);
    }
    else
    {
        printf("%s does not exists in object database.\n", type.c_str());
    }
    return e;
}
