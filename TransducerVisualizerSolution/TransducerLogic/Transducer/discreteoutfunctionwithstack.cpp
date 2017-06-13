#include "discreteoutfunctionwithstack.h"

DiscreteOutFunctionWithStack::DiscreteOutFunctionWithStack()
{

}

bool DiscreteOutFunctionWithStack::hasEpsilonMove(std::string state, char stack) const
{
    for(auto x: output)
    {
        State_Desc state_from;
        Stack_Top stack_top;
        Input input;
        std::tie(state_from, stack_top, input) = x.first;
        if(state_from == state && (input == '#' || input == '_') && (stack_top == stack || stack_top == '_'))
            return true;
    }
    return false;
}

void DiscreteOutFunctionWithStack::addOutput(std::tuple<State_Desc, Input, Stack_Top> from, std::string output_)
{
    if(output.find(from) != output.end())
        std::cerr<<"Multiple definition of transition from in sigma function!\n";
    output[from] = output_;
}

void DiscreteOutFunctionWithStack::operator()(std::string state_from, char input, char stack_top)
{
    std::tuple<State_Desc, Input, Stack_Top> prop[] = {std::make_tuple(state_from, input, stack_top),
                   std::make_tuple(state_from, input, '_'),
                   std::make_tuple(state_from, '_', stack_top),
                   std::make_tuple(state_from, '_', '_'),
                   std::make_tuple("_", '_', '_')};
    for(auto t: prop)
        if(output.find(t) != output.end())
        {
            for(auto c: output[t])
                if(c == '$')
                   out += input;
                else if(c == '%')
                {
                    if(stack_top != '#')//end of stack
                        out += stack_top;
                    else
                    {
                        std::cerr<<"Are you sure to rewrite symbol from empty stack?\n";
                    }
                }
                else
                  out += c;
            return ;
        }
    std::cerr<<"Warning! Didn't define what to do in "<<state_from<<" x "<<input<<" x "<<stack_top<<"\n";

}
