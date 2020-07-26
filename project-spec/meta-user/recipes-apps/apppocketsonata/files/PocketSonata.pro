TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Collect/ccollectbank/ccollectbank.cpp \
        MinIni/minIni.c \
        NetMem/client/ClientMemoryPage.cpp \
        NetMem/client/NetworkMemory.cpp \
        NetMem/server/ClientSocket.cpp \
        NetMem/server/MemoryPage.cpp \
        NetMem/server/ServerSocket.cpp \
        NetMem/utils/ApiNetMem.cpp \
        System/csysconfig.cpp \
        Thread/cdetectanalysis.cpp \
        Thread/cjamtech.cpp \
        Thread/cprompt.cpp \
        Thread/cpulsetrk.cpp \
        Thread/csignalcollect.cpp \
        Thread/ctaskmngr.cpp \
        Thread/curbit.cpp \
        Thread/creclan.cpp \
        Utils/clog.cpp \
        Utils/cmultiserver.cpp \
        Utils/csingleserver.cpp \
        Utils/cthread.cpp \
        Utils/cgpio.cpp \
        cmain.cpp

HEADERS += \
    Collect/ccollectbank/ccollectbank.h \
    Include/defines.h \
    Include/global.h \
    Include/struct.h \
    Include/sysmsg.h \
    Include/system.h \
    Include/thrmsg.h \
    MinIni/minGlue-FatFs.h \
    MinIni/minGlue-ccs.h \
    MinIni/minGlue-efsl.h \
    MinIni/minGlue-ffs.h \
    MinIni/minGlue-mdd.h \
    MinIni/minGlue-stdio.h \
    MinIni/minGlue.h \
    MinIni/minIni.h \
    MinIni/wxMinIni.h \
    NetMem/ClientSocket.h \
    NetMem/MemoryPage.h \
    NetMem/ServerSocket.h \
    NetMem/client/ClientMemoryPage.h \
    NetMem/client/NetworkMemory.h \
    NetMem/server/ClientSocket.h \
    NetMem/server/MemoryPage.h \
    NetMem/server/ServerSocket.h \
    NetMem/utils/ApiNetMem.h \
    NetMem/utils/PortableSocket.h \
    System/csysconfig.h \
    Thread/ccollectbank/ccollectbank.h \
    Thread/cdetectanalysis.h \
    Thread/cjamtech.h \
    Thread/cprompt.h \
    Thread/cpulsetrk.h \
    Thread/creclan.h \
    Thread/csignalcollect.h \
    Thread/ctaskmngr.h \
    Thread/curbit.h \
    Utils/cgpio.h \
    Utils/clog.h \
    Utils/cmultiserver.h \
    Utils/cqueue.h \
    Utils/csingleserver.h \
    Utils/cthread.h \
    _sysmsg.h \
    _system.h \
    cjamtech.h \
    clog.h \
    cmain.h \
    cprompt.h \
    cpulsetrk.h \
    creclan.h \
    csignalcollect.h \
    ctaskmngr.h \
    curbit.h \
    mysocket.h \
    tcpip.h

QMAKE_CXXFLAGS += -std=c++0x

LIBS += -L/usr/local/lib
LIBS += -pthread
LIBS += -lreadline
LIBS += -lboost_thread

INCLUDEPATH += /usr/local/boost

DISTFILES += \
    NetMem/CMakeLists.txt \
    NetMem/client/CMakeLists.txt \
    NetMem/server/CMakeLists.txt \
    NetMem/utils/CMakeLists.txt
