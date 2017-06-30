#ifndef ACTIONEXECUTOR_H
#define ACTIONEXECUTOR_H

#include "LuaBridge.h"

using namespace luabridge;

class Entity;

class ActionExecutor {
public:
    using ExecScript = LuaRef;
    ActionExecutor();
    virtual ~ActionExecutor();

    bool operator()(Entity* doer, Entity* target, int ms_passed);

    void set(ExecScript fun);

    void start();
    void stop();

    bool is_running();

    int get_running_time() {return ms_running;}

private:
    ExecScript exec;

    bool running;
    int ms_running; // to powinno być po stronie Lua'y albo wcale
};

#endif // ACTIONEXECUTOR_H
