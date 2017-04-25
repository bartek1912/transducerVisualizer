#include "jsonlistuut.h"
#include <QString>
#include <iostream>
#include <sstream>
JSONListUUT::JSONListUUT()
{

}

void JSONListUUT::TestEquity(std::string inp, std::string exp)
{
    std::istringstream iss(inp);

    list = JSONList(iss);
    QString res = QString::fromStdString(list.toString());
    QString test = QString::fromStdString(exp);
    test.replace(' ', "");
    res.replace(' ', "");

    QVERIFY(iss.eof());
    QVERIFY2(res == test, ("Test " + inp
                           + ". EXPECTED " + test.toStdString() +
                           " GIVEN " +   res.toStdString()).c_str());
}

void JSONListUUT::EmptyList()
{
    TestEquity("[ ]", "[]");
    TestEquity("[ ],", "[]");
}

void JSONListUUT::Singleton()
{
    TestEquity("[ A ]", "[ A ]");
    TestEquity("[ A ],", "[ A ]");
    TestEquity("[ A, ]", "[ A ]");
   QVERIFY(*(list["0"]) == "A");
}
void JSONListUUT::ListOfStrings()
{
    TestEquity("[ A, B ]", "[ A, B ]");
    TestEquity("[ A, B, ]", "[ A, B ]");
    TestEquity("[ A, B, C, A, B ],", "[ A, B, C, A, B ]");
    QVERIFY(*(list["0"]) == "A");
    QVERIFY(*(list["1"]) == "B");
    QVERIFY(*(list["2"]) == "C");
    QVERIFY(*(list["4"]) == "B");
}
void JSONListUUT::ListOfLists()
{
    TestEquity("[ [ A ] ]", "[ [ A ] ]");
    QVERIFY(*(*list["0"])["0"] == "A");
    TestEquity("[ [ A ], ]", "[ [ A ] ]");
    TestEquity("[ [ A, ], ]", "[ [ A ] ]");
    TestEquity("[ [ A, ], ],", "[ [ A ] ]");
    TestEquity("[ [ A, B ] ]", "[ [ A, B ] ]");
    QVERIFY(*(*list["0"])["1"] == "B");
    QVERIFY(*(*list["0"])["1"] == "B");
    TestEquity("[ [ A, B ], [ C ] ]", "[ [ A, B ], [ C ] ]");
    QVERIFY(*(*list["1"])["0"] == "C");
    TestEquity("[ [ [ A ] , B ], [ C ], [ [ ] ] ]", "[ [ [A] , B ], [ C ], [ [ ] ] ]");
    QVERIFY(*(*(*list["0"])["0"])["0"] == "A");
    QVERIFY(*(*list["0"])["1"] == "B");
    QVERIFY(*(*list["1"])["0"] == "C");
}
