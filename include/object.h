#pragma once 

#include <QGraphicsItem>

struct Position
{
    double x;
    double y;
};

class Object : public QGraphicsItem
{
public:
    Object(void) : size(50.0), position{ 10.0, 10.0 }{}
    Object(double sizeValue, Position positionValue) : size(sizeValue), position(positionValue) {}
    virtual ~Object() {};

protected:
    double size;
    Position position;

public:
    inline Position getPosition() const { return position; }
    inline void setPosition(const Position& newPosition) { position = newPosition; }
};

