#pragma once 

#include <QDebug>
// using QT's debug function to print file, line num and function also
#define DBG (qDebug()<<__FILE__<<":"<<__LINE__<<":"<<__PRETTY_FUNCTION__<<":")