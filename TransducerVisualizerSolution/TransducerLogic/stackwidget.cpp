#include "stackwidget.h"
#include "verticallabel.h"
#include <QLabel>
#include <QHBoxLayout>
StackWidget::StackWidget():
    QWidget(NULL)
  ,stack{new QLabel("")}
{
    QHBoxLayout* layout = new QHBoxLayout;

    QLabel *label = new QLabel("Stack");
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    layout->addWidget(label);

    QFont font = stack->font();
    font.setPointSize(24);
    font.setBold(true);
    stack->setFont(font);
    layout->addWidget(stack);

    resize(100, height());
    setLayout(layout);
}
void StackWidget::setContent(std::string t)
{
    stack->setText(QString::fromStdString(t));
}
