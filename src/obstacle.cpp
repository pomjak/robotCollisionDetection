#include "obstacle.h"

Obstacle::Obstacle()
    : m_size(DEF_OBSTACLE_SIZE)
    , m_orientation(0)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

Obstacle::Obstacle(QPointF p, qreal s)
    : m_size(s)
    , m_orientation(0)
{
    setPos(p);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

Obstacle::Obstacle(QPointF p, qreal s, qreal a)
    : m_size(s)
    , m_orientation(a)
{
    setPos(p);
    setTransformOriginPoint(boundingRect().center());
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

Obstacle::Obstacle(QJsonObject &json)
{
    qreal size  = qBound(0.0, json["size"].toDouble(), MAX_OBS_SIZE);
    qreal pos_x = qBound(0.0, json["x"].toDouble(), (MAX_W - size));
    qreal pos_y = qBound(0.0, json["y"].toDouble(), (MAX_H - size));
    qreal orient =
        qBound(0.0, json["orientation"].toDouble(), 360.0); // ? TODO
    this->setPos(pos_x, pos_y);
    setTransformOriginPoint(boundingRect().center());
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

qreal Obstacle::angle() const { return m_orientation; }
qreal Obstacle::size() const { return m_size; }

void Obstacle::setAngle(qreal a) { m_orientation = a; }
void Obstacle::setSize(qreal s) { m_size = s; }

QRectF Obstacle::boundingRect() const
{
    return QRectF(pos().x(), pos().y(), size(), size());
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::darkRed);
    painter->drawPath(shape());
}

QPainterPath Obstacle::shape() const
{
    QPainterPath path;

    path.addPolygon(QPolygonF() << topLeft() << bottomLeft() << bottomRight()
                                << topRight());

    return path;
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
    QPointF delta  = event->scenePos() - m_offset;
    QPointF newPos = pos() + (delta * 0.5);
    QRectF  newRect(newPos, QSizeF(size(), size()));
    if ( scene()->sceneRect().contains(newRect.translated(newPos)) )
    {
        setPos(newPos);
    }
    m_offset = event->scenePos();
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
