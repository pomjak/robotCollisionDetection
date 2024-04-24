#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <memory>
#include "robot.h"

#define SCENE_SIZE 800
#define VIEW_SIZE 424

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

private slots:

private:
    Ui::MainWindow* ui;

};
#endif // MAINWINDOW_H
