#include "ScriptSystem.h"
#include "GameInstance.h"
#include "DisplayManager.h"

using namespace luabridge;
using namespace std;

ScriptSystem ScriptSystem::_instance; // dlaczego jeśli to wyląduje w get_instance to program przy zamykaniu zapętla się na czymś?

ScriptSystem::ScriptSystem() {
    L = luaL_newstate();
    luaL_openlibs(L);

    string filename("data/scripts/init.lua");

    if (luaL_dofile(L, filename.c_str())) {
        logs::log("Error: script not loaded/executed (%s)\n", filename.c_str());
        logs::log("Error: %s\n",lua_tostring(L, -1));
        L = nullptr;
        active = false;
    } else active = true;

    initialize();
}

ScriptSystem::~ScriptSystem() {
    if(L) lua_close(L);
    logs::log("delete ScriptSystem");
}

void ScriptSystem::initialize() {

}

void ScriptSystem::update(int ms) {
    LuaRef updateTime = getGlobal(L, "updateTime");
    updateTime();
}

string ScriptSystem::execute(const string &command) {
    /// to by trzeba dopracować, żeby syfu nie robić
    logs::log("executing: %s\n",command.c_str());
    try {
        if(luaL_dostring(L, command.c_str())) {
            return lua_tostring(L, -1);
        }
    } catch (LuaException const& e) {
        logs::log("LuaException: %s\n", e.what());
        return e.what();
    }
    return "";
}

LuaRef& ScriptSystem::get_ref(std::string rname){ /// najlepiej jakby wszystko szło przez to
    auto it = references.find(rname);
    if(it == references.end()){
        references.insert({rname, getGlobal(L, rname.c_str())});
    }
    return references.at(rname);
}

