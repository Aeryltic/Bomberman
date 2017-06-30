#ifndef ACTION_H
#define ACTION_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include "LuaBridge.h"

using namespace luabridge;

#include "ActionExecutor.h"
#include "WorldState.h"

#include "Logs.h"

class AIPackage;
class GoapAgent;
class Entity;

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
    std::string get_target_name() { return target_name;}

    bool perform(Entity* agent, Entity* target, int ms_passed);

    void set_exec(ActionExecutor::ExecScript fun) {
        execute.set(fun);
    }

    void set_scanner(PreconditionScanner scanner) {
        this->scanner = scanner;
    }

    void scan(Entity* agent) {
        scanner(agent);
    }

    /// STATIC
    static void init_actions();
    static void init_action_packs();
    static Action* get_action(std::string name);
    static AIPackage get_ai_package(std::string name);

    static void clear();

protected:
    std::string name;
    int cost;
    std::string target_name;
    bool needs_target;

    WorldState precondition;
    WorldState effect;

    PreconditionScanner scanner;
    ActionExecutor execute;


    /// STATIC
    static std::unordered_map<std::string, Action> actions;
    static std::unordered_map<std::string, AIPackage> ai_packages;
};

#endif // ACTION_H
