#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QInputDialog>
#include "fsmwidget.h"

class ApplicationWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit ApplicationWindow(QWidget *parent = 0);
    ~ApplicationWindow();
private:
    QLabel* createLabel(const QString &text);
    FSMWidget* widget;
    QMenuBar* menuBar;
    QLabel* input;
public slots:
    void editInput();
    void showCredits();
    void notImplemented();
};

#endif // APPLICATIONWINDOW_H
