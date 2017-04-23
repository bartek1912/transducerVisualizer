#ifndef STATE_H
#define STATE_H
#include <string>

class State
{
    std::string content;
public:
    State(std::string s):content(s){}
    operator std::string() const
    {
        return content;
    }
};

#endif // STATE_H
