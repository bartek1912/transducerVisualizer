#include <QString>
#include <QtTest>
#include "JSON/jsonlistuut.h"
#include "JSON/jsonstringuut.h"
#include "JSON/jsonobjectuut.h"

int main(int argc, char** argv)
{
   int status = 0;
   {
      JSONStringUUT tc;
      if(status |= QTest::qExec(&tc, argc, argv))
         return status;
   }
   {
      JSONListUUT tc;
      if(status |= QTest::qExec(&tc, argc, argv))
          return status;
   }
   {
      JSONObjectUUT tc;
      if(status |= QTest::qExec(&tc, argc, argv))
          return status;
   }
   return status;
}
#include "tst_transducerundertesttest.moc"
