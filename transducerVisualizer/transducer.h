#ifndef TRANSDUCER_H
#define TRANSDUCER_H
#include <vector>
#include <ostream>
#include "outfunction.h"
#include "fsm.h"
/*Mealy*/
class Transducer : public FSM
{
    OutFunction    sigma;
public:
    Transducer();
    void process(std::string s);
    friend std::ostream& operator << (std::ostream& o, const Transducer& t)
    {
        //o<<t.sigma;
        //for(const auto& x: t.sigma.out)
        //    o<<x;
        return o;
    }
    friend class TransducerFactory;
};
#endif // TRANSDUCER_H
