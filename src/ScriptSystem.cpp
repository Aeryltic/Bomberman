#include "ScriptSystem.h"

using namespace luabridge;
using namespace std;
ScriptSystem::ScriptSystem(const string &filename, DisplayManager *displayManager)
{
    _displayManager = displayManager;

    _L = luaL_newstate();
    luaL_openlibs(_L);
    registerEverything();

    if (luaL_dofile(_L, filename.c_str()))
    {
        cout<<"Error: script not loaded/executed ("<<filename<<")"<<endl;
        _L = nullptr;
    }
    initialize();
}

ScriptSystem::~ScriptSystem()
{
    if(_L) lua_close(_L);
}
void ScriptSystem::initialize()
{
    //LuaRef passDisplay = getGlobal(_L, "passDisplay");
    //passDisplay(*_displayManager);
}
void ScriptSystem::update(int ms)
{
    LuaRef updateTime = getGlobal(_L, "updateTime");
    updateTime(ms);
}

void ScriptSystem::registerEverything()
{
    printf("registering\n");
/// TESTY
    getGlobalNamespace (_L)
        .beginClass <DisplayManager> ("DisplayManager")
            .addProperty ("text", &DisplayManager::getText, &DisplayManager::setText)
        .endClass();

    push (_L, _displayManager);
    lua_setglobal (_L, "display");
/// -------
    printf("done\n");
}

string ScriptSystem::execute(const string &command)
{
    /// to by trzeba dopracowaæ, ¿eby syfu nie robiæ
    printf("executing: %s\n",command.c_str());
    try{
        luaL_loadstring(_L, command.c_str());
        lua_pcall(_L,0,0,0);
    }
    catch (LuaException const& e) {
        printf("LuaException: %s\n", e.what());
        return e.what();
    }
    return "ok";
}

