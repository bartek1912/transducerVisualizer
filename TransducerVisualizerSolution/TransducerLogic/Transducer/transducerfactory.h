#ifndef TRANSDUCERFACTOR_H
#define TRANSDUCERFACTOR_H
#include <fstream>
#include <assert.h>
#include <map>
#include "JSON/jsonfactory.h"
#include "JSON/jsonobject.h"
#include "transducer.h"

struct TransducerFactory
{
    TransducerFactory();
    Transducer produceTransducer(std::ifstream& in);
private:
    std::map<std::string, std::function<void(std::ifstream&, Transducer&)> > factor;
    //static void    load_discrete_states(const JSONElement& in, Transducer& t);
    static void    load_delta(JSON::Object& tr, Transducer& t);
    static void    load_sigma(JSON::Object& tr, Transducer& t);
};


#endif // TRANSDUCERFACTOR_H
