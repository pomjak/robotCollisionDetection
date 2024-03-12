#pragma once

#include <QGraphicsScene>
#include <vector>

#include "object.h"
#include "debug.h"

enum class SimulationState { INIT, RUNNING, PAUSED, HALT };

class Simulation
{
private:
    std::vector<Object*> objectList;
    QGraphicsScene* scene;
    int timeElapsed;
    SimulationState state;

public:
    Simulation() : scene(new QGraphicsScene()), timeElapsed(0), state(SimulationState::INIT) {}
    ~Simulation() { delete scene; }

    void addObject(QGraphicsItem* item);

    QGraphicsScene* getScene() const;

    void start();
    void stop();
    void resume();
    void halt();
    void loadConfig();
    void storeConfig();
};
