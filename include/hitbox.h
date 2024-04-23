#pragma once

#include <cmath>
#include <QGraphicsItem>
#include <QPainter>
#include <QMatrix>
#include "debug.h"
#include "position.h"

class Hitbox : public QGraphicsItem
{
private:
    Position position;
    double orientation;
    double width;
    double length;

public:
    Hitbox(Position _pos, double _orientation, double _wd, double _len) : position(_pos), orientation(_orientation), width(_wd), length(_len) {};
    ~Hitbox() {}

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    inline Position getPosition() const { return position; }
    void  setPosition(Position _pos) { position = _pos; }
    inline double getWidth() const { return width; }
    inline double getLength() const { return length; }
};


