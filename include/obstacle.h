/**
 * \file obstacle.h
 * \brief Obstacle definitions
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \date 2024-04-26
 **/

#pragma once

#include <QGraphicsItem>
#include <QtCore>
#include <QPainter>


/**
 * \brief Stationary obstacle graphical item
 * \details Used as a wall for the simulation collision detection
 **/

#define DEF_OBSTACLE_SIZE 100.0
class Obstacle : public QGraphicsItem
{
private:
    double size;

public:
    Obstacle() : size(DEF_OBSTACLE_SIZE) {}
    Obstacle(QPointF _position);
    Obstacle(double _size) : size(_size) {}
    Obstacle(QJsonObject& json);
    ~Obstacle() {}
    double getSize() const { return size; }

    void setSize(double _size) { size = _size; }

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};
