#include "discreteoutfunction.h"
#include <iostream>

DiscreteOutFunction::DiscreteOutFunction():__out("")
{

}

void DiscreteOutFunction::operator()(std::string state, char c)
{
    std::string res = "";
    if(output.find(std::make_pair(state, c)) != output.end())
    {
        res = output[std::make_pair(state, c)];
        std::cerr<<"For state "<<state<<" and char "<<c<<" out: "
                <<res<<"\n";
    }
    else if(output.find(std::make_pair(state, '_')) != output.end())
        res = output[std::make_pair(state, '_')];
    if(res == "identity" || res == "$")
        out.push_back(c);
    else if(res != "none")
        for(char cX: res)
            if(cX == '$')
                out.push_back(c);
            else
                out.push_back(cX);
}

void DiscreteOutFunction::setAs_(std::string def)
{
    __out = def;
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

