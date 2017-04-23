#include "transducerfactory.h"
#include "discretetransitionfunction.h"
#include "discreteoutfunction.h"
#include "jsonobject.h"
TransducerFactory::TransducerFactory()
{
    factor["states"] = load_discrete_states;
    factor["start_state"] = load_start_state;
    factor["delta"] = load_delta;
    factor["sigma"] = load_sigma;
}

Transducer TransducerFactory::produce(std::ifstream& in)
{
    std::cout<<"Start creating transducer from file."<<std::endl;
    Transducer result;
    std::string control_s, last_accepted_command;
    std::string name;
    /*JSONObject tr(in);
    for(auto x: tr)
    {
        if(factor.find(x.first) == factor.end())
        {
            std::cerr<<"Unkown field in transducer "<<x.first<<". Skipped.\n";
            continue;
        }
        factor[x.first](x.second, result);
    }*/
    in>>name>>control_s;
    std::cout<<"Transducer: "<<name<<"\n";
    assert(control_s == "{" && "Couldn't find { staring Transducer descripiton!");
    for(in>>control_s; control_s != "}"; in>>control_s)
    {
        if(control_s.back() == ':')
            control_s.pop_back();
        if(factor.find(control_s) == factor.end())
        {
            std::cerr<<"Unknown property of Transducer: "<<control_s<<" after "<<last_accepted_command<<"\n";
            std::cerr<<"Known properties("<<factor.size()<<"): ";
            for(auto& x: factor)
                std::cerr<<x.first<<", ";
            std::cerr<<"\n";
            exit(1);
        }
        factor[control_s](in, result);
        last_accepted_command = control_s;
    }
    std::cout<<"Validating transducer.."<<std::endl;
    std::cout<<"Success! Created transducer"<<std::endl;
    return result;
}
void TransducerFactory::load_delta(std::ifstream &in, Transducer &t)
{
    std::string s;
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
    }
    t.delta = new auto(dtf);
}
void TransducerFactory::load_discrete_states(std::ifstream &in, Transducer &t)
{
    load_flat_list(in);
}
void TransducerFactory::load_sigma(std::ifstream &in, Transducer &t)
{
    DiscreteOutFunction dof;
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
    t.sigma = dof;
}
void TransducerFactory::load_start_state(std::ifstream &in, Transducer &t)
{
    std::string name;
    in>>name;
    if(name.back() == ',')
        name.pop_back();
    t.initial = t.actual = name;
}
std::vector<std::string> TransducerFactory::load_flat_list(std::ifstream& in)
{
    std::vector<std::string> res;
    std::string control_s;
    in>>control_s;
    if(control_s[0] != '[')
    {
        std::cerr<<"Wrong formatted flat list. Expected [ at the beginning, but given "<<control_s<<"\n";
        exit(1);
    }
    if(control_s.size()==1)
        in>>control_s;
    else
        control_s.erase(0, 1);
    bool b = false;
    for(; control_s != "]"; in>>control_s)
    {
        if(control_s[control_s.size()-1] == ',')
            control_s.pop_back();
        if(b |= control_s.back() == ']')
            control_s.pop_back();
        res.push_back(control_s);
        assert(!in.eof() && "Error while reading argument list");
        if(b)
            break;
    }
    return res;
}
