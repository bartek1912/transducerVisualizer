#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T19:56:20
#
#-------------------------------------------------

QT       += gui core widgets

TARGET = TransducerLogic
TEMPLATE = lib
CONFIG += dynamiclib


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += FSM/state.cpp \
    FSM/states.cpp \
    Transducer/transducerefactory.cpp \
    Transducer/discreteoutfunction.cpp \
    FSM/transitionfunction.cpp \
    FSM/fsm.cpp \
    Transducer/transducer.cpp \
    JSON/jsonfactory.cpp \
    JSON/jsonlist.cpp \
    JSON/jsonobject.cpp \
    JSON/jsonelement.cpp \
    JSON/jsonstring.cpp \
    fsmwidget.cpp \
    node.cpp \
    edge.cpp \
    applicationwindow.cpp \
    mainwindow.cpp \
    FSM/discretetransitionfunction.cpp \
    Transducer/outfunction.cpp \
    transducercontrolwidget.cpp \
    FSM/discretetransitionfunctionwithstack.cpp \
    stackwidget.cpp \
    verticallabel.cpp

HEADERS += FSM/transducerlogic_global.h\
        FSM/fsm.h \
        Transducer/transducer.h \
        Transducer/outfunction.h \
        FSM/transitionfunction.h \
        FSM/state.h \
        FSM/states.h \
        Transducer/transducerfactory.h \
        FSM/discretetransitionfunction.h \
        Transducer/discreteoutfunction.h \
        JSON/jsonfactory.h \
        JSON/jsonlist.h \
        JSON/jsonobject.h \
        JSON/jsonelement.h \
        JSON/jsonstring.h \
    fsmwidget.h \
    node.h \
    edge.h \
    applicationwindow.h \
    mainwindow.h \
    transducercontrolwidget.h \
    FSM/discretetransitionfunctionwithstack.h \
    stackwidget.h \
    verticallabel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
