#include "fsmwidget.h"
#include "node.h"
#include "Transducer/transducerfactory.h"
const int WIDTH = 400, HEIGHT = 400;

FSMWidget::FSMWidget(QWidget *parent):
    QGraphicsView(parent),
    scene(new QGraphicsScene(this))
{
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, WIDTH, HEIGHT);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(WIDTH, HEIGHT);
    setWindowTitle(tr("Elastic Nodes"));
    loadTransducer("nawiasy.json");
}




void FSMWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void FSMWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void FSMWidget::loadTransducer(std::string path)
{
    static TransducerFactory factory;
    std::ifstream input(path.c_str());
    static_cast<Transducer&>(*this) = factory.produceTransducer(input);

    for(auto x: nodes)
        delete x;
    nodes.clear();
    int x = 0, y = 0;
    for(auto s: states_description())
    {
        nodes.push_back(new Node(this, s));
        scene->addItem(nodes.back());
        nodes.back()->setPos(x, y);
        x += 70;
        if(x >= WIDTH)
        {
            x = 0;
            y += 70;
        }
    }
    updateMarks();
}

FSMWidget::~FSMWidget()
{
    for(auto x: nodes)
        delete x;
    nodes.clear();
    delete scene;
}

void FSMWidget::updateMarks()
{
    for(auto& n: nodes)
        if(*n == actual)
            n->mark();
        else
            n->unmark();
}

void FSMWidget::runTransducer()
{
    updateMarks();
    //while
    //    doTransducerStep();
    //TransducerFactory f;
    //std::ifstream input("nawiasy.json");
    //Transducer t = f.produceTransducer(input);
    //t.process_dash("ABABAAABCABC");
    //std::cout<<t<<"\n";
}

void FSMWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
