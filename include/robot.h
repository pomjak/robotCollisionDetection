#pragma once 

#include <QGraphicsItem>
#include <QPainter>
#include "object.h"
#include "debug.h"

class Robot : public virtual Object
{
private:
public:
    Robot() {}
    ~Robot() {}
    QRectF boundingRect() const 
    {
        return QRectF(10, 10, 100, 100);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) 
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->setPen(Qt::red);
        painter->setBrush(Qt::red);
        painter->drawEllipse(boundingRect());
        DBG << "painted robot";

    }
};

class RobotFactory
{
public:
    Robot* createRobot()
    {
        Robot* robot = new Robot();
        DBG << "created robot";
        return robot;
    }
};
