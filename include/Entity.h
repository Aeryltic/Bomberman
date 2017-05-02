#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include "MiscFunctions.h"
#include "Component.h"

using namespace std;

typedef unordered_map<type_index, shared_ptr<Component> > compMap;

class Entity : public std::enable_shared_from_this<Entity>
{
    public:
        Entity();
        virtual ~Entity();

        template<class C> bool has() const;
        template<class C> C* get();
        template<class C> bool remove();
        inline bool has(type_index key) const;

        bool add(shared_ptr<Component> component);



        void update(int ms);

        compMap &components(){return _component;}

        void setID(int id){_id = id;}
        int getID(){return _id;}

        void activate();
        void deactivate(){_active = false;}
        bool isActive(){return _active;}

    protected:

    private:
        int _id;
        compMap _component;
        bool _active;
};

// TEMPLATES

template<class C>
C* Entity::get()
{
    type_index key = tindex(C);
    compMap::iterator found = _component.find(key);
    if(found != _component.end())
    {
        return static_cast<C*>(found->second.get());
    }
    return nullptr;
}

template<class C>
bool Entity::has() const
{
    type_index key = tindex(C);
    return _component.find(key) != _component.end();
}

template<class C>
bool Entity::remove()
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
