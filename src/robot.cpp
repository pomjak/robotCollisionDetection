#include "robot.h"

Robot::Robot()
    : QObject()
    , QGraphicsItem()
    , m_size(DEF_ROBOT_SIZE)
    , m_speed(DEF_SPEED)
    , m_rotate_by(DEF_ROTATE_BY)
    , m_detection_dist(DEF_DETECT_DIST)
// , m_sim(nullptr)
{
    setPos(0, 0);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
};

Robot::Robot(QPointF _position)
    : QObject()
    , QGraphicsItem()
    , m_size(DEF_ROBOT_SIZE)
    , m_speed(DEF_SPEED)
    , m_rotate_by(DEF_ROTATE_BY)
    , m_detection_dist(DEF_DETECT_DIST)
// , m_sim(nullptr)
{
    setPos(_position);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
};

Robot::Robot(QJsonObject &json)
    : m_size(DEF_ROBOT_SIZE)
    , m_angle(json["orientation"].toDouble())
    , m_speed(json["speed"].toDouble())
    , m_rotate_by(json["rotation"].toDouble())
    , m_detection_dist(json["detection_dist"].toDouble())
// , m_sim(nullptr)
{
    /* Set the initial position of the robot */
    qreal pos_x = json["position_x"].toDouble();
    qreal pos_y = json["position_y"].toDouble();

    setPos(pos_x, pos_y);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QRectF Robot::boundingRect() const
{
    qreal pen_width = 1;
    return QRectF(pos().x() + pen_width / 2, pos().y() + pen_width / 2,
                  size() + pen_width, size() + pen_width);
}

QRectF Robot::newBoundingRect(QPointF newPos) const
{
    qreal pen_width = 1;
    return QRectF(newPos.x() + pen_width / 2, newPos.y() + pen_width / 2,
                  size() + pen_width, size() + pen_width);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::red);
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::green);
    painter->drawPolygon(detectionArea());
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
           << leftBumper() << rightBumper()
           << QPointF((rightBumper().x() +
                       (getDetectDistance() + radius()) * ::cos(getAngle())),
                      (rightBumper().y() +
                       (getDetectDistance() + radius()) * ::sin(getAngle())))
           << QPointF((leftBumper().x() +
                       (getDetectDistance() + radius()) * ::cos(getAngle())),
                      (leftBumper().y() +
                       (getDetectDistance() + radius()) * ::sin(getAngle())));
}

void Robot::advance(int phase)
{
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
                // DEBUG << "Collision detected!";
                // Rotate if obstacle detected
                setAngle(getAngle() + getRotation());
                return;
            }
        }

        setPos(newPos);
    }
    else
    {
        /* Rotate if hitting scene boundary */
        setAngle(getAngle() + getRotation());
        return;
    }
}

// void Robot::mousePressEvent(QGraphicsSceneMouseEvent *event)
// {
//     INFO << "Robot pressed";
//     // update();
//     QGraphicsItem::mousePressEvent(event);
// }

// void Robot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
// {
//     INFO << "Robot released";
//     // update();
//     QGraphicsItem::mouseReleaseEvent(event);
// }
