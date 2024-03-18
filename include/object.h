#pragma once 

#include <QGraphicsItem>
#include "debug.h"
struct Position
{
    double x;
    double y;

    Position& operator+=(const Position& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    friend Position operator+(const Position& lhs, const Position& rhs)
    {
        Position result;
        result.x = lhs.x + rhs.x;
        result.y = lhs.y + rhs.y;
        return result;
    }

    friend inline bool operator<(const Position& lhs, const Position& rhs) { return ( lhs.x < rhs.x && lhs.y < rhs.y ); }

    bool containsInRect(const double& minX, const double& maxX, const double& minY, const double& maxY) const
    {
        return ( x >= minX && x <= maxX && y >= minY && y <= maxY );
    }


    bool containsInRect(const Position& topLeft, const Position& bottomRight) const
    {
        return ( x >= topLeft.x && x <= bottomRight.x && y >= topLeft.y && y <= bottomRight.y );
    }

};

inline double distance(const Position& p1, const Position& p2) { return std::max(std::abs(p2.x - p1.x), std::abs(p2.y - p1.y)); }

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
