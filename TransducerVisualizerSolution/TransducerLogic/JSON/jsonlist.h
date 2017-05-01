#ifndef JSONLIST_H
#define JSONLIST_H
#include <fstream>
#include <vector>
#include "jsonelement.h"
namespace JSON
{
struct List: public Element
{
    List();
    List(std::istream&);
    virtual std::shared_ptr<Element> operator[](const std::string& x);
    virtual operator std::string();
    virtual unsigned size(){return elems.size(); }
    virtual std::vector<std::string> identifiers();
private:
    std::vector<std::shared_ptr<Element> > elems;
};
}

#endif // JSONLIST_H
