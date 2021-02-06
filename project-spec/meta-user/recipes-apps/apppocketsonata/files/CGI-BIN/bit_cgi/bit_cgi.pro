QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

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
    ../../Thread/ccgi.cpp \
    ../../Thread/curbit.cpp \
    ../../Utils/DMA/dma.cpp \
    ../../Utils/carraymsgdata.cpp \
    ../../Utils/cgpio.cpp \
    ../../Utils/chwio.cpp \
    ../../Utils/clog.cpp \
    ../../Utils/cthread.cpp \
    ../Qdecoder/md5/md5c.c \
    ../Qdecoder/mkstemp.c \
    ../Qdecoder/qArg.c \
    ../Qdecoder/qAwk.c \
    ../Qdecoder/qCount.c \
    ../Qdecoder/qDecoder.c \
    ../Qdecoder/qDownload.c \
    ../Qdecoder/qEncode.c \
    ../Qdecoder/qEnv.c \
    ../Qdecoder/qError.c \
    ../Qdecoder/qFile.c \
    ../Qdecoder/qHttpHeader.c \
    ../Qdecoder/qInternalCommon.c \
    ../Qdecoder/qInternalEntry.c \
    ../Qdecoder/qMisc.c \
    ../Qdecoder/qSed.c \
    ../Qdecoder/qSession.c \
    ../Qdecoder/qString.c \
    ../Qdecoder/qTime.c \
    ../Qdecoder/qValid.c \
    ../Qdecoder/qfDecoder.c \
    ../Qdecoder/qsDecoder.c \
    ../Qdecoder/snprintf.c \
    ../Qdecoder/strcasecmp.c \
    ../Qdecoder/strptime.c \
    ../Qdecoder/timegm.c \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DEFINES += _POCKETSONATA_
DEFINES += _CGI_

HEADERS += \
    ../../../Thread/curbit.h \
    ../../../Utils/carraymsgdata.h \
    ../../../Utils/ccommonutils.h \
    ../../../Utils/cgpio.h \
    ../../../Utils/clog.h \
    ../../../Utils/cthread.h \
    ../../Utils/DMA/dma.h \
    ../../Utils/chwio.h \
    ../../Utils/cthread.h \
    ../Qdecoder/internal.h \
    ../Qdecoder/md5/md5.h \
    ../Qdecoder/md5/md5_global.h \
    ../Qdecoder/mkstemp.h \
    ../Qdecoder/qDecoder.h \
    ../Qdecoder/qInternal.h \
    ../Qdecoder/qdecoder.h \
    ../Qdecoder/snprintf.h \
    ../Qdecoder/strcasecmp.h \
    ../Qdecoder/strptime.h \
    ../Qdecoder/timegm.h
