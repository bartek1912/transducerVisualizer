#ifndef JSONLISTUUT_H
#define JSONLISTUUT_H
#include "JSON/jsonlist.h"
#include <QtTest>

class JSONListUUT : public QObject
{
    Q_OBJECT
public:
    JSONListUUT();
private:
    void TestEquity(std::string, std::string);
    std::unique_ptr<JSONList> list;
private Q_SLOTS:
    void EmptyList();
    void Singleton();
    void ListOfStrings();
    /*void ListOfObjects();
    void ListOfLists();*/
};

#endif // JSONLISTUUT_H
