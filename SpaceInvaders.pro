TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle qt


TARGET = SpaceInvaders

linux:LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
win32:LIBS += \
    -LD:/Dev/SDL2-2.0.5/lib/x86 -lSDL2 \
    -LD:/Dev/SDL2_image-2.0.1/lib/x86 -lSDL2_image \
    -LD:/Dev/SDL2_ttf-2.0.14/lib/x86 -lSDL2_ttf \
    -LD:/Dev/SDL2_mixer-2.0.1/lib/x86 -lSDL2_mixer

win32:INCLUDEPATH += \
    D:/Dev/SDL2-2.0.5/include \
    D:/Dev/SDL2_image-2.0.1/include \
    D:/Dev/SDL2_ttf-2.0.14/include \
    D:/Dev/SDL2_mixer-2.0.1/include


copydata.commands = $(COPY_DIR) $$PWD/resources $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

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
    button.cpp \
    bullet.cpp

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
    button.h \
    bullet.h
