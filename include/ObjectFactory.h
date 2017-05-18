#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <functional>
#include <memory>
#include <unordered_map>
using namespace std;

class Entity;
class EntityManager;
using entity_creator = function<shared_ptr<Entity>(double, double)>; /// gdzie obiekt ma być

class ObjectFactory
{
public:
    ObjectFactory(EntityManager* entityManager);
    virtual ~ObjectFactory();
    shared_ptr<Entity> make_object(string type, double x, double y);

//        template<class C, class ... Args>
//        shared_ptr<C> make_component(Args && ... args);
protected:

private:
    unordered_map<string, entity_creator> constructors;

    EntityManager* entityManager;
};
/*
template<class C, class ... Args>
shared_ptr<C> ObjectFactory::make_component(Args && ... args)
{
    shared_ptr<C> component = make_shared<C>(args...);
    components[tindex(C)].push_back(component);

    return component;
}
*/
#endif // OBJECTFACTORY_H
