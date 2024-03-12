#pragma once 

#include <QGraphicsItem>
#include <QPainter>
#include "object.h"
#include "debug.h"

class Robot : public virtual Object
{
private:
    double orientation;
    double rotation;
    double speed;

public:
    Robot() {}
    ~Robot() {}
    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void move(void);
    void detectCollision(void);
    void rotate(void);
    void manualControl(void);
};

class RobotFactory
{
public:
    Robot* createRobot()
    {
        Robot* robot = new Robot();
        DBG << "created robot";
        return robot;
    }
};
