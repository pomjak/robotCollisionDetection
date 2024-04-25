#pragma once

#include <QGraphicsItem>
#include <QtCore>
#include <QPainter>

class Robot : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    double orientation;
    double speed;
    double rotation;
    double size;


public:
    Robot() : orientation(0.0), speed(0.0), rotation(0.0), size(10) {};
    Robot(double _orientation, double _speed, double _rotation, double _size)
        : orientation(_orientation), speed(_speed), rotation(_rotation), size(_size)
    {}
    Robot(QJsonObject& json);
    ~Robot() {};

    double getOrientation() const { return orientation; }
    double getSpeed() const { return speed; }
    double getRotation() const { return rotation; }
    double getSize() const { return size; }

    void setOrientation(double _orientation) { orientation = _orientation; }
    void setSpeed(double _speed) { speed = _speed; }
    void setRotation(double _rotation) { rotation = _rotation; }
    void setSize(double _size) { size = _size; }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
};
