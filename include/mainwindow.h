/**
 * \file mainwindow.h
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \brief Header file  
 * \version 0.1
 * \date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "json_handler.h"
#include "simulation.h"
#include <QMainWindow>
#include <QTimer>
#include <memory>

#define SCENE_WIDTH  940        /* Scene size */
#define SCENE_HEIGHT 820
#define MSEC         1000 / 60  /* Ticks for timer in msec */

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

/**
 * \brief Interface class for Qt's gui
 * 
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    /**
     * \brief Construct a new Main Window object
     * 
     * \param parent 
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * \brief Destroy the Main Window object
     * 
     */
    ~MainWindow();

    /**
     * \brief Sets all gui options
     * 
     */
    void    setup();

    /**
     * \brief Connects all used buttons
     * 
     */
    void    connect_buttons();

    QTimer *timer = new QTimer(this); 

  private:
    Ui::MainWindow *ui;
    Simulation     *simulation;

  public slots:
    /**
     * \brief Toggles timer [ON/OFF] and sets simulation state based on timer
     * 
     */
    void toggleTimer();
};
