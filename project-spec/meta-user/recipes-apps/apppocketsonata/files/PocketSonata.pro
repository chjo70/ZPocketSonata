TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Anal/EmitterMerge/CInverseMethod.cpp \
        Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.cpp \
        Anal/EmitterMerge/ELEmitterMergeMngr.cpp \
        Anal/EmitterMerge/ELEnvironVariableMngr.cpp \
        Anal/EmitterMerge/ELThreat.cpp \
        Anal/EmitterMerge/GeoCoordConv.cpp \
        Anal/EmitterMerge/LOBClustering.cpp \
        Anal/EmitterMerge/Matrix/Matrix.cpp \
        Anal/EmitterMerge/PositionEstimationAlg.cpp \
        Anal/EmitterMerge/Quadratic/Quadratic.cpp \
        Anal/EmitterMerge/UTM.cpp \
        Anal/Identify/ELUtil.cpp \
        Anal/Identify/Identify.cpp \
        Anal/NewSigAnal/NAnalPRI.cpp \
        Anal/NewSigAnal/NGroup.cpp \
        Anal/NewSigAnal/NMakeAET.cpp \
        Anal/NewSigAnal/NPulExt.cpp \
        Anal/NewSigAnal/NewSigAnal.cpp \
        Anal/ParamMngr.cpp \
        Anal/SigAnal/AnalPRI.cpp \
        Anal/SigAnal/Group.cpp \
        Anal/SigAnal/MakeAET.cpp \
        Anal/SigAnal/PulExt.cpp \
        Anal/SigAnal/SysPara.cpp \
        Anal/SigAnal/stdafx.cpp \
        Collect/DataFile/DataFile.cpp \
        Collect/ccollectbank/ccollectbank.cpp \
        MinIni/minIni.cpp \
        NetMem/client/ClientMemoryPage.cpp \
        NetMem/client/NetworkMemory.cpp \
        NetMem/server/ClientSocket.cpp \
        NetMem/server/MemoryPage.cpp \
        NetMem/server/ServerSocket.cpp \
        NetMem/utils/ApiNetMem.cpp \
        SQLite/Backup.cpp \
        SQLite/Column.cpp \
        SQLite/Database.cpp \
        SQLite/Exception.cpp \
        SQLite/Statement.cpp \
        SQLite/Transaction.cpp \
        System/csysconfig.cpp \
        Thread/cdetectanalysis.cpp \
        Thread/cemittermerge.cpp \
        Thread/cjamtech.cpp \
        Thread/cprompt.cpp \
        Thread/cpulsetrk.cpp \
        Thread/cscananalysis.cpp \
        Thread/csignalcollect.cpp \
        Thread/ctaskmngr.cpp \
        Thread/ctrackanalysis.cpp \
        Thread/curbit.cpp \
        Thread/creclan.cpp \
        Utils/carraymsgdata.cpp \
        Utils/ccommonutils.cpp \
        Utils/cfile.cpp \
        Utils/clog.cpp \
        Utils/cmultiserver.cpp \
        Utils/csingleserver.cpp \
        Utils/cthread.cpp \
        Utils/cgpio.cpp \
        cmain.cpp

HEADERS += \
    Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.h \
    Anal/EmitterMerge/ELEmitterDataType.h \
    Anal/EmitterMerge/ELEnvironVariableMngr.h \
    Anal/EmitterMerge/ELGMIMsgDefn.h \
    Anal/EmitterMerge/ELMsgDefn.h \
    Anal/EmitterMerge/ELOperationCtrlDataType.h \
    Anal/EmitterMerge/ELPosEstDataType.h \
    Anal/EmitterMerge/ELThreat.h \
    Anal/EmitterMerge/ElintRsltDataTypedb.h \
    Anal/EmitterMerge/ElintTaskDataTypedb.h \
    Anal/EmitterMerge/GeoCoordConv.h \
    Anal/EmitterMerge/LinearLS/LinearLS.h \
    Anal/EmitterMerge/Matrix/Matrix.h \
    Anal/EmitterMerge/NonlinearLS/NonLinearLS.h \
    Anal/EmitterMerge/PositionEstimation.h \
    Anal/EmitterMerge/PositionEstimationAlg.h \
    Anal/EmitterMerge/Quadratic/Quadratic.h \
    Anal/EmitterMerge/Stack.h \
    Anal/INC/AetIPL.h \
    Anal/INC/ErrorMsg.h \
    Anal/INC/Globals.h \
    Anal/INC/Macros.h \
    Anal/INC/OS.h \
    Anal/INC/PDW.h \
    Anal/INC/Stack.h \
    Anal/INC/TaskMsg.h \
    Anal/INC/defines.h \
    Anal/INC/structs.h \
    Anal/INC/system.h \
    Anal/Identify/ELCEDLibDataType.h \
    Anal/Identify/ELCEDLibDataType.h \
    Anal/Identify/ELCEDLibDataType2.h \
    Anal/Identify/ELCEDLibDataType2.h \
    Anal/Identify/ELCEDLibMngr2.h \
    Anal/Identify/ELCEDLibMngr2.h \
    Anal/Identify/ELUtil.h \
    Anal/Identify/ELUtil.h \
    Anal/Identify/Identify.h \
    Anal/Identify/Identify.h \
    Anal/Identify/define.h \
    Anal/Identify/define.h \
    Anal/Identify/structs.h \
    Anal/Identify/structs.h \
    Anal/NewSigAnal/NAnalPRI.h \
    Anal/NewSigAnal/NGroup.h \
    Anal/NewSigAnal/NMakeAET.h \
    Anal/NewSigAnal/NPulExt.h \
    Anal/NewSigAnal/NewSigAnal.h \
    Anal/NewSigAnal/NewSigAnal.hh \
    Anal/OFP_Main.h \
    Anal/ScanSigAnal/SAnalScan.h \
    Anal/ScanSigAnal/SDefine.h \
    Anal/ScanSigAnal/SGroup.h \
    Anal/ScanSigAnal/SPulExt.h \
    Anal/ScanSigAnal/SStruct.h \
    Anal/ScanSigAnal/ScanSigAnal.h \
    Anal/SigAnal/AnalPRI.h \
    Anal/SigAnal/Group.h \
    Anal/SigAnal/MakeAET.h \
    Anal/SigAnal/PulExt.h \
    Anal/SigAnal/SysPara.h \
    Anal/SigAnal/_Define.h \
    Anal/SigAnal/_Macro.h \
    Anal/SigAnal/_SigAnal.h \
    Anal/SigAnal/_Struct.h \
    Anal/SigAnal/_Type.h \
    Collect/DataFile/CRWRCommonVariables.h \
    Collect/DataFile/DataFile.h \
    Collect/DataFile/_iq.h \
    Collect/DataFile/_macro.h \
    Collect/DataFile/_pdw.h \
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
    SQLite/Column.h \
    SQLite/Database.h \
    SQLite/SQLiteCpp.h \
    SQLite/Transaction.h \
    SQLite/Utils.h \
    SQLite/VariadicBind.h \
    System/csysconfig.h \
    Thread/ccollectbank/ccollectbank.h \
    Thread/cdetectanalysis.h \
    Thread/cemittermerge.h \
    Thread/cjamtech.h \
    Thread/cprompt.h \
    Thread/cpulsetrk.h \
    Thread/creclan.h \
    Thread/cscananalysis.h \
    Thread/csignalcollect.h \
    Thread/ctaskmngr.h \
    Thread/ctrackanalysis.h \
    Thread/curbit.h \
    Utils/carraymsgdata.h \
    Utils/ccommonutils.h \
    Utils/cfile.h \
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
LIBS += -lsqlite3

INCLUDEPATH += /usr/local/boost
INCLUDEPATH += /usr/local/include

DEFINES += _POCKETSONATA_
DEFINES += NEX7410
DEFINES += _SQLITE_

DISTFILES += \
    NetMem/CMakeLists.txt \
    NetMem/client/CMakeLists.txt \
    NetMem/server/CMakeLists.txt \
    NetMem/utils/CMakeLists.txt \
    SQLite/pocketsonata.sqbpro \
    SQLite/pocketsonata.sqlite3
