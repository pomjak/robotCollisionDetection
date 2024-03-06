#pragma once 

#include <QtWidgets>

struct Position
{
    double x;
    double y;
};

class Object : public QWidget
{
public:
    virtual ~Object() {};

protected:
    Position position;

public:
    Position getPosition() const { return position; }
    void setPosition(const Position& newPosition) { position = newPosition; }
};

