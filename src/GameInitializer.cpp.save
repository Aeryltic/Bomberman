#include "GameInitializer.h"

#include "EntityManager.h"
#include "Components.h"

GameInitializer::GameInitializer() {

}

GameInitializer::~GameInitializer() {
    //dtor
}

void GameInitializer::init_entities(EntityManager *entityManager) {
/// TEST ENTITY'ów
    printf("initializing game...(");
    entityManager->make_object("tree", 500, 500);
    entityManager->make_object("nest", 300, 300);
    int x = 3,
        y = 3;
    for(int i=1; i<=y; i++) {
        for(int j=1; j<=x; j++) {
            entityManager->make_object("ant", j*200, i*200);
        }
    }
    printf(") done!\n");
}
