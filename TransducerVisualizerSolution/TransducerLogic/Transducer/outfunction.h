#ifndef OUTFUNCTION_H
#define OUTFUNCTION_H
#include <vector>
#include <iostream>
#include "FSM/state.h"
struct OutFunction
{
    virtual void operator()(std::string s, char c) = 0;
protected:
    std::vector<char> out;
    friend std::ostream& operator << (std::ostream& o, const OutFunction& t)
    {
        for(auto x: t.out)
            o<<x;
        return o;
    }
};

#endif // OUTFUNCTION_H
