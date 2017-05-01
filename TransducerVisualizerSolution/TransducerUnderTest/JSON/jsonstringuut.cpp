#include "jsonstringuut.h"
#include "JSON/jsonstring.h"
#include <QTest>
#include <sstream>
namespace JSON
{
void StringUUT::oneString()
{
    std::string in = "ABC";
    std::istringstream ss(in);
    String str(ss);
    QVERIFY(ss.eof());
    QVERIFY(str == in);
    QVERIFY(*str["0"] == in);
}

void StringUUT::stringWithComman()
{
    std::string exp = "AB";
    std::string in = exp + ",";
    std::istringstream ss(in);
    String str(ss);
    QVERIFY(ss.eof());
    QVERIFY(str == exp);
    QVERIFY(*str["0"] == exp);
}
void StringUUT::oneWordInQuotation()
{
    std::string in = "\"ABABC\"";
    std::string res = "ABABC";
    std::istringstream ss(in);
    String str(ss);
    QVERIFY(ss.eof());
    QVERIFY(str == res);
    QVERIFY(*str["0"] == res);
}
void StringUUT::multipleWordsInQuotation()
{
    std::string in = "\"AB ABC\"";
    std::string res = "AB ABC";
    std::istringstream ss(in);
    String str(ss);
    QVERIFY(ss.eof());
    QVERIFY(str == res);
    QVERIFY(*str["0"] == res);
}
}
