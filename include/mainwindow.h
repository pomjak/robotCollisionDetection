#pragma once
#include <QMainWindow>
#include <QTimer>
#include <memory>
#include "json_handler.h"
#include "simulation.h"

#define SCENE_WIDTH 940
#define SCENE_HEIGHT 820

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
    void setup();
    void connect_buttons();

private:
    Ui::MainWindow* ui;
    Simulation* simulation;

};
