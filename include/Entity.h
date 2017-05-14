#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include "MiscFunctions.h"
#include "Component.h"

using namespace std;

typedef unordered_map<type_index, shared_ptr<Component> > component_map;

class Entity : public std::enable_shared_from_this<Entity>
{
    public:
        Entity();
        virtual ~Entity();

        template<class C> bool has() const;
        template<class C> C* get();
        template<class C> bool remove();

        bool add(shared_ptr<Component> component);

        component_map &getComponents(){return components;}

        void setID(int id){this->id = id;}
        int getID(){return id;}
/*
        void update(int ms);
        void activate();
        void deactivate(){_active = false;}
        bool isActive(){return _active;}
*/
        //void receiveMessage(/*wiadomoœæ*/); // do otrzymywania wiadomoœci, podobnie jak przy eventach, ale raczej takich gdzie chcemy natychmiastowej reakcji (jak miêdzy komponentami jednego bytu)

    protected:

    private:
        inline bool has(type_index key) const;

        int id;
        component_map components;
//        bool _active;
};

// TEMPLATES

template<class C>
C* Entity::get()
{
    type_index key = tindex(C);
    component_map::iterator found = components.find(key);
    if(found != components.end())
    {
        return static_cast<C*>(found->second.get());
    }
    return nullptr;
}

template<class C>
bool Entity::has() const
{
    type_index key = tindex(C);
    return components.find(key) != components.end();
}

template<class C>
bool Entity::remove()
{
    type_index key = tindex(C);
    if(components.find(key) != components.end())
    {
        components.erase(key);
        return true;
    }
    return false;
}

#endif // ENTITY_H
