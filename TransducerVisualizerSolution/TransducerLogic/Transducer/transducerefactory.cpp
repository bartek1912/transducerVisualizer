#include "transducerfactory.h"
#include "FSM/discretetransitionfunction.h"
#include "discreteoutfunction.h"
#include "JSON/jsonobject.h"
#include <cstdlib>
TransducerFactory::TransducerFactory()
{
    /*factor["states"] = load_discrete_states;
    factor["start_state"] = load_start_state;
    factor["delta"] = load_delta;
    factor["sigma"] = load_sigma;*/
}

Transducer TransducerFactory::produceTransducer(std::ifstream& in)
{
    std::cout<<"Start creating transducer from file."<<std::endl;
    Transducer result;
    std::string control_s, last_accepted_command;
    std::string name;


    JSON::Object tr(in);
    result.s(tr["states"]);// TODO initialize states
    result.initial = result.actual = tr["initial_state"].toString();
    load_delta(tr, result);
    load_sigma(tr, result);
    std::cout<<"Validating transducer.."<<std::endl;
    std::cout<<"Success! Created transducer"<<std::endl;
    return result;
}
void TransducerFactory::load_delta(JSON::Object& tr, Transducer &t)
{

    DiscreteTransitionFunction dtf;
    for(auto state: tr["delta"].identifiers())
        for(auto seq: tr["delta"][state].identifiers())
        {
            auto dest = tr["delta"][state][seq].toString();
            if(seq == "default")
                dtf.setTransition(std::make_pair(state, '_'), dest);
            else
            {
                if(seq.size() > 1)
                {
                    std::cerr<<"Too long seq description in delta "<<seq<<", "<<dest<<" (Did you mean default?)\n";
                    exit(1);
                }
                dtf.setTransition(std::make_pair(state, seq[0]), dest);
            }
        }
   t.delta = new auto(dtf);
}
void TransducerFactory::load_sigma(JSON::Object& tr, Transducer &t)
{
    DiscreteOutFunction dof;
    for(auto state: tr["sigma"].identifiers())
    {
        if(state == "default")
            dof.setAsDefault(tr["sigma"][state].toString());
        else
            for(auto seq: tr["sigma"][state].identifiers())
            {
                auto dest = tr["sigma"][state][seq].toString();
                if(seq == "default")
                    dof.addOutput(std::make_pair(state, '_'), dest);
                else
                {
                    if(seq.size() > 1)
                    {
                        std::cerr<<"Too long seq description in delta "<<seq<<", "<<dest<<" (Did you mean default?)\n";
                        exit(1);
                    }
                    dof.addOutput(std::make_pair(state, seq[0]), dest);
                }
            }
    }
    t.sigma.reset( new auto(dof));
}
