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
        DEBUG << rob->getOrientation();
        DEBUG << rob->pos().x() << rob->pos().y();
        DEBUG << rob->getRotation();
        DEBUG << rob->getSize();
        DEBUG << rob->getSpeed();
    }
}

void Simulation::loadLevelLayout()
{
    QString fname = QFileDialog::getOpenFileName(nullptr, tr("Open existing layout"), "", tr("Json File (*.json);;All Files(*)"));
    if ( fname.isEmpty() )
        return;
    else
    {
        json.load(fname);
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