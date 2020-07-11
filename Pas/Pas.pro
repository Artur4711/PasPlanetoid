TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Asteroida.cpp \
        Boss.cpp \
        Obiekt.cpp \
        Powerup.cpp \
        Rakieta.cpp \
        Statek.cpp \
        main.cpp

INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    Asteroida.h \
    Boss.h \
    Obiekt.h \
    Powerup.h \
    Rakieta.h \
    Statek.h
