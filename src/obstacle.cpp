#include "obstacle.h"

Obstacle::Obstacle(QJsonObject& json)
    :size(json["size"].toDouble())
{
    double pos_x = json["position_x"].toDouble();
    double pos_y = json["position_y"].toDouble();
    this->setPos(pos_x, pos_y);
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
