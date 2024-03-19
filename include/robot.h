#pragma once

#include <cmath>
#include <QGraphicsItem>
#include <QPainter>
#include "object.h"
#include "obstacle.h"
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
        unsigned int idValue, \
        robotAttributes attributesValues)           \
        : \
        Object(sizeValue, positionValue, idValue), \
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
    std::vector<Position> getDetectionPoints();
    bool detectCollisions(const std::vector<Position>& detectionPoints, const std::vector<Object*>& objectList);
    bool detectCollisionAtPoint(const std::vector<Object*>& objectList, Position& pointOfInterest);
    bool detectBorders(const std::vector<Position>& detectionPoints,double viewSize);
    void rotate();
};

class RobotFactory
{
public:
    Robot* createRobot(double sizeValue, Position positionValue, unsigned int idValue, robotAttributes attributes)
    {
        Robot* robot = new Robot(sizeValue, positionValue, idValue, attributes);
        DBG << "created robot";
        return robot;
    }
};

inline Position calculateDeltaPosition(double speed, double& direction) { return Position{ speed * std::cos(direction), speed * std::sin(direction) }; }