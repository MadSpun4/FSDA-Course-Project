QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = CourseProject
TEMPLATE = app

SOURCES += main.cpp \
    Tree/Node.cpp \
    Tree/Tree.cpp \
    Fields/Data.cpp \
    HashTable/HashTable.cpp \
    HashTable/Key.cpp \
    Element.cpp \
    mainwindow.cpp

HEADERS += Tree/Node.h \
    Tree/Tree.h \
    Fields/Date.h \
    HashTable/HashTable.h \
    HashTable/Key.h \
    Element.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    inputHuge.txt \
    output.txt \
    input.txt
