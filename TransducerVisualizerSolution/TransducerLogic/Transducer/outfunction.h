#ifndef OUTFUNCTION_H
#define OUTFUNCTION_H
#include <vector>
#include "FSM/state.h"
struct OutFunction
{
    virtual void operator()(const State& s, const char& c);
protected:
    std::vector<char> out;
};

#endif // OUTFUNCTION_H
