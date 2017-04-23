#include <QString>
#include <QtTest>
#include "JSON/jsonlistuut.h"
#include "JSON/jsonstringuut.h"

class TransducerUnderTestTest : public QObject
{
    Q_OBJECT

public:
    TransducerUnderTestTest();
};

TransducerUnderTestTest::TransducerUnderTestTest()
{
}


int main(int argc, char** argv)
{
   int status = 0;
   {
      TransducerUnderTestTest tc;
      status |= QTest::qExec(&tc, argc, argv);
   }
   {
      JSONStringUUT tc;
      status |= QTest::qExec(&tc, argc, argv);
   }
   {
      JSONListUUT tc;
      status |= QTest::qExec(&tc, argc, argv);
   }
   return status;
}
#include "tst_transducerundertesttest.moc"
