#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H
#include "jsonelement.h"
#include <fstream>
#include <stack>
#include <map>
#include <assert.h>
namespace JSON
{

struct Object: public Element
{
    Object(std::istream&);
    virtual bool find(const std::string&) override;
    virtual Element& operator[](const std::string& x) override;
    virtual const Element& operator[](const std::string& x) const override;
    virtual operator std::string() const override;
    virtual unsigned size() { return m.size(); }
    virtual std::vector<std::string> identifiers() const override;
private:
    std::map<std::string, Element* > m;
};
}
#endif
