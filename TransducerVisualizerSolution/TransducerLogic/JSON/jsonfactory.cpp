#include "jsonfactory.h"
#include "jsonlist.h"
#include "jsonstring.h"
#include "jsonobject.h"
#include <memory>
namespace JSON
{
Factory::Factory(){}
std::shared_ptr<Element> Factory::produce(std::istream& f)
{
    while(isspace(f.peek()))
        f.get();
    assert(f.peek() != ']' && f.peek() != '}' && f.peek() && f.peek() != ',');
    if(f.peek() == '[')
        return std::shared_ptr<Element>(new List(f));
    else if(f.peek() == '{')
        return std::shared_ptr<Element>(new Object(f));
    else
        return std::shared_ptr<Element>(new String(f));

}
}
