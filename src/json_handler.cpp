/**
 * \file json_handler.cpp
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \version 0.1
 * \date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "json_handler.h"
#include <QMessageBox>

QJsonObject JsonHandler::saveToJson(Robot *robot) const
{
    QJsonObject json;
    json["orientation"]    = robot->angle();
    json["speed"]          = robot->speed();
    json["rotation"]       = robot->rotateBy();
    json["x"]              = robot->pos().x();
    json["y"]              = robot->pos().y();
    json["detection_dist"] = robot->detectionDistance();
    return json;
}

QJsonObject JsonHandler::saveToJson(Obstacle *obs) const
{
    QJsonObject json;
    json["height"]      = obs->getHeight();
    json["width"]       = obs->getWidth();
    json["x"]           = obs->pos().x();
    json["y"]           = obs->pos().y();
    json["orientation"] = obs->rotation();

    return json;
}

QJsonObject JsonHandler::getJsonObjects()
{
    QJsonArray obstacles;
    /* insert all obstacle objects into an array */
    for ( const auto &obs : *obstacleList )
    {
        obstacles.append(saveToJson(obs));
    }

    QJsonObject json;
    json["obstacles"] = obstacles;

    QJsonArray robots;
    /* insert all obstacle robot into an array */
    for ( const auto &robot : *robotList )
    {
        robots.append(saveToJson(robot));
    }
    json["robots"] = robots;

    return json;
}

void JsonHandler::save(const QString &filename)
{
    QFile saveFile(filename);

    if ( !saveFile.open(QIODevice::WriteOnly) )
    {
        QMessageBox::information(nullptr, "Unable to open file",
                                 saveFile.errorString());
        WARN << "Couldn't open file";
        return;
    }

    QJsonObject gameObject = getJsonObjects();
    saveFile.write(QJsonDocument(gameObject).toJson());
}

void JsonHandler::read(const QJsonObject &json)
{
    /* check if obstacles are present in file */
    if ( json.contains("obstacles") && json["obstacles"].isArray() )
    {
        QJsonArray obstaclesArray = json["obstacles"].toArray();
        /* create obstacles from an array */
        for ( const QJsonValue &obsValue : obstaclesArray )
        {
            DEBUG << "LOADING OBSTACLE";
            QJsonObject obj      = obsValue.toObject();
            Obstacle   *obstacle = new Obstacle(obj);
            addObstacle(obstacle);
        }
    }

    /* check if robots are present in file */
    if ( json.contains("robots") && json["robots"].isArray() )
    {
        QJsonArray robotsArray = json["robots"].toArray();

        /* create robots from an array */
        for ( const QJsonValue &robotValue : robotsArray )
        {
            DEBUG << "LOADING ROBOT";
            QJsonObject obj = robotValue.toObject();
            Robot      *rbt = new Robot(obj);
            addRobot(rbt);
        }
    }
}

void JsonHandler::load(const QString &filename)
{
    QFile loadFile(filename);

    if ( !loadFile.open(QIODevice::ReadOnly) )
    {
        QMessageBox::information(nullptr, "Unable to open file",
                                 loadFile.errorString());
        WARN << "Couldn't open save file.";
        return;
    }
    QByteArray saveData = loadFile.readAll();
    if ( saveData.size() == 0 )
    {
        QMessageBox::information(nullptr, "File empty!",
                                 loadFile.errorString());
        WARN << "File Empty!";
        return;
    }

    INFO << "read " << saveData.size();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());
}
