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
    double detectionDistance;
};


class Robot : public virtual Object
{
private:
    robotAttributes attributes;

public:
    Robot(double sizeValue, \
        Position positionValue, \
        robotAttributes attributesValues)   \
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
    bool detectCollision(const std::vector<Object*>& objectList);
    void rotate();
    void manualControl();
};

class RobotFactory
{
public:
    Robot* createRobot(double sizeValue, Position positionValue, robotAttributes attributes)
    {
        Robot* robot = new Robot(sizeValue, positionValue, attributes);
        DBG << "created robot";
        return robot;
    }
};
