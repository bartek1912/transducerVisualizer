#include "jsonelement.h"
namespace JSON
{
Element::Element()
{

}
std::string Element::toString() {
    return static_cast<std::string>(*this);
}
}
