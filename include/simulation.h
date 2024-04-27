#pragma once

#include <iostream>
#include <memory>
#include <QList>
#include <QGraphicsScene>
#include "robot.h"
#include "obstacle.h"
#include "debug.h"
#include "json_handler.h"

using std::shared_ptr;

class Simulation : public QObject
{
    Q_OBJECT
private:
    QList<Robot*> robotList;
    QList<Obstacle*> obstacleList;
    shared_ptr<QGraphicsScene> scene;
    JsonHandler json;
    double time;

public:
    Simulation();
    ~Simulation() {}

    QList<Robot*>* getRobotList() const { return new QList<Robot*>(robotList); }
    QList<Obstacle*>* getObstacleList() const { return new QList<Obstacle*>(obstacleList); }
    void addRobot(Robot* robot) { robotList.push_back(robot); }
    void addObstacle(Obstacle* obstacle) { obstacleList.push_back(obstacle); }
    void printLists();
    shared_ptr<QGraphicsScene> getScene() const { return scene; }

public slots:
    void loadLevelLayout();
    void saveLevelLayout();
    void spawnRobot();
    void spawnObstacle();
    void deleteObject();
    void purgeScene();
};