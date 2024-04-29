#include "obstacle.h"

Obstacle::Obstacle(QPointF _position)
    : m_size(DEF_OBSTACLE_SIZE)
    , m_orientation(0)
{
    setPos(_position);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

Obstacle::Obstacle(QPointF _position, double _size, double _angle)
    : m_size(_size)
    , m_orientation(_angle)
{
    setPos(_position);
    setTransformOriginPoint(boundingRect().center());
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

Obstacle::Obstacle(QJsonObject &json)
    : m_size(json["size"].toDouble())
    , m_orientation(json["orientation"].toDouble())
{
    double pos_x = json["position_x"].toDouble();
    double pos_y = json["position_y"].toDouble();
    this->setPos(pos_x, pos_y);
    setTransformOriginPoint(boundingRect().center());
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QRectF Obstacle::boundingRect() const
{
    return QRectF(pos().x(), pos().y(), getSize(), getSize());
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
    QPointF      middle = {
        boundingRect().center().x() + (m_size / 2) * ::cos(m_orientation),
        boundingRect().center().y() + (m_size / 2) * ::sin(m_orientation)};
    QPointF vertex = {
        middle.x() + (m_size / 2) * ::cos(m_orientation - M_PI / 2),
        middle.y() + (m_size / 2) * ::sin(m_orientation - M_PI / 2)};
    QPointF vertex2 = {
        middle.x() + (m_size / 2) * ::cos(m_orientation + M_PI / 2),
        middle.y() + (m_size / 2) * ::sin(m_orientation + M_PI / 2)};
    QPointF middle2 = {boundingRect().center().x() +
                           (m_size / 2) * ::cos(m_orientation - M_PI),
                       boundingRect().center().y() +
                           (m_size / 2) * ::sin(m_orientation - M_PI)};
    QPointF vertex3 = {
        middle2.x() + (m_size / 2) * ::cos(m_orientation - M_PI / 2),
        middle2.y() + (m_size / 2) * ::sin(m_orientation - M_PI / 2)};
    QPointF vertex4 = {
        middle2.x() + (m_size / 2) * ::cos(m_orientation + M_PI / 2),
        middle2.y() + (m_size / 2) * ::sin(m_orientation + M_PI / 2)};

    path.addPolygon(QPolygonF() << vertex << vertex3 << vertex4 << vertex2);
    return path;
}

void Obstacle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_offset = event->scenePos();
}

void Obstacle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) { update(); }

void Obstacle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal orientation = rotation();
    // qreal   orientationRadians = qDegreesToRadians(orientation);
    setRotation(0);
    QPointF delta  = event->scenePos() - m_offset;
    QPointF newPos = pos() + (delta * 0.5);
    QRectF  newRect(newPos, QSizeF(m_size, m_size));
    if ( scene()->sceneRect().contains(newRect.translated(newPos)) )
    {
        DEBUG << "pos: " << mapToScene(pos());
        setPos(newPos);
        DEBUG << "newPos: " << mapToScene(pos());
    }
    setRotation(orientation);
    m_offset = event->scenePos();
}
