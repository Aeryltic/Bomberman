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

struct ActionExecutor { /// to chyba powoduje HeapCorruptionException
    using exec_fun = LuaRef;//std::function<bool(Entity*, Entity*)>;
    using fun_init = LuaRef;//std::function<bool(Entity*, Entity*)>;

    ActionExecutor() :
        f_init(fun0),
        exec(ScriptSystem::getInstance()->getLuaState()),
        running(false) {}
    ActionExecutor(const fun_init& init) :
        f_init(init),
        exec(ScriptSystem::getInstance()->getLuaState()),
        running(false) {}

    bool operator()(Entity* doer, Entity* target, int ms_passed) {
        return exec(doer, target, ms_passed); // uważać z tym, bo nie chcę dodawać tu zbędnego if'a
    }

    void set(fun_init init){
        f_init = init;
    }

    void start() {
        exec = f_init();
        running = true;
    }

    void stop() {
        running = false;
    }

    bool is_running() {
        return running;
    }

private:
    fun_init f_init;
    exec_fun exec;

    bool running;

    const static fun_init fun0;
};
//-------------------------------------------------------------------------------------------------
class Action {
public:
//    Action() {}
    Action(std::string name, int cost, unsigned duration, std::string target_name="");
    virtual ~Action();

    Action& add_precondition(std::string name, bool value);
    Action& remove_precondition(std::string name);
    Action& add_effect(std::string name, bool value);
    Action& remove_effect(std::string name);

    bool is_doable(const WorldState &ws);

    WorldState act_on(WorldState ws); /// to raczej powinien być test po wykonaniu akcji - tylko dla planisty

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

    void set_exec(ActionExecutor::fun_init fun){
        execute.set(fun);
    }

    void start() {execute.start();}
    bool is_being_performed() {return execute.is_running();}


    static void init_actions();
    static Action get_action(std::string name);
    //static std::type_index void_index;

protected:
    std::string name;
    int cost;
    unsigned duration;
    std::string target_name;
    bool needs_target;

    unsigned start_tick; // nie wiem czy to tak...
    //bool performing;

    WorldState precondition;
    WorldState effect;

    //ActionInitializer a_init;
    ActionExecutor execute; /// to powinien być jakiś pointer

    //std::weak_ptr<Entity> owner;
    GoapAgent* agent;
    std::weak_ptr<Entity> target;

    static std::unordered_map<std::string, Action> actions;
};

#endif // ACTION_H
