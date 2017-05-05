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
/*
 * Plan:
 * -Konwersja na transducer moore'a
 * -Dodanie pipe'ów
 * -Ładownie transducerów z plików (później)
 * */

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ApplicationWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
