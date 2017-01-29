#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <vector>

#include "Constants.h"

using namespace std;

class Entity;
class InputManager;

class EntityManager
{
    public:
        EntityManager();
        virtual ~EntityManager();
        entity_ptr &createDefault();
        entity_ptr &createMan(int x, int y);
        entity_ptr &createPlayer(int x, int y, shared_ptr<InputManager> iManager);

        void update(int ms);

    protected:

    private:
        //unordered_map<int, entity_ptr > _entity;
        vector<entity_ptr> _entity;
};

#endif // ENTITYMANAGER_H
