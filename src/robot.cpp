#include "robot.h"

Robot::Robot(QJsonObject &json)
        : QObject(),
          QGraphicsItem(),
          orientation(json["orientation"].toDouble()),
          speed(json["speed"].toDouble()),
          rotation(json["rotation"].toDouble()),
          size(json["size"].toDouble())
{
    double pos_x = json["position_x"].toDouble();
    double pos_y = json["position_y"].toDouble();
    this->setPos(pos_x, pos_y);
}

QRectF Robot::boundingRect() const
{
    return QRectF(pos().x(), pos().y(), getSize(), getSize());
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::red);
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());

    QPointF center = boundingRect().center();
    QPointF arrowEnd = QPointF(center.x() + getSize() / 2 * cos(orientation),
                               center.y() + getSize() / 2 * sin(orientation));

    painter->drawLine(center, arrowEnd);
}

QPainterPath Robot::shape() const
{
    QPainterPath path;
    path.addEllipse(this->boundingRect());
    return path;
}