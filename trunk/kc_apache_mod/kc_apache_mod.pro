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
TARGET = kc_apache_mod
TEMPLATE = lib

DEFINES += KC_APACHE_MOD_LIBRARY
#DEFINES += AP_HAVE_DESIGNATED_INITIALIZER

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
        apache_work.cpp \
        kc_apache_mod.cpp \
        request_respond.cpp

HEADERS += \
        apache_work.h \
        kc_apache_mod_global.h  \
        request_respond.h \
        std.h

win32{
    INCLUDEPATH += D:/library/boost_1_72_vc
    LIBS += -LD:/library/boost_1_72_vc/lib32-msvc-14.0

    INCLUDEPATH += ../library/windows/Apache2_2_x86/include
    LIBS += -l$$PWD/../library/windows/Apache2_2_x86/lib/libhttpd
    LIBS += -l$$PWD/../library/windows/Apache2_2_x86/lib/libapr-1

    QMAKE_CXXFLAGS_EXCEPTIONS_ON = /EHa
    QMAKE_CXXFLAGS_STL_ON = /EHa
    DEF_FILE = kc_apache_mod.def
}
unix {
    target.path = /usr/lib
    INSTALLS += target

    INCLUDEPATH += ../library/linux/Apache2_2/include
}
