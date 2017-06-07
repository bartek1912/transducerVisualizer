#ifndef TRANSDUCER_H
#define TRANSDUCER_H
#include <vector>
#include <ostream>
#include <memory>
#include <QString>
#include "outfunction.h"
#include "FSM/fsm.h"
class Transducer : public FSM
{
    std::shared_ptr<OutFunction>    sigma;
    enum Type {Unset, Mealy, Moore};
    Type type;
    QString name;
public:
    Transducer();
    void process(char s);
    std::string get_output();
    virtual void reset() override;
    bool isMealy() const;
    bool isMoore() const;
    void setType(Type t);
    friend std::ostream& operator << (std::ostream& o, const Transducer& t)
    {
        return o<<(*t.sigma);
    }
    friend class TransducerFactory;
    void setName(const QString& s);
    QString getName() const;
};
#endif // TRANSDUCER_H
