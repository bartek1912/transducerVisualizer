#include "jsonlist.h"
#include "jsonfactory.h"
#include "jsonstring.h"
#include <assert.h>
#include <sstream>
JSONList::JSONList(std::istream& in)
{
    assert(in.peek() == '[' && "JSONList should start with [");
    std::string s;
    in>>s;
    assert(s == "[" && "Missing space after [ or invalid format of jsonlist");
    while(isspace(in.peek()))
        in.get();
    char next = in.peek();
    while(in.peek() != ']')
    {
        elems.push_back(JSONFactory::produce(in));
        while(isspace(in.peek()))
            in.get();
    }
}
std::shared_ptr<JSONElement> JSONList::operator [](int x)
{
    std::istringstream s("");
    return std::shared_ptr<JSONElement>(new JSONString(s));
}

JSONList::operator std::string()
{
    std::string res = "[";
    for(size_t i = 0; i <  elems.size(); i++)
    {
        res += elems[i]->toString();
        if(i+1 < elems.size())
            res+=", ";
    }
    return res+" ]";
}
