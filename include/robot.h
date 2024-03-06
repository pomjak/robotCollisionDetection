#pragma once 

#include "object.h"
#include <iostream>

class Robot : public virtual Object
{
private:
public:
    Robot() {}
    ~Robot() {}
};

class RobotFactory
{
public:
    Robot* createRobot()
    {
        Robot* robot = new Robot();
        return robot;
    }
};
