#include "hitbox.h"

QRectF Hitbox::boundingRect() const
{
    QRectF hitboxRect = QRectF(-getLength() / 2, -getWidth() / 2, getLength(), getWidth());

    QTransform rotationTransform;
    QPointF center = position.toQPointF();
    // rotationTransform.translate(center.x(), center.y());
    rotationTransform.rotateRadians(orientation);
    // rotationTransform.translate(-center.x(), -center.y());

    QPointF rotatedTopLeft = rotationTransform.map(hitboxRect.topLeft());
    QPointF rotatedBottomRight = rotationTransform.map(hitboxRect.bottomRight());

    QRectF boundingRect(rotatedTopLeft, rotatedBottomRight);

    return boundingRect;
}


void Hitbox::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());
}