/**
 * \file obstacle.h
 * \brief Obstacle definitions
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \date 2024-04-26
 **/

#pragma once

#include "debug.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QtCore>
#include <QtGlobal>

/**
 * \brief Stationary obstacle graphical item
 * \details Used as a wall for the simulation collision detection
 **/
#define MAX_W             1920.0
#define MAX_H             1080.0
#define MAX_OBS_SIZE      240.0
#define DEF_OBSTACLE_SIZE 120.0 /* Default obstacle parameters */

class Obstacle : public QGraphicsItem
{
  private:
    qreal   m_size;        /// Size of the obstacle
    qreal   m_orientation; /// Angle the obstacle is facing
    QPointF m_offset;      /// offset used for mouse movements

  public:
    /**
     * \brief Initialize an obstacle with default size.
     */
    Obstacle();

    /**
     * \brief Constructor for the Obstacle class with a specified position.
     *
     * \param _position The position of the obstacle.
     * \param size
     */
    Obstacle(QPointF position, qreal size);

    /**
     * \brief Constructor for the Obstacle class with a specified position,
     * size, and angle.
     *
     * \param position The position of the obstacle.
     * \param size The size of the obstacle.
     * \param angle The angle of the obstacle.
     */
    Obstacle(QPointF position, qreal size, qreal angle);

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
     * \brief Get the current orientation of the obstacle
     * \return qreal angle
     **/
    qreal angle() const;

    /**
     * \brief Get the size of the obstacle
     * \return qreal side
     **/
    qreal size() const;

    /**
     * \brief Set the Angle of the obstacle
     * \param a angle
     **/
    void setAngle(qreal a);

    /**
     * \brief Set the Size object
     *
     * \param s
     **/
    void setSize(qreal s);

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

    QPainterPath shape() const override;

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

  private:
    QPointF center() const;
    QPointF midTop() const;
    QPointF midBottom() const;
    QPointF topLeft() const;
    QPointF topRight() const;
    QPointF bottomLeft() const;
    QPointF bottomRight() const;
    qreal   dx(qreal angle_mod = 0) const;
    qreal   dy(qreal angle_mod = 0) const;
};
