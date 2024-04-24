#include "simulation.h"

inline void Simulation::addRobot(Robot *robot)
{
    robotList.push_back(robot);
}

inline void Simulation::addObstacle(Obstacle *obstacle)
{
    obstacleList.push_back(obstacle);
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
        std::cout << rob->getOrientation() << std::endl;
        std::cout << rob->pos().x() << rob->pos().y() << std::endl;
        std::cout << rob->getRotation() << std::endl;
        std::cout << rob->getSize() << std::endl;
        std::cout << rob->getSpeed() << std::endl;
    }
}