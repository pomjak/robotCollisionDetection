#pragma once
#include <algorithm>
#include <QPointF>
struct Position 
{
    double x;
    double y;

    Position& operator+=(const Position& other);
    friend Position operator+(const Position& lhs, const Position& rhs);
    friend inline bool operator<(const Position& lhs, const Position& rhs) { return ( lhs.x < rhs.x && lhs.y < rhs.y ); }
    bool containsInRect(const double& minX, const double& maxX, const double& minY, const double& maxY) const;
    bool containsInRect(const Position& topLeft, const Position& bottomRight) const;
    inline QPointF toQPointF() const { return QPointF(x, y); }
};
