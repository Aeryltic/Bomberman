#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include <unordered_map>

#include <LuaBridge.h>
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

using namespace luabridge;

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
    std::string execute(const std::string &command);

    LuaRef& get_ref(std::string rname);
protected:

private:
    ScriptSystem();

    bool active;
    lua_State* L;
    void initialize();

    static ScriptSystem _instance;

    std::unordered_map<std::string, LuaRef> references;
};

#endif // SCRIPTSYSTEM_H
