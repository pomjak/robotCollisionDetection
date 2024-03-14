#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), simulation(std::make_unique<Simulation>())
{
    QTimer* timer = new QTimer(this);
    timer->start(1000 / 33);

    ui->setupUi(this);
    addObstacle(100,Position{400,25});
    addRobot(50, Position{ 0,0 }, robotAttributes{ 0,1,5,10 });

    connect(timer, &QTimer::timeout, this, &MainWindow::updateRobotPosition);

    ui->graphicsView->setScene(simulation.get()->getScene());
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(800, 800);
    ui->graphicsView->scene()->setSceneRect(QRectF(QPointF(0, 0), QSizeF(800, 800)));
    ui->graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

}

void MainWindow::addObstacle(double sizeValue = 10, Position positionValue = Position{ 10,10 })
{
    static ObstacleFactory obstacleFactory;
    Obstacle* obstacle = obstacleFactory.createObstacle(sizeValue, positionValue);
    simulation.get()->addObject(obstacle);
}

void MainWindow::addRobot(double sizeValue = 10, Position positionValue = Position{ 10,10 }\
    , robotAttributes attributesValues = robotAttributes{ 10,10,10,10 })
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

            if ( robot->detectCollision(simulation.get()->objectList) )
            {
                robot->rotate();
            }
            else
            {
                Position delta = robot->newPosition();
                robot->moveBy(delta.x, delta.y);
                robot->correctBoundaries(ui->graphicsView->width(), ui->graphicsView->height());
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
