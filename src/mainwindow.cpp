#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QTimer* timer = new QTimer(this);
    timer->start(1000 / 33);

    setup();

    Robot r(10,11,12,13);
    Obstacle o(14);
    Simulation sim;

    sim.addRobot(&r);
    sim.addObstacle(&o);
    sim.saveToJson();
    // connect(timer, &QTimer::timeout, this, &MainWindow::updateRobotPosition);
}

void MainWindow::setup()
{
    ui->setupUi(this);
    // FIXME
    // causes segfault without setup scene
    // ui->graphicsView->setScene(simulation.get()->getScene());
    // ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    // ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->graphicsView->setFixedSize(SCENE_SIZE, SCENE_SIZE);
    // ui->graphicsView->scene()->setSceneRect(QRectF(QPointF(0, 0), QSizeF(SCENE_SIZE, SCENE_SIZE)));
    // ui->graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ui->graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}

MainWindow::~MainWindow()
{
    delete ui;
}
