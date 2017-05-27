#ifndef TransducerControlWidget_H
#define TransducerControlWidget_H
#include <QWidget>
#include <QLabel>
#include "fsmwidget.h"

class TransducerControlWidget: public QWidget
{
    Q_OBJECT
public:
    TransducerControlWidget(std::string);
    FSMWidget* widget;
    QLabel *readChars, *output;
    void resetFSM();
    QWidget* getWidget();
    std::string getName();
    void setInput(std::string);
public:
    void nextStep(char c);
private:
    QLabel* createLabel(const QString &text);
    QWidget* centralWidget;
    std::string name;
};

#endif // TransducerControlWidget_H
