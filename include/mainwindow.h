#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <memory>
#include "simulation.h"
#include "robot.h"
#include "obstacle.h"
#include "debug.h"

#define SCENE_SIZE 800
#define VIEW_SIZE  424


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void updateRobotPosition(void);

private:
    Ui::MainWindow* ui;
    std::unique_ptr<Simulation> simulation;
    void setup();
    void addObstacle(double sizeValue, Position positionValue, unsigned int idValue);
    void addRobot(double sizeValue, Position positionValue, unsigned int idValue,robotAttributes attributesValues);
    

};
#endif // MAINWINDOW_H
