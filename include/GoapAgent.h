#ifndef GOAPAGENT_H
#define GOAPAGENT_H

#include <unordered_map>
#include <memory>
#include <list>
#include <stack>

//#include "Components.h"
#include "Component.h"
#include "FSMState.h"
#include "WorldState.h"
#include "Action.h"

class GoapAgent : public Component {
    friend class PerformActionState;
public:
    GoapAgent();
    virtual ~GoapAgent();

    void add_action(Action* a);
    void remove_action(std::string name);

    void set_state(std::string name, bool value);
    WorldState& get_world_state();

    std::unordered_map<std::string, Action*>& get_actions();
//    bool has_plan() const;
//    void set_plan(std::list<Action*> plan);

    WorldState find_goal();

    void scan_world();

    void add_goal(std::string goal_name, bool goal_state, unsigned priority);

    void update(int ms) {
        states.top()->update(ms);
    }

    int get_action_perform_time();

    /// FSM
    template<typename T, class ... Args>
    void push_state(Args && ... args);

    template<typename T, class ... Args>
    void replace_state(Args && ... args);

    void pop_state();

protected:
//    FSM fsm;
    WorldState ws;
    std::unordered_map<std::string, Action*> available_actions; /// to też nie tak, a raczej tymi "paczkami"
    std::list<std::pair<unsigned, std::pair<std::string, bool>>> goals; // <priority, <goal_name, goal_state>>
//    std::list<Action*> current_actions; /// to tu nie powinno być, ale w PerformActionState - żeby np. w trakcie wykonywania jednego planu zaplanować coś nowego, wykonać to a potem wrócić do starego planu

    /// FSM
    std::stack<std::unique_ptr<FSMState>> states;
};


template<typename T, class ... Args>
void GoapAgent::push_state(Args && ... args) {
    states.push(std::make_unique<T>(this, states.empty() ? nullptr : states.top().get(), args...));
}

template<typename T, class ... Args>
void GoapAgent::replace_state(Args && ... args) {
    states.pop();
    states.push(std::make_unique<T>(this, states.empty() ? nullptr : states.top().get(), args...));
}
#endif // GOAPAGENT_H
