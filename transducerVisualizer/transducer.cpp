#include "transducer.h"
Transducer::Transducer(){}
void Transducer::process(std::string s)
{
    FSM::process(s, sigma);
}
