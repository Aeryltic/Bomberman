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

class ScriptSystem {
public:
    ScriptSystem();
    virtual ~ScriptSystem();

    void update(int ms);
    bool isActive() {
        return active;
    }

    lua_State* state() {
        return L;
    }
    std::string execute(const std::string &command);

    LuaRef get(std::string rname);

    bool do_file(const std::string& filename);
protected:

private:
    bool active;
    lua_State* L;
    void initialize();

    std::unordered_map<std::string, LuaRef> references;
};

#endif // SCRIPTSYSTEM_H
