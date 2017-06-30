#include "GameInitializer.h"

#include "Engine.h"

#include "EntityManager.h"
#include "ScriptSystem.h"

#include "StringIndexer.h"

GameInitializer::GameInitializer() {

}

GameInitializer::~GameInitializer() {
    //dtor
}

void GameInitializer::init_entities(EntityManager *entityManager) {
    logs::log("initializing game...\n");
    getGlobal(Engine::lua()->state(), "init_game")(entityManager);
    logs::log(" done!\n");
}
