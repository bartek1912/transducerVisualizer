#include <QString>
#include <QtTest>
#include "JSON/jsonlistuut.h"
#include "JSON/jsonstringuut.h"
#include "JSON/jsonobjectuut.h"

int main(int argc, char** argv)
{
   int status = 0;
   {
      JSON::StringUUT tc;
      if(status |= QTest::qExec(&tc, argc, argv))
         return status;
   }
   {
      JSON::ListUUT tc;
      if(status |= QTest::qExec(&tc, argc, argv))
          return status;
   }
   {
      JSON::ObjectUUT tc;
      if(status |= QTest::qExec(&tc, argc, argv))
          return status;
   }
   return status;
}
#include "tst_transducerundertesttest.moc"
