#pragma once

#include <QDebug>

// Using Qt's debug function to print file, line number, and function
#ifdef QT_DEBUG
#define DEBUG qDebug() << "[DEBUG]: " << __FILE__ << ": " << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": "
#define INFO qDebug() << "[INFO]: " << __FILE__ << ": " << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": "
#define WARN qDebug() << "[WARN]: " << __FILE__ << ": " << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": "
#define ERROR qDebug() << "[ERROR]: " << __FILE__ << ": " << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": "
#endif


