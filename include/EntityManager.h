#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "Constants.h"
//#include "Typedefs.h"


#include "ObjectFactory.h"
#include "ResourceManager.h"
#include "Entity.h"
#include <queue>

using namespace std;

class EntityManager {
    friend class ObjectFactory;
    using entity_ptr = shared_ptr<Entity>;
    using component_ptr = shared_ptr<Component>;
    using component_map = unordered_map<type_index, unordered_map<int, weak_ptr<Component>>>;
public:
    EntityManager(/*GameInstance *gameInstance*/);
    virtual ~EntityManager();

    void update();

    void request_entity_removal(int id);
    void request_component_removal(type_index t_index, int id);

    unordered_map<int,entity_ptr> &get_entities(){ return entities; }

    bool exists(int id);

    bool isActive(){ if(!active)printf("EntityManager is not active\n"); return active;}

    //ObjectFactory *getFactory(){return &objectFactory;}

   // void loadEntitiesFromFile(string filepath);

    template<class C, class ... Args>
    shared_ptr<C> make_component(Args && ... args);

    unordered_map<type_index, unordered_map<int, weak_ptr<Component>>> &get_components() { return components; }

    shared_ptr<Entity> make_entity();
    shared_ptr<Entity> make_object(unsigned type, double x, double y);

    void delete_component(type_index t_index, int id);

protected:

private:
    /*
    int next_eid; /// to wszystko będzie crashować po przepełnieniu
    int getNextEID() {
        return next_eid++;
    }
    */
    /*
    int next_cid;
    int getNextCID() {
        return next_cid++;
    }
    */
    unordered_map<int, entity_ptr> entities; // na vector?
    unordered_map<type_index, unordered_map<int, weak_ptr<Component>>>  components;

    bool active;

    //queue<entity_ptr> toAdd;
    queue<int> entities_to_remove;
    queue<pair<type_index,int>> components_to_remove;

    ResourceManager resourceManager;

    ObjectFactory factory;
};


template<class C, class ... Args>
shared_ptr<C> EntityManager::make_component(Args && ... args) { /// ta funkcja jest do wywalenia
    shared_ptr<C> component = make_shared<C>(args...);
    //int id = getNextCID();
    //component->set_id(id);
    components[tindex(C)].insert({component->get_id(), component}); // to chyba nie powinno tutaj być
    return component;
}



#endif // ENTITYMANAGER_H
