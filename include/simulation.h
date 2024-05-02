/**
 * \file simulation.h
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \brief   Header file for simulation
 * \version 0.1
 * \date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "debug.h"
#include "json_handler.h"
#include "obstacle.h"
#include "robot.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QList>
#include <QWidget>
#include <iostream>
#include <memory>
#include <random>

#define SCENE_WIDTH  940.0
#define SCENE_HEIGHT 860.0

#define MAX_DETECT_DIST 100.0
#define MAX_ROTATE_BY   M_PI / 8
#define MAX_SPEED       3.00

/**
 * \brief Enum class representing the state of the simulation.
 */
enum class State
{
    RUNNING, /**< The simulation is currently running. */
    STOPPED  /**< The simulation is currently stopped. */
};

/**
 * \brief Enum class representing different types of objects in the simulation.
 */
enum class ObjectType
{
    ROBOT,   /**< Represents a robot object.        */
    OBSTACLE /**< Represents an obstacle object.    */
};

/**
 * \brief Class for managing graphical items in the simulation.
 *
 * This class handles the management of graphical items within the simulation,
 * including robots and obstacles. It also manages the simulation's state,
 * timing, and interaction with a QGraphicsScene for visualization.
 */
class Simulation : public QGraphicsView
{
    Q_OBJECT
  private:
    QList<Robot *>     m_robot_list;    /* list of robots               */
    QList<Obstacle *>  m_obstacle_list; /* list of obstacles            */
    JsonHandler        json;            /* instance of json interface   */
    State              m_state;         /* state of simulation          */
    Robot             *m_selectedRobot; /* pointer to selected robot    */
    std::random_device m_rd;
    std::mt19937       m_rng{m_rd()};

  public:
    /**
     * \brief Constructs a new Simulation object.
     *
     * This constructor initializes a new instance of the Simulation class.
     */

    Simulation(QWidget *parent = nullptr);

    /**
     * \brief Destroys the Simulation object.
     *
     * This destructor cleans up resources associated with the Simulation
     * object.
     */
    ~Simulation() {}

    /**
     * \brief Retrieves a pointer to the list of robots.
     *
     * This function returns a pointer to the list of robots stored in the
     * simulation.
     *
     * \return A pointer to the list of Robot objects.
     */
    QList<Robot *> *robotList();

    /**
     * \brief Retrieves a pointer to the list of obstacles.
     *
     * This function returns a pointer to the list of obstacles stored in the
     * simulation.
     *
     * \return A pointer to the list of Robot objects.
     */
    QList<Obstacle *> *obstacleList();

    /**
     * \brief Adds a robot object to the simulation.
     *
     * This function adds a robot object to both the internal list of
     * robots and the graphics scene of the simulation.
     *
     * \param robot A pointer to the robot object to be added.
     */
    void addRobot(Robot *robot);

    /**
     * \brief Adds a obstacle object to the simulation.
     *
     * This function adds a obstacle object to both the internal list of
     * obstacles and the graphics scene of the simulation.
     *
     * \param obstacle A pointer to the obstacle object to be added.
     */
    void addObstacle(Obstacle *obstacle);

    /**
     * \brief [Debug] Prints the lists of robots and obstacles.
     *
     * This function prints the contents of the lists of robots and obstacles
     * to the console for debugging purposes.
     */
    void printLists();

    /**
     * \brief Retrieves the current state of the simulation.
     *
     * This function returns the current state of the simulation.
     *
     * \return The state of the simulation.
     */
    State getState() const;

    /**
     * \brief Sets the state of the simulation.
     *
     * This function sets the state of the simulation to the specified state.
     *
     * \param _state The state to be set.
     */
    void setState(State _state);

  public slots:
    /**
     * \brief Load a layout configuration from a file.
     *
     * This function loads the layout configuration from a file
     * and applies it to the simulation.
     */
    void loadLevelLayout();

    /**
     * \brief Save the current layout configuration to a file.
     *
     * This function saves the current layout configuration of
     * the simulation to a file for future use.
     */
    void saveLevelLayout();

    /**
     * \brief Spawn a new robot in the simulation.
     *
     * This function creates and adds a new robot to the simulation.
     */
    void spawnRobot();

    /**
     * \brief Spawn a new obstacle in the simulation.
     *
     * This function creates and adds a new obstacle to the simulation.
     */
    void spawnObstacle();

    /**
     * \brief Delete the selected robot from the simulation.
     *
     * This function removes the currently selected robot from
     * the simulation.
     */
    void deleteRobot();

    /**
     * \brief Delete the selected obstacle from the simulation.
     *
     * This function removes the currently selected obstacle from
     * the simulation.
     */
    void deleteObstacle();

    /**
     * \brief Delete all items from the simulation.
     *
     * This function removes all objects and clears the scene
     * of the simulation.
     */
    void purgeScene();

    /**
     * \brief Zooms in the view
     **/
    void zoomIn();

    /**
     * \brief Zooms out the view
     **/
    void zoomOut();

  protected:
    /**
     * \brief Handle '+/-' keys for zooming
     * \param event Keypress event
     **/
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * \brief Scales the view of the scene
     * \param factor Scale factor
     **/
    void scaleView(qreal factor);

    /**
     * \brief Draw the background of the view
     * \param painter
     * \param rect
     **/
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    /**
     * \brief Creates an object at a random available place in the simulation.
     *
     * This function creates an object of the specified type at a random
     * available location within the simulation.
     *
     * \param type The type of object to spawn.
     */
    void spawnObject(ObjectType type);

    /**
     * \brief Deletes selected object
     *
     * \param type type of object to delete
     **/
    void deleteObject(ObjectType type);

    void mousePressEvent(QMouseEvent *event) override;
};
