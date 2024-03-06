#pragma once 

#include "object.h"

class Obstacle : public virtual Object
{
public:
    Obstacle() {}
    ~Obstacle() {}
private:
    double size;
};

class ObstacleFactory
{
public:
    Obstacle* createObstacle()
    {
        Obstacle* obstacle = new Obstacle();
        return obstacle;
    }
};