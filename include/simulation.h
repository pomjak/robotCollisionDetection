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

    QList<Robot*>* getRobotList() { return &robotList; }
    QList<Obstacle*>* getObstacleList() { return &obstacleList; }
    void addRobot(Robot* robot) { robotList.push_back(robot); }
    void addObstacle(Obstacle* obstacle) { obstacleList.push_back(obstacle); }
    void printLists();
};