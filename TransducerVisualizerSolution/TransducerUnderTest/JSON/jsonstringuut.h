#ifndef JSONSTRINGUUT_H
#define JSONSTRINGUUT_H

#include <QObject>
namespace JSON
{
class StringUUT : public QObject
{
    Q_OBJECT
public:

private Q_SLOTS:
    void oneString();
    void stringWithComman();
    void oneWordInQuotation();
    void multipleWordsInQuotation();
};
}
#endif // JSONSTRINGUUT_H
