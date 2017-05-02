#include "ScriptSystem.h"

using namespace luabridge;
using namespace std;
ScriptSystem::ScriptSystem(const string &filename, DisplayManager *displayManager)
{
    _displayManager = displayManager;
    _luaState = luaL_newstate();
    registerEverything();
    luaL_openlibs(_luaState);
    if (luaL_dofile(_luaState, filename.c_str()))
    {
        cout<<"Error: script not loaded ("<<filename<<")"<<endl;
        _luaState = nullptr;
    }
}

ScriptSystem::~ScriptSystem()
{
    if(_luaState) lua_close(_luaState);
}

void ScriptSystem::update(int ms)
{
    //LuaRef updateTime = getGlobal(_luaState, "updateTime");

    //updateTime(*_displayManager, ms);

}

void ScriptSystem::showDialog(string text)
{
    _displayManager->showDialog(text);
}

void ScriptSystem::registerEverything()
{
  //  getGlobalNamespace(_luaState)
 //       .addFunction("showDialog", &ScriptSystem::showDialog);
}
