#ifndef ACTION_H
#define ACTION_H

#include <unordered_map>
#include <string>

class Action
{
public:
    Action(std::string name, int cost);
    virtual ~Action();

    void add_precondition(std::string name, bool value);
    void remove_precondition(std::string name);
    void add_effect(std::string name, bool value);
    void remove_effect(std::string name);

protected:
    std::string name;
    int cost;

    std::unordered_map<std::string, bool> preconditions;
    std::unordered_map<std::string, bool> effects;
};

#endif // ACTION_H
