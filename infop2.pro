#-------------------------------------------------
#
# Project created by QtCreator 2012-04-09T21:51:19
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = infop2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    city.cpp \
    block.cpp \
    buffers.cpp \
    glew.c \
    shaders.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    block.h \
    city.h \
    element.h \
    zone.h \
    list.h \
    mathFunctions.h \
    zone.h \
    shaders.h \
    buffers.h \
    glm.hpp \
    GL/wglew.h \
    GL/glxew.h \
    GL/glew.h

FORMS    += mainwindow.ui
