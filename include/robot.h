/**
 * \file robot.h
 * \brief
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \date 2024-04-26
 **/

#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QtCore>

#define DEF_ROBOT_SIZE 50.0
#define DEF_DETECT_DIST 25.0
#define DEF_ROTATE_BY 15.0

 /**
  * \brief A graphical item to use in the main scene and perform collision
  * detection on
  */
class Robot : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    double m_size;           /// Size of the robot (diameter)
    double m_angle;          /// Current angle of the robot
    double m_speed;          /// Speed of the robot
    double m_rotate_by;      /// Angle to rotate by when detecting a collision
    double m_detection_dist; /// Maximum distance from the robot to detect collisions
    QColor m_color;          /// Color?

public:
    /**
     * \brief Construct a new Robot object
     **/
    Robot();

    /**
     * \brief Create a new robot
     * \param _angle default angle of the robot
     * \param _speed default speed of the robot
     * \param _rotate default angle to rotate by in case of a detected collision
     * \param _detect Maximum distance from the robot at which collision is
     *detected
     **/
    Robot(double _angle, double _speed, double _rotate, double _dist);

    /**
     * \brief Construct a new Robot object
     * \param json
     **/
    Robot(QJsonObject& json);

    /**
     * \brief Destroy the \c Robot
     **/
    ~Robot() {};

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
     * \brief Sets the angle an autonomous robot will rotate by to avoid collision
     * \param _rotation
     **/
    void setRotation(double _rotation) { m_rotate_by = _rotation; }

    /**
     * \brief Resize the robot
     * \param _size new size
     **/
    void resize(double _size) { m_size = _size; }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

protected:
    void advance(int phase) override;
};
