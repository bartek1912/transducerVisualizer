#include "jsonstring.h"

JSONString::JSONString(std::istream& f)
{
    f>>val;
    if(val.back() == ',')
        val.pop_back();
}
JSONString::JSONString(const std::string& v):val(v){}

std::shared_ptr<JSONElement> JSONString::operator[](const std::string& x)
{
   return std::shared_ptr<JSONElement>(new JSONString(val));//TODO can't modify
}

JSONString::operator std::string()
{
    return val;
}
