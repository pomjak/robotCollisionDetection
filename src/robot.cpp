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


    QPointF center = boundingRect().center();
    QPointF arrowEnd = QPointF(center.x() + size / 2 * cos(attributes.orientation), \
        center.y() + size / 2 * sin(attributes.orientation));

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
    Position delta{ 0.0,0.0 };
    delta.x = attributes.speed * std::cos(attributes.orientation);
    delta.y = attributes.speed * std::sin(attributes.orientation);
    return delta;
}

void Robot::correctBoundaries(int width, int height)
{
    QPointF newPos = pos();

    if ( newPos.x() > width - 1 )
        newPos.setX(0);
    else if ( newPos.x() < 0 )
        newPos.setX(width);

    if ( newPos.y() > height - 1 )
        newPos.setY(0);
    else if ( newPos.y() < 0 )
        newPos.setY(height);

    setPos(newPos);
}

bool Robot::detectCollision(const std::vector<Object*>& objectList)
{
    QPointF center = boundingRect().center();

    QPointF frontBumper{    center.x() + size / 2 * cos(attributes.orientation), \
                            center.y() + size / 2 * sin(attributes.orientation) };

    QPointF detectionAreaEnd{   frontBumper.x() + attributes.detectionDistance * cos(attributes.orientation), \
                                frontBumper.y() + attributes.detectionDistance * sin(attributes.orientation) };

    for ( Object* object : objectList )
    {
        // QLineF(frontBumper, object).length()

    }

    return false;
}

void Robot::rotate()
{
    attributes.orientation += attributes.rotation;
    DBG << "Robot rotated";
}

void Robot::manualControl()
{

}
