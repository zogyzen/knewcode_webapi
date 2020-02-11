#-------------------------------------------------
#
# Project created by QtCreator 2017-07-30T17:48:50
#
#-------------------------------------------------

QT       -= core gui

INCLUDEPATH += ../include
LIBS += -static-libstdc++

DEFINES  -= UNICODE
#CONFIG += -m32
CONFIG += c++11

CONFIG(debug, debug | release) {
    DESTDIR += ../../bin/debug
} else {
    DESTDIR += ../../bin/release
}
TARGET = kc_framework
TEMPLATE = lib

DEFINES += KC_FRAMEWORK_LIBRARY

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
    bundle.cpp \
    bundle_context.cpp \
    framework.cpp \
    kc_framework.cpp \
    kc_lock_work.cpp \
    kc_log_thread.cpp \
    kc_signo_catch.cpp \
    service_reference.cpp \
    service_registration.cpp

HEADERS += \
    bundle.h \
    bundle_context.h \
    framework.h \
    kc_lock_work.h \
    kc_log_thread.h \
    kc_signo_catch.h \
    service_reference.h \
    service_registration.h \
    std.h

win32{
    INCLUDEPATH += D:/library/boost_1_72_vc
    LIBS += -LD:/library/boost_1_72_vc/lib32-msvc-14.0

    LIBS += -ldbghelp -lpsapi
    DEFINES += WIN32 WIN32_LEAN_AND_MEAN

    QMAKE_CXXFLAGS_EXCEPTIONS_ON = /EHa
    QMAKE_CXXFLAGS_STL_ON = /EHa
    DEF_FILE = kc_framework.def

    varCopyConfig = \"$$PWD/../config.xml\" \"$$OUT_PWD/$$DESTDIR\"
    varCopyConfig ~= s,/,\\,g
    varCopyHintFile = \"$$PWD/../hint_file\" \"$$OUT_PWD/$$DESTDIR/hint_file\"
    varCopyHintFile ~= s,/,\\,g
    #copyCmd.depends = first
    #copyCmd.commands = $$QMAKE_COPY $$varCopyCmdPath
    QMAKE_POST_LINK += $$QMAKE_COPY $$varCopyConfig $$escape_expand(\\n\\t)
    QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$varCopyHintFile
    #message($$QMAKE_POST_LINK)
    export(QMAKE_POST_LINK)
}
unix {
    target.path = /usr/lib
    INSTALLS += target
    #QMAKE_CXXFLAGS += -m32
}
