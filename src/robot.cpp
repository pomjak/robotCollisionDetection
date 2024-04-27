#include "robot.h"

Robot::Robot()
    : QObject(), QGraphicsItem(), m_size(DEF_ROBOT_SIZE),
    m_speed(0), m_rotate_by(DEF_ROTATE_BY), m_detection_dist(DEF_DETECT_DIST)
{
    setPos(0, 0);
};

Robot::Robot(QJsonObject& json)
    : m_size(DEF_ROBOT_SIZE), m_angle(json["orientation"].toDouble()),
    m_speed(json["speed"].toDouble()),
    m_rotate_by(json["rotation"].toDouble()),
    m_detection_dist(json["detection_dist"].toDouble())
{
    /* Set the initial position of the robot */
    qreal pos_x = json["position_x"].toDouble();
    qreal pos_y = json["position_y"].toDouble();

    setPos(pos_x, pos_y);
}

QRectF Robot::boundingRect() const
{
    qreal pen_width = 1;
    return QRectF(pos().x() + pen_width / 2, pos().y() + pen_width / 2,
                  size() + pen_width, size() + pen_width);
}

void Robot::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                  QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::red);
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::green);
    painter->drawPolygon(detectionArea());
    painter->setPen(Qt::white);
    painter->drawLine(center(), detectionPoint());
}

QPainterPath Robot::shape() const
{
    QPainterPath path;
    path.addEllipse(this->boundingRect());
    return path;
}

QPolygonF Robot::detectionArea() const
{
    return QPolygonF()
        << leftBumper()
        << rightBumper()
        << QPointF(( rightBumper().x() + ( getDetectDistance() + radius() ) * ::cos(getAngle()) ),
                   ( rightBumper().y() + ( getDetectDistance() + radius() ) * ::sin(getAngle()) ))
        << QPointF(( leftBumper().x() + ( getDetectDistance() + radius() ) * ::cos(getAngle()) ),
                   ( leftBumper().y() + ( getDetectDistance() + radius() ) * ::sin(getAngle()) ));
}

void Robot::advance(int phase)
{
    if ( !phase )
        return;

    DEBUG << "X: " << x();
    DEBUG << "Y: " << y();
    DEBUG << "Rot: " << getAngle();
    /* Move the robot */
    qreal dx = getSpeed() * ::cos(getAngle());
    qreal dy = getSpeed() * ::sin(getAngle());
    QPointF newPos = pos() + QPointF(dx, dy);


    if ( scene()->sceneRect().contains(newPos) )
    {
        setPos(newPos);
        return;
    }
    else
    {
        // Reverse direction if hitting scene boundary
        setAngle(-getAngle());
        return;
    }


    const QList<QGraphicsItem*> colliding_items = scene()->items(mapToScene(detectionArea()));

    DEBUG << "Collisions: " << colliding_items.size();

    for ( const QGraphicsItem* item : colliding_items )
    {
        if ( item != this && item->type() == Obstacle::Type )
        {
            // Rotate if obstacle detected
            setAngle(getAngle() + getRotation());
            break;
        }

    }


}
