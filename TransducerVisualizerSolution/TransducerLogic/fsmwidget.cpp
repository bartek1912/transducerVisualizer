#include "fsmwidget.h"
#include "node.h"
#include "edge.h"
#include "Transducer/transducerfactory.h"
#include <QMessageBox>

FSMWidget::FSMWidget(std::string file_path, QWidget* parent)
    :QGraphicsView(parent)
    ,scene(new QGraphicsScene(this))
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
    setWindowTitle(tr("Transducer Visualizer"));
    loadTransducer(file_path);
    if(nodes.size() <= 2)
        organizeOnLine();
    else if(nodes.size() <= 8)
        organizeOnRegularPolygon();
    else
       organizeOnGrid();
}

void FSMWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void FSMWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void FSMWidget::nextStep(char act)
{
    process(act);
    updateTransducerView();
}

void FSMWidget::loadTransducer(std::string path)
{
    static TransducerFactory factory;
    std::ifstream input(path.c_str());
    static_cast<Transducer&>(*this) = factory.produceTransducer(input);

    for(auto x: nodes)
        delete x.second;
    nodes.clear();
    auto states = states_description();
    for(auto s: states)
    {
        auto node = new Node(this, s);
        assert(nodes.find(s) == nodes.end() && "Multiple definitions of state");
        nodes[s] = node;
        scene->addItem(node);
    }
#define FROM second.first
#define TO second.second
    for(const auto& x: edge_description())
    {
        if(!(nodes.find(x.FROM) != nodes.end()
                && nodes.find(x.TO) != nodes.end()))
        {
            std::cerr<<"Known nodes:";
            for(auto x: nodes)
                std::cerr<<"'"<<x.first<<"', ";
            std::cerr<<"\n";
            if(nodes.find(x.FROM) == nodes.end())
                std::cerr<<"Can't find node named '"<<x.FROM<<"'\n";
            if(nodes.find(x.TO) == nodes.end())
                std::cerr<<"Can't find node named "<<x.TO<<"\n";
            exit(1);
        }
        scene->addItem(new Edge(nodes[x.FROM],
                            nodes[x.TO], x.first));
    }
    updateTransducerView();
}
#undef FROM
#undef TO

FSMWidget::~FSMWidget()
{
    for(auto x: nodes)
        delete x.second;
    nodes.clear();
    delete scene;
}

void FSMWidget::updateTransducerView()
{
    for(auto& n: nodes)
        if(*n.second == actual)
            n.second->mark();
        else
            n.second->unmark();
    viewport()->update();
}

void FSMWidget::reset()
{
    Transducer::reset();
    for(auto& n: nodes)
    {
        n.second->reset();
        if(*n.second == actual)
            n.second->mark();
    }
}

void FSMWidget::offsetNodes(int y, int x)
{
    for(auto& n: nodes)
        n.second->moveBy(25 * x, 25 * y);
}

void FSMWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}


void FSMWidget::organizeOnLine()
{
    int x = MARGIN, y = MARGIN;
    assert(nodes.size());
    int w = (WIDTH - 2*MARGIN) / std::ceil(nodes.size() - 1), h = (HEIGHT - 2*MARGIN) / std::ceil(nodes.size() - 1);
    for(auto& act: nodes)
    {
        Node* node = act.second;
        node->setPos(x, y);
        x += w;
        y += h;
    }

}

void FSMWidget::organizeOnGrid()
{
    int x = MARGIN, y = MARGIN;
    assert(nodes.size());
    int w = (WIDTH - 2*MARGIN) / std::ceil(std::sqrt(nodes.size()) - 1), h = (HEIGHT - 2*MARGIN) / std::floor(std::sqrt(nodes.size()) - 1);
    for(auto& act: nodes)
    {
        Node* node = act.second;
        node->setPos(x, y);
        x += w;
        if(x >= WIDTH)
        {
            x = MARGIN;
            y += h;
        }
    }

}

const double pi = 3.1415;

void FSMWidget::organizeOnRegularPolygon()
{
    int x = WIDTH/2, y = HEIGHT/2, i = 0, w = WIDTH/2 - MARGIN, h = HEIGHT/2 - MARGIN;
    for(auto act: nodes)
    {
        auto node = act.second;
        double delta_x = sin(i * 2.0 * pi / nodes.size()) * w;
        double delta_y = -cos(i * 2.0 * pi / (nodes.size()))*h;
        delta_x += x;
        delta_y += y;
        node->setPos(delta_x,
                     delta_y);
        i++;
    }
}

void FSMWidget::convertToMoore()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Not implemented"));
    msgBox.exec();
}

void FSMWidget::convertToMealy()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Not implemented"));
    msgBox.exec();
}

QString FSMWidget::getDescription()
{
    return (isMealy() ? "Mealy's Transducer" : "Moore's Transducer") + QString(" ") + getName();
}

std::string FSMWidget::getStack()
{
    return actual.getStack();
}
