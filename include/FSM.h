#ifndef FSM_H
#define FSM_H

#include <memory>
#include <stack>

class GoapAgent;
class FSMState;

class FSM
{
public:
    FSM(GoapAgent *agent);
    virtual ~FSM();

    void update();
    void push_state(std::unique_ptr<FSMState> state);
    void pop_state();

protected:

private:
    GoapAgent *agent;
    std::stack<std::unique_ptr<FSMState>> states;
};

#endif // FSM_H
