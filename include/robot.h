#pragma once

#include <QGraphicsItem>

class Robot : public QGraphicsItem
{
private:
    double orientation;
    double speed;
    double rotation;
    
public:
    Robot();
    ~Robot();

    inline double getOrientation() const { return orientation; }
    inline double getSpeed() const { return speed; }
    inline double getRotation() const { return rotation; }

    inline void setOrientation(double _orientation) { orientation = _orientation; }
    inline void setSpeed(double _speed) const { speed = _speed;}
    inline void setRotation(double _rotation) const { rotation = _rotation; }
};
