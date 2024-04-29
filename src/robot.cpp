#include "robot.h"
#include <QWidget>

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
    , m_angle(json["orientation"].toDouble())
    , m_speed(json["speed"].toDouble())
    , m_rotate_by(json["rotation"].toDouble())
    , m_detection_dist(json["detection_dist"].toDouble())
{
    /* Set the initial position of the robot */
    qreal pos_x = json["position_x"].toDouble();
    qreal pos_y = json["position_y"].toDouble();

    setPos(pos_x, pos_y);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setAcceptDrops(true);
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
    painter->setPen(Qt::black);
    painter->setOpacity(0.2);
    painter->setBrush(Qt::darkYellow);
    painter->drawPolygon(detectionArea());
    painter->setPen(Qt::darkCyan);
    painter->setBrush(Qt::darkGray);
    painter->setOpacity(1);
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::darkYellow); painter->setBrush(Qt::NoBrush);
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
           << center()
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

    /* Move the robot */
    qreal   dx     = getSpeed() * ::cos(getAngle());
    qreal   dy     = getSpeed() * ::sin(getAngle());
    QPointF newPos = pos() + QPointF(dx, dy);

    /* check if new bound rect is still in scene */
    if ( scene()->sceneRect().contains(
             newBoundingRect(newPos).translated(newPos)) )
    {
        DEBUG << scene()->sceneRect().size();
        /* get all objects in danger area */
        const QList<QGraphicsItem *> colliding_items = scene()->items(
            mapToScene(detectionArea()), Qt::IntersectsItemShape);

        for ( const auto &item : colliding_items )
        {
            /* ignore itself */
            if ( item != this )
            {
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

void Robot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_offset = event->scenePos();
}

void Robot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) { update(); }

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
