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
    connect(fileMenu->addAction(QObject::tr("Open")),
                                SIGNAL(triggered()), this, SLOT(notImplemented()));
    connect(fileMenu->addAction(QObject::tr("Save")),
                                SIGNAL(triggered()), this, SLOT(notImplemented()));
    auto exitAction = fileMenu->addAction(QObject::tr("Exit"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    auto transducerMenu = new QMenu(QObject::tr("Transducer"));
    connect(transducerMenu->addAction(tr("Run <F5>")),
                              SIGNAL(triggered()), this, SLOT(notImplemented()));
    connect(transducerMenu->addAction(tr("Step forward <F10>")),
                              SIGNAL(triggered()), this, SLOT(notImplemented()));
    connect(transducerMenu->addAction(tr("Clear output")),
                              SIGNAL(triggered()), this, SLOT(notImplemented()));
    connect(transducerMenu->addAction(tr("Reset FSM")),
                              SIGNAL(triggered()), this, SLOT(notImplemented()));
    connect(transducerMenu->addAction(tr("Reset input stream")),
                              SIGNAL(triggered()), this, SLOT(notImplemented()));
    connect(transducerMenu->addAction(tr("Reset all")),
            SIGNAL(triggered()), this, SLOT(notImplemented()));
    connect(transducerMenu->addAction(tr("Edit input")),
            SIGNAL(triggered()), this, SLOT(editInput()));
    transducerMenu->addAction(tr("Edit pipe"));

    auto viewMenu = new QMenu(QObject::tr("View"));
    connect(viewMenu->addAction(tr("Zoom In")),
            SIGNAL(triggered()), widget, SLOT(zoomIn()));
    connect(viewMenu->addAction(tr("Zoom Out")),
            SIGNAL(triggered()), widget, SLOT(zoomOut()));
    connect(viewMenu->addAction(tr("Model Properties")),
            SIGNAL(triggered()), this, SLOT(notImplemented()));

    auto helpMenu = new QMenu(QObject::tr("Help"));
    connect(helpMenu->addAction(tr("Credits")),
            SIGNAL(triggered()), this, SLOT(showCredits()));

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

void ApplicationWindow::notImplemented()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Not implemented"));
    msgBox.exec();
}

ApplicationWindow::~ApplicationWindow()
{
    delete widget;
    delete menuBar;
}
