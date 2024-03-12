#include "simulation.h"

void Simulation::addObject(QGraphicsItem* item)
{
    scene->addItem(item);
    DBG << "adding object to scene";
}

QGraphicsScene* Simulation::getScene() const
{
    DBG << "gettin scene";
    return scene;
}