#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <vector>
#include <typeinfo>
#include <typeindex>

#include "MiscFunctions.h"
//#include "Enumerations.h"

#include "Message.h"

using namespace std;

class Component;

typedef unordered_map<type_index, shared_ptr<Component> > component_map;
using message_callback = function<void(Message &)>;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity();
    virtual ~Entity();

    template<class C> bool has() const;
    template<class C> C* get();
    template<class C> bool remove();

    bool add(shared_ptr<Component> component);

    component_map &getComponents()
    {
        return components;
    }

    void setID(int id)
    {
        this->id = id;
    }
    int getID()
    {
        return id;
    }

    void receive_message(Message message);
    void register_listener(unsigned message_type, message_callback callback); /// potrzeba te¿ "unregister", bo jak usuniemy komponent w trakcie pracy to bêdzie crash

protected:

private:
    inline bool has(type_index key) const;

    int id;
    component_map components;
    unordered_map<unsigned, vector<message_callback>> callbacks;
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
