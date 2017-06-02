#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

//#include <functional>
#include <memory>
#include <unordered_map>
using namespace std;

class Entity;
class EntityManager;


class ObjectFactory
{
    using entity_creator = function<shared_ptr<Entity>(double, double)>;
public:
    ObjectFactory(EntityManager* entityManager);
    virtual ~ObjectFactory();
    shared_ptr<Entity> make_object(string type, double x, double y);

private:
    unordered_map<string, entity_creator> constructors;
    EntityManager* entityManager;
};
#endif // OBJECTFACTORY_H
