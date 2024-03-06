#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "object.h"
#include "simulation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RobotFactory robotFactory;
    ObstacleFactory obstacleFactory;
    Simulation simulation;

    Robot* robot = robotFactory.createRobot();
    Obstacle* obstacle = obstacleFactory.createObstacle();

    delete obstacle;
    delete robot;
}

MainWindow::~MainWindow()
{
    delete ui;
}
