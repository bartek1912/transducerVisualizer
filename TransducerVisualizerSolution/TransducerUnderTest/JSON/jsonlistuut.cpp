#include "jsonlistuut.h"
#include <QString>
#include <iostream>
#include <sstream>
namespace JSON
{
ListUUT::ListUUT()
{

}

void ListUUT::TestEquity(std::string inp, std::string exp)
{
    std::istringstream iss(inp);

    list = List(iss);
    QString res = QString::fromStdString(list.toString());
    QString test = QString::fromStdString(exp);
    test.replace(' ', "");
    res.replace(' ', "");

    QVERIFY(iss.eof());
    QVERIFY2(res == test, ("Test " + inp
                           + ". EXPECTED " + test.toStdString() +
                           " GIVEN " +   res.toStdString()).c_str());
}

void ListUUT::EmptyList()
{
    TestEquity("[ ]", "[]");
    TestEquity("[ ],", "[]");
}

void ListUUT::Singleton()
{
    TestEquity("[ A ]", "[ A ]");
    TestEquity("[ A ],", "[ A ]");
    TestEquity("[ A, ]", "[ A ]");
    QVERIFY(list["0"] == "A");
}
void ListUUT::ListOfStrings()
{
    TestEquity("[ A, B ]", "[ A, B ]");
    TestEquity("[ A, B, ]", "[ A, B ]");
    TestEquity("[ A, B, C, A, B ],", "[ A, B, C, A, B ]");
    QVERIFY(list["0"] == "A");
    QVERIFY(list["1"] == "B");
    QVERIFY(list["2"] == "C");
    QVERIFY(list["4"] == "B");
}
void ListUUT::ListOfLists()
{
    TestEquity("[ [ A ] ]", "[ [ A ] ]");
    QVERIFY(list["0"]["0"] == "A");
    TestEquity("[ [ A ], ]", "[ [ A ] ]");
    TestEquity("[ [ A, ], ]", "[ [ A ] ]");
    TestEquity("[ [ A, ], ],", "[ [ A ] ]");
    TestEquity("[ [ A, B ] ]", "[ [ A, B ] ]");
    QVERIFY(list["0"]["0"] == "A");
    QVERIFY(list["0"]["1"] == "B");
    TestEquity("[ [ A, B ], [ C ] ]", "[ [ A, B ], [ C ] ]");
    QVERIFY(list["1"]["0"] == "C");
    TestEquity("[ [ [ A ] , B ], [ C ], [ [ ] ] ]", "[ [ [A] , B ], [ C ], [ [ ] ] ]");
    QVERIFY(list["0"]["0"]["0"] == "A");
    QVERIFY(list["0"]["1"] == "B");
    QVERIFY(list["1"]["0"] == "C");
}
void ListUUT::ListOfObjects()
{
    TestEquity("[ { A: B } ]", "[ { A: B } ]");
    QVERIFY(list["0"]["A"] == "B");
    TestEquity("[ { A: B }, { C: D }, [ { E: F } ] ]", "[ { A: B }, { C: D }, [ {E: F} ] ]");
    QVERIFY(list["0"]["A"] == "B");
    QVERIFY(list["1"]["C"] == "D");
    QVERIFY(list["2"]["0"]["E"] == "F");
}
}
