#include "jsonobjectuut.h"
#include "JSON/jsonobject.h"
#include <sstream>
#include <QtTest>
#include <QString>
void JSONObjectUUT::EmptyObject()
{
    std::string test = "{ }";
    std::istringstream ss(test);

    JSONObject obj(ss);
    QString res = QString::fromStdString(obj.toString());
    QString exp = QString::fromStdString(test);
    exp.replace(' ', "");
    res.replace(' ', "");
    exp.replace('\n', "");
    res.replace('\n', "");

    QVERIFY(ss.eof());
    QVERIFY(res == exp);
}
void JSONObjectUUT::OneField()
{
    std::string test = "{ A: B }";
    std::istringstream ss(test);

    JSONObject obj(ss);
    QString res = QString::fromStdString(obj.toString());
    QString exp = QString::fromStdString(test);
    exp.replace(' ', "");
    res.replace(' ', "");

    QVERIFY(ss.eof());
    QVERIFY(res == exp);
}
void JSONObjectUUT::MoreFields()
{
    std::string test = "{ A: B, C: D }";
    std::istringstream ss(test);

    JSONObject obj(ss);

    QVERIFY(ss.eof());
    QVERIFY(obj["A"]->toString() == "B");
    QVERIFY(obj["C"]->toString() == "D");
}
void JSONObjectUUT::NestedObject()
{
    std::string test = "{ A: { X: Y } , C: D }";
    std::istringstream ss(test);

    JSONObject obj(ss);

    std::string res = obj.toString();
    QVERIFY(ss.eof());
    QVERIFY((*obj["A"])["X"]->toString() == "Y");
    QVERIFY(obj["C"]->toString() == "D");
}
