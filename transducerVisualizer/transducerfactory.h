#ifndef TRANSDUCERFACTOR_H
#define TRANSDUCERFACTOR_H
#include <fstream>
#include <assert.h>
#include <map>
#include "transducer.h"

struct TransducerFactory
{
    TransducerFactory();
    Transducer produce(std::ifstream& in);
private:
    std::map<std::string, std::function<void(std::ifstream&, Transducer&)> > factor;
    static std::vector<std::string> load_flat_list(std::ifstream& in);
    static void    load_discrete_states(std::ifstream& in, Transducer& t);
    static void    load_start_state(std::ifstream& in, Transducer& t);
    static void    load_delta(std::ifstream& in, Transducer& t);
    static void    load_sigma(std::ifstream& in, Transducer& t);
};


#endif // TRANSDUCERFACTOR_H
