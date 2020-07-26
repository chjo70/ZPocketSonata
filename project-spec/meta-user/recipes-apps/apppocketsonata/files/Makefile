APP = apppocketsonata

# Add any other object files to this list below
APP_OBJS = MinIni/minIni.o
APP_OBJS += Utils/cthread.o
APP_OBJS += Utils/cgpio.o
APP_OBJS += cjamtech.o
APP_OBJS += clog.o
APP_OBJS += cmain.o
APP_OBJS += cprompt.o
APP_OBJS += cpulsetrk.o
APP_OBJS += creclan.o
APP_OBJS += csignalcollect.o
APP_OBJS += curbit.o
APP_OBJS += mysocket.o

LDLIBS = -pthread
# -lreadline


all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS)


clean:
	$(RM) $(APP_OBJS) $(APP)


