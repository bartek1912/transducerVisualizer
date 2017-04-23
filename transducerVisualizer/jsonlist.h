#ifndef JSONLIST_H
#define JSONLIST_H
#include <fstream>
#include "jsonelement.h"

class JSONList: public JSONElement
{
public:
    JSONList(std::ifstream&);
};

#endif // JSONLIST_H
