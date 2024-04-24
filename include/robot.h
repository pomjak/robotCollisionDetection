#pragma once

#include <QGraphicsItem>
#include <QtCore>
#include <QPainter>

class Robot : public QGraphicsItem
{
private:
    double orientation;
    double speed;
    double rotation;
    double size;

public:
    Robot() : orientation(0.0), speed(0.0), rotation(0.0), size(10){};
    Robot(double _orientation, double _speed, double _rotation, double _size)
        : orientation(_orientation), speed(_speed), rotation(_rotation), size(_size) {}
    ~Robot(){};

    inline double getOrientation() const { return orientation; }
    inline double getSpeed() const { return speed; }
    inline double getRotation() const { return rotation; }
    inline double getSize() const { return size; }

    inline void setOrientation(double _orientation) { orientation = _orientation; }
    inline void setSpeed(double _speed) { speed = _speed; }
    inline void setRotation(double _rotation) { rotation = _rotation; }
    inline void setSize(double _size) { size = _size; }

    QJsonObject saveToJson(void) const;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
