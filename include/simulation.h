#pragma once

#include <iostream>
#include <QList>

#include "robot.h"
#include "obstacle.h"
#include "debug.h"

class Simulation
{
private:
    QList<Robot*> robotList;
    QList<Obstacle*> obstacleList;
    double time;

public:
    Simulation() : time(0.0) {}
    ~Simulation() {}

    inline QList<Robot*>* getRobotList() { return &robotList; }
    inline QList<Obstacle*>* getObstacleList() { return &obstacleList; }
    inline void addRobot(Robot* _);
    inline void addObstacle(Obstacle* _);
    void printLists();
};