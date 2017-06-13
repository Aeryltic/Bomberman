#include "ScriptSystem.h"
#include "GameInstance.h"
#include "DisplayManager.h"

using namespace luabridge;
using namespace std;

ScriptSystem ScriptSystem::instance; // dlaczego jeśli to wyląduje w get_instance to program przy zamykaniu zapętla się na czymś?

ScriptSystem::ScriptSystem()
{
    L = luaL_newstate();
    luaL_openlibs(L);

    string filename("data/scripts/init.lua");

    if (luaL_dofile(L, filename.c_str()))
    {
        printf("Error: script not loaded/executed (%s)\n", filename.c_str());
        printf("Error: %s\n",lua_tostring(L, -1));
        L = nullptr;
        active = false;
    }
    else active = true;

    initialize();
}

ScriptSystem::~ScriptSystem()
{
    if(L) lua_close(L);
}

void ScriptSystem::initialize()
{

}

void ScriptSystem::update(int ms)
{
    LuaRef updateTime = getGlobal(L, "updateTime");
    updateTime();
}

string ScriptSystem::execute(const string &command)
{
    /// to by trzeba dopracować, żeby syfu nie robić
    printf("executing: %s\n",command.c_str());
    try
    {
        if(luaL_dostring(L, command.c_str()))
        {
            return lua_tostring(L, -1);
        }
    }
    catch (LuaException const& e)
    {
        printf("LuaException: %s\n", e.what());
        return e.what();
    }
    return "";
}

