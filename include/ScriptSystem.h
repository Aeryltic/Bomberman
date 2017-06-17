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
    static ScriptSystem *instance()
    {
        return &_instance;
    }
    virtual ~ScriptSystem();

    void update(int ms);
    bool isActive()
    {
        return active;
    }
    //void registerEverything();
    static lua_State* state()
    {
        return _instance.L;
    }
    string execute(const string &command);
protected:

private:
    ScriptSystem();

    bool active;
    lua_State* L;
    void initialize();

    static ScriptSystem _instance;
};

#endif // SCRIPTSYSTEM_H
