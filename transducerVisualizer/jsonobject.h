#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H
#include "jsonelement.h"
#include <fstream>
#include <stack>
#include <map>
#include <assert.h>
struct JSONObject: public JSONElement
{
    JSONObject(std::ifstream& in)
    {
        assert(in.peek() == '{');

    }
    /*JSONObject& operator[](std::string x)
    {
        return m[x];
    }*/


private:
    std::map<std::string, JSONObject> m;
};
#endif
