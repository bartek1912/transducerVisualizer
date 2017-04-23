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
public:
    FSM();
    friend std::istream&    operator <<(std::istream& i, FSM& f)
    {
        std::string s;
        i>>s;
        f.process(s, [](const State&, char){});
        return i;
    }
    void process(std::string s, std::function<void(const State&, char)> callback);
};


#endif // FSM_H
