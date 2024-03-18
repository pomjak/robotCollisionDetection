#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), simulation(std::make_unique<Simulation>())
{
    QTimer* timer = new QTimer(this);
    timer->start(1000 / 33);

    setup();

    addObstacle(100, Position{ 200,50 }, 1);
    addRobot(100, Position{ 0,50}, 2, robotAttributes{ 0,M_PI,1,10 });
    connect(timer, &QTimer::timeout, this, &MainWindow::updateRobotPosition);
}

void MainWindow::setup()
{
    ui->setupUi(this);

    ui->graphicsView->setScene(simulation.get()->getScene());
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(VIEW_SIZE, VIEW_SIZE);
    ui->graphicsView->scene()->setSceneRect(QRectF(QPointF(0, 0), QSizeF(VIEW_SIZE, VIEW_SIZE)));
    ui->graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}


void MainWindow::addObstacle(double sizeValue = 10, \
    Position positionValue = Position{ 10,10 }, \
    unsigned int idValue = 0)
{
    static ObstacleFactory obstacleFactory;
    Obstacle* obstacle = obstacleFactory.createObstacle(sizeValue, positionValue, idValue);

    simulation.get()->addObject(obstacle);
}

void MainWindow::addRobot(double sizeValue = 10, \
    Position positionValue = Position{ 10,10 }\
    , unsigned int idValue = 0, \
    robotAttributes attributesValues = robotAttributes{ 10,10,10,10 })
{
    static RobotFactory robotFactory;
    Robot* robot = robotFactory.createRobot(sizeValue, positionValue, idValue, attributesValues);
    robot->setPos(positionValue.x, positionValue.y);
    simulation.get()->addObject(robot);
}

void MainWindow::updateRobotPosition()
{
    for ( Object* obj : simulation.get()->objectList )
    {
        if ( Robot* robot = dynamic_cast<Robot*>( obj ) )  // If dynamic_cast succeeds, obj points to a Robot
        {

            if ( robot->detectCollisions(robot->getDetectionPoints(), simulation.get()->objectList) )
            {
                robot->rotate();
            }
            else
            {
                Position delta = robot->newPosition();
                robot->setDeltaPosition(delta);     //  core position
                robot->moveBy(delta.x, delta.y);    //GUI Qt position
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
