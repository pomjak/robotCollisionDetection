#include "robot.h"

QJsonObject Robot::saveToJson(void) const
{
    QJsonObject json;
    json["orientation"] = orientation;
    json["speed"] = speed;
    json["rotation"] = rotation;
    json["size"] = size;
    json["position_x"] = scenePos().x();
    json["position_y"] = scenePos().y();
    return json;
}

QRectF Robot::boundingRect() const
{
    return QRectF(pos().x(), pos().y(), getSize(), getSize());
}
void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::red);
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());

    QPointF center = boundingRect().center();
    QPointF arrowEnd = QPointF(center.x() + getSize() / 2 * cos(orientation),
                               center.y() + getSize() / 2 * sin(orientation));

    painter->drawLine(center, arrowEnd);
}
