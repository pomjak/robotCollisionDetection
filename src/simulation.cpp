#include "simulation.h"


void Simulation::printLists()
{
    for ( const auto& obs : obstacleList )
    {
        DEBUG << obs->pos().x() << obs->pos().y() ;
        DEBUG << obs->getSize() ;
    }

    for ( const auto& rob : robotList )
    {
        DEBUG << rob->getOrientation() ;
        DEBUG << rob->pos().x() << rob->pos().y() ;
        DEBUG << rob->getRotation() ;
        DEBUG << rob->getSize() ;
        DEBUG << rob->getSpeed() ;
    }
}