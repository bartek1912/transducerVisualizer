#ifndef JSONOBJECTUUT_H
#define JSONOBJECTUUT_H

#include <QObject>

namespace JSON
{
class ObjectUUT : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void EmptyObject();
    void OneField();
    void MoreFields();
    void NestedObject();
    void ListAsAField();
};
}

#endif // JSONOBJECTUUT_H
