/**
 * \file robot.h
 * \brief
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \date 2024-04-26
 **/

#pragma once

#include "debug.h"
#include "obstacle.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTransform>
#include <QtCore>

#define DEF_ROBOT_SIZE  50.0 /* Default robot parameters */
#define DEF_DETECT_DIST 25.0
#define DEF_ROTATE_BY   0.1
#define DEF_SPEED       2.0

/**
 * \brief A graphical item to use in the main scene and perform collision
 * detection on
 */
class Robot
    : public QObject
    , public QGraphicsItem
{
    // friend class Simulation;
    Q_OBJECT

  private:
    double m_size;           /// Size of the robot (diameter)
    double m_angle;          /// Current angle of the robot
    double m_speed;          /// Speed of the robot
    double m_rotate_by;      /// Angle to rotate by when detecting a collision
    double m_detection_dist; /// Maximum collision detec distance

  public:
    /**
     * \brief Create a new robot
     **/
    Robot();

    /**
     * \brief Create a new robot
     * \param _angle default angle of the robot
     * \param _speed default speed of the robot
     * \param _rotate default angle to rotate by in case of a detected
     *collision
     * \param _detect Maximum distance from the robot at which
     *collision is detected
     **/
    Robot(double _angle, double _speed, double _rotate, double _dist);

    /**
     * @brief Construct a new Robot
     *
     * @param _position initial position
     */
    Robot(QPointF _position);

    /**
     * \brief Construct a new Robot object
     * \param json
     **/
    Robot(QJsonObject &json);

    /**
     * \brief Destroy the Robot
     **/
    ~Robot(){};

    /**
     * \brief
     * \return double Size of the robot (diameter)
     **/
    double size() const { return m_size; }

    /**
     * \brief current angle of the robot
     * \return double angle (rad)
     **/
    double getAngle() const { return m_angle; }

    /**
     * \brief Get the speed of the robot
     * \return double
     **/
    double getSpeed() const { return m_speed; }

    /**
     * \brief Get the angle an autonomous robot rotates by to avoid collision
     * \return double
     **/
    double getRotation() const { return m_rotate_by; }

    /**
     * \brief Get the Detect Distance object
     * \return double
     **/
    double getDetectDistance() const { return m_detection_dist; }

    /**
     * \brief Sets the current angle of the robot
     * \param _dir
     **/
    void setAngle(double _dir) { m_angle = _dir; }

    /**
     * \brief Set the speed of the robot
     * \param _speed
     **/
    void setSpeed(double _speed) { m_speed = _speed; }

    /**
     * \brief paints the contents of an item in local coordinates
     * \param painter
     * \param option
     * \param widget
     **/
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /**
     * \brief
     * \return QRectF
     **/
    QRectF boundingRect() const override;

    /**
     * @brief returns bounding rect of object based on new position passed as
     * argument
     *
     * @param newPos new position
     * @return QRectF bounding rect
     */
    QRectF newBoundingRect(QPointF newPos) const;

    /**
     * \brief
     * \return QPainterPath
     **/
    QPainterPath shape() const override;

    /**
     * \brief Called by GraphicsScene::advance slot; animates the object
     * \param phase advance is called twice, once with phase 0, indicating
     *items are about to advance, then with phase 1 to actually advance them
     **/
    void advance(int phase) override;

    /**
     * \brief
     * \return qreal
     **/
    qreal radius() const { return size() / 2; }

    /**
     * \brief Convenience function equivalent to boundingRect.center()
     * \return QPointF
     **/
    QPointF center() const { return boundingRect().center(); }

    /**
     * \brief A point on the peri
     * \return QPointF
     **/
    QPointF leftBumper() const
    {
        return QPointF(
            center().x() + radius() * ::cos(getAngle() - (M_PI / 2)),
            center().y() + radius() * ::sin(getAngle() - (M_PI / 2)));
    }

    /**
     * \brief
     * \return QPointF
     **/
    QPointF rightBumper() const
    {
        return QPointF(
            center().x() + radius() * ::cos(getAngle() + (M_PI / 2)),
            center().y() + radius() * ::sin(getAngle() + (M_PI / 2)));
    }

    /**
     * \brief
     * \return QPointF
     **/
    QPointF detectionPoint() const
    {
        return QPointF(((center().x() + radius() * ::cos(getAngle())) +
                        (getDetectDistance() * ::cos(getAngle()))),
                       ((center().y() + radius() * ::sin(getAngle())) +
                        (getDetectDistance() * ::sin(getAngle()))));
    }

    /**
     * \brief
     * \return QRectF detection area
     **/
    QPolygonF detectionArea() const;

  protected:
    // void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
