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
    logs::open("creating world...\n");
    try {
        Engine::lua()->get("init_game")(entityManager);
    } catch(LuaException const& e) {
        logs::close("LuaEx while initializing game: %s\n", e.what());
        return;
    }
    logs::close("world created!\n");
}
