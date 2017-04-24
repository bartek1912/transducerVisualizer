#include "jsonobject.h"
#include <iostream>
#include "JSON/jsonfactory.h"
JSONObject::JSONObject(std::istream& in)
{
    std::string s;
    in>>s;
    assert(s[0] == '{' && "Object don't start with {");
    while(isspace(in.peek()))
        in.get();
    while(in.peek() != '}')
    {
        if(in.peek() == ',')
            in.ignore();
        else
        {
            in>>s;
            while(isspace(in.peek()))
                in.get();
            assert((s.back() == ':' || in.peek() == ':') && "Missing : after field name in jsonobject");
            if(s.back() == ':')
                s.pop_back();
            else
                in.get();
            if(m.find(s) != m.end())
                std::cerr<<"Warning! Multiple definition of field "<<s<<"!\n";
            m[s] = (JSONFactory::produce(in));
            while(isspace(in.peek()))
                in.get();
        }
    }
}

std::shared_ptr<JSONElement> JSONObject::operator[](std::string x)
{
    if(m.find(x) == m.end())
    {
        std::cerr<<"Not found in object field named "<<x<<"\n";
        std::cerr<<"Available fields: ";
        for(auto x: m)
            std::cerr<<x.first<<", ";
        std::cerr<<"\n";
        exit(0);
    }
    return m[x];
}

JSONObject::operator std::string()
{
    std::string res = "{ ";
    for(auto x: m)
        res += x.first+":" + x.second->toString() + ",\n";
    if(!m.empty())
    {
        res.pop_back();
        res.pop_back();
    }
    return res + " }";
}
