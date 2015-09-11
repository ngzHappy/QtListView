CONFIG += c++14
CONFIG(debug,debug|release){
CONFIG += console
}

QT     += core gui
QT     += widgets

TARGET = ListWidgetView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    AbstractItemWidgetView.cpp \
    AbstractItemWidgetDelegate.cpp

HEADERS  += mainwindow.h \
    AbstractItemWidget.hpp \
    AbstractItemWidgetView.hpp \
    AbstractItemWidgetDelegate.hpp \
    ItemWidgetView.hpp
