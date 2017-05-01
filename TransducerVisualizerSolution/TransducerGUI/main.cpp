#include <QApplication>
#include <QFrame>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <iostream>
#include <fstream>
#include <QLabel>
#include "fsmwidget.h"
#include "applicationwindow.h"
QLabel* createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ApplicationWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
