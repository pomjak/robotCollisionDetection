#pragma once
#include <algorithm>
struct Position
{
    double x;
    double y;

    Position& operator+=(const Position& other);
    friend Position operator+(const Position& lhs, const Position& rhs);
    friend inline bool operator<(const Position& lhs, const Position& rhs) { return ( lhs.x < rhs.x && lhs.y < rhs.y ); }
    bool containsInRect(const double& minX, const double& maxX, const double& minY, const double& maxY) const;
    bool containsInRect(const Position& topLeft, const Position& bottomRight) const;
};

inline double distance(const Position& p1, const Position& p2) { return std::max(std::abs(p2.x - p1.x), std::abs(p2.y - p1.y)); }
