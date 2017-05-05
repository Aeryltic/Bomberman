#include "ScriptSystem.h"
#include "GameInstance.h"
#include "DisplayManager.h"

using namespace luabridge;
using namespace std;

ScriptSystem::ScriptSystem(GameInstance *gameInstance)
{
    this->displayManager = gameInstance->getDisplayManager();

    L = luaL_newstate();
    luaL_openlibs(L);

    registerEverything();

    string filename("scripts/script.lua");

    if (luaL_dofile(L, filename.c_str()))
    {
        printf("Error: script not loaded/executed (%s)\n", filename.c_str());
        L = nullptr;
    }

    initialize();
}

ScriptSystem::~ScriptSystem()
{
    if(L) lua_close(L);
}
void ScriptSystem::initialize()
{
    //LuaRef passDisplay = getGlobal(L, "passDisplay");
    //passDisplay(*_displayManager);
    active = true;
}
void ScriptSystem::update(int ms)
{
    LuaRef updateTime = getGlobal(L, "updateTime");
    updateTime(ms);
}

void ScriptSystem::registerEverything()
{
    printf("registering\n");
/// TESTY
    getGlobalNamespace (L)
        .beginClass <DisplayManager> ("DisplayManager")
            .addProperty ("text", &DisplayManager::getText, &DisplayManager::setText)
        .endClass();

    push (L, displayManager);
    lua_setglobal (L, "display");
/// -------
    printf("done\n");
}

string ScriptSystem::execute(const string &command)
{
    /// to by trzeba dopracować, żeby syfu nie robić
    printf("executing: %s\n",command.c_str());
    try
    {
        if(luaL_loadstring(L, command.c_str()) || lua_pcall(L,0,0,0))
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

