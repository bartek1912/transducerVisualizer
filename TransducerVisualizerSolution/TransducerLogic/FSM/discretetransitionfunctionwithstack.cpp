#include "discretetransitionfunctionwithstack.h"
#include <assert.h>

DiscreteTransitionFunctionWithStack::DiscreteTransitionFunctionWithStack()
{

}

bool DiscreteTransitionFunctionWithStack::hasEpsilonMove(std::string state, char stack) const
{
    for(auto x: transition)
    {
        State_Desc state_from;
        Stack_Top stack_top;
        Input input;
        std::tie(state_from, stack_top, input) = x.first;
        if(state_from == state && input == '#' && (stack_top == stack || stack_top == '_'))
            return true;
    }
    return false;
}
State DiscreteTransitionFunctionWithStack::operator()(const State& s, char c)
{
    std::vector<std::tuple<State_Desc, Stack_Top, Input>> temporary;
    for(auto x: special_transitions)
    {
        auto from = x.first;
        auto to = x.second;
        if(transition.find(std::make_tuple(from.first, c, from.second)) == transition.end())
        {
            temporary.push_back(std::make_tuple(from.first, c, from.second));
            transition[std::make_tuple(from.first, c, from.second)] = to.first;
            stack_transition[std::make_tuple(from.first, c, from.second)] = to.second;
        }
    }
    std::tuple<State_Desc, Stack_Top, Input> prop[] = {std::make_tuple(s.toString(), s.top(), c),
                   std::make_tuple(s.toString(), '_', c),
                   std::make_tuple(s.toString(), s.top(), '_'),
                   std::make_tuple(s.toString(), '_', '_')};
    //change state
    State res = s;
    bool found = false;
    for(auto p: prop)
        if(transition.find(p) != transition.end() && !found)
        {
            found = true;
            res.changeState(transition[p]);
        }
    if(found == false)
    {
        std::cerr<<"Don't know what to do in state "<<s.toString()<<" with char "<<c<<"\n";
        res = s;
    }
    //change stack
    found = false;
    for(auto p: prop)
        if(stack_transition.find(p) != stack_transition.end() && !found)
        {
            found = true;
            runStackCommand(res, stack_transition[p], c);
        }
    if(found == false)
    {
        State_Desc state_from;
        Stack_Top stack_top;
        Input input;
        std::tie(state_from, stack_top, input) = prop[0];
        std::cerr<<"Don't know what to do with stack in state "<<s.toString()<<" top of stack "<<s.top()<<" and char "<<c<<"\n";
        std::cerr<<"Have:\n";
        std::cerr<<state_from<<", "<<stack_top<<", "<<input<<"\n";
        std::cerr<<"Known actions:\n";
        for(auto x: stack_transition)
        {
            std::tie(state_from, stack_top, input) = x.first;
            std::cerr<<state_from<<", "<<stack_top<<", "<<input<<" -> "<<x.second<<"\n";
        }
    }
    for(auto x: temporary)
    {
        transition.erase(x);
        stack_transition.erase(x);
    }
    return res;
}

void DiscreteTransitionFunctionWithStack::runStackCommand(State& s, std::string command, char in)
{
    char c = command[0];
    command = command.substr(1);
    switch(c)
    {
    case '_': break;//no operation
    case 'v':
    case 'V': //remove from stack
    {
        int num = command.size() == 0 ? 1 : atoi(command.c_str());
        while(num--)
            s.pop();
        break;
    }
    case '^'://add to stack
        if(command == "$")
            s.push(in);
        else
            s.push(command);
        break;
    case '~'://empty stack
        for(;!s.empty(); s.pop());
        break;
    }
}

std::vector<std::pair<Input, State_Desc>> DiscreteTransitionFunctionWithStack::possibilites(std::string state)
{
    std::vector<std::pair<char, std::string>> res;
    assert(!transition.empty());
    for(auto t: transition)
    {
        auto& x = t.first;
        auto& y = t.second;
        State_Desc state_from;
        Stack_Top stack_top;
        Input input;
        std::tie(state_from, stack_top, input) = x;
        if(state_from == state)
        {
            res.push_back(std::make_pair(input, y));
        }
    }
    std::sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}
void DiscreteTransitionFunctionWithStack::setStackTransition(std::tuple<State_Desc, Stack_Top, Input> from, std::string state_to, std::string stack_command)
{
    State_Desc state_from;
    Stack_Top stack_top;
    Input input;
    std::tie(state_from, stack_top, input) = from;
    if(!validate(stack_command))
        std::cerr<<"Stack command should start with v, ^, ~ or _, but given "<<stack_command<<"\n";
    else if(stack_top == '$')
        special_transitions[std::make_pair(state_from, input)]   = std::make_pair(state_to, stack_command);
    else
    {
        if(stack_transition.find(from) != stack_transition.end())
        {
            if(stack_transition[from] == stack_command)
                std::cerr<<"Warning! Duplicate definition of transition for stack ("<<state_from<<", "<<stack_top<<", "<<input<<")"<<std::endl;
            else
            {
                std::cerr<<"Error while reading discreteTransitionFunction description\n";
                std::cerr<<"Multiple definitions of transition for stack from ("<<state_from<<", "<<stack_top<<", "<<input<<") to "<<stack_command<<std::endl;
                exit(1);
            }
        }
        stack_transition[from] = stack_command;
        if(transition.find(from) != transition.end())
        {
            if(transition[from] == state_to)
                std::cerr<<"Warning! Duplicate definition of transition ("<<state_from<<", "<<stack_top<<", "<<input<<")"<<std::endl;
            else
            {
                std::cerr<<"Error while reading discreteTransitionFunction description\n";
                std::cerr<<"Multiple definitions of transition for stack from ("<<state_from<<", "<<stack_top<<", "<<input<<") to "<<state_to<<std::endl;
                exit(1);
            }
        }
        transition[from] = state_to;
    }
}

bool DiscreteTransitionFunctionWithStack::validate(std::string str)
{
    return str.size() > 0 && (str[0] == 'v' || str[0] == '^' || str[0] == '~' || str[0] == '_');
}
