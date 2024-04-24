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

Robot *Simulation::createRobot()
{
    Robot *robot = new Robot();
    addRobot(robot);
    return robot;
}

Obstacle *Simulation::createObstacle()
{
    Obstacle *obstacle = new Obstacle();
    addObstacle(obstacle);
    return obstacle;
}

void Simulation::read(const QJsonObject &json)
{
    if (json.contains("obstacles") && json["obstacles"].isArray())
    {
        QJsonArray obstaclesArray = json["obstacles"].toArray();

        for (const QJsonValue &obsValue : obstaclesArray)
        {
            QJsonObject obstacleObject = obsValue.toObject();
            double posX = obstacleObject["position_x"].toDouble();
            double posY = obstacleObject["position_y"].toDouble();
            double size = obstacleObject["size"].toDouble();

            Obstacle *newObstacle = createObstacle();
            newObstacle->setPos(posX, posY);
            newObstacle->setSize(size);
        }
    }

    if (json.contains("robots") && json["robots"].isArray())
    {
        QJsonArray robotsArray = json["robots"].toArray();

        for (const QJsonValue &robotValue : robotsArray)
        {
            QJsonObject robotObject = robotValue.toObject();
            double posX = robotObject["position_x"].toDouble();
            double posY = robotObject["position_y"].toDouble();
            double orientation = robotObject["orientation"].toDouble();
            double rotation = robotObject["rotation"].toDouble();
            double size = robotObject["size"].toDouble();
            double speed = robotObject["speed"].toDouble();

            Robot *newRobot = createRobot();
            newRobot->setPos(posX, posY);
            newRobot->setOrientation(orientation);
            newRobot->setRotation(rotation);
            newRobot->setSize(size);
            newRobot->setSpeed(speed);
        }
    }
}

void Simulation::loadFromJson()
{
    QFile loadFile("save.json");

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        WARN << "Couldn't open save file.";
        return;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());
}

void Simulation::printLists()
{
    for(const auto &obs : obstacleList)
    {
        std::cout << obs->pos().x() << obs->pos().y() << std::endl;
        std::cout << obs->getSize() << std::endl;
    }

    for (const auto &rob : robotList)
    {
        std::cout << rob->pos().x() << rob->pos().y() << std::endl;
        std::cout << rob->getSize() << std::endl;
        std::cout << rob->getRotation() << std::endl;
        std::cout << rob->getOrientation() << std::endl;
        std::cout << rob->getSpeed() << std::endl;
    }
}