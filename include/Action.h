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

struct ActionExecutor { /// wrapper dla procedury egzekucji akcji - potem tu będą skrypty pewnie
    using exec_fun = LuaRef;//std::function<bool(Entity*, Entity*)>;

    ActionExecutor() : fun(fun0) {}
    ActionExecutor(exec_fun fun) : fun(fun) {}

    void operator()(Entity* doer, Entity* target) {
        fun(doer, target);
    }

    void set(exec_fun fun) {
        this->fun = fun;
    }

private:
    exec_fun fun;

    const static exec_fun fun0;
};
//-------------------------------------------------------------------------------------------------
class Action {
public:
    Action() {}
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
    int get_cost() {
        return cost;
    }
    bool does_need_target() {
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
    bool perform();
    void reset();

    void set_exec(ActionExecutor::exec_fun fun){
        execute.set(fun);
    }

    bool is_being_performed(){return start_tick!=0;}


    static void init_actions();
    static Action get_action(std::string name);
    //static std::type_index void_index;

protected:
    std::string name;
    int cost;
    unsigned duration;
    std::string target_name;
    bool needs_target;

    unsigned start_tick;

    WorldState precondition;
    WorldState effect;

    ActionExecutor execute; /// to powinien być jakiś pointer

    //std::weak_ptr<Entity> owner;
    GoapAgent* agent;
    std::weak_ptr<Entity> target;

    static std::unordered_map<std::string, Action> actions;
};

#endif // ACTION_H
