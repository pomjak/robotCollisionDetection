#pragma once 

#include <QGraphicsScene>
#include <vector>

#include "object.h"
#include "debug.h"

enum SimulationState { INIT, RUNNING, PAUSED, HALT };
class Simulation
{
private:
    std::vector<Object*> objectList;
    QGraphicsScene* scene;
    int timeElapsed;
    SimulationState STATE;

public:
    Simulation() : scene(new QGraphicsScene()), timeElapsed(0), STATE(SimulationState::INIT) {}
    ~Simulation() { delete scene; }

    void addObject(QGraphicsItem* item);

    QGraphicsScene* getScene() const;

    void start(void);
    void stop(void);
    void resume(void);
    void halt(void);
    void loadConfig(void);
    void storeConfig(void);
};


