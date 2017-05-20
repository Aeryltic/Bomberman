#include "GameInitializer.h"

#include "EntityManager.h"
#include "Components.h"

GameInitializer::GameInitializer()
{

}

GameInitializer::~GameInitializer()
{
    //dtor
}

void GameInitializer::initializeGame(EntityManager *entityManager)
{
/// TEST ENTITY'ów
    int x = 1,
        y = 1;
    for(int i=1; i<=y; i++)
    {
        for(int j=1; j<=x; j++)
        {
            entityManager->make_object("ant", j*200, i*200);
        }
    }
    entityManager->make_object("tree", 500, 500);
    entityManager->make_object("nest", 300, 300);
}
