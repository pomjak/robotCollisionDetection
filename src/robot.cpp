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
    Position delta{ 0.0,0.0 };
    delta.x = attributes.speed * std::cos(attributes.orientation);
    delta.y = attributes.speed * std::sin(attributes.orientation);
    return delta;
}

void Robot::correctBoundaries(int width, int height)
{
    if ( this->pos().x() > width - 1 )
    {
        this->setPos(0, this->pos().y());
    }

    if ( this->pos().x() < 0 )
    {
        this->setPos(width, this->pos().y());
    }

    if ( this->pos().y() > height - 1 )
    {
        this->setPos(this->pos().x(), 0);
    }

    if ( this->pos().y() < 0 )
    {
        this->setPos(this->pos().x(), height);
    }
}

void Robot::detectCollision()
{

}

void Robot::rotate()
{
    attributes.orientation += attributes.rotation;
}

void Robot::manualControl()
{

}
