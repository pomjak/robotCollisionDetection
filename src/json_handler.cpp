#include "json_handler.h"

QJsonObject JsonHandler::getJsonObjects()
{
    QJsonArray obstacles;
    for ( const auto& obs : *obstacleList )
    {
        obstacles.append(obs->saveToJson());
    }

    QJsonObject json;
    json["obstacles"] = obstacles;

    QJsonArray robots;
    for ( const auto& robot : *robotList )
    {
        robots.append(robot->saveToJson());
    }
    json["robots"] = robots;

    return json;
}

void JsonHandler::save()
{
    QFile saveFile("save.json");

    if ( !saveFile.open(QIODevice::WriteOnly) )
    {
        WARN << "Couldn't open file";
        return;
    }

    QJsonObject gameObject = getJsonObjects();
    saveFile.write(QJsonDocument(gameObject).toJson());
}

// FIXME factory needed
Robot* JsonHandler::createRobot()
{
    Robot* robot = new Robot();
    robotList->push_back(robot);
    return robot;
}

Obstacle* JsonHandler::createObstacle()
{
    Obstacle* obstacle = new Obstacle();
    obstacleList->push_back(obstacle);
    return obstacle;
}

void JsonHandler::read(const QJsonObject& json)
{
    if ( json.contains("obstacles") && json["obstacles"].isArray() )
    {
        QJsonArray obstaclesArray = json["obstacles"].toArray();

        for ( const QJsonValue& obsValue : obstaclesArray )
        {
            QJsonObject obstacleObject = obsValue.toObject();
            double posX = obstacleObject["position_x"].toDouble();
            double posY = obstacleObject["position_y"].toDouble();
            double size = obstacleObject["size"].toDouble();

            Obstacle* newObstacle = createObstacle();
            newObstacle->setPos(posX, posY);
            newObstacle->setSize(size);
        }
    }

    if ( json.contains("robots") && json["robots"].isArray() )
    {
        QJsonArray robotsArray = json["robots"].toArray();

        for ( const QJsonValue& robotValue : robotsArray )
        {
            QJsonObject robotObject = robotValue.toObject();
            double posX = robotObject["position_x"].toDouble();
            double posY = robotObject["position_y"].toDouble();
            double orientation = robotObject["orientation"].toDouble();
            double rotation = robotObject["rotation"].toDouble();
            double size = robotObject["size"].toDouble();
            double speed = robotObject["speed"].toDouble();

            Robot* newRobot = createRobot();
            newRobot->setPos(posX, posY);
            newRobot->setOrientation(orientation);
            newRobot->setRotation(rotation);
            newRobot->setSize(size);
            newRobot->setSpeed(speed);
        }
    }
}

void JsonHandler::load()
{
    QFile loadFile("save.json");

    if ( !loadFile.open(QIODevice::ReadOnly) )
    {
        WARN << "Couldn't open save file.";
        return;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());
}