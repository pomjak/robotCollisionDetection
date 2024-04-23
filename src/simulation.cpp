#include "simulation.h"

void Simulation::addObject(QGraphicsItem* item)
{
    scene->addItem(item);

    if ( Robot* robot = dynamic_cast<Robot*>( item ) )
    {
        DBG << "added hitbox";
        scene->addItem(reinterpret_cast<QGraphicsItem*>( robot->hitbox ));
    }

    objectList.push_back(reinterpret_cast<Object*>( item ));
    DBG << "adding object";
}

QGraphicsScene* Simulation::getScene() const
{
    DBG << "gettin scene";
    return scene;
}