#ifndef JSONELEMENT_H
#define JSONELEMENT_H
#include <memory>
#include <algorithm>
#include <vector>
//TODO: http://stackoverflow.com/questions/3960948/fast-and-flexible-iterator-for-abstract-class
namespace JSON
{
struct Element
{
    Element();
    virtual std::shared_ptr<Element> operator[](const std::string& x) = 0;
    virtual operator std::string() = 0;
    bool operator == (const std::string& s){return toString() == s;}
    std::string toString();
    virtual unsigned size() = 0;
    virtual std::vector<std::string> identifiers() = 0;
};
}

#endif // JSONELEMENT_H
