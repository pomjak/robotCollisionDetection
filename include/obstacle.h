#pragma once

#include <QGraphicsItem>
#include <QtCore>
#include <QPainter>

class Obstacle : public QGraphicsItem
{
private:
    double size;

public:
    Obstacle() : size(20) {}
    Obstacle(double _size) : size(_size) {}
    Obstacle(QJsonObject& json);
    ~Obstacle() {}
    double getSize() const { return size; }

    void setSize(double _size) { size = _size; }

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};
