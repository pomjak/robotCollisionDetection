#pragma once 

#include <QGraphicsScene>
#include <QGraphicsView>

#include <vector>

#include "object.h"
#include "debug.h"

class Simulation
{
private:
    std::vector<Object*> objectList;
    QGraphicsScene *scene;
public:
    Simulation() : scene(new QGraphicsScene())
    {}
    ~Simulation() { delete scene; }

    void addObject(QGraphicsItem* item)
    {
        scene->addItem(item);
        DBG << "adding object to scene";
    }

    QGraphicsScene* getScene() const
    {
        DBG << "gettin scene";
        return scene;
    }

};


