#pragma once

#include <QDebug>

// Using Qt's debug function to print file, line number, and function
#define DBG qDebug() << "DEBUG:" << __FILE__ << ":" << __LINE__ << ":" << __PRETTY_FUNCTION__ << ":"
