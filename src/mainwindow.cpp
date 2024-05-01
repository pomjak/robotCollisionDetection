/**
 * \file mainwindow.cpp
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \version 0.1
 * \date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , simulation(new Simulation(this))
    , timer(new QTimer(this))
{
    setWindowTitle(tr("ICP24 - Robot collision simulation"));
    setupActions();
    setupMenus();
    setCentralWidget(simulation);
    connect(timer, &QTimer::timeout, simulation->scene(),
            &QGraphicsScene::advance);
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

    deleteRobotAction = new QAction(tr("Remove robot"), this);
    deleteRobotAction->setShortcut(QKeySequence(tr("Delete")));
    connect(deleteRobotAction, &QAction::triggered, simulation,
            &Simulation::deleteRobot);

    deleteObstacleAction = new QAction(tr("Remove obstacle"), this);
    deleteObstacleAction->setShortcut(QKeySequence(tr("Delete")));
    connect(deleteRobotAction, &QAction::triggered, simulation,
            &Simulation::deleteObstacle);

    loadLevelAction = new QAction(tr("L&oad Level"), this);
    loadLevelAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    connect(loadLevelAction, &QAction::triggered, simulation,
            &Simulation::loadLevelLayout);

    saveLevelAction = new QAction(tr("&Save Level"), this);
    saveLevelAction->setShortcut(QKeySequence(tr("Ctrl+S")));
    connect(saveLevelAction, &QAction::triggered, simulation,
            &Simulation::saveLevelLayout);

    toggleSimAction = new QAction(tr("&Play / Pause"), this);
    toggleSimAction->setShortcut(QKeySequence(tr("Space")));
    connect(toggleSimAction, &QAction::triggered, this,
            &MainWindow::toggleTimer);

    clearSceneAction = new QAction(tr("C&lear Scene"), this);
    clearSceneAction->setShortcut(QKeySequence(tr("Ctrl+L")));
    connect(clearSceneAction, &QAction::triggered, simulation,
            &Simulation::purgeScene);
}

void MainWindow::setupMenus()
{
    file_menu = menuBar()->addMenu(tr("&File"));
    file_menu->addAction(saveLevelAction);
    file_menu->addAction(loadLevelAction);
    file_menu->addAction(exitAction);

    edit_menu = menuBar()->addMenu(tr("&Simulation"));
    edit_menu->addAction(toggleSimAction);
    edit_menu->addAction(addRobotAction);
    edit_menu->addAction(addObstacleAction);
    edit_menu->addAction(clearSceneAction);
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
}
