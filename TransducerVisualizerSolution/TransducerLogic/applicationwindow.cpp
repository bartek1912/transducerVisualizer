#include "applicationwindow.h"
#include <QLabel>
#include "fsmwidget.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QMenu>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QDir>
#include <QFileDialog>

ApplicationWindow::ApplicationWindow(QWidget *parent)
    :QMainWindow(parent)
    ,menuBar{new QMenuBar}
    ,tabWidget{new QTabWidget}
    ,input{new QLabel}
    ,output{new QLabel}
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
    connect(transducerMenu->addAction(tr("Convert to moore'a")),
            SIGNAL(triggered()), this, SLOT(convertToMoore()));
    connect(transducerMenu->addAction(tr("Convert to mealy")),
            SIGNAL(triggered()), this, SLOT(convertToMealy()));

    auto pipeMenu = new QMenu(QObject::tr("Pipe"));
    connect(pipeMenu->addAction(tr("Add transducer")),
                              SIGNAL(triggered()), this, SLOT(addToPipe()));
    connect(pipeMenu->addAction(tr("Remove transducer")),
                              SIGNAL(triggered()), this, SLOT(removeTransducer()));
    connect(pipeMenu->addAction(tr("Edit input")),
            SIGNAL(triggered()), this, SLOT(editInput()));

    auto viewMenu = new QMenu(QObject::tr("View"));
    connect(viewMenu->addAction(tr("Zoom In")),
            SIGNAL(triggered()), this, SLOT(zoomInCurrent()));
    connect(viewMenu->addAction(tr("Zoom Out")),
            SIGNAL(triggered()), this, SLOT(zoomOutCurrent()));
    connect(viewMenu->addAction(tr("Arrange nodes on line")),
            SIGNAL(triggered()), this, SLOT(organizeOnLineCurrent()));
    connect(viewMenu->addAction(tr("Arrange nodes on grid")),
            SIGNAL(triggered()), this, SLOT(organizeOnGridCurrent()));
    connect(viewMenu->addAction(tr("Arrange nodes on regular polygon")),
            SIGNAL(triggered()), this, SLOT(organizeOnRegularPolygonCurrent()));
    auto helpMenu = new QMenu(QObject::tr("Help"));
    connect(helpMenu->addAction(tr("Credits")),
            SIGNAL(triggered()), this, SLOT(showCredits()));

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(pipeMenu);
    menuBar->addMenu(transducerMenu);
    menuBar->addMenu(viewMenu);
    menuBar->addMenu(helpMenu);

    QWidget* window = new QWidget;
    QVBoxLayout* windowLayout = new QVBoxLayout;
    windowLayout->setMenuBar(menuBar);
    windowLayout->addWidget(tabWidget);
    windowLayout->addWidget(createLabel("Pipe Input:", input));
    windowLayout->addWidget(createLabel("Pipe Output:", output));
    window->setLayout(windowLayout);
    this->setCentralWidget(window);
}\

void ApplicationWindow::removeTransducer()
{
    int id = tabWidget->currentIndex();
    if(id < int(transducers.size()))
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Transducer"), QString::fromStdString("Do you want erase transducer named " + transducers[id]->getName() + " ?"),
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            int id = tabWidget->currentIndex();
            transducers.erase(transducers.begin() + id);
            tabWidget->removeTab(id);
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("No transducer selected"));
        msgBox.exec();
    }
}

void ApplicationWindow::addToPipe()
{
    bool ok2;
    QString path = QFileDialog::getOpenFileName(this, tr("Open Transducer"),
                                                QDir::currentPath(), tr("JSON Files (*.json)"));
    QString text = QInputDialog::getText(this, tr("Add new transducer"),
                                         tr("Type name of new transducer:"), QLineEdit::Normal,
                                         "", &ok2);
    if(ok2 && !text.isEmpty() && !path.isEmpty())
    {
        auto w = new TransducerControlWidget(text.toStdString(), path.toStdString());
        transducers.push_back(w);
        tabWidget->addTab(w->getWidget(), w->getName().c_str());
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Wrong file given or transducer name."));
        msgBox.exec();
    }
}

void ApplicationWindow::editInput()
{
    if(transducers.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("First add some transducer"));
        msgBox.exec();
    }
    else
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Type new input"),
                                             tr("New input for first transducer in pipe:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty())
        {
            initialInputText = text.toStdString();
            resetInput();
            QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Transducer"), "Reset transducers?",
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes)
                resetFSM();
        }
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
    for(auto x: transducers)
        x->resetFSM();
}
void ApplicationWindow::resetInput()
{
    tabWidget->setCurrentIndex(0);
    fsm_input.str(initialInputText);
    fsm_input.clear();
    input->setText(QString::fromStdString(initialInputText));
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

QWidget* ApplicationWindow::createLabel(const QString &text, QWidget* w2)
{
    QHBoxLayout* readLayout = new QHBoxLayout;
    QWidget* readWidget = new QWidget;

    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);

    readLayout->addWidget(label);
    readLayout->addWidget(w2);
    readWidget->setLayout(readLayout);
    return readWidget;
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
        zoomInCurrent();
        break;
    case Qt::Key_Minus:
        zoomOutCurrent();
        break;
    case Qt::Key_R:
        resetAll();
        break;
    case Qt::Key_S:
        offsetCurrent(-1, 0);
        break;
    case Qt::Key_W:
        offsetCurrent(1, 0);
        break;
    case Qt::Key_D:
        offsetCurrent(0, -1);
        break;
    case Qt::Key_A:
        offsetCurrent(0, 1);
        break;
    case Qt::Key_T:
        addToPipe();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

ApplicationWindow::~ApplicationWindow()
{
    delete menuBar;
    for(auto x: transducers)
        delete x;
}

void ApplicationWindow::zoomInCurrent()
{
    transducers[tabWidget->currentIndex()]->widget->zoomIn();
}

void ApplicationWindow::zoomOutCurrent()
{
    transducers[tabWidget->currentIndex()]->widget->zoomOut();
}

void ApplicationWindow::offsetCurrent(int y, int x)
{
    transducers[tabWidget->currentIndex()]->widget->offsetNodes(y, x);
}


void ApplicationWindow::organizeOnLineCurrent()
{
    transducers[tabWidget->currentIndex()]->widget->organizeOnLine();
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
        input->setText(input->text().mid(1));//cut first string
    }
    if(!fsm_input.eof())
    {
        input->setText(input->text().mid(1));
        transducers[tabWidget->currentIndex()]->nextStep(fsm_input.get());
        output->setText(transducers.back()->getOutputLabel()->text());
    }
    else
    {
        if(tabWidget->currentIndex() + 1 < int(transducers.size()))
        {
            fsm_input.str(transducers[tabWidget->currentIndex()]->getOutputLabel()->text().toStdString());
            fsm_input.clear();
            tabWidget->setCurrentIndex(tabWidget->currentIndex()+1);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText(tr("Input is empty"));
            msgBox.exec();
        }
    }

}

void ApplicationWindow::organizeOnGridCurrent()
{
    transducers[tabWidget->currentIndex()]->widget->organizeOnGrid();
}

void ApplicationWindow::organizeOnRegularPolygonCurrent()
{
    transducers[tabWidget->currentIndex()]->widget->organizeOnRegularPolygon();
}

void ApplicationWindow::convertToMealy()
{
    if(transducers[tabWidget->currentIndex()]->widget->isMealy())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("It is Mealy's transducer"));
        msgBox.exec();
    }
}

void ApplicationWindow::convertToMoore()
{
    if(transducers[tabWidget->currentIndex()]->widget->isMoore())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("It is Moore's transducer"));
        msgBox.exec();
    }
}
