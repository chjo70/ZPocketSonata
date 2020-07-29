APP = apppocketsonata

# Add any other object files to this list below
APP_OBJS = Collect/ccollectbank/ccollectbank.o
APP_OBJS += MinIni/minIni.o
#APP_OBJS += NetMem/client/ClientMemoryPage.o
#3APP_OBJS += NetMem/client/NetworkMemory.o
#APP_OBJS += NetMem/server/ClientSocket.o
#APP_OBJS += NetMem/server/MemoryPage.o
#APP_OBJS += NetMem/server/ServerSocket.o
#APP_OBJS += NetMem/utils/ApiNetMem.o
APP_OBJS += System/csysconfig.o
APP_OBJS += Thread/cdetectanalysis.o
APP_OBJS += Thread/cjamtech.o
APP_OBJS += Thread/cprompt.o
APP_OBJS += Thread/cpulsetrk.o
APP_OBJS += Thread/csignalcollect.o
APP_OBJS += Thread/ctaskmngr.o
APP_OBJS += Thread/curbit.o
APP_OBJS += Thread/creclan.o
APP_OBJS += Utils/clog.o
APP_OBJS += Utils/cmultiserver.o
APP_OBJS += Utils/csingleserver.o
APP_OBJS += Utils/cthread.o
APP_OBJS += Utils/cgpio.o
APP_OBJS += cmain.o

LDFLAGS += -I$(TMPDIR)/sysroots-components/aarch64/readline/usr/include

LIBSOURCES_CPP = Collect/ccollectbank/ccollectbank.cpp
LIBSOURCES_C = MinIni/minIni.c

SRCS = $(wildcard ./Thread/*.cpp) $(wildcard ./Thread/*.c)
SRCS += $(wildcard ./Utils/*.cpp) $(wildcard ./Utils/*.c)


LDLIBS = -pthread -lreadline
# -lreadline


all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CXX) $(LDFLAGS)  -o $@ $(APP_OBJS) $(LDLIBS)  
	
%.o: %.c*
	echo $(SRCS)
	$(CXX) $(CFLAGS) -c -fPIC $(LIBSOURCES)	
	
	


clean:
	$(RM) $(APP_OBJS) $(APP)


