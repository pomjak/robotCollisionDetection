#include "obstacle.h"

QRectF Obstacle::boundingRect() const
{
    return QRectF(position.x, position.y, size, size);
}

void Obstacle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::blue);
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());
}