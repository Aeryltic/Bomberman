#include "Action.h"

#include <functional>

#include <Entity.h>
#include <Components.h>

#include <string>
#include <fstream>
#include <streambuf>

#include "json.hpp"

///STATIC
std::unordered_map<std::string, Action> Action::actions;
//std::type_index Action::void_index = tindex(void);

using json = nlohmann::json;

void Action::init_actions() /// to zaimplementować poprzez skrypty
{
    std::ifstream t("data/actions.json");
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    json j = json::parse(str);

    for(auto a : j) {
        Action action(a["name"], a["cost"], a["duration"], a["target"]);
        for(auto p: a["preconditions"]) {
            action.add_precondition(p[0],p[1]);
        }
        for(auto e: a["effects"]) {
            action.add_effect(e[0],e[1]);
        }
        actions.insert({action.name, action});
    }
}

Action Action::get_action(std::string name)
{
    auto f = actions.find(name);
    if(f==actions.end())
    {
        throw std::runtime_error("bad action name");
    }
    return f->second;
}
/// NIE-STATIC
Action::Action(std::string name, int cost, unsigned duration, std::string target_name): name(name), cost(cost), duration(duration), target_name(target_name)
{
    needs_target = (target_name != "");
    start_tick = 0;
}
Action::~Action()
{
    //dtor
}

Action& Action::add_precondition(std::string name, bool value)
{
    precondition.add(name, value);
//    preconditions.insert({name, value});
    return *this;
}
Action& Action::remove_precondition(std::string name)
{
    precondition.remove(name);
//    preconditions.erase(name);
    return *this;
}
Action& Action::add_effect(std::string name, bool value)
{
    effect.add(name, value);
//    effects.insert({name, value});
    return *this;
}
Action& Action::remove_effect(std::string name)
{
    effect.remove(name);
//    effects.erase(name);
    return *this;
}

bool Action::is_doable(const WorldState &ws)
{
    //printf("\"%s\": checking doability on \n\tworldstate: %s\n\tneeded %s\n", name.c_str(), ws.repr().c_str(), precondition.repr().c_str());
    for(auto v : precondition.attrs)
    {
        auto f = ws.attrs.find(v.first);
        if(f == ws.attrs.end() || f->second != v.second)
        {
            //printf("  not passed\n");
            return false;
        }
    }
    //printf("  passed\n");
    return true;
}

WorldState Action::act_on(WorldState ws)
{
    for(auto p : effect.attrs)
    {
        ws[p.first] = p.second;
    }
    return ws;
}

bool Action::find_target(std::unordered_map<std::string, std::vector<std::weak_ptr<Entity>>>& targets)
{
    //printf("looking for targets\n");
    std::weak_ptr<Entity> closest;
    double dist = 0;
    auto opf = owner.lock()->get<CPhysicalForm>();
    if(opf)
    {
        for(auto target: targets[target_name])
        {
            //printf("+");
            if(!target.expired())
            {
                auto pf = target.lock()->get<CPhysicalForm>();
                if(pf)
                {
                    if(closest.expired())
                    {
                        closest = target;
                        dist = opf->pos.dist(pf->pos);
                    }
                    else
                    {
                        double temp = opf->pos.dist(pf->pos);
                        if(temp < dist)
                        {
                            closest = target;
                            dist = temp;
                        }
                    }
                }
            }
            //else printf("possible target expired!\n");
        }
        //printf("\n");
    }
    if(closest.expired())
    {
        //printf("couldn't find a target...");
        return false;
    }
    //printf("target found!\n");
    target = closest;
    return true;
}

void Action::reset()
{
    start_tick = 0;
    target.reset();
}

bool Action::perform()
{
    if(start_tick == 0)
    {
        start_tick = SDL_GetTicks();
    }
    if(SDL_GetTicks() >= start_tick + duration)
    {
        // tu się odpali jakiś przypisany skrypt...
        reset();
        return true;
    }
    return false;
}

bool Action::is_in_range(){return needs_target ? (has_target() ? (owner.lock()->get<CPhysicalForm>()->pos.dist(target.lock()->get<CPhysicalForm>()->pos) <= 10) : false) : true;}

