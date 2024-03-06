#pragma once 
#include <vector>
#include "object.h"

class Simulation
{
private:
    std::vector<Object*> objectList;
public:
    Simulation() {}
    ~Simulation() {}
};


