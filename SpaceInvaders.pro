TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = SpaceInvaders

LIBS += \
    -LC:/Dev/SDL2-2.0.5/lib/x86 -lSDL2 \
    -LC:/Dev/SDL2_image-2.0.1/lib/x86 -lSDL2_image \
    -LC:/Dev/SDL2_ttf-2.0.14/lib/x86 -lSDL2_ttf \
    -LC:/Dev/SDL2_mixer-2.0.1/lib/x86 -lSDL2_mixer

INCLUDEPATH += \
    C:/Dev/SDL2-2.0.5/include \
    C:/Dev/SDL2_image-2.0.1/include \
    C:/Dev/SDL2_ttf-2.0.14/include \
    C:/Dev/SDL2_mixer-2.0.1/include


resources.path = $$OUT_PWD/resources
resources.files = resources/*

INSTALLS += \
    resources

SOURCES += main.cpp \
    game.cpp \
    graphics.cpp \
    input.cpp \
    sprite.cpp \
    entity.cpp \
    gameobject.cpp \
    player.cpp \
    timer.cpp \
    gamestate.cpp \
    menustate.cpp \
    playstate.cpp \
    pausestate.cpp \
    button.cpp

HEADERS += \
    game.h \
    graphics.h \
    input.h \
    sprite.h \
    globals.h \
    entity.h \
    gameobject.h \
    player.h \
    timer.h \
    gamestate.h \
    menustate.h \
    playstate.h \
    pausestate.h \
    button.h
