#pragma once 

#include <QPainter>
#include <QDebug>
#include "object.h"
#include "debug.h"

class Obstacle : public virtual Object
{
public:
    Obstacle() {}
    ~Obstacle() {}

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
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
};