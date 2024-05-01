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
    , m_clockwise(true)
{
    setPos(0, 0);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
};

Robot::Robot(QPointF _pos, double _angle, double _speed, double _rotate,
             double _dist)
    : m_size(DEF_ROBOT_SIZE)
    , m_angle(_angle)
    , m_speed(_speed)
    , m_rotate_by(_rotate)
    , m_detection_dist(_dist)
    , m_clockwise(true)
{
    setPos(_pos);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
}

Robot::Robot(QPointF _position)
    : QObject()
    , QGraphicsItem()
    , m_size(DEF_ROBOT_SIZE)
    , m_speed(DEF_SPEED)
    , m_rotate_by(DEF_ROTATE_BY)
    , m_detection_dist(DEF_DETECT_DIST)
    , m_clockwise(true)
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
    m_clockwise = json["clockwise"].toBool();
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
bool  Robot::clockwise() const { return m_clockwise; }
void  Robot::setSize(qreal size) { m_size = size; }
void  Robot::setAngle(qreal angle) { m_angle = angle; }
void  Robot::setSpeed(qreal speed) { m_speed = speed; }
void  Robot::setRotateBy(qreal rotate_by) { m_rotate_by = rotate_by; }
void  Robot::setDetectionDistance(qreal dist) { m_detection_dist = dist; }
void  Robot::setClockwise(bool c) { m_clockwise = c; }

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

void Robot::rotate()
{
    clockwise() ? setAngle(angle() + rotateBy())
                : setAngle(angle() - rotateBy());
    update();
}

bool Robot::isOutOfBounds()
{
    /*  Check if the detection area is entirely within the scene rect */
    return !scene()->sceneRect().contains(
        mapToScene(detectionArea()).boundingRect());
}

QList<QGraphicsItem *> Robot::getItemsInDetectZone()
{
    /* get all objects in danger area */
    return scene()->items(mapToScene(detectionArea()));
}

void Robot::move()
{
    /* Move the robot */
    qreal   dx     = speed() * ::cos(angle());
    qreal   dy     = speed() * ::sin(angle());
    QPointF newPos = pos() + QPointF(dx, dy);

    /* set new position */
    setPos(newPos);
}

void Robot::advance(int phase)
{
    /* advance() is called twice: once with phase == 0, indicating that item */
    /* are about to advance, and then with phase == 1 for the actual advance */
    if ( !phase ) return;

    if ( isOutOfBounds() )
    {
        /* Rotate if the detection area is outside the scene */
        rotate();
        return;
    }
    const auto collidingItems = getItemsInDetectZone();

    for ( const auto &item : collidingItems )
    {
        /* ignore itself */
        if ( item != this )
        {
            /* Rotate if obstacle detected */
            rotate();
            return;
        }
    }

    /* move if no items are in detection area */
    move();
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
        setPos(newPos);
    }
    m_offset = event->scenePos();
}

void Robot::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    RobotPropertiesDialog dialog(this);
    dialog.exec();
}

RobotPropertiesDialog::RobotPropertiesDialog(Robot *r, QWidget *parent)
    : QDialog(parent)
    , m_robot(r)

{
    setupUi(this);

    posXBox->setValue(m_robot->x());
    posYBox->setValue(m_robot->y());
    orientationBox->setValue(m_robot->angle());
    rotationBox->setValue(m_robot->rotateBy());
    detectDistanceBox->setValue(m_robot->detectionDistance());
    speedBox->setValue(m_robot->speed());
    directionButton->setChecked(m_robot->clockwise());
}

void RobotPropertiesDialog::on_buttonBox_accepted()
{
    m_robot->setPos(posXBox->value(), posYBox->value());
    m_robot->setAngle(orientationBox->value());
    m_robot->setSpeed(speedBox->value());
    m_robot->setRotateBy(rotationBox->value());
    m_robot->setDetectionDistance(detectDistanceBox->value());
    m_robot->setClockwise(directionButton->isChecked());
    m_robot->update();
    QDialog::accept();
}
