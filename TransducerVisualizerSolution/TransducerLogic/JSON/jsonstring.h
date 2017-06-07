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
    virtual bool find(const std::string&) override;
    virtual Element& operator[](const std::string& x) override;
    virtual const Element& operator[](const std::string& x) const override;
    virtual operator std::string() const override;
    virtual unsigned size() {return 1;}
    virtual std::vector<std::string> identifiers() const override;
private:
    std::string val;
};
}

#endif // JSONSTRING_H
