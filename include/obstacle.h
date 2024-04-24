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
    ~Obstacle() {}
    inline double getSize() const { return size; }

    inline void setSize(double _size) { size = _size; }

    QJsonObject saveToJson(void) const;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
