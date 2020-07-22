TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

win32{
    LIBS += -lmingw32
}

LIBS += -lSDL2main -lSDL2 -lSDL2_image
LIBS += -L"E:\Development\Libs\Cpp\lib"

INCLUDEPATH += "E:\Development\Libs\Cpp\include"
INCLUDEPATH += "E:\Development\Libs\Cpp\json"


SOURCES += \
        game.cpp \
        main.cpp \
        object.cpp \
        rectobject.cpp \
        spritemanager.cpp \
        spriteobject.cpp

HEADERS += \
    game.h \
    logger.h \
    object.h \
    rectobject.h \
    spritemanager.h \
    spriteobject.h
