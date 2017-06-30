#include "ActionExecutor.h"

#include "Engine.h"
#include "ScriptSystem.h"

#include "Logs.h"

ActionExecutor::ActionExecutor() :
    exec(Engine::lua()->state()),
    running(false) {
}

ActionExecutor::~ActionExecutor() {
    //dtor
}

bool ActionExecutor::operator()(Entity* doer, Entity* target, int ms_passed) {
    ms_running += ms_passed;
    bool result = false;
    try {
        if(target != nullptr) {
            result = exec(doer, target, ms_running);
        } else {
            result = exec(doer, ms_running);
        }
    } catch(LuaException const& e) {
        logs::log("%s\n", e.what());
        result = false;
    }
    return result;
}

void ActionExecutor::set(ExecScript fun) {
    exec = fun;
}

void ActionExecutor::start() {
    ms_running = 0;
    running = true;
}

void ActionExecutor::stop() {
    running = false;
}

bool ActionExecutor::is_running() {
    return running;
}
