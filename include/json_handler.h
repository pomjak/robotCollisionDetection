/**
 * \file json_handler.h
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \brief Header file for JSON handler class, which is being interface between
 * json files and simulation file
 * \version 0.1 \date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <QList>
#include <QtCore>

#include "debug.h"
#include "obstacle.h"
#include "robot.h"

/**
 * \brief Interface between simulation and saving/loading objects from JSON
 *
 */
class JsonHandler
{
  private:
    QList<Robot *>
        *robotList; /* reference on robot list from simulation class */
    QList<Obstacle *>
        *obstacleList; /* reference on robot list from simulation class */

    /**
     * \brief Returns parameters of robot as Json object
     *
     * \param _ Robot to be processed
     * \return QJsonObject which contains parameters of processed object
     */
    QJsonObject saveToJson(Robot *_) const;

    /**
     * \brief Returns parameters of obstacle as Json object
     *
     * \param _
     * \return QJsonObject
     */
    QJsonObject saveToJson(Obstacle *_) const;

    /**
     * \brief Get the Json Objects object
     *
     * Collects all json objects from all items and process it into an json
     * array
     *
     * \return QJsonObject
     */
    QJsonObject getJsonObjects();

    /**
     * \brief Reads a JSON array from a file and creates objects based on the
     * data.
     *
     * \param json The JSON object containing data from the file.
     */
    void read(const QJsonObject &json);

    /**
     * \brief Adds a robot object to the simulation.
     *
     * \param robot A pointer to the robot object to be added.
     */
    void addRobot(Robot *robot) { robotList->push_back(robot); }

    /**
     * \brief Adds a obstacle object to the simulation.
     *
     * \param obstacle A pointer to the obstacle object to be added.
     */
    void addObstacle(Obstacle *obstacle) { obstacleList->push_back(obstacle); }

  public:
    /**
     * \brief Constructor for the JsonHandler class.
     *
     * Initializes a JsonHandler object with pointers to lists of robots and
     * obstacles.
     *
     * \param _rList Pointer to the list of robots.
     * \param _oList Pointer to the list of obstacles.
     */
    JsonHandler(QList<Robot *> *_rList, QList<Obstacle *> *_oList)
        : robotList(_rList)
        , obstacleList(_oList)
    {}

    /**
     * \brief Destructor for the JsonHandler class.
     *
     * Optionally perform cleanup tasks if needed.
     */
    ~JsonHandler() {}

    /**
     * \brief Saves data to a file.
     *
     * This is the main function for saving data to a file.
     *
     * \param filename The name of the file to save to.
     */
    void save(const QString &filename);

    /**
     * \brief Loads data from a file.
     *
     * This is the main function for loading data from a file.
     *
     * \param filename The name of the file to load from.
     */
    void load(const QString &filename);
};
