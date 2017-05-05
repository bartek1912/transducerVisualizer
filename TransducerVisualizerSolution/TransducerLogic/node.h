#ifndef NODE_H
#define NODE_H
#include <QGraphicsItem>
#include <QGraphicsWidget>
struct FSMWidget;
struct Edge;

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
    bool is_prev_marked() const;
    bool is_marked() const;
    bool operator == (std::string l) { return label.toStdString() == l; }
    void addEdge(Edge*);
protected:
    QList<Edge *> edgeList;
    void refresh();
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    FSMWidget* fsm;
    QString label;
    bool    marked;
    bool    prev_marked;
};

#endif // NODE_H
