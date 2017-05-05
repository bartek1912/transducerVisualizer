#include "transducer.h"
Transducer::Transducer(){}
void Transducer::process(char c)
{
    (*sigma)(actual, c);
    actual = (*delta)(actual, c);
}

std::string Transducer::get_output()
{
    return sigma->result();
}
