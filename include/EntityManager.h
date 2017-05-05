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
class GameInstance;

class EntityManager
{
    public:
        EntityManager(GameInstance *gameInstance);
        virtual ~EntityManager();

        void update(int ms);

        void addRequest(entity_ptr entity) {toAdd.push(entity);}
        void removeRequest(int id);

        unordered_map<int,entity_ptr> &getEntities() {return entities;}

        entity_ptr getWorld();
        entity_ptr getPlayer();

        bool exists(int id){return entities.find(id) != entities.end();}

        bool isActive(){if(!active)printf("EntityManager is not active\n");return active;}

        ObjectFactory *getFactory(){return &objectFactory;}

        template<class C>
        void add(weak_ptr<C> component)
        {
            components[tindex(C)].push_back(component);
        }

    protected:

    private:
        unordered_map<int, entity_ptr> entities; // na vector?
        unordered_map<type_index, vector<weak_ptr<Component> > >  components;

        bool active;

        queue<entity_ptr> toAdd;
        queue<int> toRemove;

        ObjectFactory objectFactory;
        int nextID;
};

#endif // ENTITYMANAGER_H
