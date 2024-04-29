#include "simview.h"

SimView::SimView()
    : QGraphicsView()
{}

void SimView::scaleView(qreal scale_factor)
{
    qreal factor = transform()
                       .scale(scale_factor, scale_factor)
                       .mapRect(QRectF(0, 0, 1, 1))
                       .width();
    if ( factor < 0.07 || factor > 100 ) return;

    scale(scale_factor, scale_factor);
}

void SimView::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key() )
    {

        case Qt::Key_Plus :  zoomIn(); break;
        case Qt::Key_Minus : zoomOut(); break;
        default :            QGraphicsView::keyPressEvent(event);
    }
}

void SimView::zoomIn() { scaleView(qreal(1.2)); }

void SimView::zoomOut() { scaleView(1 / qreal(1.2)); }
