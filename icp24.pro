
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt c++17 warn_on debug build_all

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    robot.cpp \
    obstacle.cpp \
    simulation.cpp \
    json_handler.cpp

HEADERS += \
    mainwindow.h \
    debug.h \
    robot.h \
    obstacle.h \
    simulation.h \
    json_handler.h


FORMS += \
    mainwindow.ui \
    obstacle-properties-dialog.ui \
    robot-properties-dialog.ui

CONFIG(debug, debug|release) {
    TARGET = icp24_debug
} else {
    TARGET = icp24
}
