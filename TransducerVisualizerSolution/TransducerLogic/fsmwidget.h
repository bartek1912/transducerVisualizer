#ifndef FSMWIDGET_H
#define FSMWIDGET_H

#include <QGraphicsView>
#include <vector>
#include "node.h"
#include "Transducer/transducer.h"

class FSMWidget: public QGraphicsView, public Transducer
{
    Q_OBJECT
public:
    FSMWidget(QWidget *parent = 0);
    virtual ~FSMWidget();
    void runTransducer();
    void scaleView(qreal);
protected:
    void loadTransducer(std::string);
    void updateMarks();
    std::vector<Node*> nodes;
    QGraphicsScene* scene;
public slots:
    void zoomIn();
    void zoomOut();
};

#endif // FSMWIDGET_H
