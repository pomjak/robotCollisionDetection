#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), simulation(new Simulation)
{
    QTimer* timer = new QTimer(this);
    timer->start(1000 / 33);

    setup();
    simulation->printLists();
    connect(timer, &QTimer::timeout, simulation->getScene().get(), &QGraphicsScene::advance);
}

void MainWindow::setup()
{
    ui->setupUi(this);
    ui->graphicsView->setScene(simulation->getScene().get());
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->scene()->setSceneRect(QRectF(QPointF(0, 0), QSizeF(SCENE_WIDTH, SCENE_HEIGHT)));
    ui->graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);


    connect(ui->importButton, &QPushButton::clicked, simulation, &Simulation::loadLevelLayout);
    connect(ui->exportButton, &QPushButton::clicked, simulation, &Simulation::saveLevelLayout);
}

MainWindow::~MainWindow()
{
    delete simulation;
    delete ui;
}


