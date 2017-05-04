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
    virtual Element& operator[](const std::string& x) = 0;//object handle all containing objects on their own
    virtual const Element& operator[](const std::string& x) const = 0;//no need for shared_ptr
    virtual operator std::string() const = 0;
    bool operator == (const std::string& s){return toString() == s;}
    std::string toString() const;
    virtual unsigned size() = 0;
    virtual std::vector<std::string> identifiers() const = 0;
};
}

#endif // JSONELEMENT_H
