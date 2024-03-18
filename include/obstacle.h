#pragma once

#include <QPainter>
#include <QDebug>
#include "object.h"
#include "debug.h"

class Obstacle : public virtual Object
{
public:
    Obstacle(double sizeValue, Position positionValue, unsigned int idValue) : Object(sizeValue, positionValue, idValue) {}
    ~Obstacle() {}

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

class ObstacleFactory
{
public:
    Obstacle* createObstacle(double sizeValue, Position positionValue, unsigned int idValue)
    {
        Obstacle* obstacle = new Obstacle(sizeValue, positionValue, idValue);
        DBG << "created obstacle";
        return obstacle;
    }
};
