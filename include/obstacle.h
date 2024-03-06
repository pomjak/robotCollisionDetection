#pragma once 

#include "robot.h"

class Obstacle : public Object
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