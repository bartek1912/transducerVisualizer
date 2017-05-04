#include "applicationwindow.h"
#include <QLabel>
#include "fsmwidget.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QMenu>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QDir>

QLabel* ApplicationWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}
ApplicationWindow::ApplicationWindow(QWidget *parent)
    :QMainWindow(parent)
    ,widget {new FSMWidget}
    ,menuBar{new QMenuBar}
    ,input{createLabel("")}
    ,readChars{createLabel("")}
{
    auto fileMenu = new QMenu(QObject::tr("File"));
    connect(fileMenu->addAction(QObject::tr("Open")),
                                SIGNAL(triggered()), this, SLOT(notImplemented()));
    connect(fileMenu->addAction(QObject::tr("Save")),
                                SIGNAL(triggered()), this, SLOT(notImplemented()));
    auto exitAction = fileMenu->addAction(QObject::tr("Exit"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    auto transducerMenu = new QMenu(QObject::tr("Transducer"));
    connect(transducerMenu->addAction(tr("Run <F5>")),
                              SIGNAL(triggered()), this, SLOT(run()));
    connect(transducerMenu->addAction(tr("Step forward <F10>")),
                              SIGNAL(triggered()), this, SLOT(nextStep()));
    connect(transducerMenu->addAction(tr("Clear output")),
                              SIGNAL(triggered()), this, SLOT(notImplemented()));
    connect(transducerMenu->addAction(tr("Reset FSM")),
                              SIGNAL(triggered()), this, SLOT(resetFSM()));
    connect(transducerMenu->addAction(tr("Reset input stream")),
                              SIGNAL(triggered()), this, SLOT(resetInput()));
    connect(transducerMenu->addAction(tr("Reset all")),
            SIGNAL(triggered()), this, SLOT(resetAll()));
    connect(transducerMenu->addAction(tr("Edit input")),
            SIGNAL(triggered()), this, SLOT(editInput()));
    transducerMenu->addAction(tr("Edit pipe"));

    auto viewMenu = new QMenu(QObject::tr("View"));
    connect(viewMenu->addAction(tr("Zoom In")),
            SIGNAL(triggered()), widget, SLOT(zoomIn()));
    connect(viewMenu->addAction(tr("Zoom Out")),
            SIGNAL(triggered()), widget, SLOT(zoomOut()));

    auto helpMenu = new QMenu(QObject::tr("Help"));
    connect(helpMenu->addAction(tr("Credits")),
            SIGNAL(triggered()), this, SLOT(showCredits()));

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(transducerMenu);
    menuBar->addMenu(viewMenu);
    menuBar->addMenu(helpMenu);

    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(widget);
    mainLayout->addWidget(readChars);
    mainLayout->addWidget(input);
    mainLayout->addWidget(createLabel("Transducer result"));

    QWidget* central_widget = new QWidget;
    central_widget->setLayout(mainLayout);
    this->setCentralWidget(central_widget);
}

void ApplicationWindow::run()
{
    while(!fsm_input.eof())
        nextStep();
}
void ApplicationWindow::nextStep()
{
    if(fsm_input.peek() == 0)
    {
        fsm_input.ignore();
        input->setText(input->text().mid(1));
    }
    if(!fsm_input.eof())
    {
        readChars->setText(readChars->text() + fsm_input.peek());
        input->setText(input->text().mid(1));
        widget->nextStep(fsm_input.get());
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Input is empty"));
        msgBox.exec();
    }
}

void ApplicationWindow::editInput()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Type new input"),
                                         tr("New input:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
        fsm_input.str(text.toStdString());
        fsm_input.clear();
        input->setText(text);
        QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Transducer"), "Reset transducer?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
            resetFSM();
    }
}

void ApplicationWindow::resetAll()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Transducer"), "Are you sure to reset all?",
                                QMessageBox::Yes|QMessageBox::No);

  if (reply == QMessageBox::Yes)
  {
        resetInput();
        resetFSM();
  }
}
void ApplicationWindow::resetFSM()
{
    widget->reset();
    readChars->setText("");
}
void ApplicationWindow::resetInput()
{
    fsm_input.str((readChars->text() + input->text()).toStdString());
    fsm_input.clear();
    input->setText(readChars->text() + input->text());
    readChars->setText("");
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


void ApplicationWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_F10:
        nextStep();
        break;
    case Qt::Key_F5:
        run();
        break;
    case Qt::Key_I:
        editInput();
        break;
    case Qt::Key_Plus:
        widget->zoomIn();
        break;
    case Qt::Key_Minus:
        widget->zoomOut();
        break;
    case Qt::Key_R:
        resetAll();
        break;
    case Qt::Key_S:
        widget->offsetNodes(-1, 0);
        break;
    case Qt::Key_W:
        widget->offsetNodes(1, 0);
        break;
    case Qt::Key_D:
        widget->offsetNodes(0, -1);
        break;
    case Qt::Key_A:
        widget->offsetNodes(0, 1);
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

ApplicationWindow::~ApplicationWindow()
{
    delete widget;
    delete menuBar;
}
