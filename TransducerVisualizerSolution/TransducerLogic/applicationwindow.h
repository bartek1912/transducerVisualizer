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
    QLabel* input, *readChars;
    std::istringstream fsm_input;
protected:
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void run();
    void nextStep();
    void editInput();//TODO split into classes
    void showCredits();
    void resetFSM();
    void resetAll();
    void resetInput();
    void notImplemented();
};

#endif // APPLICATIONWINDOW_H
