#pragma once

#include <cmath>
#include <QGraphicsItem>
#include <QPainter>
#include "object.h"
#include "debug.h"
struct robotAttributes
{
    double orientation;
    double rotation;
    double speed;
};


class Robot : public virtual Object
{
private:
    robotAttributes attributes;

public:
    Robot() : Object(), attributes{0.0,0.0,0.0} {}
    Robot(double sizeValue, \
        Position positionValue, \
        robotAttributes attributesValues) \
        : \
        Object(sizeValue, positionValue), \
        attributes(attributesValues) {}
    ~Robot() {}

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    double getOrientation() const;
    void setOrientation(double newOrientation);
    double getRotation() const;
    void setRotation(double newRotation);
    double getSpeed() const;
    void setSpeed(double newSpeed);

    Position newPosition();
    void correctBoundaries(int width, int height);
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

    Robot* createRobot(double sizeValue, Position positionValue, robotAttributes attributes)
    {
        Robot* robot = new Robot(sizeValue, positionValue, attributes);
        DBG << "created robot";
        return robot;
    }
};
