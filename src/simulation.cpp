#include "simulation.h"

void Simulation::addObject(QGraphicsItem* item)
{
    scene->addItem(item);
    objectList.push_back(reinterpret_cast<Object*>(item));
    DBG << "adding object";
}

QGraphicsScene* Simulation::getScene() const
{
    DBG << "gettin scene";
    return scene;
}