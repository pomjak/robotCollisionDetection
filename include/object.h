#pragma once 

#include <QGraphicsItem>
#include "debug.h"
#include "position.h"

class Object : public QGraphicsItem
{
public:
    Object(void) : size(50.0), position{ 10.0, 10.0 }, id(0) {}
    Object(double sizeValue, Position positionValue, unsigned int idValue) : size(sizeValue), position(positionValue), id(idValue) {}
    virtual ~Object() {};

protected:
    double size;
    Position position;
    unsigned int id;

public:
    inline unsigned int getId() { return id; }
    inline Position getPosition() const { return position; }
    inline double getSize() const {return size;}
    inline void setPosition(const Position& newPosition) { position = newPosition; }
    inline void setDeltaPosition(const Position& moveBy) { position += moveBy; }
};
