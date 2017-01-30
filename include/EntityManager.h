#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "Constants.h"
#include "Entity.h"

using namespace std;

class EntityManager
{
    public:
        EntityManager();
        virtual ~EntityManager();

        void update(int ms);

        void addEntity(entity_ptr entity) {_entity.push_back(entity);}

        const vector<entity_ptr> &entity() const{return _entity;}
    protected:

    private:
        vector<entity_ptr> _entity;
};

#endif // ENTITYMANAGER_H
