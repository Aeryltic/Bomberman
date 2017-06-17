#ifndef ACTION_H
#define ACTION_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include "WorldState.h"
#include "ScriptSystem.h"
class GoapAgent;
class Entity;

struct ActionExecutor {
    using exec_fun = LuaRef;

    ActionExecutor() :
        exec(ScriptSystem::instance()->state()),
        running(false) {}

    bool operator()(Entity* doer, Entity* target, int ms_passed) {
        ms_running += ms_passed;
        bool result = false;
        try {
            if(target != nullptr) result = exec(doer, target, ms_running);
            else result = exec(doer, ms_running);
        } catch (LuaException const& e) {
            printf("%s\n", e.what());
            result = false;
        }
        return result;
    }

    void set(exec_fun fun) {
        exec = fun;
    }

    void start() {
        ms_running = 0;
        running = true;
    }

    void stop() {
        running = false;
    }

    bool is_running() {
        return running;
    }

private:
    exec_fun exec;

    bool running;
    int ms_running;

};

//-------------------------------------------------------------------------------------------------
class Action {
    using PreconditionScanner = LuaRef;
public:
    Action(std::string name, int cost, std::string target_name="");
    virtual ~Action();

    Action& add_precondition(std::string name, bool value);
    Action& remove_precondition(std::string name);
    Action& add_effect(std::string name, bool value);
    Action& remove_effect(std::string name);

    bool is_doable(const WorldState &ws);

    WorldState act_on(WorldState ws); /// to raczej powininno być tylko dla planisty

    const std::string& get_name() const {
        return name;
    }
    int get_cost() const {
        return cost;
    }
    bool does_need_target() const {
        return needs_target;
    }
    bool has_target();

    void set_agent(GoapAgent* agent);
    Entity* get_owner();

    bool is_in_range();

    std::weak_ptr<Entity> get_target() {
        return target;
    }

    bool find_target(std::unordered_map<std::string, std::vector<std::weak_ptr<Entity>>>& targets);
    bool perform(int ms_passed);
    void reset();

    void set_exec(ActionExecutor::exec_fun fun) {
        execute.set(fun);
    }

    void set_scanner(PreconditionScanner scanner) {
        this->scanner = scanner;
    }

    void scan() {
        scanner(get_owner());
    }

    void start() {execute.start();}
    bool is_performed() {return execute.is_running();}

    static void init_actions();
    static Action get_action(std::string name);

protected:
    std::string name;
    int cost;
    std::string target_name;
    bool needs_target;

    WorldState precondition;
    WorldState effect;

    PreconditionScanner scanner;
    ActionExecutor execute;

    GoapAgent* agent;
    std::weak_ptr<Entity> target;

    /// STATIC
    static std::unordered_map<std::string, Action> actions;
};

#endif // ACTION_H
