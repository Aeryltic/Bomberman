#ifndef SETUPS_H
#define SETUPS_H

#include "LuaBridge.h"
using namespace luabridge;

namespace setups {
void register_all(lua_State* L);

void register_logs(lua_State* L);
void register_engine(lua_State* L);
void register_systems(lua_State* L);
void register_entity(lua_State* L);
void register_entity_manager(lua_State* L);
void register_components(lua_State* L);
void register_misc(lua_State* L);
}

#endif // SETUPS_H
