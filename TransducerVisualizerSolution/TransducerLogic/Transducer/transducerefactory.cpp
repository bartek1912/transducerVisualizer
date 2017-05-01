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
    //result.s(in); TODO initialize states
    result.initial = result.actual = tr["initial_state"]->toString();
    load_delta(tr, result);
    load_sigma(tr, result);
    std::cout<<"Validating transducer.."<<std::endl;
    std::cout<<"Success! Created transducer"<<std::endl;
    return result;
}
void TransducerFactory::load_delta(JSON::Object& tr, Transducer &t)
{

    DiscreteTransitionFunction dtf;
    for(auto state: tr["delta"]->identifiers())
        for(auto seq: (*tr["delta"])[state]->identifiers())
        {
            auto dest = (*(*tr["delta"])[state])[seq]->toString();
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
   /* std::string s;
    in>>s;
    assert(s[0] == '{' && "Wrong delta description start");
    if(s.size() > 1)
        s.erase(0,1);
    else
        in>>s;
    DiscreteTransitionFunction dtf;
    for(; s[0] != '}'; in>>s)
    {
        assert(s.back() == ':');
        if(s.back() == ',' || s.back() == ':')
            s.pop_back();
        std::string state = s;
        //load state
        in>>s;
        assert(s[0] == '{' && "Wrong delta description");
        if(s.size() > 1)
            s.erase(0,1);
        else
            in>>s;
        for(; s[0] != '}'; in>>s)
        {
            assert(s.back() == ':');
            s.pop_back();
            std::string destination;
            in>>destination;
            if(destination.back() == ',')
                destination.pop_back();
            if(s == "default")
                dtf.setTransition(make_pair(state, '_'), destination);
            else
            {
                assert(s.size() == 1 && "Wrong char size! Excpeted one char, but given more (or none)");
                dtf.setTransition(make_pair(state, s[0]), destination);
            }
        }
    }*/
    t.delta = new auto(dtf);
}
void TransducerFactory::load_sigma(JSON::Object& tr, Transducer &t)
{
    DiscreteOutFunction dof;
    for(auto state: tr["sigma"]->identifiers())
    {
        if(state == "default")
            dof.setAsDefault((*tr["sigma"])[state]->toString());
        else
            for(auto seq: (*tr["sigma"])[state]->identifiers())
            {
                auto dest = (*(*tr["sigma"])[state])[seq]->toString();
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
    /*DiscreteOutFunction dof;
    std::string s;
    in>>s;
    assert(s == "{" && "Wrong sigma description start");
    if(s.size() > 1)
        s.erase(0,1);
    else
        in>>s;
    for(;s.back() != '}'; in>>s)
    {
        std::string state = s;
        assert(state.back() == ':' && "Missing : glued to state in sigma description");
        state.pop_back();
        std::string inp;
        in>>inp;
        assert(inp[0] == '{' && "Missing { in sigma description");
        if(inp.size() == 1)
        {
            in>>inp;
            if(inp.back() == '}')
                inp.pop_back();
        }
        else
            inp.erase(0,1);
        for(;inp.back() != '}'; )
        {
            std::string out;
            in>>out;
            while(out.size() && out.back() == ',')
                    out.pop_back();
            if(out.size() && out != "identity")
            {
                if(out.size() > 1)
                {
                    std::cerr<<"Too long output - read char, by char. GIVEN: |"<<out<<"| IN: "<<inp<<"\n";
                    exit(1);
                }
                if(inp == "default")
                    dof.addOutput(std::make_pair(state, '_'), out);
                else
                {
                    if(inp.size() > 1)
                    {
                        std::cerr<<"In sigma description - can't read more than one symbol at once. GIVEN: |"<<inp<<"|\n";
                        exit(1);
                    }
                    dof.addOutput(std::make_pair(state, inp[0]), out);
                }
            }
            in>>inp;
            while(inp.size() && (inp.back() == ':' || inp.back() == ','))
                inp.pop_back();

        }
    }
    t.sigma = dof;*/
}
