#ifndef DISCRETETRANSITIONFUNCTION_H
#define DISCRETETRANSITIONFUNCTION_H
#include "transitionfunction.h"
#include "state.h"
#include <map>
class DiscreteTransitionFunction : public TransitionFunction
{
    std::map<std::pair<std::string, char>, std::string> transition;
public:
    DiscreteTransitionFunction();
    virtual State operator()(const State& s, char c);
    void setTransition(std::pair<std::string, char>, std::string);
};

DiscreteTransitionFunction::DiscreteTransitionFunction()
{

}

State DiscreteTransitionFunction::operator()(const State& s, char c)
{
    if(transition.find(std::make_pair(s,c)) != transition.end())
        return transition[std::make_pair(s, c)];
    else
    {
        assert(transition.find(std::make_pair(s, '_')) != transition.end());
        return transition[std::make_pair(s, '_')];
    }
}

void DiscreteTransitionFunction::setTransition(std::pair<std::string, char> from, std::string to)
{
    if(transition.find(from) != transition.end())
    {
        if(transition[from] == to)
            std::cerr<<"Warning! Duplicate definition of transition ("<<from.first<<", "<<from.second<<")"<<std::endl;
        else
        {
            std::cerr<<"Error while reading discreteTransitionFunction description\n";
            std::cerr<<"Multiple definitions of transition from ("<<from.first<<", "<<from.second<<") to "<<to<<std::endl;
            exit(1);
        }
    }
    transition[from] = to;
}
#endif // DISCRETETRANSITIONFUNCTION_H
