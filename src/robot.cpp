#include "robot.h"

QRectF Robot::boundingRect() const
{
    return QRectF(10, 10, 100, 100);
}

void Robot::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::red);
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect());
    
    DBG << "painted robot";

}