#ifndef DISCRETETRANSITIONFUNCTION_H
#define DISCRETETRANSITIONFUNCTION_H
#include "transitionfunction.h"
#include "state.h"
#include <vector>
#include <map>
#include <algorithm>
class DiscreteTransitionFunction : public TransitionFunction
{
    std::map<std::pair<std::string, char>, std::string> transition;
public:
    DiscreteTransitionFunction();
    virtual State operator()(const State& s, char c) override;
    std::vector<std::pair<char, std::string>> possibilites(std::string s) override;
    void setTransition(std::pair<std::string, char>, std::string);
};

#endif // DISCRETETRANSITIONFUNCTION_H
