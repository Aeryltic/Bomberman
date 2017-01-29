#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <vector>

#include "Constants.h"
#include "Entity.h"

using namespace std;

class InputManager;
class GraphicsManager;

class EntityManager
{
    public:
        EntityManager();
        virtual ~EntityManager();
        entity_ptr &createDefault();
        entity_ptr &createMan(int x, int y);
        entity_ptr &createPlayer(int x, int y, InputManager *iManager, GraphicsManager *gManager);

        void update(int ms);
        const vector<entity_ptr> &entity() const{return _entity;}
    protected:

    private:
        //unordered_map<int, entity_ptr > _entity;
        vector<entity_ptr> _entity;
};

#endif // ENTITYMANAGER_H
