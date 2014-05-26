#-------------------------------------------------
#
# Project created by QtCreator 2014-04-17T12:25:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FKOM
TEMPLATE = app


SOURCES += main.cpp\
    eventqueue.cpp \
    packetgenerator.cpp \
    event.cpp \
    packetqueue.cpp \
    service.cpp \
    worker.cpp \
    simulation.cpp \
    packet.cpp \
    distributedsimulation.cpp \
    statisticsaggregate.cpp \
    statisticsagent.cpp \
    erlangc.cpp \
    erlangb.cpp \
    scheduling.cpp \
    statisticseventgenerator.cpp

HEADERS  += \
    eventqueue.h \
    packetgenerator.h \
    event.h \
    packetqueue.h \
    service.h \
    worker.h \
    simulation.h \
    packet.h \
    distributedsimulation.h \
    statisticsaggregate.h \
    statisticsagent.h \
    erlangc.h \
    erlangb.h \
    statisticseventgenerator.h

FORMS    += mainwindow.ui


QMAKE_CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++11 -O3 -flto -march=native
