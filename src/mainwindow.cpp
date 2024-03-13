#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), simulation(std::make_unique<Simulation>())
{
    QTimer* timer = new QTimer(this);
    timer->start(1000 / 33);

    ui->setupUi(this);
    addRobot(20, Position{ 100,100 }, robotAttributes{ 0,10,10 });
    connect(timer, &QTimer::timeout, this, &MainWindow::updateRobotPosition);

    ui->graphicsView->setScene(simulation.get()->getScene());
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
