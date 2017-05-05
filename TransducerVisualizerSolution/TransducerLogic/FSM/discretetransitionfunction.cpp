#include "discretetransitionfunction.h"
#include <assert.h>
#include <algorithm>
#include <iostream>

DiscreteTransitionFunction::DiscreteTransitionFunction()
{

}


State DiscreteTransitionFunction::operator()(const State& s, char c)
{
    if(transition.find(std::make_pair(s,c)) != transition.end())
    {
        auto dest = transition[std::make_pair(s, c)];
        return dest;
    }
    else
    {
        assert(transition.find(std::make_pair(s, '_')) != transition.end());
        auto dest = transition[std::make_pair(s, '_')];
        return dest;
    }
}

std::vector<std::pair<char, std::string>> DiscreteTransitionFunction::possibilites(std::string s)
{
    std::vector<std::pair<char, std::string>> res;
    std::map<std::string, bool> map;
    assert(!transition.empty());
    //auto end = transition.upper_bound(std::make_pair(s, 255));
    //for(auto beg = transition.upper_bound(std::make_pair(s, 0)); beg != end; beg++)
    //    res.push_back(beg->second);
    for(char c = 1; c != 0; c++)//TODO change
    {
        auto p = std::make_pair(s,c);
        if(transition.find(p) != transition.end()
                && map.find(transition[p]) == map.end())
        {
            map[transition[p]] = true;
            res.push_back(std::make_pair(c, transition[std::make_pair(s,c)]));
        }
    }
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
