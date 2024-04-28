#include "simulation.h"
#include <QFileDialog>

using std::shared_ptr, std::make_shared;

Simulation::Simulation()
    : scene(make_shared<QGraphicsScene>(new QGraphicsScene))
    , json(&robotList, &obstacleList)
    , time(0.0)
    , state{State::STOPPED}
{}

void Simulation::printLists()
{
    for ( const auto &obs : obstacleList )
    {
        DEBUG << obs->pos().x() << obs->pos().y();
        DEBUG << obs->getSize();
    }

    for ( const auto &rob : robotList )
    {
        DEBUG << rob->rotation();
        DEBUG << rob->pos().x() << rob->pos().y();
        DEBUG << rob->getRotation();
        DEBUG << rob->size();
        DEBUG << rob->getSpeed();
    }
}

void Simulation::loadLevelLayout()
{
    QString fname =
        QFileDialog::getOpenFileName(nullptr, tr("Open existing layout"), "",
                                     tr("Json File (*.json);;All Files(*)"));
    if ( fname.isEmpty() )
    {
        WARN << "filename empty";
        return;
    }
    else
    {
        scene->clear();
        robotList.clear();
        obstacleList.clear();
        json.load(fname);
        int i = 0;
        for ( auto &obj : robotList )
        {
            DEBUG << "Adding robot #" << ++i;
            scene->addItem(obj);
        }
        i = 0;
        for ( auto &obj : obstacleList )
        {
            DEBUG << "Adding obstacle #" << ++i;
            scene->addItem(obj);
        }
        INFO << "Scene:";
        INFO << " w: " << scene->width();
        INFO << " h: " << scene->height();
        INFO << " elem: " << scene->items().length();
        INFO << scene->sceneRect();
    }
}

void Simulation::saveLevelLayout()
{
    QString fname =
        QFileDialog::getSaveFileName(nullptr, tr("Save current layout"), "",
                                     tr("Json File (*.json);;All Files(*)"));
    if ( fname.isEmpty() )
        return;
    else { json.save(fname); }
}

void Simulation::spawnObject(ObjectType type)
{
    qreal defaultSize;

    if ( type == ObjectType::ROBOT )
        defaultSize = DEF_ROBOT_SIZE;

    else if ( type == ObjectType::OBSTACLE )
        defaultSize =
            QRandomGenerator::global()->bounded(50, DEF_OBSTACLE_SIZE);

    QPointF spawnPoint;
    QSizeF  objectSize;
    do {
        spawnPoint = {QRandomGenerator::global()->bounded(VIEW_WIDTH),
                      QRandomGenerator::global()->bounded(VIEW_HEIGHT)};

        objectSize.setWidth(defaultSize);
        objectSize.setHeight(defaultSize);
        QRectF spawnArea(spawnPoint, objectSize);
        QRectF sceneSpawnArea = spawnArea.translated(spawnPoint);

        /* Check if there are any items at the spawn point */
        QList<QGraphicsItem *> itemsAtSpawnPoint =
            scene->items(sceneSpawnArea, Qt::IntersectsItemShape);

        /* If there are no items at the spawn point, exit the loop */
        if ( itemsAtSpawnPoint.isEmpty() ) break;
    }
    while ( true );

    if ( type == ObjectType::ROBOT )
    {
        Robot *robot = new Robot(spawnPoint);
        addRobot(robot);
        INFO << "ROBOT SPAWNED at" << spawnPoint;
    }
    else if ( type == ObjectType::OBSTACLE )
    {
        Obstacle *obstacle = new Obstacle(spawnPoint, defaultSize);
        addObstacle(obstacle);
        INFO << "Obstacle SPAWNED at" << spawnPoint << "size of"
             << defaultSize;
    }
}

void Simulation::spawnRobot() { spawnObject(ObjectType::ROBOT); }

void Simulation::spawnObstacle() { spawnObject(ObjectType::OBSTACLE); }

void Simulation::deleteObject()
{
    // TODO
    return;
}

void Simulation::purgeScene()
{
    scene->clear();
    robotList.clear();
    obstacleList.clear();
}
