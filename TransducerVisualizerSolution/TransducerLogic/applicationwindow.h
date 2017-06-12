#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QInputDialog>
#include "fsmwidget.h"
#include "transducercontrolwidget.h"

class ApplicationWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit ApplicationWindow(QWidget *parent = 0);
    ~ApplicationWindow();
private:
    QMenuBar *menuBar;
    QTabWidget *tabWidget;
    QLabel  *input, *output;
    std::istringstream fsm_input;
    std::vector<TransducerControlWidget*> transducers;
    std::string initialInputText;
    int currentFSM;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    QWidget* createLabel(const QString &text, QWidget* text2);
public slots:
    void editInput();//TODO split into classes
    void showCredits();
    void notImplemented();
    void resetFSM();
    void resetAll(bool = true);
    void resetInput();
    void addToPipe();
    void zoomInCurrent();
    void zoomOutCurrent();
    void offsetCurrent(int, int);
    void organizeOnLineCurrent();
    void organizeOnGridCurrent();
    void run();
    void nextStep();
    void organizeOnRegularPolygonCurrent();
    void convertToMealy();
    void convertToMoore();
    void removeTransducer();
};

#endif // APPLICATIONWINDOW_H
