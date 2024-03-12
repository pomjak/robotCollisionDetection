#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "object.h"
#include "robot.h"
#include "obstacle.h"
#include "simulation.h"
#include "debug.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DBG << "ui setup";
    RobotFactory robotFactory;
    ObstacleFactory obstacleFactory;
    Simulation* simulation = new Simulation();

    Robot* robot = robotFactory.createRobot();
    Obstacle* obstacle = obstacleFactory.createObstacle();


    simulation->addObject(robot);
    simulation->addObject(obstacle);
    ui->graphicsView->setScene(simulation->getScene());

}

MainWindow::~MainWindow()
{
    delete ui;
}
