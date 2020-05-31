TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        _os.cpp \
        interp.cpp \
        main.cpp \
        token.cpp

HEADERS += \
    _os.h \
    interp.h \
    token.h \
    tokentypes.h
