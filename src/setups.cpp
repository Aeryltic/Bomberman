#include "setups.h"

#include <memory>

#include "LuaBridge.h"

#include "Entity.h"
#include "Component.h"

#include "ScriptSystem.h"
#include "EntityManager.h"

namespace setups {

void setup_entity(){
    lua_State* L = ScriptSystem::getInstance()->getLuaState();
    getGlobalNamespace(L)
        .beginClass<Entity>("Entity")
            .addFunction("get_id", &Entity::get_id)
            .addFunction("add", &Entity::add)
        .endClass()
        .beginClass<std::shared_ptr<Entity>>("shared_ptr_Entity")
            .addFunction("get", &std::shared_ptr<Entity>::get) // tylko czy to zadziała prawidłowo?
        .endClass();
}

void setup_entity_manager() {
    lua_State* L = ScriptSystem::getInstance()->getLuaState();
    getGlobalNamespace(L)
        .beginClass<EntityManager>("EntityManager")
            .addFunction("make_entity", &EntityManager::make_entity)
//            .addFunction("make_component", &EntityManager::make_component)
        .endClass();
}

}
