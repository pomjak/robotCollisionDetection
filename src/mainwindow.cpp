#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), simulation(std::make_unique<Simulation>())
{
    QTimer* timer = new QTimer(this);
    timer->start(1000 / 33);

    setup();

    addObstacle(100, Position{ 300,200 }, 1);
    addObstacle(100, Position{ 100,200 }, 1);
    addRobot(50, Position{ 200,200 }, 2, robotAttributes{ 0,M_PI,2.5,10 });
    connect(timer, &QTimer::timeout, this, &MainWindow::updateRobotPosition);
}

void MainWindow::setup()
{
    ui->setupUi(this);

    ui->graphicsView->setScene(simulation.get()->getScene());
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(SCENE_SIZE, SCENE_SIZE);
    ui->graphicsView->scene()->setSceneRect(QRectF(QPointF(0, 0), QSizeF(SCENE_SIZE, SCENE_SIZE)));
    ui->graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}


void MainWindow::addObstacle(double sizeValue = 10, \
    Position positionValue = Position{ 10,10 }, \
    unsigned int idValue = 0)
{
    static ObstacleFactory obstacleFactory;
    Obstacle* obstacle = obstacleFactory.createObstacle(sizeValue, positionValue, idValue);
    obstacle->setPos(positionValue.x, positionValue.y);
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
            auto points = robot->getDetectionPoints();
            if ( robot->detectCollisions(points, simulation.get()->objectList)  \
                || \
                robot->detectBorders(points, VIEW_SIZE) )
            {
                robot->rotate();
            }
            else
            {
                Position newPos = robot->getPosition() + robot->newPosition();
                robot->setPosition(newPos);     //  core position
                robot->setPos(newPos.x, newPos.y);    //GUI Qt position
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
