#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include <LuaBridge.h>
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class Console;
class GameInstance;
class DisplayManager;

using namespace luabridge;
using namespace std;
class ScriptSystem
{
    public:
        ScriptSystem(GameInstance *gameInstance);
        virtual ~ScriptSystem();
        void update(int ms);
        bool isActive(){return active;}
        void registerEverything();
        lua_State* getLuaState(){return L;}
        string execute(const string &command);
    protected:

    private:
        bool active;
        lua_State* L;
        DisplayManager *displayManager;
        void initialize();
};

#endif // SCRIPTSYSTEM_H
