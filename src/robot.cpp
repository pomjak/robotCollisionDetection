#include "robot.h"

QRectF Robot::boundingRect() const
{
    return QRectF(position.x, position.y, size, size);
}

void Robot::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::red);
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect());

    DBG << "painted robot";

}

inline double Robot::getOrientation() const
{
    return orientation;
}

void Robot::setOrientation(double newOrientation)
{
    orientation = newOrientation;
}

inline double Robot::getRotation() const
{
    return rotation;
}

void Robot::setRotation(double newRotation)
{
    rotation = newRotation;
}

inline double Robot::getSpeed() const
{
    return speed;
}

void Robot::setSpeed(double newSpeed)
{
    speed = newSpeed;
}

Position Robot::newPosition()
{
    Position delta{ 0.0,0.0 };
    delta.x = speed * std::cos(orientation);
    delta.y = speed * std::sin(orientation);
    return delta;
}

void Robot::detectCollision()
{

}

void Robot::rotate()
{

}

void Robot::manualControl()
{

}
