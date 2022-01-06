/* Aligned for ppc-64 - PPC64 Big-Endian */


/* THIS FILE IS AUTO_GENERATED. PLEASE DO NOT EDIT. */

#ifndef _ASMLANGUAGE

#include <vxWorks.h>
#include <taskLib.h>
#include <rtpLib.h>
#include <sdLib.h>
#include <shlLib.h>
#include <signal.h>
#if (defined(_WRS_CONFIG_SOCKET))
#include <socket.h>
#endif
#include <time.h>
#include <setjmp.h>
#include <ioLib.h>
#include <private/semSysCall.h>
#include <private/objLibP.h>
#include <private/rtpLibP.h>
#include <private/mqPxSysCall.h>
#include <private/pxObjSysCall.h>
#include <private/semPxSysCall.h>
#include <private/taskSysCall.h>
#include <private/timerSysCall.h>
#include <private/eventSysCall.h>
#include <private/randomNumGenSysCallP.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <base/b_trace_attr_t.h>
#include <base/b_trace_id_t.h>
#include <base/b_trace_event_id_t.h>
#include <base/b_pthread_t.h>
#include <private/vxSysInfoCommonP.h>

struct _exitScArgs 
	{
	UINT32 statusPad;
	int status;
	};

struct _openScArgs 
	{
	const char * name;
	UINT32 flagsPad;
	int flags;
	UINT32 modePad;
	int mode;
	};

struct _closeScArgs 
	{
	UINT32 fdPad;
	int fd;
	};

struct _readScArgs 
	{
	UINT32 fdPad;
	int fd;
	void * buffer;
	size_t maxbytes;
	};

struct _writeScArgs 
	{
	UINT32 fdPad;
	int fd;
	const void * buffer;
	size_t nbytes;
	};

struct _ioctlScArgs 
	{
	UINT32 fdPad;
	int fd;
	UINT32 functionPad;
	int function;
	_Vx_ioctl_arg_t arg;
	};

struct _dupScArgs 
	{
	UINT32 fdPad;
	int fd;
	UINT32 startFdPad;
	int startFd;
	};

struct _dup2ScArgs 
	{
	UINT32 fdPad;
	int fd;
	UINT32 fd2Pad;
	int fd2;
	};

struct _pipeScArgs 
	{
	int * fildes;
	UINT32 flagsPad;
	int flags;
	};

struct _removeScArgs 
	{
	const char * name;
	};

struct _selectXScArgs 
	{
	UINT32 widthPad;
	int width;
	fd_set * readFds;
	fd_set * writeFds;
	fd_set * excFds;
	struct timeval * timeout;
	UINT32 clearSemPad;
	BOOL clearSem;
	};

#if (defined(_WRS_CONFIG_SOCKET))
struct _socketScArgs 
	{
	UINT32 domainPad;
	int domain;
	UINT32 typePad;
	int type;
	UINT32 protocolPad;
	int protocol;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _bindScArgs 
	{
	UINT32 sPad;
	int s;
	const struct sockaddr * name;
	UINT32 namelenPad;
	socklen_t namelen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _listenScArgs 
	{
	UINT32 sPad;
	int s;
	UINT32 backlogPad;
	int backlog;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _acceptScArgs 
	{
	UINT32 sPad;
	int s;
	struct sockaddr * addr;
	socklen_t *addrlen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _connectScArgs 
	{
	UINT32 sPad;
	int s;
	const struct sockaddr * name;
	UINT32 namelenPad;
	socklen_t namelen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _sendtoScArgs 
	{
	UINT32 sPad;
	int s;
	const void * buf;
	size_t bufLen;
	UINT32 flagsPad;
	int flags;
	const struct sockaddr * to;
	UINT32 tolenPad;
	socklen_t tolen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _sendScArgs 
	{
	UINT32 sPad;
	int s;
	const void * buf;
	size_t bufLen;
	UINT32 flagsPad;
	int flags;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _sendmsgScArgs 
	{
	UINT32 sPad;
	int s;
	const struct msghdr * mp;
	UINT32 flagsPad;
	int flags;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _recvfromScArgs 
	{
	UINT32 sPad;
	int s;
	void * buf;
	size_t bufLen;
	UINT32 flagsPad;
	int flags;
	struct sockaddr *from;
	socklen_t * pFromLen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _recvScArgs 
	{
	UINT32 sPad;
	int s;
	void * buf;
	size_t bufLen;
	UINT32 flagsPad;
	int flags;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _recvmsgScArgs 
	{
	UINT32 sPad;
	int s;
	struct msghdr * mp;
	UINT32 flagsPad;
	int flags;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _setsockoptScArgs 
	{
	UINT32 sPad;
	int s;
	UINT32 levelPad;
	int level;
	UINT32 optnamePad;
	int optname;
	const void * optval;
	UINT32 optlenPad;
	socklen_t optlen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _getsockoptScArgs 
	{
	UINT32 sPad;
	int s;
	UINT32 levelPad;
	int level;
	UINT32 optnamePad;
	int optname;
	void * optval;
	socklen_t * optlen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _getsocknameScArgs 
	{
	UINT32 sPad;
	int s;
	struct sockaddr *name;
	socklen_t * namelen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _getpeernameScArgs 
	{
	UINT32 sPad;
	int s;
	struct sockaddr *name;
	socklen_t * namelen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _shutdownScArgs 
	{
	UINT32 sPad;
	int s;
	UINT32 howPad;
	int how;
	};
#endif

struct mmapScArgs 
	{
	void * addr;
	size_t len;
	UINT32 protPad;
	int prot;
	UINT32 flagsPad;
	int flags;
	UINT32 fildesPad;
	int fildes;
	off64_t off;
	};

struct munmapScArgs 
	{
	void * addr;
	size_t len;
	};

struct mprotectScArgs 
	{
	void * addr;
	size_t len;
	UINT32 protPad;
	int prot;
	};

struct killScArgs 
	{
	UINT32 rtpIdPad;
	OBJ_HANDLE rtpId;
	UINT32 signoPad;
	int signo;
	};

struct sigpendingScArgs 
	{
	sigset_t * pSet;
	};

struct sigprocmaskScArgs 
	{
	UINT32 howPad;
	int how;
	const sigset_t * pSet;
	sigset_t * pOset;
	};

struct _sigqueueScArgs 
	{
	UINT32 rtpIdPad;
	OBJ_HANDLE rtpId;
	UINT32 signoPad;
	int signo;
	const union sigval * pValue;
	UINT32 sigCodePad;
	int sigCode;
	};

struct _sigsuspendScArgs 
	{
	const sigset_t * pSet;
	};

struct _sigtimedwaitScArgs 
	{
	const sigset_t * pSet;
	struct siginfo * pInfo;
	const struct timespec * pTime;
	};

struct _sigactionScArgs 
	{
	UINT32 signoPad;
	int signo;
	const struct sigaction * pAct;
	struct sigaction * pOact;
	void * retAddr;
	};

struct chdirScArgs 
	{
	const char * name;
	};

struct _getcwdScArgs 
	{
	char * buffer;
	UINT32 lengthPad;
	int length;
	};

struct _waitpidScArgs 
	{
	UINT32 childRtpIdPad;
	OBJ_HANDLE childRtpId;
	int * pStatus;
	UINT32 optionsPad;
	int options;
	};

struct sysctlScArgs 
	{
	int * pName;
	UINT32 nameLenPad;
	u_int nameLen;
	void * pOld;
	size_t * pOldLen;
	void * pNew;
	size_t newLen;
	};

struct _schedPxInfoGetScArgs 
	{
	BOOL * pTimeSlicingOn;
	ULONG * pTimeSlicePeriod;
	};

struct sigaltstackScArgs 
	{
	stack_t * ss;
	stack_t * oss;
	};

struct _unlinkScArgs 
	{
	const char * name;
	};

struct _linkScArgs 
	{
	const char * name;
	const char * newname;
	};

struct _fsyncScArgs 
	{
	UINT32 fdPad;
	int fd;
	};

struct _fdatasyncScArgs 
	{
	UINT32 fdPad;
	int fd;
	};

struct _renameScArgs 
	{
	const char * oldname;
	const char * newname;
	};

struct _fpathconfScArgs 
	{
	UINT32 fdPad;
	int fd;
	UINT32 namePad;
	int name;
	};

struct _pathconfScArgs 
	{
	const char * path;
	UINT32 namePad;
	int name;
	};

struct _accessScArgs 
	{
	const char * path;
	UINT32 amodePad;
	int amode;
	};

struct _chmodScArgs 
	{
	const char * path;
	UINT32 modePad;
	mode_t mode;
	};

struct pxTraceCreationScArgs 
	{
	UINT32 cmdPad;
	int cmd;
	pid_t pid;
	trace_attr_t * attr;
	UINT32 fdPad;
	int fd;
	trace_id_t * trid;
	};

struct pxTraceCtlScArgs 
	{
	UINT32 cmdPad;
	int cmd;
	UINT32 tridPad;
	trace_id_t trid;
	struct trace_event_set_t * filter;
	UINT32 howPad;
	int how;
	pthread_t thread_id;
	void * pc;
	void * ptr_out;
	};

struct pxTraceEventScArgs 
	{
	UINT32 cmdPad;
	int cmd;
	UINT32 id_inPad;
	int id_in;
	char * data;
	size_t data_len;
	pthread_t thread_id;
	void * pc;
	trace_event_id_t * id_out;
	};

struct pxTraceEventNameQueryScArgs 
	{
	UINT32 cmdPad;
	int cmd;
	UINT32 tridPad;
	trace_id_t trid;
	UINT32 id_in1Pad;
	int id_in1;
	UINT32 id_in2Pad;
	int id_in2;
	char * name;
	trace_event_id_t * id_out;
	int * unavailable;
	};

struct pxTraceLogScArgs 
	{
	UINT32 cmdPad;
	int cmd;
	UINT32 trid_inPad;
	trace_id_t trid_in;
	UINT32 fdPad;
	int fd;
	trace_id_t *trid_out;
	};

struct pxTraceEventGetScArgs 
	{
	UINT32 cmdPad;
	int cmd;
	UINT32 tridPad;
	trace_id_t trid;
	size_t num_bytes;
	struct timespec * timeout;
	struct posix_trace_event_info * event;
	void * data;
	size_t * data_len;
	int * unavailable;
	};

struct eventReceiveExScArgs 
	{
	UINT32 eventsPad;
	UINT32 events;
	UINT32 optionsPad;
	UINT32 options;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	UINT32 * pEvtsReceived;
	};

struct eventSendScArgs 
	{
	UINT32 taskIdPad;
	int taskId;
	UINT32 eventsPad;
	UINT32 events;
	};

struct eventCtlScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 commandPad;
	VX_EVT_CTL_CMD command;
	void * pArg;
	size_t * pArgSize;
	};

struct msgQSendScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	char * buffer;
	size_t nBytes;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	UINT32 priorityPad;
	int priority;
	};

struct msgQReceiveScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	char * buffer;
	size_t maxNBytes;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct _msgQOpenScArgs 
	{
	const char * name;
	size_t maxMsgs;
	size_t maxMsgLength;
	UINT32 optionsPad;
	int options;
	UINT32 modePad;
	int mode;
	void * context;
	};

struct objDeleteScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 optionsPad;
	int options;
	};

struct objInfoGetScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	void * pInfo;
	size_t * pInfoSize;
	UINT32 levelPad;
	int level;
	};

struct _semTakeScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct _semGiveScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	};

struct _semOpenScArgs 
	{
	const char * name;
	UINT32 typePad;
	SEM_TYPE type;
	UINT32 initStatePad;
	int initState;
	UINT32 optionsPad;
	int options;
	UINT32 modePad;
	int mode;
	void * context;
	};

struct semCtlScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 commandPad;
	VX_SEM_CTL_CMD command;
	void * pArg;
	size_t * pArgSize;
	};

struct _taskOpenScArgs 
	{
	struct vx_task_open_sc_args * pArgs;
	};

struct _taskDelayScArgs 
	{
	UINT32 ticksPad;
	_Vx_ticks_t ticks;
	};

struct rtpSpawnScArgs 
	{
	const char * rtpFileName;
	const char ** argv;
	const char ** envp;
	UINT32 priorityPad;
	int priority;
	size_t uStackSize;
	UINT32 optionsPad;
	int options;
	UINT32 taskOptionsPad;
	int taskOptions;
	};

struct rtpInfoGetScArgs 
	{
	UINT32 rtpIdPad;
	OBJ_HANDLE rtpId;
	RTP_DESC * rtpStruct;
	};

struct taskKillScArgs 
	{
	UINT32 taskHandlePad;
	OBJ_HANDLE taskHandle;
	UINT32 signoPad;
	int signo;
	};

struct _taskSigqueueScArgs 
	{
	UINT32 taskHandlePad;
	OBJ_HANDLE taskHandle;
	UINT32 signoPad;
	int signo;
	const union sigval * pValue;
	UINT32 sigCodePad;
	int sigCode;
	};

struct _timer_openScArgs 
	{
	const char * name;
	UINT32 modePad;
	int mode;
	clockid_t clockId;
	struct sigevent * evp;
	void * context;
	};

struct timerCtlScArgs 
	{
	UINT32 cmdCodePad;
	TIMER_CTL_CMD cmdCode;
	UINT32 timerHandlePad;
	OBJ_HANDLE timerHandle;
	void * pArgs;
	size_t pArgSize;
	};

struct pxOpenScArgs 
	{
	UINT32 typePad;
	PX_OBJ_TYPE type;
	const char * name;
	UINT32 objOpenModePad;
	int objOpenMode;
	void * attr;
	};

struct pxCloseScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	};

struct pxUnlinkScArgs 
	{
	UINT32 typePad;
	PX_OBJ_TYPE type;
	const char * name;
	};

struct pxCtlScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 cmdCodePad;
	PX_CTL_CMD_CODE cmdCode;
	void * pArgs;
	size_t * pArgSize;
	};

struct pxMqReceiveScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	char * pMsg;
	size_t msgLen;
	unsigned int * pMsgPrio;
	UINT32 waitOptionPad;
	PX_WAIT_OPTION waitOption;
	const struct timespec * time_out;
	};

struct pxMqSendScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	const char * pMsg;
	size_t msgLen;
	UINT32 msgPrioPad;
	unsigned int msgPrio;
	UINT32 waitOptionPad;
	PX_WAIT_OPTION waitOption;
	const struct timespec * time_out;
	};

struct pxSemWaitScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 waitOptionPad;
	PX_WAIT_OPTION waitOption;
	const struct timespec * time_out;
	};

struct pxSemPostScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	};

struct pipeDevCreateScArgs 
	{
	const char * name;
	size_t nMessages;
	size_t nBytes;
	};

struct pipeDevDeleteScArgs 
	{
	const char * name;
	UINT32 forcePad;
	BOOL force;
	};

struct _sdCreateScArgs 
	{
	char * name;
	UINT32 optionsPad;
	int options;
	size_t size;
	off64_t physAddress;
	UINT32 attrPad;
	MMU_ATTR attr;
	void ** pVirtAddress;
	};

struct _sdOpenScArgs 
	{
	char * name;
	UINT32 optionsPad;
	int options;
	UINT32 modePad;
	int mode;
	size_t size;
	off64_t physAddress;
	UINT32 attrPad;
	MMU_ATTR attr;
	void ** pVirtAddress;
	};

struct sdDeleteScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 optionsPad;
	int options;
	};

struct sdMapScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 attrPad;
	MMU_ATTR attr;
	UINT32 optionsPad;
	int options;
	};

struct sdUnmapScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 optionsPad;
	int options;
	};

struct sdProtectScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 attrPad;
	MMU_ATTR attr;
	};

struct _edrErrorInjectScArgs 
	{
	UINT32 kindPad;
	int kind;
	const char *fileName;
	UINT32 lineNumberPad;
	int lineNumber;
	REG_SET *regset;
	void *addr;
	const char *msg;
	};

#if (defined(_WRS_CONFIG_SYSTEMVIEWER))
struct wvEventScArgs 
	{
	UINT32 eventIdPad;
	int eventId;
	const char * pData;
	UINT32 dataSizePad;
	unsigned int dataSize;
	};
#endif

struct rtpVarAddScArgs 
	{
	void ** pVar;
	void * value;
	};

struct sdInfoGetScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	SD_DESC * pSdStruct;
	};

struct _shlOpenScArgs 
	{
	const char * name;
	UINT32 optionsPad;
	int options;
	};

struct _shlUnlockScArgs 
	{
	UINT32 shlIdPad;
	SHL_ID shlId;
	};

struct _shlCloseScArgs 
	{
	UINT32 shlIdPad;
	SHL_ID shlId;
	};

struct _shlGetScArgs 
	{
	UINT32 shlIdPad;
	SHL_ID shlId;
	SHLINFO *pInfo;
	};

struct _shlPutScArgs 
	{
	UINT32 shlIdPad;
	SHL_ID shlId;
	const SHLINFO *pInfo;
	};

struct objUnlinkScArgs 
	{
	const char * name;
	UINT32 classTypePad;
	enum windObjClassType classType;
	};

struct getprlimitScArgs 
	{
	UINT32 idtypePad;
	int idtype;
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 resourcePad;
	int resource;
	struct rlimit *rlp;
	};

struct setprlimitScArgs 
	{
	UINT32 idtypePad;
	int idtype;
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 resourcePad;
	int resource;
	struct rlimit *rlp;
	};

struct _mctlScArgs 
	{
	void * addr;
	size_t len;
	UINT32 functionPad;
	int function;
	void * arg;
	};

struct _taskOpenWithGuardScArgs 
	{
	struct vx_task_open_guard_sc_args * pArgs;
	};

struct clockCtlScArgs 
	{
	clockid_t clock_id;
	UINT32 cmdCodePad;
	CLOCK_CTL_CMD cmdCode;
	void * pArgStruct;
	size_t * pArgSize;
	};

struct _semRTakeScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct _semWTakeScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct _semExchangeScArgs 
	{
	UINT32 giveHandlePad;
	OBJ_HANDLE giveHandle;
	UINT32 takeHandlePad;
	OBJ_HANDLE takeHandle;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

#if (defined(_WRS_CONFIG_SYSTEMVIEWER))
struct wvRtpEventScArgs 
	{
	UINT32 eventIdPad;
	int eventId;
	const char * pData;
	UINT32 dataSizePad;
	unsigned int dataSize;
	};
#endif

struct _condVarOpenScArgs 
	{
	const char *name;
	UINT32 optionsPad;
	int options;
	UINT32 modePad;
	int mode;
	void *context;
	};

struct _condVarWaitScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 mtx_handlePad;
	OBJ_HANDLE mtx_handle;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct _condVarSignalScArgs 
	{
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 broadcastPad;
	int broadcast;
	};

struct _setuidScArgs 
	{
	UINT32 uidPad;
	int uid;
	};

struct _setgidScArgs 
	{
	UINT32 gidPad;
	int gid;
	};

struct _seteuidScArgs 
	{
	UINT32 euidPad;
	int euid;
	};

struct _setegidScArgs 
	{
	UINT32 egidPad;
	int egid;
	};

struct getlogin_rScArgs 
	{
	char * loginName;
	size_t nameSz;
	};

struct _clock_getresScArgs 
	{
	clockid_t clock_id;
	struct timespec * res;
	};

struct _clock_gettimeScArgs 
	{
	clockid_t clock_id;
	struct timespec * tp;
	};

struct _clock_settimeScArgs 
	{
	clockid_t clock_id;
	const struct timespec * tp;
	};

#if (defined(_WRS_CONFIG_FILE_CREATION_MASK))
struct _umaskScArgs 
	{
	UINT32 cmaskPad;
	mode_t cmask;
	};
#endif

struct randNumGenCtlScArgs 
	{
	UINT32 commandPad;
	VX_RANDOM_NUM_GEN_CTL_CMD command;
	void * pArg;
	size_t pArgSize;
	};

struct taskStateCtlScArgs 
	{
	UINT32 tidPad;
	int tid;
	UINT32 commandPad;
	VX_TASK_CTL_CMD command;
	void * pArg;
	size_t argSize;
	};

struct taskParamCtlScArgs 
	{
	UINT32 tidPad;
	int tid;
	UINT32 commandPad;
	VX_TASK_CTL_CMD command;
	void * pArg;
	};

struct taskPriCtlScArgs 
	{
	UINT32 tidPad;
	int tid;
	UINT32 commandPad;
	VX_TASK_CTL_CMD command;
	void * pArg;
	};

struct taskCpuAffCtlScArgs 
	{
	UINT32 tidPad;
	int tid;
	UINT32 commandPad;
	VX_TASK_CTL_CMD command;
	void * pArg;
	};

struct taskVarCtlScArgs 
	{
	UINT32 tidPad;
	int tid;
	UINT32 commandPad;
	VX_TASK_CTL_CMD command;
	long * pVar;
	long* pValue;
	};

struct taskPxAttrCtlScArgs 
	{
	UINT32 tidPad;
	int tid;
	UINT32 commandPad;
	VX_TASK_CTL_CMD command;
	void * pArg;
	};

struct _taskWaitScArgs 
	{
	UINT32 tidPad;
	int tid;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct atomic32OpScArgs 
	{
	atomic32_t* target;
	UINT32 oldValuePad;
	atomic32Val_t oldValue;
	UINT32 valuePad;
	atomic32Val_t value;
	atomic32Val_t* returnVal;
	UINT32 atomicSwitchPad;
	int atomicSwitch;
	};

struct atomic64OpScArgs 
	{
	atomic64_t* target;
	atomic64Val_t oldValue;
	atomic64Val_t value;
	atomic64Val_t* returnVal;
	UINT32 atomicSwitchPad;
	int atomicSwitch;
	};

struct _rtpTaskExitRegisterScArgs 
	{
	void * funcPtr;
	};

struct vxSysInfoGetScArgs 
	{
	_VX_SYS_INFO * pVxSysInfo;
	};

struct _tick64GetScArgs 
	{
	_Vx_ticks64_t * pTickVal;
	};

struct shmVolNameGetScArgs 
	{
	char * name;
	size_t len;
	};

struct _selWakeupOpScArgs 
	{
	UINT32 tidPad;
	int tid;
	UINT32 opPad;
	int op;
	};

struct pipeAnonCreateScArgs 
	{
	size_t nMessages;
	size_t nBytes;
	UINT32 flagsPad;
	unsigned flags;
	int * pFd;
	};

struct taskDelayExScArgs 
	{
	UINT32 ticksPad;
	_Vx_ticks_t ticks;
	UINT32 flagsPad;
	UINT32 flags;
	};

#endif	/* _ASMLANGUAGE */
