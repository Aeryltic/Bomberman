#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include <LuaBridge.h>
#include <iostream>
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include <DisplayManager.h>

using namespace luabridge;
using namespace std;
class ScriptSystem
{
    public:
        ScriptSystem(const string &filename, DisplayManager *displayManager);
        virtual ~ScriptSystem();
        void update(int ms);
        bool isActive(){return _luaState;}
        void registerEverything();
    protected:

    private:
        bool _active;
        lua_State* _luaState;
        DisplayManager *_displayManager;
        void showDialog(string text);
//        LuaRef updateTime;
};

#endif // SCRIPTSYSTEM_H
