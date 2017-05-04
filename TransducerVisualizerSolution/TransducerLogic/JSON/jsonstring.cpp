#include "jsonstring.h"
namespace JSON
{
String::String(std::istream& f)
{
    f>>val;
    if(val[0] == '"')
    {
        std::string res;
        bool found_end = false;
        val.erase(0,1);
        while(!found_end)
        {
            if(res.size())
                res += ' ';
            for(unsigned i = 0; i < val.size() && !found_end; i++)
                if(val[i] == '"')
                    found_end = true;
                else
                    res += val[i];
            if(!found_end)
                f>>val;
        }
        val = res;
    }
    if(val.back() == ',')
        val.pop_back();
}
String::String(const std::string& v):val(v){}


Element& String::operator[](const std::string& x)
{
    return *this;
}

const Element& String::operator[](const std::string&) const
{
   return *this;//TODO can't modify - maybe ok
}

String::operator std::string() const
{
    return val;
}
std::vector<std::string> String::identifiers() const
{
    return {"0"};
}
}
