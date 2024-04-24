#pragma once

#include <iostream>
#include <QList>

#include "robot.h"
#include "obstacle.h"
#include "debug.h"

class Simulation
{
private:
    QList<Robot *> robotList;
    QList<Obstacle *> obstacleList;
    double time;
    
    QJsonObject getJsonObjects();

public:
    Simulation() : time(0.0) {}
    ~Simulation() {}

    Robot* createRobot();
    Obstacle* createObstacle();
    void addRobot(Robot* _);
    void addObstacle(Obstacle* _);
    void saveToJson();
    void loadFromJson();
    void read(const QJsonObject &json);
    void printLists();
};