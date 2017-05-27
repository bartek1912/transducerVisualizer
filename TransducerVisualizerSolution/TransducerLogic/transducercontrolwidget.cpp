#include "transducercontrolwidget.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

TransducerControlWidget::TransducerControlWidget(std::string name, std::string file_path)
    :widget {new FSMWidget(file_path)}
    ,readChars{createLabel("")}
    ,output{createLabel("")}
    ,centralWidget{new QWidget}
    ,name(name)
{

    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* readLayout = new QHBoxLayout;
    QWidget* readWidget = new QWidget;
    readLayout->addWidget(createLabel("Read:"));
    readLayout->addWidget(readChars);
    readWidget->setLayout(readLayout);

    QHBoxLayout* outputLayout = new QHBoxLayout;
    QWidget* outputWidget = new QWidget;
    outputLayout->addWidget(createLabel("Output buffer:"));
    outputLayout->addWidget(output);
    outputWidget->setLayout(outputLayout);

    mainLayout->addWidget(widget);
    mainLayout->addWidget(readWidget);
    mainLayout->addWidget(outputWidget);
    centralWidget->setLayout(mainLayout);
}

QLabel* TransducerControlWidget::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}

void TransducerControlWidget::resetFSM()
{
    widget->reset();
    readChars->setText("");
    output->setText("");
}

std::string TransducerControlWidget::getName()
{
    return name;
}


QWidget* TransducerControlWidget::getWidget()
{
    return centralWidget;
}

void TransducerControlWidget::nextStep(char c)
{
    readChars->setText(readChars->text() + c);
    widget->nextStep(c);
    output->setText(QString::fromStdString(widget->get_output()));
}
QLabel* TransducerControlWidget::getOutputLabel()
{
    return output;
}
