QT += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
versionAtLeast(QT_MAJOR_VERSION, 5.4): QT += openglwidgets

CONFIG += c++17
QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#LIBS += -lGLU


SOURCES += \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    ModelOperations.cc \
    ReadMethods.cc

HEADERS += \
    glwidget.h \
    mainwindow.h \
    headers/Controller.h \
    headers/Model.h \
    headers/Reader.h \
    headers/Scene.h \
    headers/State.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
