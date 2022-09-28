TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        enterName.cpp \
        game.cpp \
        gameRules.cpp \
        main.cpp \
        mainMenu.cpp \
        showRecords.cpp

HEADERS += \
    button.h \
    entity.h \
    hitBox.h \
    main.h \
    mushroom.h \
    personage.h \
    player.h \
    staticPictures.h \
    text.h

INCLUDEPATH += C:\Users\vasil\Documents\SDL2-devel-2.0.14-mingw\x86_64-w64-mingw32\include
LIBS += -L C:\Users\vasil\Documents\SDL2-devel-2.0.14-mingw\x86_64-w64-mingw32\lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

