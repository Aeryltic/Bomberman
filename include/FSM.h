#ifndef FSM_H
#define FSM_H

#include <memory>
#include <stack>

class GoapAgent;
class FSMState;

class FSM {
public:
    FSM(GoapAgent *agent);
    virtual ~FSM();

    void update(int ms);
    void push_state(std::unique_ptr<FSMState> state);
    void pop_state();

    GoapAgent *get_agent() {
        return agent;
    }

private:
    GoapAgent *agent;
    std::stack<std::unique_ptr<FSMState>> states;
};

#endif // FSM_H
