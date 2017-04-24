#ifndef JSONLIST_H
#define JSONLIST_H
#include <fstream>
#include <vector>
#include "jsonelement.h"

struct JSONList: public JSONElement
{
    JSONList(std::istream&);
    virtual std::shared_ptr<JSONElement> operator[](std::string x);
    virtual operator std::string();
private:
    std::vector<std::shared_ptr<JSONElement> > elems;
};

#endif // JSONLIST_H
