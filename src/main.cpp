/**
 * \file main.cpp
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \version 0.1
 * \date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow   w;
    w.show();
    return a.exec();
}
