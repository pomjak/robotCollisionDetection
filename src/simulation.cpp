#include "simulation.h"
#include <QFileDialog>


using std::shared_ptr, std::make_shared;

Simulation::Simulation() : scene(make_shared<QGraphicsScene>(new QGraphicsScene)), json(&robotList, &obstacleList), time(0.0)
{}

void Simulation::printLists()
{
    for ( const auto& obs : obstacleList )
    {
        DEBUG << obs->pos().x() << obs->pos().y();
        DEBUG << obs->getSize();
    }

    for ( const auto& rob : robotList )
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
    QString fname = QFileDialog::getOpenFileName(nullptr, tr("Open existing layout"), "", tr("Json File (*.json);;All Files(*)"));
    if ( fname.isEmpty() )
    {
        WARN << "filename empty";
        return;
    }
    else
    {
        scene->clear();
        json.load(fname);
        int i = 0;
        for ( auto& obj : robotList )
        {
            DEBUG << "Adding robot #" << ++i;
            scene->addItem(obj);
        }
        i = 0;
        for ( auto& obj : obstacleList )
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
    QString fname = QFileDialog::getSaveFileName(nullptr, tr("Save current layout"), "", tr("Json File (*.json);;All Files(*)"));
    if ( fname.isEmpty() )
        return;
    else
    {
        json.save(fname);
    }
}