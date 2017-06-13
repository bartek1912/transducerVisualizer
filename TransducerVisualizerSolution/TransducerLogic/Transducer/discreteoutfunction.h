#ifndef DISCRETEOUTFUNCTION_H
#define DISCRETEOUTFUNCTION_H
#include "outfunction.h"
#include <map>

typedef std::string State_Desc;
typedef char Stack_Top;
typedef char Input;
struct DiscreteOutFunction : public OutFunction
{
    DiscreteOutFunction();
    void addOutput(std::pair<std::string, char>, std::string);
    void setAs_(std::string);
    void operator()(std::string, char c, char stack) override;
    virtual bool hasEpsilonMove(std::string state, char stack) const override;
protected:
    std::map<std::pair<std::string,char>, std::string> output;
    std::string __out;
};

#endif // DISCRETEOUTFUNCTION_H
