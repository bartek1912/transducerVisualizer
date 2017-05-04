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
 * -Uruchomienie transducera (naprawienie etykiet, dodanie testów bo coś nie działa)
 * -Konwersja na transducer moore'a
 * -Dodanie pipe'ów
 * */

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ApplicationWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
