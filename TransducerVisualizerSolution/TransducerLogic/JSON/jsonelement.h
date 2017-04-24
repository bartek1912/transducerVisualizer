#ifndef JSONELEMENT_H
#define JSONELEMENT_H
#include <memory>

struct JSONElement
{
    JSONElement();
    virtual std::shared_ptr<JSONElement> operator[](std::string x) = 0;
    virtual operator std::string() = 0;
    bool operator == (const std::string& s){return toString() == s;}
    std::string toString();
};

#endif // JSONELEMENT_H
