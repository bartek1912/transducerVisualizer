#ifndef JSONFACTORY_H
#define JSONFACTORY_H
#include <istream>
#include <memory>
#include "jsonelement.h"

class JSONFactory
{
    JSONFactory();
public:
    static std::shared_ptr<JSONElement> produce(std::istream& f);
};

#endif // JSONFACTORY_H
