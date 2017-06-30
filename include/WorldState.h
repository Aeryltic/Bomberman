#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include <unordered_map>
class WorldState {
    friend class Action;
public:
    WorldState();
    virtual ~WorldState();

    WorldState& add(std::string name, bool value);
    WorldState& remove(std::string name);

    int distanceTo(const WorldState& other);
    bool fulfills(const WorldState& other) const;
    bool& operator[](std::string s) {
        return attrs[s];
    }
    bool operator==(const WorldState& other) const {
        return attrs == other.attrs;
    }

    std::string repr() const {
        std::string s = "{ ";
        for(auto p: attrs) {
            s += p.first + ": " + (p.second ? "true" : "false") + ", ";
        }
        s += "}";
        return s;
    }
protected:

private:
    std::unordered_map<std::string, bool> attrs;
};

#endif // WORLDSTATE_H
