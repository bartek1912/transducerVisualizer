#include "transducerfactory.h"
#include "FSM/discretetransitionfunction.h"
#include "discreteoutfunction.h"
#include "FSM/discretetransitionfunctionwithstack.h"
#include "JSON/jsonobject.h"
#include <QRegExp>
#include <cstdlib>
#include <sstream>
TransducerFactory::TransducerFactory(){}

Transducer TransducerFactory::produceTransducer(std::ifstream& in)
{
    std::cout<<"Start creating transducer from file."<<std::endl;
    std::string str((std::istreambuf_iterator<char>(in)),
                     std::istreambuf_iterator<char>());

    QString qstr = QString::fromStdString(str);
    qstr.replace(QRegExp("([{:,])"), "\\1 ");
    qstr.replace(QRegExp("([}])"), " \\1");
    std::istringstream iss;
    iss.str(qstr.toStdString());
    JSON::Object tr(iss);

    Transducer result;
    result.s(tr["states"]);//TODO initialize states
    result.setName(QString::fromStdString(tr["name"].toString()));
    result.initial = result.actual = tr["initial_state"].toString();
    load_delta(tr, result);
    load_sigma(tr, result);
    std::cout<<"Validating transducer.."<<std::endl;
    std::cout<<"Success! Created transducer"<<std::endl;
    return result;
}
void TransducerFactory::load_delta(JSON::Object& tr, Transducer &t)
{

    TransitionFunction* dtf = NULL;
    if(tr.find("hasStack") && tr["hasStack"] == "true")
    {
        DiscreteTransitionFunctionWithStack* dtfws = new DiscreteTransitionFunctionWithStack();
        for(auto state: tr["delta"].identifiers())
            for(auto seq: tr["delta"][state].identifiers())
                for(auto stack_symbol: tr["delta"][state][seq].identifiers())
                {
                    JSON::Element* dest = &tr["delta"][state][seq][stack_symbol];
                    assert(dest->find("1") && "This Transducer's delta function should  result in two element list - state and stack command");
                    std::cerr<<state<<" x "<<seq<<" x "<<stack_symbol<<"\n";
                    if(seq == "default")
                        seq = "_";//old style
                    if(stack_symbol == "default")
                        stack_symbol = "_";
                    assert(stack_symbol.size() == 1 && "Stack symbol for delta must be one char");
                    dtfws->setStackTransition(std::make_tuple(state, stack_symbol[0], seq[0]), (*dest)["0"], (*dest)["1"]);
                }
        dtf = dtfws;
    }
    else
    {
        DiscreteTransitionFunction* dtf2 = new DiscreteTransitionFunction();
        for(auto state: tr["delta"].identifiers())
            for(auto seq: tr["delta"][state].identifiers())
            {
                auto dest = tr["delta"][state][seq].toString();
                if(seq == "default")
                        seq = "_";//old style
                if(seq == "_")
                    dtf2->setTransition(std::make_pair(state, '_'), dest);
                else
                {
                    if(seq.size() > 1)
                    {
                        std::cerr<<"Too long seq description in delta "<<seq<<", "<<dest<<" (Did you mean _?)\n";
                        exit(1);
                    }
                    dtf2->setTransition(std::make_pair(state, seq[0]), dest);
                }
            }
        dtf = dtf2;
   }
   t.delta = dtf;
}
void TransducerFactory::load_sigma(JSON::Object& tr, Transducer &t)
{
    DiscreteOutFunction dof;
    assert((tr["type"] == "Mealy"  || tr["type"] == "Moore") && "Unacceptable type of transducer. Expected: \"Mealy\" or \"Moore\".");
    t.setType(tr["type"] == "Mealy" ? Transducer::Type::Mealy : Transducer::Type::Moore);
    for(auto state: tr["sigma"].identifiers())
    {
        if(state == "_")
            dof.setAs_(tr["sigma"][state].toString());
        else
        {
            if(tr["type"] == "Mealy")
            {
                for(auto seq: tr["sigma"][state].identifiers())
                {
                    auto dest = tr["sigma"][state][seq].toString();
                    if(seq == "default")
                        seq = "_";
                    if(seq == "_")
                        dof.addOutput(std::make_pair(state, '_'), dest);
                    else
                    {
                        if(seq.size() > 1)
                        {
                            std::cerr<<"Too long seq description in sigma "<<seq<<", "<<dest<<" (Did you mean _?)\n";
                            exit(1);
                        }
                        dof.addOutput(std::make_pair(state, seq[0]), dest);
                    }
                }
            }
            else
            {
                auto dest = tr["sigma"][state].toString();
                dof.addOutput(std::make_pair(state, '_'), dest);
            }

        }
    }
    t.sigma.reset( new auto(dof));
}
