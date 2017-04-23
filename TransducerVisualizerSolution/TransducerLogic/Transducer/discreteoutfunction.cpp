#include "discreteoutfunction.h"
#include <iostream>

DiscreteOutFunction::DiscreteOutFunction()
{

}

void OutFunction::operator()(const State&, const char& c)
{}
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

