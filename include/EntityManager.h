#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "Constants.h"
#include "Entity.h"
#include <stack>

using namespace std;

class EntityManager
{
    public:
        EntityManager();
        virtual ~EntityManager();

        void update(int ms);

        void removeRequest(int id){_toRemove.push(id);}
        void addRequest(entity_ptr entity){_toAdd.push(entity);}

        const vector<entity_ptr> &entity() const{return _entity;}

        entity_ptr getWorld();
        entity_ptr getPlayer();
    protected:

    private:
        stack<int> _toRemove;
        stack<entity_ptr> _toAdd;

        vector<entity_ptr> _entity; /// przebudowac na unordered_map

        weak_ptr<Entity>    _world, _player;
       // entity_ptr    _world, _player;
        int _nextID;

        void removeEntity(int id);
        void removeEntity(entity_ptr entity);

        void addEntity(entity_ptr entity) {entity->setID(_nextID++);_entity.push_back(entity);}
};

#endif // ENTITYMANAGER_H
