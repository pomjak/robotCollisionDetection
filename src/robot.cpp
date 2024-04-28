#include "robot.h"

Robot::Robot()
    : QObject()
    , QGraphicsItem()
    , m_size(DEF_ROBOT_SIZE)
    , m_speed(DEF_SPEED)
    , m_rotate_by(DEF_ROTATE_BY)
    , m_detection_dist(DEF_DETECT_DIST)
{
    setPos(0, 0);
};

Robot::Robot(QPointF _position)
    : QObject()
    , QGraphicsItem()
    , m_size(DEF_ROBOT_SIZE)
    , m_speed(DEF_SPEED)
    , m_rotate_by(DEF_ROTATE_BY)
    , m_detection_dist(DEF_DETECT_DIST)
{
    setPos(_position);
};

Robot::Robot(QJsonObject &json)
    : m_size(DEF_ROBOT_SIZE)
    , m_angle(json["orientation"].toDouble())
    , m_speed(json["speed"].toDouble())
    , m_rotate_by(json["rotation"].toDouble())
    , m_detection_dist(json["detection_dist"].toDouble())
{
    /* Set the initial position of the robot */
    qreal pos_x = json["position_x"].toDouble();
    qreal pos_y = json["position_y"].toDouble();

    setPos(pos_x, pos_y);
}

QRectF Robot::boundingRect() const
{
    /* it is important to include half the pen width in the bounding rect */
    qreal pen_width = 1;
    return QRectF(pos().x() + pen_width / 2, pos().y() + pen_width / 2,
                  size() + pen_width, size() + pen_width);
}

QRectF Robot::newBoundingRect(QPointF newPos) const
{
    /* it is important to include half the pen width in the bounding rect */
    qreal pen_width = 1;
    return QRectF(newPos.x() + pen_width / 2, newPos.y() + pen_width / 2,
                  size() + pen_width, size() + pen_width);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    /* paint circular robot body */
    painter->setPen(Qt::red);
    painter->drawEllipse(boundingRect());

    /* paint detection area */
    painter->setPen(Qt::green);
    painter->drawPolygon(detectionArea());

    /* paint direction arrow */
    painter->setPen(Qt::black);
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
           /* add left and right bumper based on orientation of robot */
           << leftBumper()
           << rightBumper()
           /* from right side move at the end of detection zone in direction of
              orientation */
           << QPointF((rightBumper().x() +
                       (getDetectDistance() + radius()) * ::cos(getAngle())),
                      (rightBumper().y() +
                       (getDetectDistance() + radius()) * ::sin(getAngle())))
           /* same as before */
           << QPointF((leftBumper().x() +
                       (getDetectDistance() + radius()) * ::cos(getAngle())),
                      (leftBumper().y() +
                       (getDetectDistance() + radius()) * ::sin(getAngle())));
}

void Robot::advance(int phase)
{
    /* advance() is called twice: once with step == 0, indicating that item  */
    /* are about to advance, and then with step == 1 for the actual advance. */
    if ( !phase ) return;

    // DEBUG << "X: " << pos().x();
    // DEBUG << "Y: " << pos().y();
    // DEBUG << "Rot: " << getAngle();
    /* Move the robot */
    qreal   dx     = getSpeed() * ::cos(getAngle());
    qreal   dy     = getSpeed() * ::sin(getAngle());
    QPointF newPos = pos() + QPointF(dx, dy);

    /* check if new bound rect is still in scene */
    if ( scene()->sceneRect().contains(
             newBoundingRect(newPos).translated(newPos)) )
    {
        /* get all objects in danger area */
        const QList<QGraphicsItem *> colliding_items = scene()->items(
            mapToScene(detectionArea()), Qt::IntersectsItemShape);

        for ( const auto &item : colliding_items )
        {
            /* ignore itself */
            if ( item != this )
            {
                DEBUG << "Collision detected!";
                /* Rotate if obstacle detected */
                setAngle(getAngle() + getRotation());
                return;
            }
        }
        /* set new position if no item is in detection area */
        setPos(newPos);
    }
    else
    {
        /* Rotate if hitting scene boundary */
        setAngle(getAngle() + getRotation());
        return;
    }
}
