#include "simulation.h"


void Simulation::printLists()
{
    for ( const auto& obs : obstacleList )
    {
        std::cout << obs->pos().x() << obs->pos().y() << std::endl;
        std::cout << obs->getSize() << std::endl;
    }

    for ( const auto& rob : robotList )
    {
        std::cout << rob->getOrientation() << std::endl;
        std::cout << rob->pos().x() << rob->pos().y() << std::endl;
        std::cout << rob->getRotation() << std::endl;
        std::cout << rob->getSize() << std::endl;
        std::cout << rob->getSpeed() << std::endl;
    }
}