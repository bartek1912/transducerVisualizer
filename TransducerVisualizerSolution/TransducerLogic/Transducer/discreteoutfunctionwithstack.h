#ifndef DISCRETEOUTFUNCTIONWITHSTACK_H
#define DISCRETEOUTFUNCTIONWITHSTACK_H
#include "outfunction.h"
#include <map>
#include <algorithm>

typedef std::string State_Desc;
typedef char Stack_Top;
typedef char Input;

struct DiscreteOutFunctionWithStack : public OutFunction
{
    DiscreteOutFunctionWithStack();
    void addOutput(std::tuple<State_Desc, Input, Stack_Top>, std::string);
    void operator()(std::string, char c, char stack) override;
    bool hasEpsilonMove(std::string state, char stack) const override;
protected:
    std::map<std::tuple<State_Desc, Input, Stack_Top>, std::string> output;
};
#endif // DISCRETEOUTFUNCTIONWITHSTACK_H
