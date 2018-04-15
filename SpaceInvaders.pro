TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle qt


TARGET = SpaceInvaders

linux:LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
win32:LIBS += -LD:/Dev/SDL2/lib/x86 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
win32:INCLUDEPATH += D:/Dev/SDL2/include

linux{
    copydata.commands = $(COPY_DIR) $$PWD/resources $$OUT_PWD
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

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
    bullet.cpp \
    utils.cpp

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
    bullet.h \
    gmath/Matrix3x3.hpp \
    gmath/Quaternion.hpp \
    gmath/Vector2.hpp \
    gmath/Vector3.hpp \
    utils.h
