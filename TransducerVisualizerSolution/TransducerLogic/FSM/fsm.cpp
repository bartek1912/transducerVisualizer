#include "fsm.h"
FSM::FSM():
    delta(NULL),
    initial(""),
    actual("")
{
}
void FSM::reset()
{
    actual = initial;
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

std::vector<std::string> FSM::states_description() const
{
    return s.description();
}
std::vector<std::pair<std::string, std::string> > FSM::edge_description() const
{
    std::vector<std::pair<std::string, std::string> > res;
    for(auto from: states_description())
        for(auto to: (*delta).possibilites(from))
            res.push_back(std::make_pair(from, to));
    return res;
    /*return {std::make_pair("A", "X"),
                std::make_pair("Y", "X"),
                std::make_pair("AA", "B"),
                std::make_pair("A", "AA"),
                std::make_pair("C", "D"),
                std::make_pair("E", "F"),
                std::make_pair("E", "D"),
                std::make_pair("E", "X")};*/
}
