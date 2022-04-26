QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += HAVE_CONFIG_H
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=\
    main.cpp \
    mainwindow.cpp \
    mysocket.cpp \
    protocol.cpp \
    qrencode-4.1.0/bitstream.c \
    qrencode-4.1.0/mask.c \
    qrencode-4.1.0/mmask.c \
    qrencode-4.1.0/mqrspec.c \
    qrencode-4.1.0/qrenc.c \
    qrencode-4.1.0/qrencode.c \
    qrencode-4.1.0/qrinput.c \
    qrencode-4.1.0/qrspec.c \
    qrencode-4.1.0/rsecc.c \
    qrencode-4.1.0/split.c






HEADERS +=\
    mainwindow.h \
    mysocket.h \
    protocol.h \
    qrencode-4.1.0/bitstream.h \
    qrencode-4.1.0/config.h \
    qrencode-4.1.0/mask.h \
    qrencode-4.1.0/mmask.h \
    qrencode-4.1.0/mqrspec.h \
    qrencode-4.1.0/qrencode.h \
    qrencode-4.1.0/qrencode_inner.h \
    qrencode-4.1.0/qrinput.h \
    qrencode-4.1.0/qrspec.h \
    qrencode-4.1.0/rsecc.h \
    qrencode-4.1.0/split.h



FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qrencode-3.4.4/config.h \
    state_machine_client.pro.user
