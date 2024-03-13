#pragma once

#include <QPainter>
#include <QDebug>
#include "object.h"
#include "debug.h"

class Obstacle : public virtual Object
{
public:
    Obstacle() : Object() {}
    Obstacle(double sizeValue, Position positionValue) : Object(sizeValue, positionValue) {}
    ~Obstacle() {}

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

class ObstacleFactory
{
public:
    Obstacle* createObstacle()
    {
        Obstacle* obstacle = new Obstacle();
        DBG << "created obstacle";
        return obstacle;
    }

    Obstacle* createObstacle(double sizeValue, Position positionValue)
    {
        Obstacle* obstacle = new Obstacle(sizeValue, positionValue);
        DBG << "created obstacle";
        return obstacle;
    }
};
