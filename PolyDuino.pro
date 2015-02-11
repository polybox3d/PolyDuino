#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T11:01:25
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PolyDuino
TEMPLATE = app

#INCLUDEPATH += "/usr/lib/avr/include/"
#INCLUDEPATH += "/usr/share/arduino/hardware/arduino/cores/arduino/"

INCLUDEPATH += Checker
INCLUDEPATH += Module

#UART Lib
include(./qextserialport/src/qextserialport.pri)

SOURCES += main.cpp\
        MainWindow.cpp \
    SerialPort.cpp \
    AbstractClient.cpp \
    Checker/SCannerChecker.cpp \
    Checker/PrinterChecker.cpp \
    Checker/GlobalChecker.cpp \
    Checker/CNCChecker.cpp \
    Checker/CheckerModele.cpp \
    Checker/AbstractChecker.cpp \
    Module/ScannerModule.cpp \
    Module/PrinterModule.cpp \
    Module/LabViewModule.cpp \
    Module/GlobalModule.cpp \
    Module/CNCModule.cpp \
    Module/AbstractModule.cpp \
    Face.cpp \
    Led.cpp \
    Temperature.cpp \
    Module/PolyboxModule.cpp \
    Config.cpp \
    ClosedLoopTimer.cpp

HEADERS  += MainWindow.h \
    SerialPort.h \
    AbstractClient.h \
    mcode.h \
    Checker/SCannerChecker.h \
    Checker/PrinterChecker.h \
    Checker/GlobalChecker.h \
    Checker/CNCChecker.h \
    Checker/CheckerModele.h \
    Checker/AbstractChecker.h \
    Module/ScannerModule.h \
    Module/PrinterModule.h \
    Module/LabViewModule.h \
    Module/GlobalModule.h \
    Module/CNCModule.h \
    Module/AbstractModule.h \
    Face.h \
    Led.h \
    Temperature.h \
    Module/PolyboxModule.h \
    Config.h \
    ClosedLoopTimer.h

FORMS    += MainWindow.ui \
    Checker/SCannerChecker.ui \
    Checker/PrinterChecker.ui \
    Checker/GlobalChecker.ui \
    Checker/CNCChecker.ui \
    Checker/CheckerModele.ui

RESOURCES += \
    ressources.qrc
