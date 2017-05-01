#ifndef NODE_H
#define NODE_H
#include <QGraphicsItem>
#include <QGraphicsWidget>
struct Edge;
struct FSMWidget;

struct Node : public QGraphicsItem
{
    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    Node(FSMWidget*, std::string);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void mark();
    void unmark();
    bool operator == (std::string l) { return label.toStdString() == l; }
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    FSMWidget* fsm;
    QString label;
    bool    marked;
};

#endif // NODE_H
