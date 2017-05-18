#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include <LuaBridge.h>
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

using namespace luabridge;
using namespace std;

class ScriptSystem
{
public:
    static ScriptSystem *getInstance()
    {
        return &instance;
    }
    virtual ~ScriptSystem();

    void update(int ms);
    bool isActive()
    {
        return active;
    }
    //void registerEverything();
    lua_State* getLuaState()
    {
        return L;
    }
    string execute(const string &command);
protected:

private:
    ScriptSystem();

    bool active;
    lua_State* L;
    void initialize();

    static ScriptSystem instance;
};

#endif // SCRIPTSYSTEM_H
