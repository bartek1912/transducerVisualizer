#include "states.h"

States::States()
{

}

void States::operator () (const JSON::Element& in)
{
    states_space.clear();
    for(const auto& x : in.identifiers())
        states_space.push_back(in[x].toString());//TODO
}

std::vector<std::string> States::description() const
{
    return states_space;
}
