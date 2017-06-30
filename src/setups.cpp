#include "setups.h"

#include <memory>

#include "LuaBridge.h"

#include "Engine.h"

#include "Entity.h"
#include "Component.h"

#include "Components.h"
#include "GoapAgent.h"

#include "ScriptSystem.h"
#include "EntityManager.h"

namespace setups {
void register_all() {
    register_entity();
    register_entity_manager();
    register_components();
    register_misc();
}

void register_engine(){
//    lua_State *L = Engine::getScriptSystem()->state();
//
//    getGlobalNamespace(L)
//        .beginClass<DisplayManager>("Engine")
//
//        .endClass();
//
//    push(L, Engine::);
//    lua_setglobal(L, "engine");
}

void register_entity() {
    lua_State* L = Engine::lua()->state();
    getGlobalNamespace(L)
        .beginClass<Entity>("Entity")
//            .addConstructor<void(*)()>()
            .addFunction("destroy_me", &Entity::destroy_me)

            .addFunction("physical_form", &Entity::get<CPhysicalForm>)
            .addFunction("movement", &Entity::get<CMovement>)
            .addFunction("energy_store", &Entity::get<CEnergyStore>)
            .addFunction("needs", &Entity::get<CNeeds>)
            .addFunction("goap", &Entity::get<GoapAgent>)
            .addFunction("aspect", &Entity::get<CAspect>)
            .addFunction("bag", &Entity::get<CAbstractObjectContainer>)
            .addFunction("property", &Entity::get<CProperties>)
        .endClass()
    ;
}

void register_entity_manager() {
    lua_State* L = Engine::lua()->state();
    getGlobalNamespace(L)
        .beginClass<EntityManager>("EntityManager")
            .addFunction("make_object", &EntityManager::make_object)
        .endClass()
    ;
}

void register_components() {
    lua_State *L = Engine::lua()->state();
    getGlobalNamespace(L)
        .beginNamespace("components")

            .beginClass<CPhysicalForm>("CPhysicalForm")
//                .addConstructor<void(*)(double x, double y, double z, double w, double h, double d)>()
                .addProperty("pos", &CPhysicalForm::get_pos)
            .endClass()

            .beginClass<CAspect>("CAspect")
                .addConstructor<void(*)(Uint8 r, Uint8 g, Uint8 b, Uint8 a)>()
                .addFunction("set_color", &CAspect::set_color)
                .addFunction("reset_color", &CAspect::reset_color)
            .endClass()

            .beginClass<CMovement>("CMovement")
//                .addConstructor<void(*)(float)>()
//                .addProperty("max_speed", &CMovement::get_max_speed, &CMovement::set_max_speed)
                .addFunction("set_speed", &CMovement::set_speed)
                .addFunction("stop", &CMovement::stop)
            .endClass()

            .beginClass<CEnergyStore>("CEnergyStore")
//                .addConstructor<void(*)(float)>()
                .addProperty("amount", &CEnergyStore::get_amount, &CEnergyStore::set_amount)
            .endClass()

            .beginClass<CNeeds>("CNeeds")
//                .addConstructor<void(*)(double, double, double)>()
                .addProperty("thirst", &CNeeds::get_thirst, &CNeeds::set_thirst)
                .addProperty("hunger", &CNeeds::get_hunger, &CNeeds::set_hunger)
                .addProperty("weariness", &CNeeds::get_weariness, &CNeeds::set_weariness)
            .endClass()

            .beginClass<GoapAgent>("GoapAgent")
//                .addConstructor<void(*)()>()
                .addFunction("set_state", &GoapAgent::set_state)
                .addFunction("time_passed", &GoapAgent::get_action_perform_time)
            .endClass()

            .beginClass<CAbstractObjectContainer>("CAbstractObjectContainer")
//                .addConstructor<void(*)()>()
                .addFunction("get_item", &CAbstractObjectContainer::get_item)
                .addFunction("set_item", &CAbstractObjectContainer::set_item)
            .endClass()

            .beginClass<CProperties>("CProperties")
//                .addConstructor<void(*)()>()
                .addFunction("get", &CProperties::get)
                .addFunction("set", &CProperties::set)
            .endClass()

        .endNamespace()
    ;
}

void register_misc(){
    lua_State *L = Engine::lua()->state();
    getGlobalNamespace(L)
        .beginClass<vec3d>("vec3d")
            .addConstructor<void(*)(double, double, double)>()
            .addFunction("movement_step", &vec3d::movement_step)
        .endClass()
    ;

    push (L, TIMESTEP);
    lua_setglobal (L, "timestep");
}

}
