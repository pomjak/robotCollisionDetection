#include "simulation.h"

void Simulation::addRobot(Robot *robot)
{
    robotList.push_back(robot);
}

void Simulation::addObstacle(Obstacle *obstacle)
{
    obstacleList.push_back(obstacle);
}

QJsonObject Simulation::getJsonObjects()
{
    QJsonArray obstacles;
    for (const auto &obs : obstacleList)
    {
        obstacles.append(obs->saveToJson());
    }

    QJsonObject json;
    json["obstacles"] = obstacles;

    QJsonArray robots;
    for (const auto &robot : robotList)
    {
        robots.append(robot->saveToJson());
    }
    json["robots"] = robots;

    return json;
}

void Simulation::saveToJson()
{
    QFile saveFile("save.json");

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        WARN << "Couldn't open file";
        return;
    }

    QJsonObject gameObject = getJsonObjects();
    saveFile.write(QJsonDocument(gameObject).toJson());
}