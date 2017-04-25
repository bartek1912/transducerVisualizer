#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H
#include "jsonelement.h"
#include <fstream>
#include <stack>
#include <map>
#include <assert.h>
struct JSONObject: public JSONElement
{
    JSONObject(std::istream&);
    virtual std::shared_ptr<JSONElement> operator[](const std::string& x);
    virtual operator std::string();
private:
    std::map<std::string, std::shared_ptr<JSONElement> > m;
};
#endif
