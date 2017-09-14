TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = SpaceInvaders

LIBS += \
    -LD:/Dev/SDL2-2.0.5/lib/x86 -lSDL2 \
    -LD:/Dev/SDL2_image-2.0.1/lib/x86 -lSDL2_image \
    -LD:/Dev/SDL2_ttf-2.0.14/lib/x86 -lSDL2_ttf \
    -LD:/Dev/SDL2_mixer-2.0.1/lib/x86 -lSDL2_mixer

INCLUDEPATH += \
    D:/Dev/SDL2-2.0.5/include \
    D:/Dev/SDL2_image-2.0.1/include \
    D:/Dev/SDL2_ttf-2.0.14/include \
    D:/Dev/SDL2_mixer-2.0.1/include


resources.path = $$OUT_PWD/resources
resources.files = resources/*

INSTALLS += \
    resources

SOURCES += main.cpp \
    ltexture.cpp \
    game.cpp \
    graphics.cpp \
    input.cpp \
    sprite.cpp \
    entity.cpp \
    gameobject.cpp \
    player.cpp \
    timer.cpp \
    button.cpp \
    gamestate.cpp

HEADERS += \
    ltexture.h \
    game.h \
    graphics.h \
    input.h \
    sprite.h \
    globals.h \
    entity.h \
    gameobject.h \
    player.h \
    timer.h \
    button.h \
    gamestate.h
