#include"position.h"

Position& Position::operator += ( const Position & other )
{
    x += other.x;
    y += other.y;
    return *this;
}

Position operator+(const Position& lhs, const Position& rhs)
{
    Position result;
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    return result;
}

bool Position::containsInRect(const double& minX, const double& maxX, const double& minY, const double& maxY) const
{
    return ( x >= minX && x <= maxX && y >= minY && y <= maxY );
}


bool Position::containsInRect(const Position& topLeft, const Position& bottomRight) const
{
    return ( x >= topLeft.x && x <= bottomRight.x && y >= topLeft.y && y <= bottomRight.y );
}