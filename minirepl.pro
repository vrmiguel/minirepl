TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Sources/interp.cpp \
        Sources/main.cpp \
        Sources/os.cpp \
        Sources/token.cpp

HEADERS += \
    Headers/interp.h \
    Headers/os.h \
    Headers/token.h \
    Headers/tokentypes.h
