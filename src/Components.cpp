#include "Components.h"

#include "ScriptSystem.h"

unordered_map<string, vector<weak_ptr<Entity>>> CActionTarget::targets;
namespace comp_setup{
void register_components() { /// to potem
    lua_State *L = ScriptSystem::getInstance()->getLuaState();
    getGlobalNamespace(L)
        .beginNamespace("components")
            .beginClass<CPhysicalForm>("CPhysicalForm")
                .addConstructor<void(*)(double x, double y, double z, double w, double h, double d)>()
            .endClass()
            .beginClass<CAspect>("CAspect")
                .addConstructor<void(*)(Uint8 r, Uint8 g, Uint8 b, Uint8 a)>()
            .endClass()
            .beginClass<CEnergyStore>("CEnergyStore")
                .addConstructor<void(*)(float)>()
                .addProperty("amount", &CEnergyStore::get_amount, &CEnergyStore::set_amount)
            .endClass()
    .endNamespace();
}
}

/// CPhysicalForm ---------------------------------------------------------------------------
/*
SDL_Rect CPhysicalForm::rect(int ms)
{
    SDL_Rect rect = {.x = (int)pos.x, .y = (int)pos.y, .w = (int)vol.x, .h = (int)vol.y};
//    rect.x += cos(_angle) * _v * ms / 1000.0;
//    rect.y += sin(_angle) * _v * ms / 1000.0;
    return rect;
}
*/
