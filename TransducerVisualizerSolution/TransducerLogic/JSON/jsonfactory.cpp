#include "jsonfactory.h"
#include "jsonlist.h"
#include "jsonstring.h"
#include "jsonobject.h"
#include <memory>
namespace JSON
{
Factory::Factory(){}
Element* Factory::produce(std::istream& f)
{
    while(isspace(f.peek()))
        f.get();
    assert(f.peek() != ']' && f.peek() != '}' && f.peek() && f.peek() != ',');
    if(f.peek() == '[')
        return new List(f);
    else if(f.peek() == '{')
        return new Object(f);
    else
        return new String(f);

}
}
