#ifndef STATES_H
#define STATES_H
#include <vector>
#include <string>
#include "JSON/jsonelement.h"
class States
{
public:
    States();
    void operator()(const JSON::Element&);
    std::vector<std::string> description() const;
private:
    std::vector<std::string> states_space;
};

#endif // STATES_H
