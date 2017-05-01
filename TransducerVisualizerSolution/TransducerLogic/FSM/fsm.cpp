#include "fsm.h"
FSM::FSM():
    delta(NULL),
    initial(""),
    actual("")
{
}
void FSM::process_dash(std::string s)
{
    for(auto c: s)
        process(c);
}
void FSM::process(char c)
{
    actual = (*delta)(actual, c);
    std::cerr<<"State: "<<(std::string)(actual)<<"\n";
}

std::vector<std::string> FSM::states_description()
{
    return {"A", "X", "Y", "AA", "B", "C", "D", "E", "F", "G", "H", "I"};
}
