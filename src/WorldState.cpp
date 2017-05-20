#include "WorldState.h"

WorldState::WorldState()
{
    //ctor
}

WorldState::~WorldState()
{
    //dtor
}


WorldState& WorldState::add(std::string name, bool value)
{
    attrs.insert({name, value});
    return *this;
}

WorldState& WorldState::remove(std::string name)
{
    attrs.erase(name);
    return *this;
}

int WorldState::distanceTo(const WorldState& other)
{
    int distance = 0;

    for(auto v : other.attrs)
    {
        auto f = attrs.find(v.first);
        if(f == attrs.end() || f->second != v.second) /// heurystyka wzięta od tamtego gościa
        {
            distance++;
        }
    }
    return distance;
}

bool WorldState::fulfills(const WorldState& other) const /// w praktyce to to samo co distanceTo(other) == 0, ale jednak szybsze
{
    for(auto v : other.attrs)
    {
        auto f = attrs.find(v.first);
        if(f == attrs.end() || f->second != v.second)
        {
            return false;
        }
    }
    return true;
}
