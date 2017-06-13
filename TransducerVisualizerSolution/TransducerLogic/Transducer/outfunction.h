#ifndef OUTFUNCTION_H
#define OUTFUNCTION_H
#include <vector>
#include <iostream>
#include "FSM/state.h"
struct OutFunction
{
    std::string result();
    virtual void operator()(std::string s, char c, char stack) = 0;
    virtual bool hasEpsilonMove(std::string state, char stack) const = 0;
    void reset();
protected:
    std::string out;
    friend std::ostream& operator << (std::ostream& o, const OutFunction& t)
    {
        return o<<t.out;
    }
public:
};

#endif // OUTFUNCTION_H
