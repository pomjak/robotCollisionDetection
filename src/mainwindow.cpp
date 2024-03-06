#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "object.h"
#include "robot.h"
#include "obstacle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RobotFactory robotFactory;
    ObstacleFactory obstacleFactory;

    Robot* robot = robotFactory.createRobot();
    Obstacle* obstacle = obstacleFactory.createObstacle();
    
    delete obstacle;
    delete robot;
}

MainWindow::~MainWindow()
{
    delete ui;
}
