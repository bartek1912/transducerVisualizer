#ifndef JSONOBJECTUUT_H
#define JSONOBJECTUUT_H

#include <QObject>

class JSONObjectUUT : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void EmptyObject();
    void OneField();
    void MoreFields();
    void NestedObject();
};

#endif // JSONOBJECTUUT_H
