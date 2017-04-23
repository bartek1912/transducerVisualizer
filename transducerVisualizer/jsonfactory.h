#ifndef JSONFACTORY_H
#define JSONFACTORY_H
#include <fstream>
#include "jsonelement.h"

class JSONFactory
{
    JSONFactory();
public:
    static JSONElement produce(std::ifstream& f);
};

#endif // JSONFACTORY_H
