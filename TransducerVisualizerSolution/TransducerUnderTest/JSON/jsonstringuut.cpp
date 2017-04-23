#include "jsonstringuut.h"
#include "JSON/jsonstring.h"
#include <QTest>
#include <sstream>
void JSONStringUUT::oneString()
{
    std::string in = "ABC";
    std::istringstream ss(in);
    JSONString str(ss);
    QVERIFY(str == in);
    QVERIFY(*str[0] == in);
}

void JSONStringUUT::stringWithComman()
{
    std::string exp = "AB";
    std::string in = exp + ",";
    std::istringstream ss(in);
    JSONString str(ss);
    QVERIFY(str == exp);
    QVERIFY(*str[0] == exp);

}
