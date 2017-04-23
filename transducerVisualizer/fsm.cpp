#include "fsm.h"
FSM::FSM():
    delta(NULL),
    initial(""),
    actual("")
{
}
void FSM::process(std::string s, std::function<void(const State&, char)> callback)
{
    //char::get_next_char()
    for(auto c: s)
    {
        callback(actual, c);
        actual = (*delta)(actual, c);
        std::cerr<<"State: "<<(std::string)(actual)<<"\n";
    }
}
