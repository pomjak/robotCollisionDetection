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
    virtual ~Object() {};

protected:
    Position position;
    double size;

public:
    inline Position getPosition() const { return position; }
    inline void setPosition(const Position& newPosition) { position = newPosition; }
};

