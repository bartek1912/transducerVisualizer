#include "jsonobject.h"
JSONObject::JSONObject(std::istream&)
{

}

std::shared_ptr<JSONElement> JSONObject::operator[](int x)
{
    return std::unique_ptr<JSONElement>(nullptr);
}

JSONObject::operator std::string()
{
    return "";
}
