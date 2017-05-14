#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <functional>
#include <memory>
#include <unordered_map>
using namespace std;

class Entity;
class EntityManager;
using entity_creator = function<shared_ptr<Entity>(EntityManager*, double, double)>;

class ObjectFactory
{
    public:
        ObjectFactory();
        virtual ~ObjectFactory();
        shared_ptr<Entity> newObject(string type, double x, double y, EntityManager *entityManager);
    protected:

    private:
        unordered_map<string, entity_creator> constructors;
};

#endif // OBJECTFACTORY_H
