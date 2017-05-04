#include "discretetransitionfunction.h"
#include <assert.h>
#include <algorithm>


DiscreteTransitionFunction::DiscreteTransitionFunction()
{

}


State DiscreteTransitionFunction::operator()(const State& s, char c)
{
    if(transition.find(std::make_pair(s,c)) != transition.end())
        return transition[std::make_pair(s, c)];
    else
    {
        assert(transition.find(std::make_pair(s, '_')) != transition.end());
        return transition[std::make_pair(s, '_')];
    }
}

std::vector<std::string> DiscreteTransitionFunction::possibilites(std::string s)
{
    std::vector<std::string> res;
    assert(!transition.empty());
    //auto end = transition.upper_bound(std::make_pair(s, 255));
    //for(auto beg = transition.upper_bound(std::make_pair(s, 0)); beg != end; beg++)
    //    res.push_back(beg->second);
    for(char c = 1; c != 0; c++)//TODO change
        if(transition.find(std::make_pair(s, c)) != transition.end())
            res.push_back(transition[std::make_pair(s,c)]);
    std::sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

void DiscreteTransitionFunction::setTransition(std::pair<std::string, char> from, std::string to)
{
    if(transition.find(from) != transition.end())
    {
        if(transition[from] == to)
            std::cerr<<"Warning! Duplicate definition of transition ("<<from.first<<", "<<from.second<<")"<<std::endl;
        else
        {
            std::cerr<<"Error while reading discreteTransitionFunction description\n";
            std::cerr<<"Multiple definitions of transition from ("<<from.first<<", "<<from.second<<") to "<<to<<std::endl;
            exit(1);
        }
    }
    transition[from] = to;
}
