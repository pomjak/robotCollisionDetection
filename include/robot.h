#pragma once

#include <cmath>
#include <QGraphicsItem>
#include <QPainter>
#include "object.h"
#include "debug.h"

class Robot : public virtual Object
{
private:
    double orientation;
    double rotation;
    double speed;

public:
    Robot() : Object(), orientation(0.0), rotation(0.0), speed(0.0) {}
    ~Robot() {}

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    double getOrientation() const;
    void setOrientation(double value);
    double getRotation() const;
    void setRotation(double value);
    double getSpeed() const;
    void setSpeed(double value);

    void move();
    void detectCollision();
    void rotate();
    void manualControl();
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
