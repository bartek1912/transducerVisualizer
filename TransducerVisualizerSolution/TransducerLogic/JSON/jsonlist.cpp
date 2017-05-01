#include "jsonlist.h"
#include "jsonfactory.h"
#include "jsonstring.h"
#include <assert.h>
#include <sstream>
namespace JSON
{
List::List(){}
List::List(std::istream& in)
{
    assert(in.peek() == '[' && "List should start with [");
    std::string s;
    in>>s;
    assert(s == "[" && "Missing space after [ or invalid format of json List");
    while(isspace(in.peek()))
        in.get();
    char next = in.peek();
    while(in.peek() != ']')
    {
        if(in.peek() == ',')
            in.ignore();
        else
        {
            elems.push_back(Factory::produce(in));
            while(isspace(in.peek()))
                in.get();
        }
    }
    in>>s;
    assert(s[0] == ']');
}
std::shared_ptr<Element> List::operator[](const std::string& x)
{
    int i = stoi(x);
    assert(i < elems.size() && i >= 0 && "Not valid element number in json list!");
    return elems[i];
}

List::operator std::string()
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
std::vector<std::string> List::identifiers()
{
    std::vector<std::string> res;
    for(int i = 0; i < elems.size(); i++)
        res.push_back(std::to_string(i));
    return res;
}
}
