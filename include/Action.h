#ifndef ACTION_H
#define ACTION_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include "WorldState.h"

class Entity;
class LuaRef;

class Action
{
public:


    Action(){}
    Action(std::string name, int cost, unsigned duration, std::string target_name="");
    virtual ~Action();

    Action& add_precondition(std::string name, bool value);
    Action& remove_precondition(std::string name);
    Action& add_effect(std::string name, bool value);
    Action& remove_effect(std::string name);

    bool is_doable(const WorldState &ws);

    WorldState act_on(WorldState ws); /// to raczej powinien być test po wykonaniu akcji - to tylko dla planisty

    const std::string& get_name() const {return name;}
    int get_cost(){return cost;}
    bool does_need_target(){return needs_target;}
    bool has_target(){return !target.expired();}

    void set_owner(std::weak_ptr<Entity> owner) {this->owner = owner;}

    bool is_in_range();

    std::weak_ptr<Entity> get_target(){return target;}
//    void set_target(std::weak_ptr<Entity> target){
//        this->target = target;
//    }
    bool find_target(std::unordered_map<std::string, std::vector<std::weak_ptr<Entity>>>& targets);
    bool perform();
    void reset();
   // void set_owner(std::weak_ptr<Entity> owner){this->owner = owner;}


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

    //std::weak_ptr<Entity> owner;

    WorldState precondition;
    WorldState effect;

    //shared_ptr<LuaRef> preform_script;

    std::weak_ptr<Entity> owner;
    std::weak_ptr<Entity> target;

    static std::unordered_map<std::string, Action> actions;
};

#endif // ACTION_H
