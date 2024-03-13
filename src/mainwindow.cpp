#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), simulation(std::make_unique<Simulation>())
{
    ui->setupUi(this);
    DBG << "ui setup";

    RobotFactory robotFactory;
    ObstacleFactory obstacleFactory;

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateRobotPosition);
    timer->start(1000/33);

    
    Robot* robot = robotFactory.createRobot();
    Obstacle* obstacle = obstacleFactory.createObstacle();

    ui->graphicsView->setScene(simulation.get()->getScene());

    simulation.get()->addObject(robot);
    simulation.get()->addObject(obstacle);

    robot->setSpeed(10);
    robot->setRotation(10);
    robot->setOrientation(1.5);

}

void MainWindow::updateRobotPosition()
{
    for(Object* obj : simulation.get()->objectList)
    {
        if ( Robot* robot = dynamic_cast<Robot*>( obj ) )  // If dynamic_cast succeeds, obj points to a Robot
        {
            Position delta = robot->newPosition();
            robot->moveBy(delta.x, delta.y);
            DBG << "Moving by:" << delta.x << delta.y;
        }
        
    }
    
}

MainWindow::~MainWindow()
{
    delete ui;
}
