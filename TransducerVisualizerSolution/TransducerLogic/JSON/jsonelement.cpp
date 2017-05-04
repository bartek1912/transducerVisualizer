#include "jsonelement.h"
namespace JSON
{
Element::Element()
{

}
std::string Element::toString() const {
    return static_cast<std::string>(*this);
}
}
