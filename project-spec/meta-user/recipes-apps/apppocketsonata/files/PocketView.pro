QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Anal/SigAnal/cencdec.cpp \
    Collect/DataFile/DataFile.cpp \
    Utils/cfile.cpp \
    chexspinbox.cpp \
    mainView.cpp \
    mainwindow.cpp

HEADERS += \
    Anal/SigAnal/cencdec.h \
    Collect/DataFile/CRWRCommonVariables.h \
    Collect/DataFile/DataFile.h \
    chexspinbox.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    PocketView_ko_KR.ts

DEFINES += _SONATA_
DEFINES += _GUI_

QMAKE_LFLAGS += -no-pie


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_FILE = icon.rc


