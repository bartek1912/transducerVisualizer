#include "transducer.h"
Transducer::Transducer(){}
void Transducer::process(char c)
{
    (*sigma)(actual, c);
    actual = (*delta)(actual, c);
    std::cerr<<"Transducer: "<<(std::string)(actual)<<"\n";
}
