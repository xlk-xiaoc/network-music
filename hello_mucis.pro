#-------------------------------------------------
#
# Project created by QtCreator 2020-07-07T14:05:30
#
#-------------------------------------------------

QT       += core gui network multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hello_mucis
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    login.cpp \
    sql.cpp

HEADERS += \
        widget.h \
    login.h \
    sql.h

FORMS += \
        widget.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ui_sgin.qrc

DISTFILES += \
    my-images/close.png \
    my-images/closew.png \
    my-images/danqu.png \
    my-images/heart00.png \
    my-images/heart01.png \
    my-images/ico.png \
    my-images/last.png \
    my-images/last1.png \
    my-images/logo.png \
    my-images/min.png \
    my-images/min1.png \
    my-images/minw.png \
    my-images/mode.png \
    my-images/next.png \
    my-images/next1.png \
    my-images/nosound_dark.png \
    my-images/nosound_light.png \
    my-images/picstyle.png \
    my-images/picstyle2.png \
    my-images/play1.png \
    my-images/play2.png \
    my-images/play3.png \
    my-images/play4.png \
    my-images/play5.png \
    my-images/progress_thume.png \
    my-images/shunxu.png \
    my-images/sound.png \
    my-images/suiji.png \
    my-images/traylast.png \
    my-images/traynext.png \
    my-images/trayplay1.png \
    my-images/trayplay2.png \
    my-images/traysound1.png \
    my-images/traysound2.png \
    my-images/traysoundless.png \
    my-images/图标.png \
    my-images/图标2.png \
    my-images/close.png \
    my-images/closew.png \
    my-images/danqu.png \
    my-images/heart00.png \
    my-images/heart01.png \
    my-images/ico.png \
    my-images/last.png \
    my-images/last1.png \
    my-images/logo.png \
    my-images/min.png \
    my-images/min1.png \
    my-images/minw.png \
    my-images/mode.png \
    my-images/next.png \
    my-images/next1.png \
    my-images/nosound_dark.png \
    my-images/nosound_light.png \
    my-images/picstyle.png \
    my-images/picstyle2.png \
    my-images/play1.png \
    my-images/play2.png \
    my-images/play3.png \
    my-images/play4.png \
    my-images/play5.png \
    my-images/progress_thume.png \
    my-images/shunxu.png \
    my-images/sound.png \
    my-images/suiji.png \
    my-images/traylast.png \
    my-images/traynext.png \
    my-images/trayplay1.png \
    my-images/trayplay2.png \
    my-images/traysound1.png \
    my-images/traysound2.png \
    my-images/traysoundless.png \
    my-images/图标.png \
    my-images/图标2.png
