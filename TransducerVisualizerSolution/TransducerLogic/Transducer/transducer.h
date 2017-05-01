#ifndef TRANSDUCER_H
#define TRANSDUCER_H
#include <vector>
#include <ostream>
#include <memory>
#include "outfunction.h"
#include "FSM/fsm.h"
/*Mealy*/
class Transducer : public FSM
{
    std::shared_ptr<OutFunction>    sigma;
public:
    Transducer();
    void process(char s);
    friend std::ostream& operator << (std::ostream& o, const Transducer& t)
    {
        return o<<(*t.sigma);
    }
    friend class TransducerFactory;
};
#endif // TRANSDUCER_H
