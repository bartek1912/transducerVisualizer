#include "transducer.h"
#include <QString>
Transducer::Transducer()
    :type(Unset)
{}
void Transducer::process(char c)
{
    (*sigma)(actual, c);
    actual = (*delta)(actual, c);
}

std::string Transducer::get_output()
{
    return sigma->result();
}
void Transducer::reset()
{
    FSM::reset();
    sigma->reset();
}

bool Transducer::isMoore() const
{
    return type == Moore;
}

bool Transducer::isMealy() const
{
    return type == Mealy;
}

void Transducer::setType(Type t)
{
    type = t;
}

QString Transducer::getName() const
{
    return name;
}

void Transducer::setName(const QString &s)
{
    name = s;
}
