#include "jsonobjectuut.h"
#include "JSON/jsonobject.h"
#include <sstream>
#include <QtTest>
#include <QString>
namespace JSON
{
void ObjectUUT::EmptyObject()
{
    std::string test = "{ }";
    std::istringstream ss(test);

    Object obj(ss);
    QString res = QString::fromStdString(obj.toString());
    QString exp = QString::fromStdString(test);
    exp.replace(' ', "");
    res.replace(' ', "");
    exp.replace('\n', "");
    res.replace('\n', "");

    QVERIFY(ss.eof());
    QVERIFY(res == exp);
}
void ObjectUUT::OneField()
{
    std::string test = "{ A: B }";
    std::istringstream ss(test);

    Object obj(ss);
    QString res = QString::fromStdString(obj.toString());
    QString exp = QString::fromStdString(test);
    exp.replace(' ', "");
    res.replace(' ', "");

    QVERIFY(ss.eof());
    QVERIFY(res == exp);
}
void ObjectUUT::MoreFields()
{
    std::string test = "{ A: B, C: D }";
    std::istringstream ss(test);

    Object obj(ss);

    QVERIFY(ss.eof());
    QVERIFY(obj["A"]->toString() == "B");
    QVERIFY(obj["C"]->toString() == "D");
}
void ObjectUUT::NestedObject()
{
    std::string test = "{ A: { X: Y } , C: D }";
    std::istringstream ss(test);

    Object obj(ss);

    std::string res = obj.toString();
    QVERIFY(ss.eof());
    QVERIFY((*obj["A"])["X"]->toString() == "Y");
    QVERIFY(obj["C"]->toString() == "D");
}

void ObjectUUT::ListAsAField()
{
    std::string test = "{ A: [ X, Y ] , C: D }";
    std::istringstream ss(test);

    Object obj(ss);

    std::string res = obj.toString();
    QVERIFY(ss.eof());
    QVERIFY((*obj["A"])["0"]->toString() == "X");
    QVERIFY((*obj["A"])["1"]->toString() == "Y");
    QVERIFY(obj["C"]->toString() == "D");

}
}
