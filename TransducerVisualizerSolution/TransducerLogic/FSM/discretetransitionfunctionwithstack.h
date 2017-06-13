#ifndef DISCRETETRANSITIONFUNCTIONWITHSTACK_H
#define DISCRETETRANSITIONFUNCTIONWITHSTACK_H
#include "discretetransitionfunction.h"
typedef std::string State_Desc;
typedef char Stack_Top;
typedef char Input;
struct DiscreteTransitionFunctionWithStack : public TransitionFunction
{
    DiscreteTransitionFunctionWithStack();
    bool hasEpsilonMove(std::string state, char stack) const override;
    virtual State operator()(const State& s, Input c) override;
    void setStackTransition(std::tuple<State_Desc, Stack_Top, Input>, std::string state, std::string stack_command);
    std::vector<std::pair<char, std::string>> possibilites(std::string) override;
private:
    std::map<std::tuple<State_Desc, Stack_Top, Input>, std::string> stack_transition;//stack commands
    std::map<std::tuple<State_Desc, Stack_Top, Input>, std::string> transition;
    std::map<std::pair<State_Desc, Input>, std::pair<std::string, std::string> > special_transitions;
    bool validate(std::string);
    void runStackCommand(State& s, std::string command, char c);
};

#endif // DISCRETETRANSITIONFUNCTIONWITHSTACK_H
