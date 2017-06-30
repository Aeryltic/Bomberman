#include "ScriptSystem.h"
#include "Engine.h"
#include "DisplayManager.h"

using namespace luabridge;
using namespace std;

//ScriptSystem ScriptSystem::_instance; // dlaczego jeśli to wyląduje w get_instance to program przy zamykaniu zapętla się na czymś?

ScriptSystem::ScriptSystem() {
    logs::open("creating script system...\n");
    L = luaL_newstate();
    //getGlobal(L, "non-existent-variable");
    luaL_openlibs(L);

    string filename("data/scripts/init.lua");

    if(!do_file(filename)) {
        lua_close(L);
        L = nullptr;
        active = false;
    } else active = true;

    initialize();

    logs::close("done\n");

    ///test

}

ScriptSystem::~ScriptSystem() {
    references.clear();
    if(L) {
        logs::log("closing LuaState...");
        lua_close(L);
        logs::log(" done.\n");
    }
    logs::log("delete ScriptSystem\n");
}

void ScriptSystem::initialize() {

}

void ScriptSystem::update(int ms) {
//    LuaRef updateTime = getGlobal(L, "updateTime");
//    updateTime();
}

string ScriptSystem::execute(const string &command) {
    /// to by trzeba dopracować, żeby syfu nie robić
    logs::log("executing: %s\n",command.c_str());
    try {
        if(luaL_dostring(L, command.c_str())) {
            return lua_tostring(L, -1);
        }
    } catch(LuaException const& e) {
        logs::log("LuaException: %s\n", e.what());
        return e.what();
    }
    return "";
}

LuaRef ScriptSystem::get(std::string rname) { /// najlepiej jakby wszystko szło przez to
    logs::log("getting ref: %s\n", rname.c_str());
    auto it = references.find(rname);
    if(it == references.end()) {
        LuaRef r = getGlobal(L, rname.c_str());
        references.insert({rname, r});
        return r;
    }
    return it->second;
}

bool ScriptSystem::do_file(const std::string& filename) {
    if (luaL_dofile(L, filename.c_str())) {
        logs::log("Error: file not executed (%s)\n", filename.c_str());
        logs::log("Error: %s\n", lua_tostring(L, -1));
        return false;
    }
    return true;
}
