#ifndef JSONSTRING_H
#define JSONSTRING_H
#include "jsonelement.h"
#include <fstream>
struct JSONString: public JSONElement
{
    JSONString(std::istream&);
    virtual std::shared_ptr<JSONElement> operator[](int x);
    virtual operator std::string();
private:
    std::string val;
};

#endif // JSONSTRING_H
