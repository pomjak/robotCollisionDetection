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
     * Collects all json objects from all items and process it into an json array 
     * 
     * \return QJsonObject 
     */
    QJsonObject getJsonObjects();
    void        read(const QJsonObject &json);
    void        addRobot(Robot *robot) { robotList->push_back(robot); }
    void addObstacle(Obstacle *obstacle) { obstacleList->push_back(obstacle); }

  public:
    JsonHandler(QList<Robot *> *_rList, QList<Obstacle *> *_oList)
        : robotList(_rList)
        , obstacleList(_oList)
    {}
    ~JsonHandler() {}

    void save(const QString &filename);
    void load(const QString &filename);
};
