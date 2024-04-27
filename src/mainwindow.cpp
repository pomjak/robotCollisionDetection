#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), simulation(new Simulation)
{
    QTimer* timer = new QTimer(this);
    timer->start(1000 / 33);

    setup();
    connect_buttons();
    connect(timer, &QTimer::timeout, simulation->getScene().get(), &QGraphicsScene::advance);

}

void MainWindow::setup()
{
    ui->setupUi(this);
    ui->graphicsView->setScene(simulation->getScene().get());
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->graphicsView->setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->scene()->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    // ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->viewport()->update();
    ui->graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->scale(qreal(0.8), qreal(0.8));

    ui->graphicsView->setWindowTitle(tr("ICP - 24"));
}

void MainWindow::connect_buttons()
{
    /* Buttons */
    connect(ui->importButton, &QPushButton::clicked, simulation, &Simulation::loadLevelLayout);
    connect(ui->exportButton, &QPushButton::clicked, simulation, &Simulation::saveLevelLayout);
    connect(ui->addRobotButton, &QPushButton::clicked, simulation, &Simulation::spawnRobot);
    connect(ui->addObstacleButton, &QPushButton::clicked, simulation, &Simulation::spawnObstacle);
    connect(ui->deleteObjectButton, &QPushButton::clicked, simulation, &Simulation::deleteObject);
    connect(ui->deleteAllButton, &QPushButton::clicked, simulation, &Simulation::purgeScene);
}

MainWindow::~MainWindow()
{
    delete simulation;
    delete ui;
}


