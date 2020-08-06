APP = apppocketsonata

# Add any other object files to this list below
APP_OBJS = Collect/ccollectbank/ccollectbank.o
APP_OBJS += Collect/DataFile/DataFile.o
APP_OBJS += MinIni/minIni.o
APP_OBJS += NetMem/client/ClientMemoryPage.o
APP_OBJS += NetMem/client/NetworkMemory.o
APP_OBJS += NetMem/server/ClientSocket.o
APP_OBJS += NetMem/server/MemoryPage.o
APP_OBJS += NetMem/server/ServerSocket.o
APP_OBJS += NetMem/utils/ApiNetMem.o
APP_OBJS += System/csysconfig.o
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
APP_OBJS += cmain.o
		


INCLUDES = -I$(TMPDIR)/sysroots-components/aarch64/readline/usr/include
INCLUDES += -I$(TMPDIR)/sysroots-components/aarch64/ncurses/usr/include
INCLUDES += -I$(TMPDIR)/sysroots-components/aarch64/boost/usr/include

LIBS = -L$(TMPDIR)/sysroots-components/aarch64/readline/usr/lib
LIBS += -L$(TMPDIR)/sysroots-components/aarch64/ncurses/lib
LIBS += -L$(TMPDIR)/sysroots-components/aarch64/ncurses/usr/lib
LIBS += -L$(TMPDIR)/sysroots-components/aarch64/boost/usr/lib

SRCS = $(APP_OBJS:.o=.cpp)

LDLIBS = -pthread -lreadline -lncurses -lboost_thread -lboost_system


all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS) $(LIBS)
	
%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDES)


clean:
	$(RM) $(APP_OBJS) $(APP)


