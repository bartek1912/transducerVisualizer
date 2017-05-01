#ifndef DISCRETEOUTFUNCTION_H
#define DISCRETEOUTFUNCTION_H
#include "outfunction.h"
#include <map>

struct DiscreteOutFunction : public OutFunction
{
    DiscreteOutFunction();
    void addOutput(std::pair<std::string, char>, std::string);
    void setAsDefault(std::string);
    virtual void operator()(std::string, char c);
protected:
    std::map<std::pair<std::string,char>, std::string> output;
    std::string default_out;
};

#endif // DISCRETEOUTFUNCTION_H
