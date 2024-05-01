/**
 * \file obstacle.cpp
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \version 0.1
 * \date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "obstacle.h"

Obstacle::Obstacle()
    : m_height(DEF_OBSTACLE_SIZE)
    , m_width(DEF_OBSTACLE_SIZE)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

Obstacle::Obstacle(QPointF position, qreal w, qreal h)
    : m_height(h)
    , m_width(w)
{
    setPos(position);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

Obstacle::Obstacle(QPointF position, QSizeF size)
    : m_height(size.height())
    , m_width(size.width())
{
    setPos(position);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

Obstacle::Obstacle(QJsonObject &json)
{
    m_width     = qBound(0.0, json["width"].toDouble(), MAX_OBS_SIZE);
    m_height    = qBound(0.0, json["height"].toDouble(), MAX_OBS_SIZE);
    qreal pos_x = qBound(0.0, json["x"].toDouble(), (MAX_W));
    qreal pos_y = qBound(0.0, json["y"].toDouble(), (MAX_H));

    this->setPos(pos_x, pos_y);
    update();

    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

void Obstacle::setSize(qreal w, qreal h)
{
    m_width  = w;
    m_height = h;
}

qreal Obstacle::getHeight() const { return m_height; }

qreal Obstacle::getWidth() const { return m_width; }

QRectF Obstacle::boundingRect() const
{
    return QRectF(pos().x(), pos().y(), m_width, m_height);
}

QRectF Obstacle::newBoundingRect(QPointF newPos) const
{

    return QRectF(newPos.x(), newPos.y(), m_width, m_height);
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::darkRed);
    painter->drawPath(shape());

    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
}

void Obstacle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_offset = event->scenePos();
}

void Obstacle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    update();
}

void Obstacle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ( event->buttons() & Qt::LeftButton )
    {
        /* Calculate the new position based on the cursor position */
        QPointF delta = event->scenePos() - m_offset;

        QPointF newPos = pos() + (delta * 0.5);

        if ( scene()->sceneRect().contains(
                 newBoundingRect(newPos).translated(newPos)) )
        {
            setPos(newPos);
        }

        m_offset = event->scenePos();
    }
    m_offset = event->scenePos();
}

void Obstacle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    ObstaclePropertiesDialog dialog(this);
    dialog.exec();
}

QPointF Obstacle::center() const { return boundingRect().center(); }

QPointF Obstacle::midTop() const
{
    return QPointF(center().x() + dx(), center().y() + dy());
}

QPointF Obstacle::midBottom() const
{
    return QPointF(center().x() + dx(-M_PI), center().y() + dy(-M_PI));
}

QPointF Obstacle::topLeft() const
{
    return QPointF(midTop().x() + dx(-M_PI / 2), midTop().y() + dy(-M_PI / 2));
}

QPointF Obstacle::topRight() const
{
    return QPointF(midTop().x() + dx(M_PI / 2), midTop().y() + dy(M_PI / 2));
}

QPointF Obstacle::bottomLeft() const
{
    return QPointF(midBottom().x() + dx(-M_PI / 2),
                   midBottom().y() + dy(-M_PI / 2));
}

QPointF Obstacle::bottomRight() const
{
    return QPointF(midBottom().x() + dx(M_PI / 2),
                   midBottom().y() + dy(M_PI / 2));
}

qreal Obstacle::dx(qreal a) const
{
    return ((size() / 2) * ::cos(angle() + a));
}

qreal Obstacle::dy(qreal a) const
{
    return ((size() / 2) * ::sin(angle() + a));
}

ObstaclePropertiesDialog::ObstaclePropertiesDialog(Obstacle *o,
                                                   QWidget  *parent)
    : QDialog(parent)
    , m_obstacle(o)

{
    setupUi(this);

    posXBox->setValue(m_obstacle->x());
    posYBox->setValue(m_obstacle->y());
    // widthBox->setValue(m_obstacle->width());
    // heightBox->setValue(m_obstacle->height());
    // ! TODO directionComboBox
}

void ObstaclePropertiesDialog::on_buttonBox_accepted()
{
    m_obstacle->setPos(posXBox->value(), posYBox->value());
    // m_obstacle->setWidth(widthBox->value());
    // m_obstacle->setHeight(heightBox->value());
    m_obstacle->update();
    QDialog::accept();
}
