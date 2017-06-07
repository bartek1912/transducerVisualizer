#ifndef STACKWIDGET_H
#define STACKWIDGET_H
#include <QWidget>
#include <QLabel>

class StackWidget: public QWidget
{
public:
    StackWidget();
    void setContent(std::string);
    QLabel* stack;
};

#endif // STACKWIDGET_H
