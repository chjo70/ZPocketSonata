APP = apppocketsonata

# Add any other object files to this list below
APP_OBJS = Anal/EmitterMerge/CInverseMethod.o
APP_OBJS += Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.o
APP_OBJS += Anal/EmitterMerge/ELEmitterMergeMngr.o
APP_OBJS += Anal/EmitterMerge/ELEnvironVariableMngr.o
APP_OBJS += Anal/EmitterMerge/ELThreat.o
APP_OBJS += Anal/EmitterMerge/GeoCoordConv.o
APP_OBJS += Anal/EmitterMerge/LOBClustering.o
APP_OBJS += Anal/EmitterMerge/Matrix/Matrix.o
APP_OBJS += Anal/EmitterMerge/PositionEstimationAlg.o
APP_OBJS += Anal/EmitterMerge/Quadratic/Quadratic.o
APP_OBJS += Anal/EmitterMerge/UTM.o
APP_OBJS += Anal/Identify/ELUtil.o
APP_OBJS += Anal/Identify/Identify.o
APP_OBJS += Anal/KnownSigAnal/KAnalPRI.o
APP_OBJS += Anal/KnownSigAnal/KGroup.o
APP_OBJS += Anal/KnownSigAnal/KMakeAET.o
APP_OBJS += Anal/KnownSigAnal/KPulExt.o
APP_OBJS += Anal/KnownSigAnal/KnownSigAnal.o
APP_OBJS += Anal/NewSigAnal/NGroup.o
APP_OBJS += Anal/NewSigAnal/NPulExt.o
APP_OBJS += Anal/NewSigAnal/NAnalPRI.o
APP_OBJS += Anal/NewSigAnal/NMakeAET.o
APP_OBJS += Anal/NewSigAnal/NewSigAnal.o
APP_OBJS += Anal/ParamMngr.o
APP_OBJS += Anal/SigAnal/Group.o
APP_OBJS += Anal/SigAnal/PulExt.o
APP_OBJS += Anal/SigAnal/AnalPRI.o
APP_OBJS += Anal/SigAnal/MakeAET.o
APP_OBJS += Anal/SigAnal/SysPara.o
APP_OBJS += Anal/SigAnal/stdafx.o
APP_OBJS += Collect/DataFile/DataFile.o
APP_OBJS += Collect/ccollectbank/ccollectbank.o
APP_OBJS += MinIni/minIni.o
APP_OBJS += NetMem/client/ClientMemoryPage.o
APP_OBJS += NetMem/client/NetworkMemory.o
APP_OBJS += NetMem/server/ClientSocket.o
APP_OBJS += NetMem/server/MemoryPage.o
APP_OBJS += NetMem/server/ServerSocket.o
APP_OBJS += NetMem/utils/ApiNetMem.o
APP_OBJS += SQLite/Backup.o
APP_OBJS += SQLite/Column.o
APP_OBJS += SQLite/Database.o
APP_OBJS += SQLite/Exception.o
APP_OBJS += SQLite/Statement.o
APP_OBJS += SQLite/Transaction.o
APP_OBJS += System/csysconfig.o
APP_OBJS += System/csharedmemory.o
APP_OBJS += Thread/ccgi.o
APP_OBJS += Thread/cdetectanalysis.o
APP_OBJS += Thread/cemittermerge.o
APP_OBJS += Thread/cjamtech.o
APP_OBJS += Thread/cprompt.o
APP_OBJS += Thread/cpulsetrk.o
APP_OBJS += Thread/cscananalysis.o
APP_OBJS += Thread/csignalcollect.o
APP_OBJS += Thread/ctaskmngr.o
APP_OBJS += Thread/ctrackanalysis.o
APP_OBJS += Thread/curbit.o
APP_OBJS += Thread/creclan.o
APP_OBJS += Utils/carraymsgdata.o
APP_OBJS += Utils/ccommonutils.o
APP_OBJS += Utils/cfile.o
APP_OBJS += Utils/clog.o
APP_OBJS += Utils/cmultiserver.o
APP_OBJS += Utils/csingleserver.o
APP_OBJS += Utils/cthread.o
APP_OBJS += Utils/cgpio.o
APP_OBJS += Utils/programrev.o
APP_OBJS += cmain.o
		


INCLUDES = -I$(TMPDIR)/sysroots-components/aarch64/readline/usr/include
INCLUDES += -I$(TMPDIR)/sysroots-components/aarch64/ncurses/usr/include
INCLUDES += -I$(TMPDIR)/sysroots-components/aarch64/boost/usr/include
INCLUDES += -I$(TMPDIR)/sysroots-components/aarch64/sqlite3/usr/include

LIBS = -L$(TMPDIR)/sysroots-components/aarch64/readline/usr/lib
LIBS += -L$(TMPDIR)/sysroots-components/aarch64/ncurses/lib
LIBS += -L$(TMPDIR)/sysroots-components/aarch64/ncurses/usr/lib
LIBS += -L$(TMPDIR)/sysroots-components/aarch64/boost/usr/lib
LIBS += -L$(TMPDIR)/sysroots-components/aarch64/sqlite3/usr/lib

SRCS = $(APP_OBJS:.o=.cpp)

LDLIBS = -pthread -lreadline -lncurses -lboost_thread -lboost_system -lsqlite3

DEFINES += -D_POCKETSONATA_
DEFINES += -D_SQLITE_


all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS) $(LIBS)
	
%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDES) $(DEFINES) 


clean:
	$(RM) $(APP_OBJS) $(APP)


