#ifndef FSM_H
#define FSM_H
#include <functional>
#include <iostream>
#include "transitionfunction.h"
#include "states.h"
#include "state.h"
typedef char Label;
typedef std::string State_desc;
class FSM
{
protected:
    TransitionFunction* delta;
    States               s;
    State                initial, actual;
    virtual void process(char c);
public:
    FSM();
    virtual void reset();
    friend std::istream&    operator <<(std::istream& i, FSM& f)
    {
        std::string s;
        i>>s;
        f.process_dash(s);
        return i;
    }
    void process_dash(std::string s);
    std::vector<std::string> states_description() const;
    std::vector<std::pair<Label, std::pair<State_desc, State_desc>>> edge_description() const;
};


#endif // FSM_H
