/**
 * \file obstacle.cpp
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \version 0.1
 * \date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "obstacle.h"

Obstacle::Obstacle(QPointF _position)
    : size(DEF_OBSTACLE_SIZE)
{
    setPos(_position);
}

Obstacle::Obstacle(QPointF _position, double _size, double _angle)
    : size(_size)
{
    setPos(_position);
    /* find center and rotate if needed */
    setTransformOriginPoint(boundingRect().center());
    setRotation(_angle);
}

Obstacle::Obstacle(QJsonObject &json)
    : size(json["size"].toDouble())
{
    double pos_x = json["position_x"].toDouble();
    double pos_y = json["position_y"].toDouble();
    this->setPos(pos_x, pos_y);
    /* find center and rotate if needed */
    setTransformOriginPoint(boundingRect().center());
    setRotation(json["orientation"].toInt());
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
