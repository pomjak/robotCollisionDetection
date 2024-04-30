/**
 * \file robot.cpp
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \version 0.1
 * \date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "robot.h"
#include <QWidget>
#include <QtGlobal>

Robot::Robot()
    : QObject()
    , QGraphicsItem()
    , m_size(DEF_ROBOT_SIZE)
    , m_speed(DEF_SPEED)
    , m_rotate_by(DEF_ROTATE_BY)
    , m_detection_dist(DEF_DETECT_DIST)
{
    setPos(0, 0);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setAcceptDrops(true);
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
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setAcceptDrops(true);
};

Robot::Robot(QJsonObject &json)
    : m_size(DEF_ROBOT_SIZE)
{
    /* Set the initial position of the robot */
    qreal pos_x = qBound(0.0, json["x"].toDouble(), (MAX_W - size()));
    qreal pos_y = qBound(0.0, json["y"].toDouble(), (MAX_H - size()));
    /* ? TODO Possibly change min/max values */
    m_angle     = qBound(0.0, json["orientation"].toDouble(), 360.0);
    m_speed     = qBound(1.0, json["speed"].toDouble(), 10.0);
    m_rotate_by = qBound(1.0, json["rotation"].toDouble(), 90.0);
    m_detection_dist =
        qBound(DEF_DETECT_DIST, json["detection_dist"].toDouble(), 100.0);

    setPos(pos_x, pos_y);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setAcceptDrops(true);
}

qreal Robot::size() const { return m_size; }
qreal Robot::angle() const { return m_angle; }
qreal Robot::speed() const { return m_speed; }
qreal Robot::rotateBy() const { return m_rotate_by; }
qreal Robot::detectionDistance() const { return m_detection_dist; }

void Robot::setSize(qreal size) { m_size = size; }
void Robot::setAngle(qreal angle) { m_angle = angle; }
void Robot::setSpeed(qreal speed) { m_speed = speed; }
void Robot::setRotateBy(qreal rotate_by) { m_rotate_by = rotate_by; }
void Robot::setDetectionDistance(qreal dist) { m_detection_dist = dist; }

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setOpacity(0.2);
    painter->setBrush(Qt::darkYellow);
    painter->drawPolygon(detectionArea());
    painter->setPen(Qt::darkCyan);
    painter->setBrush(Qt::darkGray);
    painter->setOpacity(1);
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::darkYellow);
    painter->setBrush(Qt::NoBrush);
    painter->drawLine(center(), detectionPoint());
}

QPainterPath Robot::shape() const
{
    QPainterPath path;
    path.addEllipse(this->boundingRect());
    return path;
}

QRectF Robot::boundingRect() const
{
    return QRectF(pos().x(), pos().y(), size(), size());
}

QRectF Robot::newBoundingRect(QPointF newPos) const
{
    return QRectF(newPos.x(), newPos.y(), size(), size());
}

qreal Robot::radius() const { return size() / 2; }

QPointF Robot::center() const { return boundingRect().center(); }

QPointF Robot::leftBumper() const
{
    return QPointF(center().x() + radius() * ::cos(angle() - (M_PI / 2)),
                   center().y() + radius() * ::sin(angle() - (M_PI / 2)));
}

QPointF Robot::rightBumper() const
{
    return QPointF(center().x() + radius() * ::cos(angle() + (M_PI / 2)),
                   center().y() + radius() * ::sin(angle() + (M_PI / 2)));
}

QPointF Robot::detectionPoint() const
{
    return QPointF(((center().x() + radius() * ::cos(angle())) +
                    (detectionDistance() * ::cos(angle()))),
                   ((center().y() + radius() * ::sin(angle())) +
                    (detectionDistance() * ::sin(angle()))));
}

QPolygonF Robot::detectionArea() const
{
    return QPolygonF()
           << center()
           << QPointF((rightBumper().x() +
                       (detectionDistance() + radius()) * ::cos(angle())),
                      (rightBumper().y() +
                       (detectionDistance() + radius()) * ::sin(angle())))
           << QPointF((leftBumper().x() +
                       (detectionDistance() + radius()) * ::cos(angle())),
                      (leftBumper().y() +
                       (detectionDistance() + radius()) * ::sin(angle())));
}

void Robot::advance(int phase)
{
    /* advance() is called twice: once with step == 0, indicating that item  */
    /* are about to advance, and then with step == 1 for the actual advance. */
    if ( !phase ) return;

    /* Move the robot */
    qreal   dx     = speed() * ::cos(angle());
    qreal   dy     = speed() * ::sin(angle());
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
                // Rotate if obstacle detected
                setAngle(angle() + rotateBy());
                return;
            }
        }
        /* set new position if no item is in detection area */
        setPos(newPos);
    }
    else
    {
        /* Rotate if hitting scene boundary */
        setAngle(angle() + rotateBy());
        return;
    }
}

void Robot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_offset = event->scenePos();
}

void Robot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    INFO << "Robot released...";
    update();
}

void Robot::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF delta  = event->scenePos() - m_offset;
    QPointF newPos = pos() + (delta * 0.5);
    if ( scene()->sceneRect().contains(
             newBoundingRect(newPos).translated(newPos)) )
    {
        DEBUG << "pos: " << mapToScene(pos());
        setPos(newPos);
        DEBUG << "newPos: " << mapToScene(pos());
    }
    m_offset = event->scenePos();
}
