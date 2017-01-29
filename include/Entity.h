#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include <unordered_map>
#include <typeinfo>

using namespace std;
typedef unordered_map<int, Component*> comp_map;
class Entity : public std::enable_shared_from_this<Entity>
{
    public:
        Entity();
        virtual ~Entity();

        template<class C>
        bool hasComponent() const;
        inline bool hasComponent(int key) const;

        template<class C>
        C* getComponent();

        bool addComponent(Component *component);
        template<class C>
        bool removeComponent();

        void update(int ms);

        void setAsTarget();

        comp_map &components(){return _component;}

    protected:

    private:
        int _id;
        unordered_map<int, Component*> _component; /* typeid(T).hash_code() */
        /** zamiast prostej mapy moze lepiej byloby zaimplementowac inteligentny kontener, ktory moglby uproscic odwolania do elementow
        * zeby nie musiec pisac calej tej dlugiej formulki z hasComponent i getComponent
        *
        */
};

// TEMPLATES

template<class C>
C* Entity::getComponent()
{
    int key = typeid(C).hash_code();
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
    int key = typeid(C).hash_code();
    return _component.find(key) != _component.end();
}

#endif // ENTITY_H
