#include "EntityManager.h"

#include "Entity.h"
EntityManager::EntityManager()
{
    //ctor
}

EntityManager::~EntityManager()
{
    //dtor
}

entity_ptr &EntityManager::createDefault()
{
    entity_ptr def = make_shared<Entity>();
    _entity.push_back(def);
    return _entity.back();
}

entity_ptr &EntityManager::createMan(int x, int y)
{
    entity_ptr &man = createDefault();
    man->addComponent(new LifeComponent);
    man->addComponent(new PhysicalFormComponent(x,y,64,64));
    man->addComponent(new MovementComponent);
    return man;
}

entity_ptr &EntityManager::createPlayer(int x, int y, shared_ptr<InputManager> iManager)
{
    entity_ptr &player = createMan(x,y);
    player->addComponent(new PCControllerComponent(iManager));
    player->setAsTarget();
    printf("player ready\n");
    return player;
}

void EntityManager::update(int ms)
{
    printf("updating: %llu\n", _entity.size());
    for(auto &entity : _entity)
    {
        entity->update(ms);
    }
}
