#ifndef FSM_H
#define FSM_H

//#include <memory>
//#include <stack>
//
//class GoapAgent;
//class FSMState;
//
//class FSM {
//public:
////    FSM(GoapAgent *agent);
////    virtual ~FSM();
////
////    void update(int ms);
////
////    template<typename T, class ... Args>
////    void push_state(Args && ... args);
////
////    template<typename T, class ... Args>
////    void replace_state(Args && ... args);
//////    void push_state(std::unique_ptr<FSMState> state*);
////
////    void pop_state();
////
////    GoapAgent *get_agent() {
////        return agent;
////    }
//
//private:
//    GoapAgent *agent;
//    std::stack<std::unique_ptr<FSMState>> states;
//};
//
//template<typename T, class ... Args>
//void FSM::push_state(Args && ... args) {
//    states.push(std::make_unique<T>(this, args...));
//}
//
//template<typename T, class ... Args>
//void FSM::replace_state(Args && ... args) {
//    states.pop();
//    states.push(std::make_unique<T>(this, args...));
//}
#endif // FSM_H
