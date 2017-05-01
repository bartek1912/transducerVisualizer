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
    virtual std::shared_ptr<Element> operator[](const std::string& x) override;
    virtual operator std::string() override;
    virtual unsigned size() { return m.size(); }
    virtual std::vector<std::string> identifiers() override;
private:
    std::map<std::string, std::shared_ptr<Element> > m;
};
}
#endif
