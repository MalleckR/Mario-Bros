TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        fonteluz.cpp \
        inimigos.cpp \
        main.cpp \
        mario.cpp \
        plataforma.cpp

QT   += core gui opengl
LIBS += -lopengl32 -lfreeglut -lglu32

HEADERS += \
    fonteluz.h \
    inimigos.h \
    mario.h \
    plataforma.h

