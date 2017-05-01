#include "applicationwindow.h"
#include <QLabel>
#include "fsmwidget.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QMenu>
#include <QVBoxLayout>
#include <QInputDialog>

QLabel* ApplicationWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}
ApplicationWindow::ApplicationWindow(QWidget *parent):
    QMainWindow(parent)
{
    widget = new FSMWidget;
    menuBar = new QMenuBar;

    auto fileMenu = new QMenu(QObject::tr("&File"));
    fileMenu->addAction(QObject::tr("Open"));
    fileMenu->addAction(QObject::tr("Save"));
    auto exitAction = fileMenu->addAction(QObject::tr("Exit"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    auto transducerMenu = new QMenu(QObject::tr("Transducer"));
    transducerMenu->addAction(tr("Run <F5>"));
    transducerMenu->addAction(tr("Step forward <F10>"));
    transducerMenu->addAction(tr("Clear output"));
    transducerMenu->addAction(tr("Reset FSM"));
    transducerMenu->addAction(tr("Reset input stream"));
    transducerMenu->addAction(tr("Reset all"));
    auto editInput = transducerMenu->addAction(tr("Edit input"));
    connect(editInput, SIGNAL(triggered()), this, SLOT(editInput()));
    transducerMenu->addAction(tr("Edit pipe"));

    auto viewMenu = new QMenu(QObject::tr("View"));
    auto zoomIn = viewMenu->addAction(tr("Zoom In"));
    connect(zoomIn, SIGNAL(triggered()), widget, SLOT(zoomIn()));
    auto zoomOut = viewMenu->addAction(tr("Zoom Out"));
    connect(zoomOut, SIGNAL(triggered()), widget, SLOT(zoomOut()));
    auto modelProperties = viewMenu->addAction(tr("Model Properties"));
    connect(modelProperties, SIGNAL(triggered()), widget, SLOT(zoomOut()))

    auto helpMenu = new QMenu(QObject::tr("Help"));
    auto credits = helpMenu->addAction(tr("Credits"));
    connect(credits, SIGNAL(triggered()), this, SLOT(showCredits()));

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(transducerMenu);
    menuBar->addMenu(viewMenu);
    menuBar->addMenu(helpMenu);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    input = createLabel("");

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(widget);
    mainLayout->addWidget(input);
    mainLayout->addWidget(createLabel("Transducer result"));

    QWidget* central_widget = new QWidget;
    central_widget->setLayout(mainLayout);
    this->setCentralWidget(central_widget);
}

void ApplicationWindow::editInput()
{
    input->setText("Done");
}

void ApplicationWindow::showCredits()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Application created by Bartłomiej Najdecki in 2017."));
    msgBox.exec();
}

ApplicationWindow::~ApplicationWindow()
{
    delete widget;
    delete menuBar;
}
