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
#include <QList>
#include <iostream>
#include <memory>

#define VIEW_WIDTH  444.0 /* view size */
#define VIEW_HEIGHT 384.0

using std::shared_ptr;
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
class Simulation : public QObject
{
    Q_OBJECT
  private:
    QList<Robot *>             robotList;    /* list of robots               */
    QList<Obstacle *>          obstacleList; /* list of obstacles            */
    shared_ptr<QGraphicsScene> scene;        /* pointer to scene             */
    JsonHandler                json;         /* instance of json interface   */
    double                     time;         /* time of simulation           */
    State                      state;        /* state of simulation          */

  public:
    /**
     * \brief Constructs a new Simulation object.
     *
     * This constructor initializes a new instance of the Simulation class.
     */
    Simulation();

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
    QList<Robot *> *getRobotList() const
    {
        return new QList<Robot *>(robotList);
    }

    /**
     * \brief Retrieves a pointer to the list of obstacles.
     *
     * This function returns a pointer to the list of obstacles stored in the
     * simulation.
     *
     * \return A pointer to the list of Robot objects.
     */
    QList<Obstacle *> *getObstacleList() const
    {
        return new QList<Obstacle *>(obstacleList);
    }

    /**
     * \brief Adds a robot object to the simulation.
     *
     * This function adds a robot object to both the internal list of robots
     * and the graphics scene of the simulation.
     *
     * \param robot A pointer to the robot object to be added.
     */
    void addRobot(Robot *robot)
    {
        robotList.push_back(robot);
        scene->addItem(robot);
    }

    /**
     * \brief Adds a obstacle object to the simulation.
     *
     * This function adds a obstacle object to both the internal list of
     * obstacles and the graphics scene of the simulation.
     *
     * \param obstacle A pointer to the obstacle object to be added.
     */
    void addObstacle(Obstacle *obstacle)
    {
        obstacleList.push_back(obstacle);
        scene->addItem(obstacle);
    }

    /**
     * \brief [Debug] Prints the lists of robots and obstacles.
     *
     * This function prints the contents of the lists of robots and obstacles
     * to the console for debugging purposes.
     */
    void printLists();

    /**
     * \brief Retrieves a shared pointer to the graphics scene.
     *
     * This function returns a shared pointer to the QGraphicsScene object
     * used in the simulation.
     *
     * \return A shared pointer to the QGraphicsScene object.
     */
    shared_ptr<QGraphicsScene> getScene() const { return scene; }

    /**
     * \brief Retrieves the current state of the simulation.
     *
     * This function returns the current state of the simulation.
     *
     * \return The state of the simulation.
     */
    State getState() const { return state; }

    /**
     * \brief Sets the state of the simulation.
     *
     * This function sets the state of the simulation to the specified state.
     *
     * \param _state The state to be set.
     */
    void setState(State _state) { state = _state; }

    /**
     * \brief Creates an object at a random available place in the simulation.
     *
     * This function creates an object of the specified type at a random
     * available location within the simulation.
     *
     * \param type The type of object to spawn.
     */
    void spawnObject(ObjectType type);

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
     * \brief Delete the selected object from the simulation.
     *
     * This function removes the currently selected object from
     * the simulation.
     */
    void deleteObject();

    /**
     * \brief Delete all items from the simulation.
     *
     * This function removes all objects and clears the scene
     * of the simulation.
     */
    void purgeScene();
};
