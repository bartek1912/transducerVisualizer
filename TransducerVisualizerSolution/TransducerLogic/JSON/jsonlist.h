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
    virtual Element& operator[](const std::string& x) override;
    virtual const Element& operator[](const std::string& x) const override;
    virtual operator std::string() const override;
    virtual unsigned size(){return elems.size(); }
    virtual std::vector<std::string> identifiers() const override;
private:
    std::vector<Element* > elems;
};
}

#endif // JSONLIST_H
