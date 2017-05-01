#ifndef FSM_H
#define FSM_H
#include <functional>
#include <iostream>
#include "transitionfunction.h"
#include "states.h"
#include "state.h"

class FSM
{
protected:
    TransitionFunction* delta;
    States               s;
    State                initial, actual;
    virtual void process(char c);
public:
    FSM();
    friend std::istream&    operator <<(std::istream& i, FSM& f)
    {
        std::string s;
        i>>s;
        f.process_dash(s);
        return i;
    }
    void process_dash(std::string s);
    std::vector<std::string> states_description();
};


#endif // FSM_H
