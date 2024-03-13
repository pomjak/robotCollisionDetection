#pragma once

#include <QDebug>

// Using Qt's debug function to print file, line number, and function
#ifdef QT_DEBUG
#define DBG qDebug() << "DEBUG:" << __FILE__ << ":" << __LINE__ << ":" << __PRETTY_FUNCTION__ << ":"
#else
#define DBG if (false) qDebug()
#endif


