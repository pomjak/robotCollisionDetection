#include "robot.h"

QRectF Robot::boundingRect() const
{
    return QRectF(getPosition().x - (getSize() / 2), getPosition().y - (getSize() / 2), getSize(), getSize());
}

void Robot::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::red);
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());


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
    return calculateDeltaPosition(attributes.speed, attributes.orientation);
}

std::vector<Position> Robot::getDetectionPoints()
{
    const double step = 1;

    std::vector<Position> points;

    const Position delta = calculateDeltaPosition(step, attributes.orientation);
    const Position frontBumper = position + calculateDeltaPosition(getSize() / 2, attributes.orientation);
    const Position endPoint = frontBumper + calculateDeltaPosition(attributes.detectionDistance, attributes.orientation);


    for ( Position runner = frontBumper; distance(runner, endPoint) > step; runner += delta )
    {
        points.push_back(runner);
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

            DBG << "Point:" << pointOfInterest.x << pointOfInterest.y;
            if ( pointOfInterest.containsInRect(leftTop, bottomRight) )
            {
                DBG << "robot_x :" << this->getPosition().x;
                DBG << "robot_y :" << this->getPosition().y;
                DBG << "robot_size :" << this->getSize();
                DBG << "-----------";

                DBG << "obstacle_x : "<< obstacle->getPosition().x;
                DBG << "obstacle_y : "<< obstacle->getPosition().y;
                DBG << "obstacle size : "<< obstacle->getSize();
                DBG << "-----------";

                DBG << leftTop.x << leftTop.y;
                DBG << bottomRight.x << bottomRight.y;
                DBG << "Point:" << pointOfInterest.x << pointOfInterest.y;
                DBG << "point is indeed in rectangle";
                return true;
            }
            else return false;
        }
    }
    return false;
}

void Robot::rotate()
{
    attributes.orientation += attributes.rotation;
    DBG << "Robot rotated";
}