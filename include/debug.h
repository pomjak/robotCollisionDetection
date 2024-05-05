/**
 * \file debug.h
 * \author Pomsar Jakub (xpomsa00@stud.fit.vutbr.cz)
 * \author Simon Cagala <xcagal00@stud.fit.vutbr.cz>
 * \brief debug functions
 * \version 0.1 \date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <QDebug>

/* Using Qt's debug function to print file, line number, and function */
#ifdef QT_DEBUG
#define DEBUG                                                                 \
    qDebug() << "[DEBUG]: " << __FILE__ << ": " << __LINE__ << ": "           \
             << __PRETTY_FUNCTION__ << ": "
#define INFO                                                                  \
    qDebug() << "[INFO]: " << __FILE__ << ": " << __LINE__ << ": "            \
             << __PRETTY_FUNCTION__ << ": "
#define WARN                                                                  \
    qDebug() << "[WARN]: " << __FILE__ << ": " << __LINE__ << ": "            \
             << __PRETTY_FUNCTION__ << ": "
#define ERROR                                                                 \
    qDebug() << "[ERROR]: " << __FILE__ << ": " << __LINE__ << ": "           \
             << __PRETTY_FUNCTION__ << ": "
#endif
