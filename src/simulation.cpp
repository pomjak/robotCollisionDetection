/**
 * \file simulation.cpp
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \version 0.1
 * \date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "simulation.h"
#include <QFileDialog>

using std::shared_ptr, std::make_shared;

Simulation::Simulation(QWidget *parent)
    : QGraphicsView(parent)
    , json(robotList(), obstacleList())
    , m_state{State::STOPPED}
{
    QGraphicsScene *newscene = new QGraphicsScene(this);
    newscene->setSceneRect(QRectF(QPointF(0, 0), QPointF(1920, 1080)));
    DEBUG << sceneRect();
    setTransformationAnchor(AnchorUnderMouse);
    setScene(newscene);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    setMaximumWidth(1920);
    setMinimumWidth(800);
    setMaximumHeight(1080);
    setMinimumHeight(600);
}

QList<Robot *>    *Simulation::robotList() { return &m_robot_list; }
QList<Obstacle *> *Simulation::obstacleList() { return &m_obstacle_list; }

void Simulation::addRobot(Robot *robot)
{
    m_robot_list.push_back(robot);
    scene()->addItem(robot);
}

void Simulation::addObstacle(Obstacle *obstacle)
{
    m_obstacle_list.push_back(obstacle);
    scene()->addItem(obstacle);
}

void Simulation::printLists()
{
    for ( const auto &obs : m_obstacle_list )
    {
        DEBUG << obs->pos().x() << obs->pos().y();
        DEBUG << obs->getHeight();
        DEBUG << obs->getWidth();
    }

    for ( const auto &rob : m_robot_list )
    {
        DEBUG << rob->rotation();
        DEBUG << rob->pos().x() << rob->pos().y();
        DEBUG << rob->rotateBy();
        DEBUG << rob->size();
        DEBUG << rob->speed();
    }
}

State Simulation::getState() const { return m_state; }

void Simulation::setState(State _state) { m_state = _state; }

void Simulation::spawnObject(ObjectType type)
{
    QSizeF objectSize;

    if ( type == ObjectType::ROBOT )
    {
        objectSize = {DEF_ROBOT_SIZE, DEF_ROBOT_SIZE};
    }

    else if ( type == ObjectType::OBSTACLE )
    {
        objectSize = {QRandomGenerator::global()->bounded(20, MAX_OBS_SIZE),
                      QRandomGenerator::global()->bounded(20, MAX_OBS_SIZE)};
    }

    QPointF spawnPoint;
    do {
        spawnPoint = {QRandomGenerator::global()->bounded(SCENE_WIDTH),
                      QRandomGenerator::global()->bounded(SCENE_HEIGHT / 2)};

        QRectF spawnArea(spawnPoint, objectSize);
        QRectF sceneSpawnArea = spawnArea.translated(spawnPoint);

        /* Check if there are any items at the spawn point */
        QList<QGraphicsItem *> itemsAtSpawnPoint =
            scene()->items(sceneSpawnArea, Qt::IntersectsItemShape);

        /* If there are no items at the spawn point, exit the loop */
        if ( itemsAtSpawnPoint.isEmpty() ) break;
    }
    while ( true );

    if ( type == ObjectType::ROBOT )
    {
        double angle    = QRandomGenerator::global()->bounded(MAX_ROTATE_BY);
        double speed    = QRandomGenerator::global()->bounded(MAX_SPEED);
        double rotateBy = QRandomGenerator::global()->bounded(MAX_ROTATE_BY);
        double dist     = QRandomGenerator::global()->bounded(MAX_DETECT_DIST);

        Robot *robot = new Robot(spawnPoint, angle, speed, rotateBy, dist);
        addRobot(robot);

        INFO << "ROBOT SPAWNED at" << spawnPoint;
    }
    else if ( type == ObjectType::OBSTACLE )
    {
        Obstacle *obstacle = new Obstacle(spawnPoint, objectSize);

        addObstacle(obstacle);

        INFO << "OBSTACLE SPAWNED at" << spawnPoint << "size:" << objectSize;
    }
}

void Simulation::loadLevelLayout()
{
    QString fname =
        QFileDialog::getOpenFileName(nullptr, tr("Open existing layout"), "",
                                     tr("Json File (*.json);;All Files(*)"));
    if ( fname.isEmpty() )
    {
        WARN << "filename empty";
        return;
    }
    else
    {
        scene()->clear();
        m_robot_list.clear();
        m_obstacle_list.clear();
        json.load(fname);
        int i = 0;
        for ( auto &obj : m_robot_list )
        {
            DEBUG << "Adding robot #" << ++i;
            scene()->addItem(obj);
        }
        i = 0;
        for ( auto &obj : m_obstacle_list )
        {
            DEBUG << "Adding obstacle #" << ++i;
            scene()->addItem(obj);
        }
    }
}

void Simulation::saveLevelLayout()
{
    QString fname =
        QFileDialog::getSaveFileName(nullptr, tr("Save current layout"), "",
                                     tr("Json File (*.json);;All Files(*)"));
    if ( fname.isEmpty() )
        return;
    else { json.save(fname); }
}

void Simulation::spawnRobot() { spawnObject(ObjectType::ROBOT); }

void Simulation::spawnObstacle() { spawnObject(ObjectType::OBSTACLE); }

void Simulation::deleteRobot() { deleteObject(ObjectType::ROBOT); }

void Simulation::deleteObstacle() { deleteObject(ObjectType::OBSTACLE); }

void Simulation::purgeScene()
{
    scene()->clear();
    m_robot_list.clear();
    m_obstacle_list.clear();
}

void Simulation::zoomIn() { scaleView(qreal(1.1)); }

void Simulation::zoomOut() { scaleView(1 / qreal(1.1)); }

void Simulation::scaleView(qreal scale_factor)
{
    qreal factor = transform()
                       .scale(scale_factor, scale_factor)
                       .mapRect(QRectF(0, 0, 1, 1))
                       .width();
    if ( factor < 0.07 || factor > 100 ) return;

    scale(scale_factor, scale_factor);
}
void Simulation::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key() )
    {
        case Qt::Key_Plus :  zoomIn(); break;
        case Qt::Key_Minus : zoomOut(); break;
        default :            QGraphicsView::keyPressEvent(event);
    }
}

void Simulation::drawBackground(QPainter *painter, const QRectF &rect)
{
    // scene rectangle
    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);

    // painter->fillRect(rect, Qt::darkGray);
    QRectF sr = scene()->sceneRect();
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

void Simulation::deleteObject(ObjectType type)
{
    QList<QGraphicsItem *>                items = scene()->selectedItems();
    QMutableListIterator<QGraphicsItem *> it(items);
    if ( type == ObjectType::ROBOT )
    {
        while ( it.hasNext() )
        {
            Robot *robot = dynamic_cast<Robot *>(it.next());
            if ( robot )
            {
                delete robot;
                it.remove();
            }
        }
    }
    else if ( type == ObjectType::OBSTACLE )
    {
        while ( it.hasNext() )
        {
            Obstacle *obs = dynamic_cast<Obstacle *>(it.next());
            if ( obs )
            {
                delete obs;
                it.remove();
            }
        }
    }
    qDeleteAll(items);
}
