#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "Constants.h"
#include "ObjectFactory.h"

#include "Entity.h"
#include <queue>

using namespace std;

class GraphicsManager;
class InputManager;

class EntityManager
{
    public:
        EntityManager(GraphicsManager *graphicsManager, InputManager *inputManager);
        virtual ~EntityManager();

        void update(int ms);

        void addRequest(entity_ptr entity){_toAdd.push(entity);} ///nikt poza ObjectFactory nie powinien miec do tego dostepu

        const unordered_map<int,entity_ptr> &entity() const{return _entity;}

        entity_ptr getWorld();
        entity_ptr getPlayer();

        bool exists(int id){return _entity.find(id) != _entity.end();}

        bool isActive(){if(!_active)printf("EntityManager is not active\n");return _active;}

        ObjectFactory *getFactory(){return &_objectFactory;}
    protected:

    private:
        bool _active;
        //queue<int> _toRemove;
        queue<entity_ptr> _toAdd;

        //vector<entity_ptr> _entity; /// przebudowac na unordered_map
        unordered_map<int,entity_ptr> _entity;

        weak_ptr<Entity> _world, _player;

        ObjectFactory _objectFactory;
       // entity_ptr    _world, _player;
        int _nextID;

  //      void removeEntity(int id);
  //      void removeEntity(entity_ptr entity);

        void addEntity(entity_ptr entity) {entity->setID(_nextID);/*_entity.push_back(entity);*/ _entity.insert({_nextID++, entity});}

//        void removeRequest(int id){printf("to remove %d\n",id);_toRemove.push(id); if(exists(id))_entity[id]->deactivate();}
//        void removeRequest(entity_ptr entity){_toRemove.push(entity->getID());entity->deactivate();}

};

#endif // ENTITYMANAGER_H
