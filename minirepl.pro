TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Sources/_os.cpp \
        Sources/interp.cpp \
        Sources/main.cpp \
        Sources/token.cpp

HEADERS += \
    Headers/_os.h \
    Headers/interp.h \
    Headers/token.h \
    Headers/tokentypes.h \
    _os.h \
    interp.h \
    token.h \
    tokentypes.h
