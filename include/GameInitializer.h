#ifndef GAMEINITIALIZER_H
#define GAMEINITIALIZER_H

#include <functional>
#include <memory>
#include <unordered_map>

class EntityManager;
class Entity;

using namespace std;

using entity_creator = function<shared_ptr<Entity>(EntityManager*, double, double)>;
class EntityManager;
class GameInitializer
{
    public:
        GameInitializer();
        virtual ~GameInitializer();
        void initializeGame(EntityManager *entityManager);
    protected:

    private:
        //unordered_map<string, entity_creator> creators;
};

#endif // GAMEINITIALIZER_H
