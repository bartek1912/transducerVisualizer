#include "jsonfactory.h"
#include "jsonlist.h"
#include "jsonstring.h"
#include "jsonobject.h"
#include <memory>
JSONFactory::JSONFactory(){}
std::shared_ptr<JSONElement> JSONFactory::produce(std::istream& f)
{
    assert(f.peek() != ']' && f.peek() != '}' && f.peek());
    if(f.peek() == '[')
        return std::shared_ptr<JSONElement>(new JSONList(f));
    else if(f.peek() == '{')
        return std::shared_ptr<JSONElement>(new JSONObject(f));
    else
        return std::shared_ptr<JSONElement>(new JSONString(f));

}
