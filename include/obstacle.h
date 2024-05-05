/**
 * \file obstacle.h
 * \brief Obstacle definitions
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \date 2024-04-26
 **/

#pragma once

#include "debug.h"
#include "ui_obstacle-properties-dialog.h"
#include <QDialog>
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
    qreal   m_width;  ///   width of the obstacle
    qreal   m_height; ///   height of the obstacle
    QPointF m_offset; ///   offset used for mouse movements

  public:
    /**
     * \brief Initialize an obstacle with default size.
     */
    Obstacle();

    /**
     * \brief Constructor for the Obstacle class with a specified position.
     *
     * \param _position The position of the obstacle.
     * \param w width of the obstacle
     * \param h height of the obstacle
     */
    Obstacle(QPointF position, qreal w, qreal h);

    /**
     * \brief Construct a new Obstacle with specified position and QSizeF
     *
     * \param position The position of the obstacle.
     * \param size The size of the obstacle.
     */
    Obstacle(QPointF position, QSizeF size);

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
     * \brief Get the size of the obstacle
     * \return qreal side
     **/
    qreal size() const;
    /**
     * \brief Set the Size object
     *
     * \param w width of the obstacle
     * \param h height of the obstacle
     **/
    void setSize(qreal w, qreal h);

    void setWidth(qreal w);
    void setHeight(qreal h);

    /**
     * \brief Get the Height of the obstacle
     *
     * \return qreal
     */
    qreal getHeight() const;

    /**
     * \brief Get the Width of the obstacle
     *
     * \return qreal
     */
    qreal getWidth() const;

    /**
     * \brief Returns the bounding rectangle of the obstacle.
     *
     * \return The bounding rectangle of the obstacle.
     */
    QRectF boundingRect() const override;

    /**
     * \brief Returns the bounding rectangle of the obstacle based on new
     * position.
     *
     * \param QPointF new position
     *
     * \return The bounding rectangle of the obstacle.
     */
    QRectF newBoundingRect(QPointF newPos) const;

    /**
     * \brief Paints the obstacle on the graphics scene.
     *
     * \param painter The QPainter object used for painting.
     * \param option Extra parameters for painting. (IGNORED)
     * \param widget The widget to be painted. (IGNORED)
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

class ObstaclePropertiesDialog
    : public QDialog
    , private Ui::ObstacleDialog
{
    Q_OBJECT
  public:
    ObstaclePropertiesDialog(Obstacle *o, QWidget *parent = 0);

  private slots:
    void on_buttonBox_accepted();

  private:
    Obstacle *m_obstacle;
};
