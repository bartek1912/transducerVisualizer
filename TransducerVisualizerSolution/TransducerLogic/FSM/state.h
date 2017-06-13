#ifndef STATE_H
#define STATE_H
#include <string>
#include "JSON/jsonelement.h"

class State
{
    std::string content;
    std::string stack;
public:
    State(std::string s, std::string stack=""):content(s), stack(stack){}
    void changeState(std::string s2)
    {
        content = s2;
    }

    operator std::string() const
    {
        return content;
    }
    std::string toString() const
    {
        return static_cast<std::string>(*this);
    }
    std::string getStack() const
    {
        return stack;
    }
    void push(std::string t)
    {
        stack += t;
    }
    void push(char c)
    {
        stack += c;
    }
    char top() const
    {
        return stack.empty() ? '#' : stack.back();
    }
    void pop()
    {
        if(stack.size() > 0)
            stack.pop_back();
    }
    bool empty()
    {
        return stack.empty();
    }

    //virtual operator ()(const JSONElement&) = 0; TODO discrete state class
};

#endif // STATE_H
