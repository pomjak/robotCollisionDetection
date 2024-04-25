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
    inline void addRobot(Robot* robot) { robotList.push_back(robot); }
    inline void addObstacle(Obstacle* obstacle) { obstacleList.push_back(obstacle); }
    void printLists();
};