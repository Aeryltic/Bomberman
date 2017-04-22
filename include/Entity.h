#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include <unordered_map>
#include <typeinfo>

#include <typeindex>

/// BOSKIE MAKRO
#define tindex(a) type_index(typeid(a))

using namespace std;
typedef unordered_map<type_index, Component*> comp_map;
class Entity : public std::enable_shared_from_this<Entity>
{
    public:
        Entity();
        virtual ~Entity();

        template<class C>
        bool hasComponent() const;
        inline bool hasComponent(type_index key) const;

        template<class C>
        C* getComponent();

        bool addComponent(Component *component);
        template<class C>
        bool removeComponent();

        void update(int ms);

        void activate();
        void deactivate(){_active = false;}

        comp_map &components(){return _component;}

        void setID(int id){/*printf("got ID: #%d\n",id);*/_id = id;}
        int getID(){return _id;}

        bool isActive(){return _active;}

    protected:

    private:
        int _id;
        comp_map _component;
        bool _active;
        /** zamiast prostej mapy moze lepiej byloby zaimplementowac inteligentny kontener, ktory moglby uproscic odwolania do elementow
        * zeby nie musiec pisac calej tej dlugiej formulki z hasComponent i getComponent
        *
        */
};

// TEMPLATES

template<class C>
C* Entity::getComponent()
{
    type_index key = tindex(C);
    comp_map::iterator found = _component.find(key);
    if(found != _component.end())
    {
        return static_cast<C*>(found->second);
    }
    return nullptr;
}

template<class C>
bool Entity::hasComponent() const
{
    type_index key = tindex(C);
    return _component.find(key) != _component.end();
}

template<class C>
bool Entity::removeComponent()
{
    type_index key = tindex(C);
    if(_component.find(key) != _component.end())
    {
        _component.erase(key);
        return true;
    }
    return false;
}

#endif // ENTITY_H
