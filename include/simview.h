/**
 * \file simview.h
 * \brief
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \date 2024-04-29
 **/

#pragma once

#include <QGraphicsView>
#include <QKeyEvent>

class SimView : public QGraphicsView
{
    Q_OBJECT
  public:
    SimView();
  public slots:
    void zoomIn();
    void zoomOut();

  protected:
    void keyPressEvent(QKeyEvent *event) override;
    void scaleView(qreal factor);

  private:
};
