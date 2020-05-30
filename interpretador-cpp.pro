TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        interp.cpp \
        main.cpp \
        token.cpp

HEADERS += \
    interp.h \
    token.h \
    tokentypes.h
