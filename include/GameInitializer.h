#ifndef GAMEINITIALIZER_H
#define GAMEINITIALIZER_H

//#include <functional>
#include <memory>
#include <unordered_map>

class EntityManager;
class Entity;
class EntityManager;

using namespace std;

class GameInitializer {
    using entity_creator = function<shared_ptr<Entity>(double, double)>;
public:
    GameInitializer();
    virtual ~GameInitializer();
    void init_entities(EntityManager *entityManager);
protected:

private:
    //unordered_map<string, entity_creator> creators;
};

#endif // GAMEINITIALIZER_H
