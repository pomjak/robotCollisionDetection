
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt c++17 warn_on debug build_all lm

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \ 
    obstacle.cpp \
    robot.cpp \
    object.cpp \
    simulation.cpp \
    position.cpp

HEADERS += \
    mainwindow.h \
    object.h \
    obstacle.h \
    robot.h \
    simulation.h \
    position.h

FORMS += \
    mainwindow.ui

CONFIG(debug, debug|release) {
    TARGET = icp24_debug
} else {
    TARGET = icp24
}
