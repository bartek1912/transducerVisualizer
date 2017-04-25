#include "jsonlist.h"
#include "jsonfactory.h"
#include "jsonstring.h"
#include <assert.h>
#include <sstream>
JSONList::JSONList(){}
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
        if(in.peek() == ',')
            in.ignore();
        else
        {
            elems.push_back(JSONFactory::produce(in));
            while(isspace(in.peek()))
                in.get();
        }
    }
    in>>s;
    assert(s[0] == ']');
}
std::shared_ptr<JSONElement> JSONList::operator[](const std::string& x)
{
    int i = stoi(x);
    assert(i < elems.size() && i >= 0 && "Not valid element number in json list!");
    return elems[i];
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
