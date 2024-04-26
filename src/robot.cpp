#include "robot.h"

Robot::Robot()
    : QObject(), QGraphicsItem(), m_size(DEF_ROBOT_SIZE), m_angle(0),
    m_speed(0), m_rotate_by(DEF_ROTATE_BY), m_detection_dist(DEF_DETECT_DIST),
    m_color(QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256))
{};

Robot::Robot(QJsonObject& json)
    : QObject(), QGraphicsItem(), m_size(DEF_ROBOT_SIZE),
    m_angle(json["orientation"].toDouble()),
    m_speed(json["speed"].toDouble()),
    m_rotate_by(json["rotation"].toDouble()),
    m_detection_dist(DEF_DETECT_DIST),
    m_color(QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256))
{
    /* Set the initial position of the robot */
    double pos_x = json["position_x"].toDouble();
    double pos_y = json["position_y"].toDouble();
    this->setPos(pos_x, pos_y);
}

QRectF Robot::boundingRect() const
{
    return QRectF(pos().x(), pos().y(), size(), size());
}

void Robot::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                  QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::red);
    painter->drawEllipse(boundingRect());

    /* Draw an arrow from the center, until the end of the detection area */
    QPointF center = boundingRect().center();
    QPointF arrowEnd = QPointF(center.x() + size() + getDetectDistance() / 2 * cos(getAngle()),
                               center.y() + size() + getDetectDistance() / 2 * sin(getAngle()));

    painter->drawLine(center, arrowEnd);
}

QPainterPath Robot::shape() const
{
    QPainterPath path;
    path.addEllipse(this->boundingRect());
    return path;
}

void Robot::advance(int phase)
{
    if ( !phase )
        return;
}