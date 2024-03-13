#include "mainwindow.h"
#include "ui_mainwindow.h"


RobotFactory robotFactory;
Robot* robot = robotFactory.createRobot();

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), simulation(std::make_unique<Simulation>())
{
    ui->setupUi(this);
    DBG << "ui setup";

    
    ObstacleFactory obstacleFactory;

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateRobotPosition);
    timer->start(1000/33);

    
    Obstacle* obstacle = obstacleFactory.createObstacle();

    ui->graphicsView->setScene(simulation.get()->getScene());

    simulation.get()->addObject(robot);
    simulation.get()->addObject(obstacle);
    robot->setSpeed(10);
    robot->setRotation(10);
    robot->setOrientation(0);

}

void MainWindow::updateRobotPosition()
{
    Position delta = robot->newPosition();
    robot->moveBy(delta.x,delta.y);
}

MainWindow::~MainWindow()
{
    delete ui;
}
