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

std::vector<Position> Robot::getDetectionPoints()
{
    const double step = 1;

    std::vector<Position> points;

    const Position delta = calculateDeltaPosition(step, attributes.orientation);
    const Position frontBumper = getPosition() + calculateDeltaPosition(getSize() / 2, attributes.orientation);

    Position runner = frontBumper;

    for ( double i = 0; i < attributes.detectionDistance; i += step )
    {
        points.emplace_back(runner);
        runner += delta;
    }

    return points;
}


bool Robot::detectCollisions(const std::vector<Position>& detectionPoints, const std::vector<Object*>& objectList)
{
    for ( Position point : detectionPoints )
    {
        if ( detectCollisionAtPoint(objectList, point) )
            return true;
    }
    return false;
}

bool Robot::detectCollisionAtPoint(const std::vector<Object*>& objectList, Position& pointOfInterest)
{
    for ( Object* obj : objectList )
    {
        if ( this == obj ) //when robot iterates over itself from object list
            continue;

        if ( Robot* robot = dynamic_cast<Robot*>( obj ) )
        {
            continue;
        }
        else if ( Obstacle* obstacle = dynamic_cast<Obstacle*>( obj ) )
        {
            Position leftTop = { obstacle->getPosition().x - ( obstacle->getSize() / 2 ), \
                                        obstacle->getPosition().y - ( obstacle->getSize() / 2 ) };

            Position bottomRight = { obstacle->getPosition().x + ( obstacle->getSize() / 2 ), \
                                        obstacle->getPosition().y + ( obstacle->getSize() / 2 ) };

            return pointOfInterest.containsInRect(leftTop, bottomRight);
        }
    }
    return false;
}
bool Robot::detectBorders(const std::vector<Position>& detectionPoints, double viewSize)
{
    for ( Position point : detectionPoints )
        if ( !point.containsInRect(0, viewSize, 0, viewSize) )
            return true;
    return false;
}


void Robot::rotate()
{
    attributes.orientation += attributes.rotation;
}