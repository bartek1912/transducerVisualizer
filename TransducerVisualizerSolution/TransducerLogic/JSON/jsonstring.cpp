#include "jsonstring.h"

JSONString::JSONString(std::istream& f)
{
    f>>val;
    if(val.back() == ',')
        val.pop_back();
}

std::shared_ptr<JSONElement> JSONString::operator[](int x)
{
   return std::shared_ptr<JSONElement>(new JSONString(*this));
}

JSONString::operator std::string()
{
    return val;
}
