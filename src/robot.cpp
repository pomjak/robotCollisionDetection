#include "robot.h"

QRectF Robot::boundingRect() const
{
    return QRectF(getPosition().x - getSize(), getPosition().y - getSize(), getSize(), getSize());
}

void Robot::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::red);
    painter->drawEllipse(boundingRect());

    QPointF center = boundingRect().center();
    QPointF arrowEnd = QPointF(center.x() + getSize() / 2 * cos(attributes.orientation), \
        center.y() + getSize() / 2 * sin(attributes.orientation));

    painter->setPen(Qt::black);
    painter->drawLine(center, arrowEnd);

}

inline double Robot::getOrientation() const
{
    return attributes.orientation;
}

void Robot::setOrientation(double newOrientation)
{
    attributes.orientation = newOrientation;
}

inline double Robot::getRotation() const
{
    return attributes.rotation;
}

void Robot::setRotation(double newRotation)
{
    attributes.rotation = newRotation;
}

inline double Robot::getSpeed() const
{
    return attributes.speed;
}

void Robot::setSpeed(double newSpeed)
{
    attributes.speed = newSpeed;
}

Position Robot::newPosition()
{
    return calculateDeltaPosition(attributes.speed, attributes.orientation);
}

bool Robot::detectCollisions(const std::vector<Object*>& objectList)
{
    return false;
}

void Robot::rotate()
{
    attributes.orientation += attributes.rotation;
}