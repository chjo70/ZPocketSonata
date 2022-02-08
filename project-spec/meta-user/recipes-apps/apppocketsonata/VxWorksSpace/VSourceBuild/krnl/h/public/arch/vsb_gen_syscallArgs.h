/* Aligned for ppc - align 64-bit elements */


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
	int status;
	};

struct _openScArgs 
	{
	const char * name;
	int flags;
	int mode;
	};

struct _closeScArgs 
	{
	int fd;
	};

struct _readScArgs 
	{
	int fd;
	void * buffer;
	size_t maxbytes;
	};

struct _writeScArgs 
	{
	int fd;
	const void * buffer;
	size_t nbytes;
	};

struct _ioctlScArgs 
	{
	int fd;
	int function;
	_Vx_ioctl_arg_t arg;
	};

struct _dupScArgs 
	{
	int fd;
	int startFd;
	};

struct _dup2ScArgs 
	{
	int fd;
	int fd2;
	};

struct _pipeScArgs 
	{
	int * fildes;
	int flags;
	};

struct _removeScArgs 
	{
	const char * name;
	};

struct _selectXScArgs 
	{
	int width;
	fd_set * readFds;
	fd_set * writeFds;
	fd_set * excFds;
	struct timeval * timeout;
	BOOL clearSem;
	};

#if (defined(_WRS_CONFIG_SOCKET))
struct _socketScArgs 
	{
	int domain;
	int type;
	int protocol;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _bindScArgs 
	{
	int s;
	const struct sockaddr * name;
	socklen_t namelen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _listenScArgs 
	{
	int s;
	int backlog;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _acceptScArgs 
	{
	int s;
	struct sockaddr * addr;
	socklen_t *addrlen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _connectScArgs 
	{
	int s;
	const struct sockaddr * name;
	socklen_t namelen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _sendtoScArgs 
	{
	int s;
	const void * buf;
	size_t bufLen;
	int flags;
	const struct sockaddr * to;
	socklen_t tolen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _sendScArgs 
	{
	int s;
	const void * buf;
	size_t bufLen;
	int flags;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _sendmsgScArgs 
	{
	int s;
	const struct msghdr * mp;
	int flags;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _recvfromScArgs 
	{
	int s;
	void * buf;
	size_t bufLen;
	int flags;
	struct sockaddr *from;
	socklen_t * pFromLen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _recvScArgs 
	{
	int s;
	void * buf;
	size_t bufLen;
	int flags;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _recvmsgScArgs 
	{
	int s;
	struct msghdr * mp;
	int flags;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _setsockoptScArgs 
	{
	int s;
	int level;
	int optname;
	const void * optval;
	socklen_t optlen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _getsockoptScArgs 
	{
	int s;
	int level;
	int optname;
	void * optval;
	socklen_t * optlen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _getsocknameScArgs 
	{
	int s;
	struct sockaddr *name;
	socklen_t * namelen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _getpeernameScArgs 
	{
	int s;
	struct sockaddr *name;
	socklen_t * namelen;
	};
#endif

#if (defined(_WRS_CONFIG_SOCKET))
struct _shutdownScArgs 
	{
	int s;
	int how;
	};
#endif

struct mmapScArgs 
	{
	void * addr;
	size_t len;
	int prot;
	int flags;
	int fildes;
	int offPad;
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
	int prot;
	};

struct killScArgs 
	{
	OBJ_HANDLE rtpId;
	int signo;
	};

struct sigpendingScArgs 
	{
	sigset_t * pSet;
	};

struct sigprocmaskScArgs 
	{
	int how;
	const sigset_t * pSet;
	sigset_t * pOset;
	};

struct _sigqueueScArgs 
	{
	OBJ_HANDLE rtpId;
	int signo;
	const union sigval * pValue;
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
	int length;
	};

struct _waitpidScArgs 
	{
	OBJ_HANDLE childRtpId;
	int * pStatus;
	int options;
	};

struct sysctlScArgs 
	{
	int * pName;
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
	int fd;
	};

struct _fdatasyncScArgs 
	{
	int fd;
	};

struct _renameScArgs 
	{
	const char * oldname;
	const char * newname;
	};

struct _fpathconfScArgs 
	{
	int fd;
	int name;
	};

struct _pathconfScArgs 
	{
	const char * path;
	int name;
	};

struct _accessScArgs 
	{
	const char * path;
	int amode;
	};

struct _chmodScArgs 
	{
	const char * path;
	mode_t mode;
	};

struct pxTraceCreationScArgs 
	{
	int cmd;
	pid_t pid;
	trace_attr_t * attr;
	int fd;
	trace_id_t * trid;
	};

struct pxTraceCtlScArgs 
	{
	int cmd;
	trace_id_t trid;
	struct trace_event_set_t * filter;
	int how;
	pthread_t thread_id;
	void * pc;
	void * ptr_out;
	};

struct pxTraceEventScArgs 
	{
	int cmd;
	int id_in;
	char * data;
	size_t data_len;
	pthread_t thread_id;
	void * pc;
	trace_event_id_t * id_out;
	};

struct pxTraceEventNameQueryScArgs 
	{
	int cmd;
	trace_id_t trid;
	int id_in1;
	int id_in2;
	char * name;
	trace_event_id_t * id_out;
	int * unavailable;
	};

struct pxTraceLogScArgs 
	{
	int cmd;
	trace_id_t trid_in;
	int fd;
	trace_id_t *trid_out;
	};

struct pxTraceEventGetScArgs 
	{
	int cmd;
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
	UINT32 events;
	UINT32 options;
	_Vx_ticks_t timeout;
	UINT32 * pEvtsReceived;
	};

struct eventSendScArgs 
	{
	int taskId;
	UINT32 events;
	};

struct eventCtlScArgs 
	{
	OBJ_HANDLE handle;
	VX_EVT_CTL_CMD command;
	void * pArg;
	size_t * pArgSize;
	};

struct msgQSendScArgs 
	{
	OBJ_HANDLE handle;
	char * buffer;
	size_t nBytes;
	_Vx_ticks_t timeout;
	int priority;
	};

struct msgQReceiveScArgs 
	{
	OBJ_HANDLE handle;
	char * buffer;
	size_t maxNBytes;
	_Vx_ticks_t timeout;
	};

struct _msgQOpenScArgs 
	{
	const char * name;
	size_t maxMsgs;
	size_t maxMsgLength;
	int options;
	int mode;
	void * context;
	};

struct objDeleteScArgs 
	{
	OBJ_HANDLE handle;
	int options;
	};

struct objInfoGetScArgs 
	{
	OBJ_HANDLE handle;
	void * pInfo;
	size_t * pInfoSize;
	int level;
	};

struct _semTakeScArgs 
	{
	OBJ_HANDLE handle;
	_Vx_ticks_t timeout;
	};

struct _semGiveScArgs 
	{
	OBJ_HANDLE handle;
	};

struct _semOpenScArgs 
	{
	const char * name;
	SEM_TYPE type;
	int initState;
	int options;
	int mode;
	void * context;
	};

struct semCtlScArgs 
	{
	OBJ_HANDLE handle;
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
	_Vx_ticks_t ticks;
	};

struct rtpSpawnScArgs 
	{
	const char * rtpFileName;
	const char ** argv;
	const char ** envp;
	int priority;
	size_t uStackSize;
	int options;
	int taskOptions;
	};

struct rtpInfoGetScArgs 
	{
	OBJ_HANDLE rtpId;
	RTP_DESC * rtpStruct;
	};

struct taskKillScArgs 
	{
	OBJ_HANDLE taskHandle;
	int signo;
	};

struct _taskSigqueueScArgs 
	{
	OBJ_HANDLE taskHandle;
	int signo;
	const union sigval * pValue;
	int sigCode;
	};

struct _timer_openScArgs 
	{
	const char * name;
	int mode;
	clockid_t clockId;
	struct sigevent * evp;
	void * context;
	};

struct timerCtlScArgs 
	{
	TIMER_CTL_CMD cmdCode;
	OBJ_HANDLE timerHandle;
	void * pArgs;
	size_t pArgSize;
	};

struct pxOpenScArgs 
	{
	PX_OBJ_TYPE type;
	const char * name;
	int objOpenMode;
	void * attr;
	};

struct pxCloseScArgs 
	{
	OBJ_HANDLE handle;
	};

struct pxUnlinkScArgs 
	{
	PX_OBJ_TYPE type;
	const char * name;
	};

struct pxCtlScArgs 
	{
	OBJ_HANDLE handle;
	PX_CTL_CMD_CODE cmdCode;
	void * pArgs;
	size_t * pArgSize;
	};

struct pxMqReceiveScArgs 
	{
	OBJ_HANDLE handle;
	char * pMsg;
	size_t msgLen;
	unsigned int * pMsgPrio;
	PX_WAIT_OPTION waitOption;
	const struct timespec * time_out;
	};

struct pxMqSendScArgs 
	{
	OBJ_HANDLE handle;
	const char * pMsg;
	size_t msgLen;
	unsigned int msgPrio;
	PX_WAIT_OPTION waitOption;
	const struct timespec * time_out;
	};

struct pxSemWaitScArgs 
	{
	OBJ_HANDLE handle;
	PX_WAIT_OPTION waitOption;
	const struct timespec * time_out;
	};

struct pxSemPostScArgs 
	{
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
	BOOL force;
	};

struct _sdCreateScArgs 
	{
	char * name;
	int options;
	size_t size;
	int physAddressPad;
	off64_t physAddress;
	MMU_ATTR attr;
	void ** pVirtAddress;
	};

struct _sdOpenScArgs 
	{
	char * name;
	int options;
	int mode;
	size_t size;
	off64_t physAddress;
	MMU_ATTR attr;
	void ** pVirtAddress;
	};

struct sdDeleteScArgs 
	{
	OBJ_HANDLE handle;
	int options;
	};

struct sdMapScArgs 
	{
	OBJ_HANDLE handle;
	MMU_ATTR attr;
	int options;
	};

struct sdUnmapScArgs 
	{
	OBJ_HANDLE handle;
	int options;
	};

struct sdProtectScArgs 
	{
	OBJ_HANDLE handle;
	MMU_ATTR attr;
	};

struct _edrErrorInjectScArgs 
	{
	int kind;
	const char *fileName;
	int lineNumber;
	REG_SET *regset;
	void *addr;
	const char *msg;
	};

#if (defined(_WRS_CONFIG_SYSTEMVIEWER))
struct wvEventScArgs 
	{
	int eventId;
	const char * pData;
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
	OBJ_HANDLE handle;
	SD_DESC * pSdStruct;
	};

struct _shlOpenScArgs 
	{
	const char * name;
	int options;
	};

struct _shlUnlockScArgs 
	{
	SHL_ID shlId;
	};

struct _shlCloseScArgs 
	{
	SHL_ID shlId;
	};

struct _shlGetScArgs 
	{
	SHL_ID shlId;
	SHLINFO *pInfo;
	};

struct _shlPutScArgs 
	{
	SHL_ID shlId;
	const SHLINFO *pInfo;
	};

struct objUnlinkScArgs 
	{
	const char * name;
	enum windObjClassType classType;
	};

struct getprlimitScArgs 
	{
	int idtype;
	OBJ_HANDLE handle;
	int resource;
	struct rlimit *rlp;
	};

struct setprlimitScArgs 
	{
	int idtype;
	OBJ_HANDLE handle;
	int resource;
	struct rlimit *rlp;
	};

struct _mctlScArgs 
	{
	void * addr;
	size_t len;
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
	CLOCK_CTL_CMD cmdCode;
	void * pArgStruct;
	size_t * pArgSize;
	};

struct _semRTakeScArgs 
	{
	OBJ_HANDLE handle;
	_Vx_ticks_t timeout;
	};

struct _semWTakeScArgs 
	{
	OBJ_HANDLE handle;
	_Vx_ticks_t timeout;
	};

struct _semExchangeScArgs 
	{
	OBJ_HANDLE giveHandle;
	OBJ_HANDLE takeHandle;
	_Vx_ticks_t timeout;
	};

#if (defined(_WRS_CONFIG_SYSTEMVIEWER))
struct wvRtpEventScArgs 
	{
	int eventId;
	const char * pData;
	unsigned int dataSize;
	};
#endif

struct _condVarOpenScArgs 
	{
	const char *name;
	int options;
	int mode;
	void *context;
	};

struct _condVarWaitScArgs 
	{
	OBJ_HANDLE handle;
	OBJ_HANDLE mtx_handle;
	_Vx_ticks_t timeout;
	};

struct _condVarSignalScArgs 
	{
	OBJ_HANDLE handle;
	int broadcast;
	};

struct _setuidScArgs 
	{
	int uid;
	};

struct _setgidScArgs 
	{
	int gid;
	};

struct _seteuidScArgs 
	{
	int euid;
	};

struct _setegidScArgs 
	{
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
	mode_t cmask;
	};
#endif

struct randNumGenCtlScArgs 
	{
	VX_RANDOM_NUM_GEN_CTL_CMD command;
	void * pArg;
	size_t pArgSize;
	};

struct taskStateCtlScArgs 
	{
	int tid;
	VX_TASK_CTL_CMD command;
	void * pArg;
	size_t argSize;
	};

struct taskParamCtlScArgs 
	{
	int tid;
	VX_TASK_CTL_CMD command;
	void * pArg;
	};

struct taskPriCtlScArgs 
	{
	int tid;
	VX_TASK_CTL_CMD command;
	void * pArg;
	};

struct taskCpuAffCtlScArgs 
	{
	int tid;
	VX_TASK_CTL_CMD command;
	void * pArg;
	};

struct taskVarCtlScArgs 
	{
	int tid;
	VX_TASK_CTL_CMD command;
	long * pVar;
	long* pValue;
	};

struct taskPxAttrCtlScArgs 
	{
	int tid;
	VX_TASK_CTL_CMD command;
	void * pArg;
	};

struct _taskWaitScArgs 
	{
	int tid;
	_Vx_ticks_t timeout;
	};

struct atomic32OpScArgs 
	{
	atomic32_t* target;
	atomic32Val_t oldValue;
	atomic32Val_t value;
	atomic32Val_t* returnVal;
	int atomicSwitch;
	};

struct atomic64OpScArgs 
	{
	atomic64_t* target;
	int oldValuePad;
	atomic64Val_t oldValue;
	atomic64Val_t value;
	atomic64Val_t* returnVal;
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
	int tid;
	int op;
	};

struct pipeAnonCreateScArgs 
	{
	size_t nMessages;
	size_t nBytes;
	unsigned flags;
	int * pFd;
	};

struct taskDelayExScArgs 
	{
	_Vx_ticks_t ticks;
	UINT32 flags;
	};

#endif	/* _ASMLANGUAGE */
