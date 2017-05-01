#ifndef JSONSTRING_H
#define JSONSTRING_H
#include "jsonelement.h"
#include <fstream>
namespace JSON
{
struct String: public Element
{
    String(const std::string& v);
    String(std::istream&);
    virtual std::shared_ptr<Element> operator[](const std::string& x);
    virtual operator std::string();
    virtual unsigned size() {return 1;}
    virtual std::vector<std::string> identifiers();
private:
    std::string val;
};
}

#endif // JSONSTRING_H
