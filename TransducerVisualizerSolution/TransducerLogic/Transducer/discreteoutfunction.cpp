#include "discreteoutfunction.h"
#include <iostream>

DiscreteOutFunction::DiscreteOutFunction():default_out("")
{

}

void DiscreteOutFunction::operator()(std::string s, char c)
{
    if(output.find(std::make_pair(s, c)) != output.end())
        for(char c: output[std::make_pair(s, c)])
            out.push_back(c);
    else if(output.find(std::make_pair(s, '_')) != output.end())
    {
        std::string res = output[std::make_pair(s, '_')];
        for(char c: res)
            out.push_back(c);
    }
}

void DiscreteOutFunction::setAsDefault(std::string def)
{
    default_out = def;
}

void DiscreteOutFunction::addOutput(std::pair<std::string, char> p, std::string o)
{
    if(output.find(p) != output.end())
    {
        if(output[p] == o)
            std::cerr<<"Warning! Multiple definition of the same sigma transition: "<<p.first<<","<<p.second<<" -> "<<o<<"\n";
        else
        {
            std::cerr<<"Warning! Multiple definition of the same sigma transition: "<<p.first<<","<<p.second<<" -> "<<o<<" vs "<<output[p]<<"\n";
            exit(1);
        }
    }
    output[p] = o;
}

