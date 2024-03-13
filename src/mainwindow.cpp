#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), simulation(std::make_unique<Simulation>())
{
    QTimer* timer = new QTimer(this);
    timer->start(1000 / 33);

    ui->setupUi(this);
    addObstacle(35, Position{ 10,10 });
    addObstacle(35, Position{ 200,25 });
    addObstacle(35, Position{ 100,100 });
    addRobot(35, Position{ 0,0 }, robotAttributes{ 0,10,5,1 });
    addRobot(35, Position{ 0,0 }, robotAttributes{ 1,10,5,1 });
    addRobot(35, Position{ 0,0 }, robotAttributes{ 2,10,5,1 });
    addRobot(35, Position{ 0,0 }, robotAttributes{ 3,10,5,1 });
    addRobot(35, Position{ 0,0 }, robotAttributes{ 4,10,5,1 });
    addRobot(35, Position{ 0,0 }, robotAttributes{ 5,10,5,1 });
    connect(timer, &QTimer::timeout, this, &MainWindow::updateRobotPosition);

    ui->graphicsView->setScene(simulation.get()->getScene());
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::addObstacle()
{
    static ObstacleFactory obstacleFactory;
    Obstacle* obstacle = obstacleFactory.createObstacle();
    simulation.get()->addObject(obstacle);
}

void MainWindow::addObstacle(double sizeValue, Position positionValue)
{
    static ObstacleFactory obstacleFactory;
    Obstacle* obstacle = obstacleFactory.createObstacle(sizeValue, positionValue);
    simulation.get()->addObject(obstacle);
}

void MainWindow::addRobot(void)
{
    static RobotFactory robotFactory;
    Robot* robot = robotFactory.createRobot();
    simulation.get()->addObject(robot);
}

void MainWindow::addRobot(double sizeValue, Position positionValue, robotAttributes attributesValues)
{
    static RobotFactory robotFactory;
    Robot* robot = robotFactory.createRobot(sizeValue, positionValue, attributesValues);
    simulation.get()->addObject(robot);
}


void MainWindow::updateRobotPosition()
{
    for ( Object* obj : simulation.get()->objectList )
    {
        if ( Robot* robot = dynamic_cast<Robot*>( obj ) )  // If dynamic_cast succeeds, obj points to a Robot
        {
            Position delta = robot->newPosition();
            robot->moveBy(delta.x, delta.y);
            
            robot->correctBoundaries(ui->graphicsView->width(), ui->graphicsView->height());
            DBG << "Moving by:" << delta.x << delta.y;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
