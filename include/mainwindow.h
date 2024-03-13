#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <memory>
#include "simulation.h"
#include "robot.h"
#include "obstacle.h"
#include "debug.h"


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

};
#endif // MAINWINDOW_H
