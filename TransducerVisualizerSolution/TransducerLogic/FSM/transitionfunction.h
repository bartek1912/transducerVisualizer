#ifndef TRANSITIONFUNCTION_H
#define TRANSITIONFUNCTION_H
#include "state.h"
#include <iostream>
class TransitionFunction
{
//    TransitionFunction(const TransitionFunction& f);
//    void operator = (const TransitionFunction& f);
public:
    TransitionFunction();
    virtual bool hasEpsilonMove(std::string state, char stack) const = 0;
    virtual State operator()(const State& s, char c) = 0;
    virtual std::vector<std::pair<char, std::string>> possibilites(std::string) = 0;
};

/*
template<typename char>
State TransitionFunction<char>::operator()(const State& s, char)
{
    return s;
}*/

#endif // TRANSITIONFUNCTION_H
