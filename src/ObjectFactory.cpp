#include "ObjectFactory.h"

#include "Entity.h"
#include "EntityManager.h"
#include "Components.h"
#include "GoapAgent.h"

#include "StringIndexer.h"

ObjectFactory::ObjectFactory(EntityManager* entityManager) : entityManager(entityManager) { /// to ma wylądować w skryptach
    Action::init_actions();

    constructors[StringIndexer::get_id("nest")] = ([=](double x, double y) {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(x,y,0,50,50));
        e->add(entityManager->make_component<CAspect>(SDL_Color{.r=100,.g=50,.b=50,.a=255}));

        e->add(entityManager->make_component<CEnergyStore>(0));
        e->add(entityManager->make_component<CBreeder>("ant", 500, 1, 2));
        e->add(entityManager->make_component<CActionTarget>("TARGET_NEST"));
        return e;
    });

    constructors[StringIndexer::get_id("ant")] = ([=](double x, double y) {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(x,y,0,10,10));
        e->add(entityManager->make_component<CAspect>(SDL_Color{.r=255,.g=0,.b=0,.a=255}));
        e->add(entityManager->make_component<CMovement>(100));
        e->add(entityManager->make_component<CActionTarget>("TARGET_ANT"));

        auto agent = entityManager->make_component<GoapAgent>();
        agent->set_state("have_grain", false);
        agent->add_action(Action::get_action("deliver_grain"));
        agent->add_action(Action::get_action("pickup_grain"));
        agent->add_goal("grain_delivered", true, 1);
        e->add(agent);

        return e;
    });

    constructors[StringIndexer::get_id("tree")] = ([=](double x, double y) {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(x,y,0,30,30));
        e->add(entityManager->make_component<CAspect>(SDL_Color{.r=50,.g=155,.b=0,.a=155}));
        e->add(entityManager->make_component<CEnergyStore>(200));
        e->add(entityManager->make_component<CBreeder>("grain", 500, 1, 5));

        return e;
    });

    constructors[StringIndexer::get_id("grain")] = ([=](double x, double y) {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(x, y, 0, 10, 10));
        e->add(entityManager->make_component<CAspect>( SDL_Color{.r=0,.g=155,.b=0,.a=255}));
        e->add(entityManager->make_component<CActionTarget>("TARGET_GRAIN"));

        return e;
    });

    constructors[StringIndexer::get_id("water_source")] = ([=](double x, double y) {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(x,y,0,50,50));
        e->add(entityManager->make_component<CAspect>(SDL_Color{.r=70,.g=130,.b=180,.a=220}));
        e->add(entityManager->make_component<CEnergyStore>(200));
        e->add(entityManager->make_component<CActionTarget>("TARGET_WATER"));

        return e;
    });

    constructors[StringIndexer::get_id("monster")] = ([=](double x, double y) {
        shared_ptr<Entity> e = entityManager->make_entity();
        e->add(entityManager->make_component<CPhysicalForm>(x, y, 0, 20, 20));
        e->add(entityManager->make_component<CAspect>(SDL_Color{.r=50,.g=40,.b=20,.a=255}));
        e->add(entityManager->make_component<CMovement>(20));

        auto agent = entityManager->make_component<GoapAgent>();
        agent->set_state("enemy_killed", false);
        agent->add_action(Action::get_action("kill_enemy"));
        agent->add_goal("enemy_killed", true, 1);
        e->add(agent);

        return e;
    });
}

ObjectFactory::~ObjectFactory() {
    //dtor
}

shared_ptr<Entity> ObjectFactory::make_object(unsigned type, double x, double y) {
    shared_ptr<Entity> e = nullptr;
    if(constructors.find(type) != constructors.end()) {
        e = constructors[type](x, y);
    } else {
        printf("%d does not exists in object of object's references.\n", type);
    }
    return e;
}
