#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T08:47:52
#
#-------------------------------------------------

QT       -= core gui

INCLUDEPATH += ../include

CONFIG(debug, debug | release) {
    DESTDIR += ../../bin/debug
} else {
    DESTDIR += ../../bin/release
}
TARGET = kc_webapi_main
TEMPLATE = lib

DEFINES += KC_APACHE_MOD_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        activator.cpp \
        kc_webapi_work.cpp \
        request_respond.cpp

HEADERS += \
        activator.h \
        kc_apache_mod_global.h  \
        kc_webapi_work.h \
        request_respond.h \
        std.h

win32{
    INCLUDEPATH += D:/library/boost_1_72_vc
    LIBS += -LD:/library/boost_1_72_vc/lib32-msvc-14.0

    LIBS += -ldbghelp -lpsapi
    DEFINES += WIN32 WIN32_LEAN_AND_MEAN

    QMAKE_CXXFLAGS_EXCEPTIONS_ON = /EHa
    QMAKE_CXXFLAGS_STL_ON = /EHa
    DEF_FILE = activator.def
}
unix {
    target.path = /usr/lib
    INSTALLS += target
}
