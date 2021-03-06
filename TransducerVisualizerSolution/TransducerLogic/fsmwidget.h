#ifndef FSMWIDGET_H
#define FSMWIDGET_H

#include <QGraphicsView>
#include <vector>
#include <sstream>
#include "node.h"
#include "Transducer/transducer.h"

class FSMWidget: public QGraphicsView, public Transducer
{
    Q_OBJECT
    enum {WIDTH = 700, HEIGHT = 400, MARGIN = 10};
    std::string name;
public:
    FSMWidget(std::string = "nawiasy.json", QWidget *parent = 0);
    virtual ~FSMWidget();
    void scaleView(qreal);
    void offsetNodes(int, int);
    void reset() override;
    void editInput(std::string);
    QString getDescription();
    std::string getStack();
protected:
    void loadTransducer(std::string);
    void updateTransducerView();
    std::map<std::string, Node*> nodes;
    QGraphicsScene* scene;
public slots:
    void zoomIn();
    void zoomOut();
    virtual void nextStep(char act);
    void organizeOnLine();
    void organizeOnGrid();
    void organizeOnRegularPolygon();
    void convertToMoore();
    void convertToMealy();
};

#endif // FSMWIDGET_H
