#include "simview.h"

SimView::SimView(QWidget *parent)
    : QGraphicsView(parent)
{
    setTransformationAnchor(AnchorUnderMouse);
}

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

void SimView::zoomIn() { scaleView(qreal(1.1)); }

void SimView::zoomOut() { scaleView(1 / qreal(1.1)); }

void SimView::drawBackground(QPainter *painter, const QRectF &rect)
{
    // scene rectangle
    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);

    // painter->fillRect(rect, Qt::darkGray);
    QRectF sr = this->sceneRect();

    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sr);
    QRectF  msgRect(sr.left() + 785, sr.top() + 390, 350, 150);
    QString message = {tr("Ctrl+O - load a new layout\n"
                          "Ctrl+S - save current layout\n"
                          "Ctrl+L - clear screen\n"
                          "Ctrl+N - spawn a new robot\n"
                          "Ctrl+M - spawn a new obstacle\n"
                          "Space  - Play / Pause\n"
                          "'+/-'  - zoom in/out\n")};

    painter->setBrush(Qt::darkGreen);
    painter->setPen(Qt::black);
    painter->drawText(msgRect, message);
}
