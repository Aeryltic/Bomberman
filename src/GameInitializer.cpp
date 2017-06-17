#include "GameInitializer.h"

#include "EntityManager.h"
//#include "Components.h"

#include "StringIndexer.h"

GameInitializer::GameInitializer() {

}

GameInitializer::~GameInitializer() {
    //dtor
}

void GameInitializer::init_entities(EntityManager *entityManager) {
/// TEST ENTITY'ów
    printf("initializing game...");
    entityManager->make_object(StringIndexer::get_id("water_source"), 500, 100);
    entityManager->make_object(StringIndexer::get_id("tree"), 500, 500);
    entityManager->make_object(StringIndexer::get_id("tree"), 800, 500);

    entityManager->make_object(StringIndexer::get_id("store"), 300, 300);
    entityManager->make_object(StringIndexer::get_id("store"), 700, 300);

    entityManager->make_object(StringIndexer::get_id("inn"), 600, 600);

    //entityManager->make_object(StringIndexer::get_id("monster"), 10, 10);
    int x = 3,
        y = 3;
    for(int i=1; i<=y; i++) {
        for(int j=1; j<=x; j++) {
            entityManager->make_object(StringIndexer::get_id("ant"), j*200, i*200);
        }
    }
    //entityManager->make_component<CPhysicalForm>(x, y, 0, 10, 10);
    //entityManager->make_component<GoapAgent>();
    printf(" done!\n");
}
