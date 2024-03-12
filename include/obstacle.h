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
    QRectF boundingRect() const override
    {
        return QRectF(100, 100, 100, 100);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->setPen(Qt::blue);
        painter->setBrush(Qt::blue);
        painter->drawRect(boundingRect());

        DBG << "painted obstacle";
    }
private:
    double size;
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