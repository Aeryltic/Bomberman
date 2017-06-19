#include "GameInitializer.h"

#include "EntityManager.h"

#include "StringIndexer.h"

#include "ScriptSystem.h"

GameInitializer::GameInitializer() {

}

GameInitializer::~GameInitializer() {
    //dtor
}

void GameInitializer::init_entities(EntityManager *entityManager) {
    logs::log("initializing game...\n");
    getGlobal(ScriptSystem::state(), "init_game")(entityManager);
    logs::log(" done!\n");
}
