#ifndef JSONSTRING_H
#define JSONSTRING_H
#include "jsonelement.h"
#include <fstream>
class JSONString: public JSONElement
{
public:
    JSONString(std::ifstream&);
};

#endif // JSONSTRING_H
