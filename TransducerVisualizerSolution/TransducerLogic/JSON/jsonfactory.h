#ifndef JSONFACTORY_H
#define JSONFACTORY_H
#include <istream>
#include <memory>
#include "jsonelement.h"
namespace JSON {
class Factory
{
    Factory();
public:
    static Element* produce(std::istream& f);
};
}

#endif // JSONFACTORY_H
