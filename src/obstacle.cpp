#include "obstacle.h"

QJsonObject Obstacle::saveToJson(void) const
{
    QJsonObject json;
    json["size"] = size;
    json["position_x"] = scenePos().x();
    json["position_y"] = scenePos().y();
    return json;
}

QRectF Obstacle::boundingRect() const
{
    return QRectF(pos().x(), pos().y(), getSize(), getSize());
}

void Obstacle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::blue);
    painter->drawRect(boundingRect());
}
