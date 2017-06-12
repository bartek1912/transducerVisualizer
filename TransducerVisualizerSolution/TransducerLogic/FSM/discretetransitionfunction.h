#ifndef DISCRETETRANSITIONFUNCTION_H
#define DISCRETETRANSITIONFUNCTION_H
//TODO nie korzystać z currentIndex jako tab tylko z nowej zmiennej
//TODO stos/niedeterministyczny
//TODO nieskończone słowa - nie da się zrealizować
//TODO space sensitive (brak spacji po przecinku, spacja przed)
//TODO konwersja nie jest zrobiona
//TODO praca: co to transducer, dlaczego takie technologie,
//przykłady, testy, podsumowanie [ zastosowania, jakie kierunki rozwoju, co nie zostało zrobione] + cytaty(min 7)
//TODO  przetestować usuwanie transducer'a w którym obecnie jest input (może reset?)
#include "transitionfunction.h"
#include "state.h"
#include <vector>
#include <map>
#include <algorithm>
class DiscreteTransitionFunction : public TransitionFunction
{
    std::map<std::pair<std::string, char>, std::string> transition;
public:
    DiscreteTransitionFunction();
    virtual State operator()(const State& s, char c) override;
    std::vector<std::pair<char, std::string>> possibilites(std::string s) override;
    void setTransition(std::pair<std::string, char>, std::string);
};

#endif // DISCRETETRANSITIONFUNCTION_H
