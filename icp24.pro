
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 debug_and_release build_all

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    object.h \
    obstacle.h \
    robot.h \
    simulation.h 

FORMS += \
    mainwindow.ui

CONFIG(debug, debug|release) {
    TARGET = icp24_debug
} else {
    TARGET = icp24
}
