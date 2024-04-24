#pragma once

#include <QtCore>
#include <QList>

#include "simulation.h"

class JsonHandler
{
private:
    QList<Robot*>* robotList;
    QList<Obstacle*>* obstacleList;

    QJsonObject getJsonObjects();
    void read(const QJsonObject& json);

    Robot* createRobot(); // TODO  - factory remake
    Obstacle* createObstacle();

public:
    JsonHandler(QList<Robot*>* _rList, QList<Obstacle*>* _oList)
        : robotList(_rList), obstacleList(_oList)
    {}
    ~JsonHandler() {}

    void save();
    void load();
};
