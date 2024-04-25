#pragma once

#include <QtCore>
#include <QList>

#include "simulation.h"
#include "robot.h"
#include "obstacle.h"

class JsonHandler
{
private:
    QList<Robot*>* robotList;
    QList<Obstacle*>* obstacleList;

    QJsonObject saveToJson(Robot* _) const;
    QJsonObject saveToJson(Obstacle* _) const;
    QJsonObject getJsonObjects();
    void read(const QJsonObject& json);

public:
    JsonHandler(QList<Robot*>* _rList, QList<Obstacle*>* _oList)
        : robotList(_rList), obstacleList(_oList)
    {}
    ~JsonHandler() {}

    void save();
    void load();
};
