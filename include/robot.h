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
#include "ui_robot-properties-dialog.h"
#include <QCursor>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTransform>
#include <QtCore>

#define DEF_ROBOT_SIZE  50.0 /* Default robot parameters */
#define DEF_DETECT_DIST 25.0
#define DEF_ROTATE_BY   0.1
#define DEF_SPEED       2.0

#define MAX_DETECT_DIST 100.0
#define MAX_ROTATE_BY   M_PI
#define MAX_SPEED       5.00

/**
 * \brief A graphical item to use in the main scene and perform collision
 * detection on
 */
class Robot
    : public QObject
    , public QGraphicsItem
{
    Q_OBJECT

  private:
    double  m_size;           /// Size of the robot (diameter)
    double  m_angle;          /// Current angle of the robot
    double  m_speed;          /// Speed of the robot
    double  m_rotate_by;      /// Angle to rotate by when detecting a collision
    double  m_detection_dist; /// Maximum collision detec distance
    bool    m_clockwise;
    QPointF m_offset;

  public:
    /**
     * \brief Create a new robot
     **/
    Robot();

    /**
     * \brief Create a new robot
     * \param _pos  position of the robot
     * \param _angle default angle of the robot
     * \param _speed default speed of the robot
     * \param _rotate default angle to rotate by in case of a detected
     *collision
     * \param _detect Maximum distance from the robot at which
     *collision is detected
     **/
    Robot(QPointF _pos, double _angle, double _speed, double _rotate,
          double _dist);

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
    qreal size() const;

    /**
     * \brief current angle of the robot
     * \return double angle (rad)
     **/
    qreal angle() const;

    /**
     * \brief Get the speed of the robot
     * \return double
     **/
    qreal speed() const;

    /**
     * \brief Get the angle an autonomous robot rotates by to avoid collision
     * \return double
     **/
    qreal rotateBy() const;

    /**
     * \brief Get the Detect Distance object
     * \return double
     **/
    qreal detectionDistance() const;

    /**
     * \brief Indicates default rotate direction
     * \return true Clockwise rotation
     * \return false Anticlockwise rotation
     **/
    bool clockwise() const;

    /**
     * \brief Set the size of the robot
     * \param _size
     **/
    void setSize(qreal _size);

    /**
     * \brief Sets the current angle of the robot
     * \param _dir
     **/
    void setAngle(qreal _dir);

    /**
     * \brief Set the speed of the robot
     * \param _speed
     **/
    void setSpeed(qreal _speed);

    /**
     * \brief Sets the angle a robot rotates by upon detection a collision
     * \param rotate_by
     **/
    void setRotateBy(qreal rotate_by);

    /**
     * \brief Sets max distance in front of a robot scanned for collisions
     * \param dist
     **/
    void setDetectionDistance(qreal dist);

    void setClockwise(bool c);

    /**
     * \brief paints the contents of an item in local coordinates
     * \param painter
     * \param option
     * \param widget
     **/
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /**
     * \brief The shape to draw in scene
     * \return QPainterPath
     **/
    QPainterPath shape() const override;

    /**
     * \brief bouding rectangle of the robot
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
     * \brief get the radius of the robot
     * \return qreal
     **/
    qreal radius() const;

    /**
     * \brief Convenience function equivalent to boundingRect.center()
     * \return QPointF
     **/
    QPointF center() const;

    /**
     * \brief A point on the left side of the center line (1Pi on the unit
     * circle)
     * \return QPointF
     **/
    QPointF leftBumper() const;

    /**
     * \brief A point on the right side of the center line (0 on Unit Circle)
     * \return QPointF
     **/
    QPointF rightBumper() const;

    /**
     * \brief Furthest point from the center where collisions are detected
     * \return QPointF
     **/
    QPointF detectionPoint() const;

    /**
     * \brief The area in front of the robot which scans for collisions
     * \return QRectF detection area
     **/
    QPolygonF detectionArea() const;

    /**
     * \brief rotate the robot based on its parameters
     *
     */
    void rotate();

    /**
     * \brief 
     * 
     * \return true 
     * \return false 
     */
    bool isOutOfBounds();

    QList<QGraphicsItem *> getItemsInDetectZone();

    void move();

    /**
     * \brief Called by GraphicsScene::advance slot; animates the object
     * \param phase advance is called twice, once with phase 0, indicating
     *items are about to advance, then with phase 1 to actually advance
     *them
     **/
    void advance(int phase) override;

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

class RobotPropertiesDialog
    : public QDialog
    , private Ui::PropertiesDialog
{
    Q_OBJECT

  public:
    RobotPropertiesDialog(Robot *r, QWidget *parent = 0);

  private slots:
    void on_buttonBox_accepted();

  private:
    Robot *m_robot;
};
