#include "obstacle.h"

Obstacle::Obstacle(QPointF _position)
    : size(DEF_OBSTACLE_SIZE)
{
    setPos(_position);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

Obstacle::Obstacle(QPointF _position, double _size, double _angle)
    : size(_size)
{
    setPos(_position);
    setTransformOriginPoint(boundingRect().center());
    setRotation(_angle);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

Obstacle::Obstacle(QJsonObject &json)
    : size(json["size"].toDouble())
{
    double pos_x = json["position_x"].toDouble();
    double pos_y = json["position_y"].toDouble();
    this->setPos(pos_x, pos_y);
    setTransformOriginPoint(boundingRect().center());
    setRotation(json["orientation"].toInt());
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QRectF Obstacle::boundingRect() const
{
    return QRectF(pos().x(), pos().y(), getSize(), getSize());
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::gray);
    painter->drawRect(boundingRect());
}
