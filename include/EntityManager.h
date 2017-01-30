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

        void addEntity(entity_ptr entity) {_entity.push_back(entity);}
/*
        entity_ptr &createDefault();

        entity_ptr &createMan(int x, int y);
        entity_ptr &createPlayer(int x, int y, InputManager *iManager, GraphicsManager *gManager);
        entity_ptr &createEnemy(int x, int y, GraphicsManager *gManager);

        entity_ptr &createBomb(int x, int y, GraphicsManager *gManager);
*/
        void update(int ms);
        const vector<entity_ptr> &entity() const{return _entity;}
    protected:

    private:
        //unordered_map<int, entity_ptr > _entity;
        /// dodac InputManager *_iManager, GraphicsManager *_gManager oraz ich obsluge
        vector<entity_ptr> _entity;
};

#endif // ENTITYMANAGER_H
