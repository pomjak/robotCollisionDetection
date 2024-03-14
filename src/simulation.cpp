#include "simulation.h"

void Simulation::addObject(QGraphicsItem* item)
{
    scene->addItem(item);
    objectList.push_back(reinterpret_cast<Object*>( item ));
    DBG << "adding object";
}

bool Simulation::isLineOccupied(const std::vector<QPointF>& line, QGraphicsScene* scene)
{
    if ( !scene )
        return false;

    for ( const QPointF& point : line )
    {
        for ( QGraphicsItem* item : scene->items(point) )
        {
            if ( item->contains(item->mapFromScene(point)) )
            {
                DBG << "Collision detected !!";
                return true;
            }
        }
    }
    return false;
}

QGraphicsScene* Simulation::getScene() const
{
    DBG << "gettin scene";
    return scene;
}