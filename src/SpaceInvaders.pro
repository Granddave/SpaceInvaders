TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle qt


TARGET = SpaceInvaders

linux:LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
win32:LIBS += -LD:/Dev/SDL2/lib/x86 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
win32:INCLUDEPATH += D:/Dev/SDL2/include

linux{
    copydata.commands = $(COPY_DIR) $$PWD/res $$OUT_PWD
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

HEADERS += \
    entities/bullet.h \
    entities/entity.h \
    entities/gameobject.h \
    entities/player.h \
    entities/enemy.h \
    gmath/Matrix3x3.hpp \
    gmath/Quaternion.hpp \
    gmath/Vector2.hpp \
    gmath/Vector3.hpp \
    graphics/button.h \
    graphics/graphics.h \
    graphics/sprite.h \
    graphics/texturemanager.h \
    states/gamestate.h \
    states/menustate.h \
    states/pausestate.h \
    states/playstate.h \
    utils/globals.h \
    utils/input.h \
    utils/timer.h \
    utils/utils.h \
    game.h

SOURCES += \
    entities/bullet.cpp \
    entities/entity.cpp \
    entities/gameobject.cpp \
    entities/player.cpp \
    entities/enemy.cpp \
    graphics/button.cpp \
    graphics/graphics.cpp \
    graphics/sprite.cpp \
    graphics/texturemanager.cpp \
    states/menustate.cpp \
    states/pausestate.cpp \
    states/playstate.cpp \
    utils/input.cpp \
    utils/timer.cpp \
    utils/utils.cpp \
    game.cpp \
    main.cpp



