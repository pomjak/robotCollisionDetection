#include "mainwindow.h"
// #include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    // , ui(new Ui::MainWindow)
    , simulation(new Simulation)
    , view(new QGraphicsView)
    , timer(new QTimer(this))
{
    setup();
    // connect_buttons();

    connect(timer, &QTimer::timeout, simulation->getScene().get(),
            &QGraphicsScene::advance);
}

void MainWindow::setup()
{
    // ui->graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    // ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // ui->graphicsView->setWindowTitle(tr("ICP - 24"));

    // simulation->getScene()->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(simulation->getScene().get());
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);

    // view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    view->setMaximumWidth(1920);
    view->setMinimumWidth(800);
    view->setMaximumHeight(1080);
    view->setMinimumHeight(600);

    setWindowTitle(tr("ICP24 - Robot collision simulation"));
    setCentralWidget(view);

    setupActions();
    setupMenus();
}

void MainWindow::setupActions()
{
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(QKeySequence(tr("Ctrl+Q")));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    addRobotAction = new QAction(tr("Add Robot"), this);
    addRobotAction->setShortcut(QKeySequence(tr("Ctrl+N")));
    connect(addRobotAction, &QAction::triggered, simulation,
            &Simulation::spawnRobot);

    addObstacleAction = new QAction(tr("Add Obstacle"), this);
    addObstacleAction->setShortcut(QKeySequence(tr("Ctrl+M")));
    connect(addObstacleAction, &QAction::triggered, simulation,
            &Simulation::spawnObstacle);

    loadLevelAction = new QAction(tr("L&oad Level"), this);
    loadLevelAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    connect(loadLevelAction, &QAction::triggered, simulation,
            &Simulation::loadLevelLayout);

    saveLevelAction = new QAction(tr("&Save Level"), this);
    saveLevelAction->setShortcut(QKeySequence(tr("Ctrl+S")));
    connect(saveLevelAction, &QAction::triggered, simulation,
            &Simulation::saveLevelLayout);

    toggleSimAction = new QAction(tr("Play / Pause"), this);
    toggleSimAction->setShortcut(QKeySequence(tr("F5")));
    connect(toggleSimAction, &QAction::triggered, this,
            &MainWindow::toggleTimer);
}

void MainWindow::setupMenus()
{
    file_menu = menuBar()->addMenu(tr("&File"));
    // TODO
    file_menu->addAction(saveLevelAction);
    file_menu->addAction(loadLevelAction);
    file_menu->addAction(exitAction);

    edit_menu = menuBar()->addMenu(tr("&Simulation"));
    edit_menu->addAction(toggleSimAction);
    edit_menu->addAction(addRobotAction);
    edit_menu->addAction(addObstacleAction);
}

void MainWindow::toggleTimer()
{
    if ( simulation->getState() == State::RUNNING )
    {
        timer->stop();
        simulation->setState(State::STOPPED);
        INFO << "Simulation stopped";
    }
    else
    {
        timer->start(MSEC);
        simulation->setState(State::RUNNING);
        INFO << "Simulation running";
    }
}

MainWindow::~MainWindow()
{
    delete timer;
    delete simulation;
    delete view;
    // delete ui;
}
