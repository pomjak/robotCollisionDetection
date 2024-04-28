/**
 * \file obstacle.h
 * \brief Obstacle definitions
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \date 2024-04-26
 **/

#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QtCore>

/**
 * \brief Stationary obstacle graphical item
 * \details Used as a wall for the simulation collision detection
 **/

#define DEF_OBSTACLE_SIZE 100.0 /* Default obstacle parameters */
class Obstacle : public QGraphicsItem
{
  private:
    double size; /* obstacle size */

  public:
    /**
     * \brief Default constructor for the Obstacle class.
     *
     * Initializes an obstacle with the default size.
     */
    Obstacle()
        : size(DEF_OBSTACLE_SIZE) /* Initialize size with the default size */
    {}

    /**
     * \brief Constructor for the Obstacle class with a specified position.
     *
     * \param _position The position of the obstacle.
     */
    Obstacle(QPointF _position);

    /**
     * \brief Constructor for the Obstacle class with a specified position,
     * size, and angle.
     *
     * \param _position The position of the obstacle.
     * \param _size The size of the obstacle.
     * \param _angle The angle of the obstacle.
     */
    Obstacle(QPointF _position, double _size, double _angle);

    /**
     * \brief Constructor for the Obstacle class using data from a JSON object.
     *
     * \param json The JSON object containing data for the obstacle.
     */
    Obstacle(QJsonObject &json);

    /**
     * \brief Destructor for the Obstacle class.
     */
    ~Obstacle() {}

    /**
     * \brief Gets the size of the obstacle.
     *
     * \return The size of the obstacle.
     */
    double getSize() const { return size; }

    /**
     * \brief Sets the size of the obstacle.
     *
     * \param _size The new size of the obstacle.
     */
    void setSize(double _size) { size = _size; }

    /**
     * \brief Returns the bounding rectangle of the obstacle.
     *
     * \return The bounding rectangle of the obstacle.
     */
    QRectF boundingRect() const override;

    /**
     * \brief Paints the obstacle on the graphics scene.
     *
     * \param painter The QPainter object used for painting.
     * \param option Extra parameters for painting. (IGNORED)
     * \param widget The widget to be painted. (IGNORED)
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};
