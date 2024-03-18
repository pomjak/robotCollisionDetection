#include "obstacle.h"

QRectF Obstacle::boundingRect() const
{
    return QRectF(getPosition().x , getPosition().y - (getSize() / 2), getSize(), getSize());
}

void Obstacle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::blue);
    painter->drawRect(boundingRect());
}