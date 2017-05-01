#ifndef JSONLISTUUT_H
#define JSONLISTUUT_H
#include "JSON/jsonlist.h"
#include <QtTest>
namespace JSON
{
class ListUUT : public QObject
{
    Q_OBJECT
public:
    ListUUT();
private:
    void TestEquity(std::string, std::string);
    List list;
private Q_SLOTS:
    void EmptyList();
    void Singleton();
    void ListOfStrings();
    void ListOfLists();
    void ListOfObjects();
};
}

#endif // JSONLISTUUT_H
