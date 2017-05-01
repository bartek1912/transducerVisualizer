#ifndef STATE_H
#define STATE_H
#include <string>
#include "JSON/jsonelement.h"

class State
{
    std::string content;
public:
    State(std::string s):content(s){}
    operator std::string() const
    {
        return content;
    }
    std::string toString() const
    {
        return static_cast<std::string>(*this);
    }

    //virtual operator ()(const JSONElement&) = 0; TODO discrete state class
};

#endif // STATE_H
