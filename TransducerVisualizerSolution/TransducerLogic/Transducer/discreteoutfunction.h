#ifndef DISCRETEOUTFUNCTION_H
#define DISCRETEOUTFUNCTION_H
#include "outfunction.h"
#include <map>

struct DiscreteOutFunction : public OutFunction
{
    DiscreteOutFunction();
    void addOutput(std::pair<std::string, char>, std::string);
protected:
    std::map<std::pair<std::string,char>, std::string> output;
};

#endif // DISCRETEOUTFUNCTION_H
