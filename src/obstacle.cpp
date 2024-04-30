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
    : m_size(DEF_OBSTACLE_SIZE)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

Obstacle::Obstacle(QPointF p, qreal s)
    : m_size(s)
{
    setPos(p);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

Obstacle::Obstacle(QPointF p, qreal s, qreal a)
    : m_size(s)
{
    setPos(p);
    prepareGeometryChange();
    setTransformOriginPoint(boundingRect().center());
    setRotation(a);
    update();
    setTransformOriginPoint(boundingRect().center());
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

Obstacle::Obstacle(QJsonObject &json)
{
    /* find center and rotate if needed */
    prepareGeometryChange();
    setTransformOriginPoint(boundingRect().center());

    qreal size  = qBound(0.0, json["size"].toDouble(), MAX_OBS_SIZE);
    qreal pos_x = qBound(0.0, json["x"].toDouble(), (MAX_W - size));
    qreal pos_y = qBound(0.0, json["y"].toDouble(), (MAX_H - size));
    setRotation(qBound(0.0, json["orientation"].toDouble(), 360.0));

    this->setPos(pos_x, pos_y);
    update();

    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

qreal Obstacle::size() const { return m_size; }

void Obstacle::setSize(qreal s) { m_size = s; }

QRectF Obstacle::boundingRect() const
{

    return QRectF(pos().x(), pos().y(), size(), size());
}

QRectF Obstacle::newBoundingRect(QPointF newPos) const
{

    return QRectF(newPos.x(), newPos.y(), size(), size());
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

        QTransform transform;
        /* transform ( or try ) position into original coordinates */
        transform.translate(delta.x(), delta.y());
        transform.rotate(-rotation());

        delta = transform.map(delta);
        
        QPointF newPos = pos() + (delta * 0.45);
        if ( scene()->sceneRect().contains(
                 newBoundingRect(newPos).translated(newPos)) ) //! FIXME
        {
            setPos(newPos);
        }

        m_offset = event->scenePos();
    }
}
