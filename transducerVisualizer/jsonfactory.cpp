#include "jsonfactory.h"
#include "jsonlist.h"
#include "jsonstring.h"
#include "jsonobject.h"
JSONFactory::JSONFactory(){}
JSONElement JSONFactory::produce(std::ifstream& f)
{
    if(f.peek() == '[')
        return JSONList(f);
    else if(f.peek() == '{')
        return JSONObject(f);
    else
        return JSONString(f);
}
