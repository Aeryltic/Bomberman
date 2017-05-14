#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "Constants.h"
#include "Typedefs.h"


#include "ObjectFactory.h"
#include "ResourceManager.h"
#include "Entity.h"
#include <queue>

using namespace std;

class EntityManager
{
    public:
        EntityManager(/*GameInstance *gameInstance*/);
        virtual ~EntityManager();

        void update(int ms);

        void addRequest(entity_ptr entity) {toAdd.push(entity);}
        void removeRequest(int id);

        unordered_map<int,entity_ptr> &getEntities() {return entities;}

        bool exists(int id){return entities.find(id) != entities.end();}

        bool isActive(){if(!active)printf("EntityManager is not active\n");return active;}

        //ObjectFactory *getFactory(){return &objectFactory;}

        void loadEntitiesFromFile(string filepath);

        template<class C, class ... Args>
        shared_ptr<C> make_component(Args && ... args);

        unordered_map<type_index, vector<weak_ptr<Component>>> &getComponents() {return components;}

        shared_ptr<Entity> make_entity();

        shared_ptr<Entity> make_object(string type, double x, double y);

    protected:

    private:
        static int getNextID();

        unordered_map<int, entity_ptr> entities; // na vector?
        unordered_map<type_index, vector<weak_ptr<Component>>>  components;

        bool active;

        queue<entity_ptr> toAdd;
        queue<int> toRemove;

        ResourceManager resourceManager;
        int nextID;

        ObjectFactory factory;
};


template<class C, class ... Args>
shared_ptr<C> EntityManager::make_component(Args && ... args)
{
    shared_ptr<C> component = make_shared<C>(args...);
    components[tindex(C)].push_back(component);

    return component;
}


#endif // ENTITYMANAGER_H
