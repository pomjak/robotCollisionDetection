#include "json_handler.h"
#include <QMessageBox>


QJsonObject JsonHandler::saveToJson(Robot* robot) const
{
    QJsonObject json;
    json["orientation"] = robot->getOrientation();
    json["speed"] = robot->getSpeed();
    json["rotation"] = robot->getRotation();
    json["size"] = robot->getSize();
    json["position_x"] = robot->pos().x();
    json["position_y"] = robot->pos().y();
    return json;
}

QJsonObject JsonHandler::saveToJson(Obstacle* obs) const
{
    QJsonObject json;
    json["size"] = obs->getSize();
    json["position_x"] = obs->pos().x();
    json["position_y"] = obs->pos().y();
    return json;
}

QJsonObject JsonHandler::getJsonObjects()
{
    QJsonArray obstacles;
    for ( const auto& obs : *obstacleList )
    {
        obstacles.append(saveToJson(obs));
    }

    QJsonObject json;
    json["obstacles"] = obstacles;

    QJsonArray robots;
    for ( const auto& robot : *robotList )
    {
        robots.append(saveToJson(robot));
    }
    json["robots"] = robots;

    return json;
}

void JsonHandler::save(const QString& filename)
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

void JsonHandler::read(const QJsonObject& json)
{
    if ( json.contains("obstacles") && json["obstacles"].isArray() )
    {
        QJsonArray obstaclesArray = json["obstacles"].toArray();

        for ( const QJsonValue& obsValue : obstaclesArray )
        {
            QJsonObject obj = obsValue.toObject();
            Obstacle* obst = new Obstacle(obj);
            obstacleList->push_back(obst);
        }
    }

    if ( json.contains("robots") && json["robots"].isArray() )
    {
        QJsonArray robotsArray = json["robots"].toArray();

        for ( const QJsonValue& robotValue : robotsArray )
        {
            QJsonObject obj = robotValue.toObject();
            Robot* rbt = new Robot(obj);
            robotList->push_back(rbt);
        }
    }
}

void JsonHandler::load(const QString& filename)
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

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());
}