#pragma once

#include <iostream>
#include <memory>
#include <QList>
#include <QGraphicsScene>
#include "robot.h"
#include "obstacle.h"
#include "debug.h"
#include "json_handler.h"

#define VIEW_WIDTH 444.0
#define VIEW_HEIGHT 384.0

using std::shared_ptr;
enum class State { RUNNING, STOPPED };
enum class ObjectType { ROBOT, OBSTACLE };

class Simulation : public QObject
{
    Q_OBJECT
private:
    QList<Robot*> robotList;
    QList<Obstacle*> obstacleList;
    shared_ptr<QGraphicsScene> scene;
    JsonHandler json;
    double time;
    State state;


public:
    Simulation();
    ~Simulation() {}

    QList<Robot*>* getRobotList() const { return new QList<Robot*>(robotList); }
    QList<Obstacle*>* getObstacleList() const { return new QList<Obstacle*>(obstacleList); }
    void addRobot(Robot* robot) { robotList.push_back(robot); scene->addItem(robot); }
    void addObstacle(Obstacle* obstacle) { obstacleList.push_back(obstacle);scene->addItem(obstacle); }
    void printLists();
    shared_ptr<QGraphicsScene> getScene() const { return scene; }
    State getState() const { return state; }
    void setState(State _state) { state = _state; }
    void spawnObject(ObjectType type);

public slots:
    void loadLevelLayout();
    void saveLevelLayout();
    void spawnRobot();
    void spawnObstacle();
    void deleteObject();
    void purgeScene();
};