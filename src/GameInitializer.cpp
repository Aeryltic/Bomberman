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
    for(int i=1; i<=3; i++)
    {
        for(int j=1; j<=3; j++)
        {
            entityManager->make_object("ant", i*200, j*200);
        }
    }
    entityManager->make_object("tree", 500, 500);
    entityManager->make_object("nest", 300, 300);
}
