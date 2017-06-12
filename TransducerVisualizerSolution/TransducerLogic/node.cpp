#include "node.h"
#include "edge.h"
#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <assert.h>

Node::Node(FSMWidget *graphWidget, std::string name):
    fsm(graphWidget),
    label(name.c_str()),
    marked(false)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    double scale = (marked? 1.5: 1);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-NODE_WIDTH*scale/2 + 3*scale, -NODE_HEIGHT*scale/2 + 3*scale,
                         NODE_WIDTH*scale, NODE_HEIGHT*scale);

    QRadialGradient gradient(-3, -3, 10);
    if(marked || prev_marked)
    {
        gradient.setColorAt(0, Qt::darkGray);
        gradient.setColorAt(1, Qt::black);
    }
    else
    {
        if (option->state & QStyle::State_Sunken) {
            gradient.setCenter(3*scale, 3*scale);
            gradient.setFocalPoint(3*scale, 3*scale);
            gradient.setColorAt(1, QColor(Qt::yellow).light(120));
            gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
        } else {
            gradient.setColorAt(0, Qt::yellow);
            gradient.setColorAt(1, Qt::darkYellow);
        }
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-NODE_WIDTH*scale/2, -NODE_HEIGHT*scale/2, NODE_WIDTH*scale, NODE_HEIGHT*scale);

    QRectF textRect = boundingRect();
    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(11);
    painter->setFont(font);
    if(marked || prev_marked)
        painter->setPen(Qt::white);
    else
        painter->setPen(Qt::black);
    painter->drawText(textRect, Qt::AlignCenter, label);
}

void Node::addEdge(Edge * ed)
{
    assert(ed);
    edgeList << ed;
}

QRectF Node::boundingRect() const
{
    double scale = (marked? 1.5: 1);
    qreal adjust = 2*scale;
    return QRectF( -NODE_WIDTH*scale/2 - adjust, -NODE_HEIGHT*scale/2 - adjust,
                   NODE_WIDTH*scale + 2*adjust, NODE_HEIGHT*scale + 2*adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    double scale = (marked? 1.5: 1);
    path.addEllipse(-NODE_WIDTH*scale/2, -NODE_HEIGHT*scale/2, NODE_WIDTH*scale, NODE_HEIGHT*scale);
    return path;
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        refresh();
        //widget->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
void Node::refresh()
{
    foreach (Edge *edge, edgeList)
        edge->adjust();
}

void Node::mark()
{
    if(marked == false || prev_marked != marked)
        update(boundingRect());
    prev_marked = marked;
    marked = true;
}
void Node::unmark()
{
    if(marked == true || prev_marked != marked)
        update(boundingRect());
    prev_marked = marked;
    marked = false;
}
void Node::reset()
{
    prev_marked = marked = false;
}

bool Node::is_prev_marked() const
{
    return prev_marked;
}
bool Node::is_marked() const
{
    return marked;
}
