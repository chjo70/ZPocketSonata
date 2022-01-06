/* statTbl.c - status code symbol table */

/* CREATED BY makeStatTbl
 *       FROM D:/vxWorks7/vxworks-7/pkgs/os/utils/ostools-1.0.3.1/src
 *         ON Mon Nov 22 11:35:25 대한민국 표준시 2021
 */

#include <vxWorks.h>
#include <symbol.h>


#include "rpc/rpctypes.h"
#include "rpc/xdr.h"
#include "nfs/xdr_nfs_common.h"
#include "rpc/auth.h"
#include "rpc/clnt.h"
#include "vwModNum.h"


/* 
 * USB errnos are defined as being part of the USB host Module, as are all
 * vxWorks module numbers, but the USB Module number is further divided into 
 * sub-modules.  Each sub-module has upto 255 values for its own error codes
 */
 
#define USB_OSS_SUB_MODULE	1
#define USB_QUEUE_SUB_MODULE  	2
#define USB_HANDLE_SUB_MODULE	3
#define USB_HCD_SUB_MODULE	4
#define USB_USBD_SUB_MODULE	5
#define USB_KEYBOARD_SUB_MODULE	6
#define USB_PRINTER_SUB_MODULE	7
#define USB_MOUSE_SUB_MODULE	8
#define USB_SPEAKER_SUB_MODULE  9
#define USB_BULK_SUB_MODULE	11
#define USB_CBI_SUB_MODULE	12
#define USB_PEGASUS_SUB_MODULE	14

#define M_usbHandleLib 	( (USB_HANDLE_SUB_MODULE  << 8) | M_usbHostLib )
#define M_ossLib        ( (USB_OSS_SUB_MODULE  << 8) | M_usbHostLib )
#define M_usbQueueLib 	( (USB_QUEUE_SUB_MODULE  << 8) | M_usbHostLib )
#define M_usbdLib 	( (USB_USBD_SUB_MODULE  << 8) | M_usbHostLib )

#define ossErr(x)               (M_ossLib | (x))
#define usbQueueErr(x)		(M_usbQueueLib | (x))
#define hdlErr(x)	        (M_usbHandleLib | (x))
#define usbdErr(x)	        (M_usbdLib | (x))
#define M_usbBulkLib		( (USB_BULK_SUB_MODULE  << 8) | M_usbHostLib )
#define usbBulkErr(x)		(M_usbBulkLib | (x))
#define M_usbCbiUfiLib		( (USB_CBI_SUB_MODULE  << 8) | M_usbHostLib )
#define usbCbiUfiErr(x)		(M_usbCbiUfiLib | (x))
#define M_usbHcdLib		( (USB_HCD_SUB_MODULE  << 8) | M_usbHostLib )
#define hcdErr(x)		(M_usbHcdLib | (x))
#define M_usbKeyboardLib	( (USB_KEYBOARD_SUB_MODULE  << 8) | \
				M_usbHostLib )
#define usbKbdErr(x)		(M_usbKeyboardLib | (x))
#define M_usbMouseLib		( (USB_MOUSE_SUB_MODULE << 8) | M_usbHostLib )
#define usbMseErr(x)		(M_usbMouseLib | (x))
#define M_usbPegasusLib		( (USB_PEGASUS_SUB_MODULE << 8) | M_usbHostLib )
#define usbPegasusErr(x)	(M_usbPegasusLib | (x))
#define M_usbPrinterLib		( ( USB_PRINTER_SUB_MODULE   << 8) | \
				M_usbHostLib )
#define usbPrnErr(x)		(M_usbPrinterLib | (x))
#define M_usbSpeakerLib		( (USB_SPEAKER_SUB_MODULE << 8) | M_usbHostLib )
#define usbSpkrErr(x)		(M_usbSpeakerLib | (x))

#define M_aimcacheLib (190 << 16)
#define M_shellInterpCmdLib	(174 << 16)
#define	S_adrSpaceLib_LIB_NOT_INITIALIZED	(M_adrSpaceLib | 1)
#define	S_adrSpaceLib_CANNOT_REINITIALIZE	(M_adrSpaceLib | 2)
#define	S_adrSpaceLib_PARAMETER_NOT_ALIGNED	(M_adrSpaceLib | 3)
#define	S_adrSpaceLib_REGION_NOT_AVAILABLE	(M_adrSpaceLib | 4)
#define	S_adrSpaceLib_VIRT_ADRS_NOT_ALIGNED	(M_adrSpaceLib | 5)
#define	S_adrSpaceLib_SIZE_IS_INVALID        	(M_adrSpaceLib | 6)
#define	S_adrSpaceLib_INVALID_PARAMETER		(M_adrSpaceLib | 7)
#define	S_adrSpaceLib_VIRTUAL_OVERLAP		(M_adrSpaceLib | 8) 
#define S_adrSpaceLib_PHYSICAL_OVERLAP		(M_adrSpaceLib | 9)
#define S_adrSpaceLib_ADDRESS_OUT_OF_RANGE	(M_adrSpaceLib |10)
#define S_adrSpaceLib_INSUFFICIENT_SPACE_IN_RGN	(M_adrSpaceLib |11)
#define S_adrSpaceLib_REGION_CONFLICT		(M_adrSpaceLib |12)
#define S_adrSpaceLib_MMU_LESS_NONIDENTITY	(M_adrSpaceLib |13)
#define S_adrSpaceLib_NO_PHYS_PAGES		(M_adrSpaceLib |14)
#define S_adrSpaceLib_NO_CONTIG_PHYS_PAGES	(M_adrSpaceLib |15)
#define S_adrSpaceLib_MMU_NOT_ENABLED    	(M_adrSpaceLib |16)
#define	S_adrSpaceLib_INVALID_REGION		(M_adrSpaceLib |17)
#define	S_adrSpaceLib_REGION_NOT_CONFIGURED	(M_adrSpaceLib |18)
#define	S_adrSpaceLib_INVALID_CONTEXT   	(M_adrSpaceLib |19)
#define S_arpLib_INVALID_ARGUMENT		(M_arpLib | 1)
#define S_arpLib_INVALID_HOST 			(M_arpLib | 2)
#define S_arpLib_INVALID_ENET_ADDRESS 		(M_arpLib | 3)
#define S_arpLib_INVALID_FLAG			(M_arpLib | 4)
#define S_bootLoadLib_ROUTINE_NOT_INSTALLED		(M_bootLoadLib | 1)
#define S_cacheLib_INVALID_CACHE	(M_cacheLib | 1)
#define S_cacheLib_UNSUPPORTED 		(M_cacheLib | 2)
#define S_cacheLib_DMA32_RAM_UNSUPPORTED (M_cacheLib | 3)
#define S_cacheLib_QOS_CACHE_LEVEL_ERROR (M_cacheLib | 4)
#define S_cacheLib_QOS_NOT_INITIALIZED   (M_cacheLib | 5)
#define S_cacheLib_QOS_CPUSET_ERROR      (M_cacheLib | 6)
#define S_cacheLib_QOS_OVERALLOCATION    (M_cacheLib | 7)
#define S_cacheLib_QOS_MASK_UNAVAILABLE  (M_cacheLib | 8)
#define S_cacheLib_QOS_NO_FREE_COSID     (M_cacheLib | 9)
#define S_cacheLib_QOS_INVALID_BITMASK   (M_cacheLib | 10)
#define S_cacheLib_QOS_INVALID_COSID     (M_cacheLib | 11)
#define S_cacheLib_QOS_UNSUPPORTED       (M_cacheLib | 12)
#define S_classLib_CLASS_ID_ERROR		(M_classLib | 1)
#define S_classLib_NO_CLASS_DESTROY		(M_classLib | 2)
#define S_condVarLib_INVALID_QUEUE_TYPE		(M_condVarLib | 101)
#define S_condVarLib_INVALID_OPERATION		(M_condVarLib | 102)
#define S_coreDumpLib_CORE_DUMP_HOOK_TABLE_FULL		(M_coreDumpLib | 1)
#define S_coreDumpLib_CORE_DUMP_HOOK_NOT_FOUND		(M_coreDumpLib | 2)
#define S_coreDumpLib_CORE_DUMP_INVALID_DEVICE		(M_coreDumpLib | 3)
#define S_coreDumpLib_CORE_DUMP_DEVICE_READ_ERROR	(M_coreDumpLib | 4)
#define S_coreDumpLib_CORE_DUMP_DEVICE_WRITE_ERROR	(M_coreDumpLib | 5)
#define S_coreDumpLib_CORE_DUMP_DEVICE_ERASE_ERROR	(M_coreDumpLib | 6)
#define S_coreDumpLib_CORE_DUMP_DEVICE_OPEN_ERROR	(M_coreDumpLib | 7)
#define S_coreDumpLib_CORE_DUMP_DEVICE_CLOSE_ERROR	(M_coreDumpLib | 8)
#define S_coreDumpLib_CORE_DUMP_INVALID_ARGS		(M_coreDumpLib | 9)
#define S_coreDumpLib_CORE_DUMP_INVALID_CORE_DUMP	(M_coreDumpLib | 10)
#define S_coreDumpLib_CORE_DUMP_STORAGE_NOT_FORMATED	(M_coreDumpLib | 11)
#define S_coreDumpLib_CORE_DUMP_DEVICE_NOT_INITIALIZED	(M_coreDumpLib | 12)
#define S_coreDumpLib_CORE_DUMP_TOO_MANY_CORE_DUMP	(M_coreDumpLib | 13)
#define S_coreDumpLib_CORE_DUMP_COMPRESSION_ERROR	(M_coreDumpLib | 14)
#define S_coreDumpLib_CORE_DUMP_FILTER_TABLE_FULL	(M_coreDumpLib | 15)
#define S_coreDumpLib_CORE_DUMP_GENERATE_ALREADY_RUNNING (M_coreDumpLib | 16)
#define S_coreDumpLib_CORE_DUMP_PATH_TOO_LONG		(M_coreDumpLib | 17)
#define S_coreDumpLib_CORE_DUMP_GENERATE_NOT_RUNNING	(M_coreDumpLib | 18)
#define S_coreDumpLib_CORE_DUMP_DEVICE_TOO_SMALL	(M_coreDumpLib | 19)
#define S_coreDumpLib_CORE_DUMP_FILTER_NOT_FOUND	(M_coreDumpLib | 20)
#define S_coreDumpLib_CORE_DUMP_CKSUM_VERIFY_ERROR	(M_coreDumpLib | 21)
#define S_coreDumpLib_CORE_DUMP_VARIABLES_CORRUPTED	(M_coreDumpLib | 22)
#define S_coreDumpLib_CORE_DUMP_STREAM_DEV_ALREADY_INITIALIZED (M_coreDumpLib | 23)
#define S_coreDumpLib_CORE_DUMP_RAW_DEV_ALREADY_INITIALIZED (M_coreDumpLib | 24)
#define S_coreDumpLib_TASK_HOOK_ALREADY_INSTALLED       (M_coreDumpLib | 25)
#define S_coreDumpLib_INVALID_TASK_HOOK                 (M_coreDumpLib | 26)
#define S_coreDumpLib_COPY_HOOK_ALREADY_INSTALLED       (M_coreDumpLib | 27)
#define S_coreDumpLib_INVALID_COPY_HOOK                 (M_coreDumpLib | 28)
#define S_coreDumpLib_MODULE_HOOK_ALREADY_INSTALLED     (M_coreDumpLib | 29)
#define S_coreDumpLib_INVALID_MODULE_HOOK               (M_coreDumpLib | 30)
#define S_devMemLib_PHYS_ADDR_OUT_OF_RANGE (M_devMemLib | 1)
#define S_devMemLib_PHYS_ADDR_NOT_ALIGNED  (M_devMemLib | 2)
#define S_devMemLib_INVALID_SIZE           (M_devMemLib | 3)
#define S_devMemLib_INVALID_MMU_ATTR       (M_devMemLib | 4)
#define S_erfLib_INVALID_PARAMETER      (M_erfLib | 0x0001)
#define S_erfLib_MEMORY_ERROR           (M_erfLib | 0x0002)
#define S_erfLib_INIT_ERROR             (M_erfLib | 0x0003)
#define S_erfLib_TOO_MANY_USER_CATS     (M_erfLib | 0x0004)
#define S_erfLib_TOO_MANY_USER_TYPES    (M_erfLib | 0x0005)
#define S_erfLib_HANDLER_NOT_FOUND      (M_erfLib | 0x0006)
#define S_erfLib_QUEUE_EMPTY            (M_erfLib | 0x0007)
#define S_erfLib_QUEUE_FULL             (M_erfLib | 0x0008)
#define S_erfLib_QUEUE_ALREADY_CREATED  (M_erfLib | 0x0009)
#define S_erfLib_AUTO_UNREG_ERROR       (M_erfLib | 0x000A)
#define S_dsmLib_UNKNOWN_INSTRUCTION    (M_dsmLib | 1)
#define S_edrLib_NOT_INITIALIZED	(M_edrLib | 1)
#define S_edrLib_ERRLOG_CORRUPTED	(M_edrLib | 2)
#define S_edrLib_ERRLOG_INCOMPATIBLE	(M_edrLib | 3)
#define S_edrLib_PROTECTION_FAILURE	(M_edrLib | 4)
#define S_edrLib_PMREGION_ERROR		(M_edrLib | 5)
#define S_edrLib_INJECT_HOOK_TABLE_FULL	(M_edrLib | 7)
#define S_edrLib_INJECT_HOOK_NOT_FOUND	(M_edrLib | 8)
#define S_edrLib_TEXT_HOOK_TABLE_FULL	(M_edrLib | 9)
#define S_edrLib_TEXT_HOOK_NOT_FOUND	(M_edrLib | 10)
#define S_edrLib_PP_HOOK_TABLE_FULL	(M_edrLib | 11)
#define S_edrLib_PP_HOOK_NOT_FOUND	(M_edrLib | 12)
#define S_edrLib_INVALID_OPTION		(M_edrLib | 6)
#define S_errnoLib_NO_STAT_SYM_TBL      (M_errnoLib | 1)
#define S_eventLib_TIMEOUT			(M_eventLib | 0x0001)
#define S_eventLib_NOT_ALL_EVENTS		(M_eventLib | 0x0002)
#define S_eventLib_ALREADY_REGISTERED		(M_eventLib | 0x0003)
#define S_eventLib_EVENTSEND_FAILED		(M_eventLib | 0x0004)
#define S_eventLib_ZERO_EVENTS			(M_eventLib | 0x0005)
#define S_eventLib_TASK_NOT_REGISTERED		(M_eventLib | 0x0006)
#define S_eventLib_NULL_TASKID_AT_INT_LEVEL	(M_eventLib | 0x0007)
#define	S_excLib_EXCEPTION_STACK_OVERFLOW	(M_excLib | 1)
#define	S_excLib_INTERRUPT_STACK_OVERFLOW	(M_excLib | 2)
#define S_fsimLib_EBASE         1000
#define S_fsimLib_EPARAM        (S_fsimLib_EBASE + 1)   /* invalid parameter */
#define S_fsimLib_EMEM          (S_fsimLib_EBASE + 2)   /* memory error */
#define S_fsimLib_EIO           (S_fsimLib_EBASE + 3)   /* IO error */
#define S_fsimLib_EREBOOT       (S_fsimLib_EBASE + 4)   /* system reboot */
#define S_fsimLib_EBADBLOCK     (S_fsimLib_EBASE + 5)   /* bad block */
#define S_fsimLib_ECHIP         (S_fsimLib_EBASE + 6)   /* chip error */
#define S_fsimLib_ENOTRUNNING   (S_fsimLib_EBASE + 7)   /* fsim not running */
#define S_fsimLib_ENOTSTARTED   (S_fsimLib_EBASE + 8)   /* fsim not started */
#define S_fsimLib_EDEV          (S_fsimLib_EBASE + 9)   /* fsim device error */
#define S_fsimLib_EECC_REC      (S_fsimLib_EBASE + 10)  /* ecc recoverable error */
#define S_fsimLib_EECC_NOTREC   (S_fsimLib_EBASE + 11)  /* ecc unrecoverable error */
#define S_fsimLib_EECC_NOTREC_FAKE (S_fsimLib_EBASE + 12)  /* fake ecc unrecoverable error */
#define S_fsimLib_ENOTREC       (S_fsimLib_EBASE + 13)  /* unrecoverable error page */
#define S_fsimLib_EID           (S_fsimLib_EBASE + 14)  /* invalid id */
#define S_ftlLib_INVALID_PARAM          (M_ftlLib | 1)
#define S_ftlLib_NO_DEV                 (M_ftlLib | 2)
#define S_ftlLib_DEV_TOO_SMALL          (M_ftlLib | 3)
#define S_ftlLib_NO_VALID_FTL_ID        (M_ftlLib | 4)
#define S_ftlLib_NO_VALID_BBMT          (M_ftlLib | 5)
#define S_ftlLib_DATA_ERROR_ECC_UNRECV  (M_ftlLib | 6)
#define S_ftlLib_BAD_BLOCK_MAP          (M_ftlLib | 7)
#define S_ftlLib_BAD_PAGE_MAP           (M_ftlLib | 8)
#define S_ftlLib_NO_FREE_REPL_BLK       (M_ftlLib | 9)
#define S_ftpLib_ILLEGAL_VALUE                  (M_ftpLib | 1)
#define S_ftpLib_TRANSIENT_RETRY_LIMIT_EXCEEDED (M_ftpLib | 2)
#define S_ftpLib_FATAL_TRANSIENT_RESPONSE       (M_ftpLib | 3)
#define S_ftpLib_REMOTE_SERVER_STATUS_221       (M_ftpLib | 221)
#define S_ftpLib_REMOTE_SERVER_STATUS_226       (M_ftpLib | 226)
#define S_ftpLib_REMOTE_SERVER_STATUS_257       (M_ftpLib | 257)
#define S_ftpLib_REMOTE_SERVER_ERROR_422        (M_ftpLib | 422)
#define S_ftpLib_REMOTE_SERVER_ERROR_425        (M_ftpLib | 425)
#define S_ftpLib_REMOTE_SERVER_ERROR_450        (M_ftpLib | 450)
#define S_ftpLib_REMOTE_SERVER_ERROR_451        (M_ftpLib | 451)
#define S_ftpLib_REMOTE_SERVER_ERROR_452        (M_ftpLib | 452)
#define S_ftpLib_REMOTE_SERVER_ERROR_500        (M_ftpLib | 500)
#define S_ftpLib_REMOTE_SERVER_ERROR_501        (M_ftpLib | 501)
#define S_ftpLib_REMOTE_SERVER_ERROR_502        (M_ftpLib | 502)
#define S_ftpLib_REMOTE_SERVER_ERROR_503        (M_ftpLib | 503)
#define S_ftpLib_REMOTE_SERVER_ERROR_504        (M_ftpLib | 504)
#define S_ftpLib_REMOTE_SERVER_ERROR_520        (M_ftpLib | 520)
#define S_ftpLib_REMOTE_SERVER_ERROR_521        (M_ftpLib | 521)
#define S_ftpLib_REMOTE_SERVER_ERROR_530        (M_ftpLib | 530)
#define S_ftpLib_REMOTE_SERVER_ERROR_550        (M_ftpLib | 550)
#define S_ftpLib_REMOTE_SERVER_ERROR_551        (M_ftpLib | 551)
#define S_ftpLib_REMOTE_SERVER_ERROR_552        (M_ftpLib | 552)
#define S_ftpLib_REMOTE_SERVER_ERROR_553        (M_ftpLib | 553)
#define S_ftpLib_REMOTE_SERVER_ERROR_554        (M_ftpLib | 554)
#define S_hashLib_KEY_CLASH		(M_hashLib | 1)
#define S_hookLib_HOOK_TABLE_FULL   (M_hookLib | 1)
#define S_hookLib_HOOK_NOT_FOUND    (M_hookLib | 2)
#define S_hookLib_HOOK_TABLE_NULL   (M_hookLib | 3)
#define S_hostLib_UNKNOWN_HOST			(M_hostLib | 1)
#define S_hostLib_HOST_ALREADY_ENTERED		(M_hostLib | 2)
#define S_hostLib_INVALID_PARAMETER             (M_hostLib | 3)
#define S_hostLib_NETDB_INTERNAL                (M_hostLib | 4)  /* see errno */
#define S_hostLib_HOST_NOT_FOUND                (M_hostLib | 5)
#define S_hostLib_TRY_AGAIN                     (M_hostLib | 6)
#define S_hostLib_NO_RECOVERY                   (M_hostLib | 7)
#define S_inetLib_ILLEGAL_INTERNET_ADDRESS		(M_inetLib | 1)
#define S_inetLib_ILLEGAL_NETWORK_NUMBER		(M_inetLib | 2)
#define S_intLib_NOT_ISR_CALLABLE		(M_intLib | 1)
#define S_intLib_VEC_TABLE_WP_UNAVAILABLE	(M_intLib | 2)
#define S_ioLib_MEDIA_CHANGED           (M_ioLib | 1)
#define S_ipcom_ERR_FAILED              (M_ipcom | (0xffff & -1000))
#define S_ipcom_ERR_NO_MEMORY           (M_ipcom | (0xffff & -1010))
#define S_ipcom_ERR_NOT_FOUND           (M_ipcom | (0xffff & -1011))
#define S_ipcom_ERR_NOT_SUPPORTED       (M_ipcom | (0xffff & -1012))
#define S_ipcom_ERR_PERMISSION_DENIED   (M_ipcom | (0xffff & -1013))
#define S_ipcom_ERR_ALREADY_OPEN        (M_ipcom | (0xffff & -1040))
#define S_ipcom_ERR_ALREADY_CLOSED      (M_ipcom | (0xffff & -1041))
#define S_ipcom_ERR_ALREADY_INSTALLED   (M_ipcom | (0xffff & -1042))
#define S_ipcom_ERR_ALREADY_STARTED     (M_ipcom | (0xffff & -1043))
#define S_ipcom_ERR_NOT_OPENED          (M_ipcom | (0xffff & -1050))
#define S_ipcom_ERR_NOT_CLOSED          (M_ipcom | (0xffff & -1051))
#define S_ipcom_ERR_NOT_INSTALLED       (M_ipcom | (0xffff & -1052))
#define S_ipcom_ERR_NOT_STARTED         (M_ipcom | (0xffff & -1053))
#define S_ipcom_ERR_INVALID_ARG         (M_ipcom | (0xffff & -1060))
#define S_ipcom_ERR_INVALID_CONFIG      (M_ipcom | (0xffff & -1061))
#define S_ipcom_ERR_INVALID_VERSION     (M_ipcom | (0xffff & -1062))
#define S_ipcom_ERR_INVALID_ALIGNMENT   (M_ipcom | (0xffff & -1063))
#define S_ipcom_ERR_INVALID_INTERFACE   (M_ipcom | (0xffff & -1064))
#define S_ipcom_ERR_NO_ROUTE            (M_ipcom | (0xffff & -1070))
#define S_ipcom_ERR_DEAD_ROUTE          (M_ipcom | (0xffff & -1071))
#define S_ipcom_ERR_INVALID_ROUTE       (M_ipcom | (0xffff & -1072))
#define S_ipcom_ERR_INVALID_MASK        (M_ipcom | (0xffff & -1073))
#define S_ipcom_ERR_INVALID_RTCLIENT    (M_ipcom | (0xffff & -1074))
#define S_ipcom_ERR_DUPLICATE           (M_ipcom | (0xffff & -1080))
#define S_ipcom_ERR_LOCKED              (M_ipcom | (0xffff & -1081))
#define S_ipcom_ERR_END                 (M_ipcom | (0xffff & -1082))
#define S_ipcom_ERR_READONLY            (M_ipcom | (0xffff & -1083))
#define S_ipcom_ERR_INVALID_TAG_VALUE   (M_ipcom | (0xffff & -1090))
#define S_ipcom_ERR_UNSUPPORTED_TAG     (M_ipcom | (0xffff & -1091))
#define S_ipcom_ERR_INVALID_PACKET      (M_ipcom | (0xffff & -1100))
#define S_ipcom_ERR_BAD_PACKET          (M_ipcom | (0xffff & -1101))
#define S_ipcom_ERR_IGNORED_PACKET      (M_ipcom | (0xffff & -1102))
#define S_ipcom_ERR_SOCKCALLFAILED      (M_ipcom | (0xffff & -1110))
#define S_ipcom_ERR_REACHED_MIN         (M_ipcom | (0xffff & -1111))
#define S_ipcom_ERR_REACHED_MAX         (M_ipcom | (0xffff & -1112))
#define S_ipcom_ERR_TIMEOUT             (M_ipcom | (0xffff & -1120))
#define S_ipcom_ERR_WOULDBLOCK          (M_ipcom | (0xffff & -1121))
#define S_ipcom_ERR_INTERRUPT           (M_ipcom | (0xffff & -1122))
#define S_ipcom_ERR_PENDING             (M_ipcom | (0xffff & -1123))
#define S_ipcom_ERR_AUTH_FAILED         (M_ipcom | (0xffff & -1130))
#define S_ipcom_ERR_AUTH_UNKNOWN        (M_ipcom | (0xffff & -1131))
#define S_ipcom_ENOMEDIUM           (M_ipcom | 123)
#define S_ipcom_EMEDIUMTYPE         (M_ipcom | 124)
#define S_ipcom_ENODATA             (M_ipcom | 200)
#define S_ipcom_ECOMM               (M_ipcom | 201)
#define S_ipcom_EINTERNAL	    (M_ipcom | 1000)
#define S_ipcom_ENOSUPPORT          (M_ipcom | 1001)
#define S_ipcom_EINITFAILED         (M_ipcom | 1002)
#define S_ipcom_ECONFIG             (M_ipcom | 1003)
#define S_ipcom_ENOTOME             (M_ipcom | 1004)
#define S_ipcom_ENOTFOUND           (M_ipcom | 1005)
#define S_ipcom_EFIREWALL           (M_ipcom | 1006)
#define S_isrLib_ISR_NOT_INIT			(M_isrLib | 1)
#define S_isrLib_INVALID_PARAM			(M_isrLib | 2)
#define S_loadElfLib_HDR_READ		    (M_loadElfLib | 1)
#define S_loadElfLib_HDR_ERROR		    (M_loadElfLib | 2)
#define S_loadElfLib_PHDR_MALLOC	    (M_loadElfLib | 3)  /* obsoleted */
#define S_loadElfLib_PHDR_READ		    (M_loadElfLib | 4)  /* obsoleted */
#define S_loadElfLib_SHDR_MALLOC	    (M_loadElfLib | 5)  /* obsoleted */
#define S_loadElfLib_SHDR_READ		    (M_loadElfLib | 6)
#define S_loadElfLib_READ_SECTIONS	    (M_loadElfLib | 7)
#define S_loadElfLib_LOAD_SECTIONS	    (M_loadElfLib | 8)  /* obsoleted */
#define S_loadElfLib_LOAD_PROG		    (M_loadElfLib | 9)  /* obsoleted */
#define S_loadElfLib_SYMTAB		    (M_loadElfLib | 10) /* obsoleted */
#define S_loadElfLib_RELA_SECTION	    (M_loadElfLib | 11)
#define S_loadElfLib_SCN_READ		    (M_loadElfLib | 12) /* obsoleted */
#define S_loadElfLib_SDA_MALLOC		    (M_loadElfLib | 13) /* obsoleted */
#define S_loadElfLib_SST_READ		    (M_loadElfLib | 15) /* obsoleted */
#define S_loadElfLib_JMPADDR_ERROR	    (M_loadElfLib | 20) /* obsoleted */
#define S_loadElfLib_GPREL_REFERENCE	    (M_loadElfLib | 21) /* obsoleted */
#define S_loadElfLib_UNRECOGNIZED_RELOCENTRY	(M_loadElfLib | 22)
#define S_loadElfLib_RELOC		    (M_loadElfLib | 23)
#define S_loadElfLib_UNSUPPORTED	    (M_loadElfLib | 24)
#define S_loadElfLib_REL_SECTION	    (M_loadElfLib | 25)
#define S_loadElfLib_INVALID_ARGUMENT		    (M_loadElfLib | 27)
#define S_loadElfLib_RELOCATION_OFFSET_TOO_LARGE    (M_loadElfLib | 28)
#define S_loadElfLib_RELOCATION_UNIT_NOT_INSTALLED  (M_loadElfLib | 29)
#define S_loadElfLib_SIG_SECTION_ERROR             (M_loadElfLib | 30)
#define S_loadElfLib_SIG_KEY_INVALID               (M_loadElfLib | 31)
#define S_loadLib_ROUTINE_NOT_INSTALLED		(M_loadLib | 1)
#define S_loadLib_TOO_MANY_SYMBOLS		(M_loadLib | 2) /* obsoleted */
#define S_loadLib_ILLEGAL_FLAGS_COMBINATION	(M_loadLib | 3)
#define S_loadLib_INVALID_ARGUMENT	        (M_loadLib | 4)
#define S_loadLib_UNDEFINED_REFERENCES		(M_loadLib | 5)
#define S_loadLib_UNSPECIFIED_SEGMENT_ADDRESS	(M_loadLib | 6)
#define S_loadLib_INVALID_LOAD_FLAG		(M_loadLib | 7)
#define S_loadLib_SDA_NOT_SUPPORTED		(M_loadLib | 8)
#define S_loadLib_MISSING_SYMBOL_TABLE		(M_loadLib | 9)
#define S_loadLib_ABI_MISMATCH			(M_loadLib | 10)
#define S_loadLib_ISA_MISMATCH			(M_loadLib | 11)
#define S_loadLib_INCOMPATIBLE_MODULE		(M_loadLib | 12)
#define S_loadLib_USR_INIT_ERROR		(M_loadLib | 13)
#define S_loadLib_ALREADY_LOADED		(M_loadLib | 14)
#define S_m2Lib_INVALID_PARAMETER               (M_m2Lib | 1)
#define S_m2Lib_ENTRY_NOT_FOUND			(M_m2Lib | 2)
#define S_m2Lib_TCPCONN_FD_NOT_FOUND		(M_m2Lib | 3)
#define S_m2Lib_INVALID_VAR_TO_SET		(M_m2Lib | 4)
#define S_m2Lib_CANT_CREATE_SYS_SEM		(M_m2Lib | 5)
#define S_m2Lib_CANT_CREATE_IF_SEM		(M_m2Lib | 6)
#define S_m2Lib_CANT_CREATE_ROUTE_SEM		(M_m2Lib | 7)
#define S_m2Lib_ARP_PHYSADDR_NOT_SPECIFIED	(M_m2Lib | 8)
#define S_m2Lib_IF_TBL_IS_EMPTY			(M_m2Lib | 9)
#define S_m2Lib_IF_CNFG_CHANGED			(M_m2Lib | 10)
#define S_m2Lib_TOO_BIG                         (M_m2Lib | 11)
#define S_m2Lib_BAD_VALUE                       (M_m2Lib | 12)
#define S_m2Lib_READ_ONLY                       (M_m2Lib | 13)
#define S_m2Lib_GEN_ERR                         (M_m2Lib | 14)
#define S_memLib_INVALID_NBYTES			(M_memLib | 2)
#define S_memLib_BLOCK_ERROR			(M_memLib | 3)
#define S_memLib_NO_PARTITION_DESTROY		(M_memLib | 4)
#define S_memLib_PAGE_SIZE_UNAVAILABLE		(M_memLib | 5)
#define S_memLib_WRONG_PART_ID			(M_memLib | 6)
#define S_memLib_INVALID_ADDRESS		(M_memLib | 7)
#define S_memLib_INVALID_ALIGNMENT		(M_memLib | 8)
#define S_memLib_FUNC_NOT_AVAILABLE		(M_memLib | 9)
#define S_memLib_MEM_ALLOC_ERROR_NO_ALLOC_SET   (M_memLib | 10)
#define S_memLib_RTP_MEM_ALLOC_ERROR_NO_ALLOC_SET   (M_memLib | 11)
#define S_memLib_RTP_MEM_FREE_ERROR_NO_ALLOC_SET    (M_memLib | 12)
#define S_miiLib_PHY_LINK_DOWN			(M_miiLib | 1)
#define S_miiLib_PHY_NULL		        (M_miiLib | 2)
#define S_miiLib_PHY_NO_ABLE             	(M_miiLib | 3)
#define S_miiLib_PHY_AN_FAIL             	(M_miiLib | 4)
#define	S_mmuLib_INVALID_PAGE_SIZE		(M_mmuLib | 1)
#define	S_mmuLib_NO_DESCRIPTOR			(M_mmuLib | 2)
#define	S_mmuLib_INVALID_DESCRIPTOR		(M_mmuLib | 3)
#define	S_mmuLib_OUT_OF_PMEGS			(M_mmuLib | 5)
#define	S_mmuLib_VIRT_ADDR_OUT_OF_BOUNDS	(M_mmuLib | 6)
#define	S_mmuLib_TLB_LOCKED_PAGE		(M_mmuLib | 7)
#define	S_mmuLib_TLB_PAGE_NOT_LOCKED		(M_mmuLib | 8)
#define S_mmuLib_LOCK_NO_MORE_TLB_RESOURCES     (M_mmuLib | 9)
#define S_mmuLib_NOT_CONTIGUOUS_ADDR            (M_mmuLib | 10)
#define S_mmuLib_NOT_CONTIGUOUS_STATE           (M_mmuLib | 11)
#define	S_mmuLib_ISR_CALL_BLOCKED		(M_mmuLib | 12)
#define S_mmuLib_MARKED_ISR_CALLABLE            (M_mmuLib | 13)
#define S_mmuLib_NOT_GLOBAL_PAGE                (M_mmuLib | 15)
#define S_mmulib_LOCK_REQUIRED			(M_mmuLib | 16)
#define S_mmulib_INVALID_PHYS_ADDR		(M_mmuLib | 17)
#define S_mmulib_VIRT_ADDR_ALREADY_MAPPED	(M_mmuLib | 18)
#define S_mmuLib_INVALID_UNION_INIT		(M_mmuLib | 19)
#define S_mmuLib_INVALID_ATTR			(M_mmuLib | 20)
#define S_mmuLib_INVALID_GLOBAL_PAGE_OP		(M_mmuLib | 21)
#define S_moduleLib_MODULE_NOT_FOUND		(M_moduleLib | 1)
#define S_moduleLib_HOOK_NOT_FOUND              (M_moduleLib | 2)
#define S_moduleLib_BAD_CHECKSUM                (M_moduleLib | 3)
#define S_moduleLib_MAX_MODULES_LOADED          (M_moduleLib | 4)
#define S_moduleLib_INVALID_SECTION_ID          (M_moduleLib | 5)
#define S_moduleLib_INVALID_MODULE_ID		(M_moduleLib | 6)
#define S_msgQLib_INVALID_MSG_LENGTH		(M_msgQLib | 1)
#define S_msgQLib_NON_ZERO_TIMEOUT_AT_INT_LEVEL	(M_msgQLib | 2)
#define S_msgQLib_INVALID_QUEUE_TYPE		(M_msgQLib | 3)
#define S_msgQLib_ILLEGAL_OPTIONS		(M_msgQLib | 4)
#define S_msgQLib_ILLEGAL_PRIORITY		(M_msgQLib | 5)
#define S_msgQLib_UNSUPPORTED_OPERATION		(M_msgQLib | 6)
#define S_msgQLib_INVALID_MSG_COUNT	        (M_msgQLib | 7)
#define S_muxLib_LOAD_FAILED                  (M_muxLib | 1)
#define S_muxLib_NO_DEVICE                    (M_muxLib | 2)
#define S_muxLib_INVALID_ARGS                 (M_muxLib | 3)
#define S_muxLib_ALLOC_FAILED                 (M_muxLib | 4)
#define S_muxLib_ALREADY_BOUND                (M_muxLib | 5)
#define S_muxLib_UNLOAD_FAILED                (M_muxLib | 6)
#define S_muxLib_NOT_A_TK_DEVICE              (M_muxLib | 7)
#define S_muxLib_NO_TK_DEVICE                 (M_muxLib | 8)
#define S_muxLib_END_BIND_FAILED              (M_muxLib | 9)
#define S_muxLib_MISSING_WRAPPERS             (M_muxLib | 10)
#define S_muxLib_END_SUSPEND_FAILED           (M_muxLib | 11)
#define S_muxLib_NO_LAUNCH_CAPABILITY         (M_muxLib | 12)
#define S_muxLib_LAUNCH_OVERFLOW              (M_muxLib | 13)
#define S_muxLib_LAUNCH_MISSED                (M_muxLib | 14)
#define S_muxLib_LAUNCH_SETUP_FAILED          (M_muxLib | 15)
#define	S_netBufLib_MEMSIZE_INVALID		(M_netBufLib | 1)
#define	S_netBufLib_CLSIZE_INVALID		(M_netBufLib | 2)
#define	S_netBufLib_NO_SYSTEM_MEMORY		(M_netBufLib | 3)
#define	S_netBufLib_MEM_UNALIGNED		(M_netBufLib | 4)
#define	S_netBufLib_MEMSIZE_UNALIGNED		(M_netBufLib | 5)
#define	S_netBufLib_MEMAREA_INVALID		(M_netBufLib | 6)
#define S_netBufLib_MBLK_INVALID		(M_netBufLib | 7)
#define S_netBufLib_NETPOOL_INVALID		(M_netBufLib | 8)
#define S_netBufLib_INVALID_ARGUMENT		(M_netBufLib | 9)
#define S_netBufLib_NO_POOL_MEMORY		(M_netBufLib | 10)
#define S_netBufLib_LIB_NOT_INITIALIZED		(M_netBufLib | 11)
#define S_netBufLib_POOL_FEATURE_NOT_SUPPORTED	(M_netBufLib | 12)
#define S_netBufLib_DUPLICATE_POOL 		(M_netBufLib | 13)
#define S_netBufLib_POOL_RELEASED 		(M_netBufLib | 14)
#define S_netBufLib_POOL_RELEASE_IGNORE		(M_netBufLib | 15)
#define S_netDrv_INVALID_NUMBER_OF_BYTES	(M_netDrv | 1)
#define S_netDrv_SEND_ERROR			(M_netDrv | 2)
#define S_netDrv_RECV_ERROR			(M_netDrv | 3)
#define S_netDrv_UNKNOWN_REQUEST		(M_netDrv | 4)
#define S_netDrv_BAD_SEEK			(M_netDrv | 5)
#define S_netDrv_SEEK_PAST_EOF_ERROR		(M_netDrv | 6)
#define S_netDrv_BAD_EOF_POSITION		(M_netDrv | 7)
#define S_netDrv_SEEK_FATAL_ERROR		(M_netDrv | 8)
#define	S_netDrv_WRITE_ONLY_CANNOT_READ		(M_netDrv | 9)
#define	S_netDrv_READ_ONLY_CANNOT_WRITE		(M_netDrv | 10)
#define	S_netDrv_READ_ERROR			(M_netDrv | 11)
#define S_netDrv_WRITE_ERROR			(M_netDrv | 12)
#define S_netDrv_NO_SUCH_FILE_OR_DIR		(M_netDrv | 13)
#define S_netDrv_PERMISSION_DENIED		(M_netDrv | 14)
#define S_netDrv_IS_A_DIRECTORY			(M_netDrv | 15)
#define S_netDrv_UNIX_FILE_ERROR		(M_netDrv | 16)
#define S_netDrv_ILLEGAL_VALUE			(M_netDrv | 17)
#define S_mountLib_ILLEGAL_MODE             (M_mountLib | 1)
#define S_nfsLib_NFS_AUTH_UNIX_FAILED           (M_nfsLib | 1)
#define S_nfsLib_NFS_INAPPLICABLE_FILE_TYPE     (M_nfsLib | 2)
#define S_nfsLib_NFS_OK                 (M_nfsStat | (int) NFS_OK)
#define S_nfsLib_NFSERR_PERM            (M_nfsStat | (int) NFSERR_PERM)
#define S_nfsLib_NFSERR_NOENT           (M_nfsStat | (int) NFSERR_NOENT)
#define S_nfsLib_NFSERR_IO              (M_nfsStat | (int) NFSERR_IO)
#define S_nfsLib_NFSERR_NXIO            (M_nfsStat | (int) NFSERR_NXIO)
#define S_nfsLib_NFSERR_ACCESS          (M_nfsStat | (int) NFSERR_ACCESS)
#define S_nfsLib_NFSERR_EXIST           (M_nfsStat | (int) NFSERR_EXIST)
#define S_nfsLib_NFSERR_NODEV           (M_nfsStat | (int) NFSERR_NODEV)
#define S_nfsLib_NFSERR_NOTDIR          (M_nfsStat | (int) NFSERR_NOTDIR)
#define S_nfsLib_NFSERR_ISDIR           (M_nfsStat | (int) NFSERR_ISDIR)
#define S_nfsLib_NFSERR_INVAL           (M_nfsStat | (int) NFSERR_INVAL)
#define S_nfsLib_NFSERR_FBIG            (M_nfsStat | (int) NFSERR_FBIG)
#define S_nfsLib_NFSERR_NOSPC           (M_nfsStat | (int) NFSERR_NOSPC)
#define S_nfsLib_NFSERR_ROFS            (M_nfsStat | (int) NFSERR_ROFS)
#define S_nfsLib_NFSERR_NAMETOOLONG     (M_nfsStat | (int) NFSERR_NAMETOOLONG)
#define S_nfsLib_NFSERR_NOTEMPTY        (M_nfsStat | (int) NFSERR_NOTEMPTY)
#define S_nfsLib_NFSERR_DQUOT           (M_nfsStat | (int) NFSERR_DQUOT)
#define S_nfsLib_NFSERR_STALE           (M_nfsStat | (int) NFSERR_STALE)
#define S_nfsLib_NFSERR_WFLUSH          (M_nfsStat | (int) NFSERR_WFLUSH)
#define S_nfsLib_NFSERR_REMOTE          (M_nfsStat | (int) NFSERR_REMOTE)
#define S_nfsLib_NFSERR_BADHANDLE       (M_nfsStat | (int) NFSERR_BADHANDLE)
#define S_nfsLib_NFSERR_NOT_SYNC        (M_nfsStat | (int) NFSERR_NOT_SYNC)
#define S_nfsLib_NFSERR_BAD_COOKIE      (M_nfsStat | (int) NFSERR_BAD_COOKIE)
#define S_nfsLib_NFSERR_NOTSUPP         (M_nfsStat | (int) NFSERR_NOTSUPP)
#define S_nfsLib_NFSERR_TOOSMALL        (M_nfsStat | (int) NFSERR_TOOSMALL)
#define S_nfsLib_NFSERR_SERVERFAULT     (M_nfsStat | (int) NFSERR_SERVERFAULT)
#define S_nfsLib_NFSERR_BADTYPE         (M_nfsStat | (int) NFSERR_BADTYPE)
#define S_nfsLib_NFSERR_JUKEBOX         (M_nfsStat | (int) NFSERR_JUKEBOX)
#define  S_nfsDrv_INVALID_NUMBER_OF_BYTES	      (M_nfsDrv | 1)
#define  S_nfsDrv_BAD_FLAG_MODE			         (M_nfsDrv | 2)
#define  S_nfsDrv_CREATE_NO_FILE_NAME		      (M_nfsDrv | 3)
#define	S_nfsDrv_FATAL_ERR_FLUSH_INVALID_CACHE	(M_nfsDrv | 4)
#define	S_nfsDrv_WRITE_ONLY_CANNOT_READ		   (M_nfsDrv | 5)
#define	S_nfsDrv_READ_ONLY_CANNOT_WRITE		   (M_nfsDrv | 6)
#define	S_nfsDrv_NOT_AN_NFS_DEVICE		         (M_nfsDrv | 7)
#define	S_nfsDrv_NO_HOST_NAME_SPECIFIED		   (M_nfsDrv | 8)
#define	S_nfsDrv_PERMISSION_DENIED		         (M_nfsDrv | 9)
#define	S_nfsDrv_NO_SUCH_FILE_OR_DIR		      (M_nfsDrv | 10)
#define	S_nfsDrv_IS_A_DIRECTORY			         (M_nfsDrv | 11)
#define S_objLib_OBJ_ID_ERROR                   (M_objLib _WRS_BIT_OR 1)
#define S_objLib_OBJ_UNAVAILABLE                (M_objLib _WRS_BIT_OR 2)
#define S_objLib_OBJ_DELETED                    (M_objLib _WRS_BIT_OR 3)
#define S_objLib_OBJ_TIMEOUT                    (M_objLib _WRS_BIT_OR 4)
#define S_objLib_OBJ_NO_METHOD                  (M_objLib _WRS_BIT_OR 5)
#define S_objLib_OBJ_NO_ACCESS_RIGHTS           (M_objLib _WRS_BIT_OR 6)
#define S_objLib_OBJ_NAME_TRUNCATED             (M_objLib _WRS_BIT_OR 7)
#define S_objLib_OBJ_NAME_CLASH                 (M_objLib _WRS_BIT_OR 8)
#define S_objLib_OBJ_NOT_NAMED                  (M_objLib _WRS_BIT_OR 9)
#define S_objLib_OBJ_ILLEGAL_CLASS_TYPE         (M_objLib _WRS_BIT_OR 10)
#define S_objLib_OBJ_OPERATION_UNSUPPORTED      (M_objLib _WRS_BIT_OR 11)
#define S_objLib_OBJ_INVALID_OWNER              (M_objLib _WRS_BIT_OR 12)
#define S_objLib_OBJ_RENAME_NOT_ALLOWED         (M_objLib _WRS_BIT_OR 13)
#define S_objLib_OBJ_DESTROY_ERROR              (M_objLib _WRS_BIT_OR 14)
#define S_objLib_OBJ_HANDLE_TBL_FULL            (M_objLib _WRS_BIT_OR 15)
#define S_objLib_OBJ_NOT_FOUND                  (M_objLib _WRS_BIT_OR 16)
#define S_objLib_OBJ_INVALID_ARGUMENT           (M_objLib _WRS_BIT_OR 17)
#define S_objLib_OBJ_LIB_NOT_INITIALIZED        (M_objLib _WRS_BIT_OR 18)
#define S_objLib_ACCESS_DENIED                  (M_objLib _WRS_BIT_OR 19)
#define S_pingLib_NOT_INITIALIZED               (M_pingLib | 1)
#define S_pingLib_TIMEOUT                       (M_pingLib | 2)
#define S_poolLib_ARG_NOT_VALID		(M_poolLib | 1) /* invalid input arg */
#define S_poolLib_INVALID_POOL_ID	(M_poolLib | 2) /* invalid pool ID */
#define S_poolLib_NOT_POOL_ITEM		(M_poolLib | 3) /* unrecognized item */
#define S_poolLib_UNUSED_ITEM		(M_poolLib | 4) /* unused item */
#define S_poolLib_POOL_IN_USE		(M_poolLib | 5) /* can't delete pool */
#define S_poolLib_STATIC_POOL_EMPTY	(M_poolLib | 6) /* empty static pool */
#define S_poolLib_INVALID_BLK_ADDR	(M_poolLib | 7) /* invalid block addr */
#define S_poolLib_BLOCK_TOO_SMALL	(M_poolLib | 8) /* block too small */
#define S_poolLib_INT_CTX_POOL_EMPTY	(M_poolLib | 9) /* pool empty in ISR */
#define S_coprocLib_ALLOC_FAILED                  (M_coprocLib | 1)
#define S_coprocLib_COPROC_ENABLE_FAILED          (M_coprocLib | 2)
#define S_coprocLib_COPROC_DISABLE_FAILED         (M_coprocLib | 3)
#define S_coprocLib_EXCHANDLER_REGISTER_FAILED    (M_coprocLib | 4)
#define S_coprocLib_HOOK_ATTACH_FAILED            (M_coprocLib | 5)
#define S_coprocLib_INVALID_ARGUMENT              (M_coprocLib | 6)
#define S_coprocLib_INVALID_OPERATION             (M_coprocLib | 7)
#define S_coprocLib_NO_COPROC_SUPPORT             (M_coprocLib | 8)
#define S_loadRtpLib_INVALID_ARGUMENT               (M_loadRtpLib | 101)
#define S_loadRtpLib_INVALID_OPTION                 (M_loadRtpLib | 102)
#define S_loadRtpLib_SYMTBL_DESTROY_INCOMPLETE      (M_loadRtpLib | 103)
#define S_loadRtpLib_TOO_MANY_SEGMENTS              (M_loadRtpLib | 104)
#define S_loadRtpLib_NO_LOADABLE_SEGMENT            (M_loadRtpLib | 105)
#define S_loadRtpLib_ADDRESS_OVERFLOW               (M_loadRtpLib | 106)
#define S_loadRtpLib_SEGMENT_READ                   (M_loadRtpLib | 107)
#define S_loadRtpLib_COMMON_SYMBOL                  (M_loadRtpLib | 108)
#define S_loadRtpLib_UNDEFINED_SYMBOL               (M_loadRtpLib | 109)
#define S_loadRtpLib_NO_RELOCATION_SECTION          (M_loadRtpLib | 110)
#define S_loadRtpLib_NOT_EXECUTABLE                 (M_loadRtpLib | 111)
#define S_loadRtpLib_NO_ENTRY_POINT                 (M_loadRtpLib | 112)
#define S_loadRtpLib_NO_PROG_HDR                    (M_loadRtpLib | 113)
#define S_loadRtpLib_FIRST_LOAD_SEG_NOT_EXECUTABLE  (M_loadRtpLib | 114)
#define S_loadRtpLib_SECOND_LOAD_SEG_NOT_WRITEABLE  (M_loadRtpLib | 115)
#define S_loadRtpLib_DATA_SEG_BEFORE_TEXT_SEG       (M_loadRtpLib | 116)
#define S_loadRtpLib_TOO_FEW_SEGMENTS               (M_loadRtpLib | 117)
#define S_loadRtpLib_INVALID_SEGMENTS               (M_loadRtpLib | 118)
#define S_loadRtpLib_DYNAMIC_SEGMENTS_NOT_SUPPORTED (M_loadRtpLib | 118)
#define S_loadRtpLib_INSUFFICIENT_MEMORY            (M_loadRtpLib | 119)
#define	S_pgPoolLib_INVALID_PAGE_SIZE		(M_pgPoolLib | 1)
#define	S_pgPoolLib_INVALID_PAGE_COUNT		(M_pgPoolLib | 2)
#define S_pgPoolLib_INVALID_ALIGNMENT		(M_pgPoolLib | 3)
#define S_pgPoolLib_NOT_ENOUGH_FREE_PAGES	(M_pgPoolLib | 4)
#define S_pgPoolLib_PAGE_RANGE_OUT_OF_POOL	(M_pgPoolLib | 5)
#define S_pgPoolLib_PAGE_OVERLAP		(M_pgPoolLib | 6)
#define S_pgPoolLib_PAGES_NOT_FREE		(M_pgPoolLib | 7)
#define S_pgPoolLib_PAGES_NOT_ALLOCATED		(M_pgPoolLib | 8)
#define S_pgPoolLib_INVALID_POOL_TYPE		(M_pgPoolLib | 9)
#define S_pgPoolLib_INVALID_STATE		(M_pgPoolLib | 10)
#define S_pgPoolLib_ALLOC_ERROR_NO_ALLOC_SET    (M_pgPoolLib | 11)
#define S_taskPxLib_ILLEGAL_PRIORITY		(M_taskPxLib | 101)
#define S_taskPxLib_ILLEGAL_POLICY		(M_taskPxLib | 102)
#define S_taskPxLib_NOT_ENOUGH_ATTRS            (M_taskPxLib | 103)
#define S_taskPxLib_INVALID_INITBUDGET          (M_taskPxLib | 104)
#define S_taskPxLib_INVALID_MAXREPL		(M_taskPxLib | 105)
#define S_taskPxLib_NOT_SPECIFY_POLICY		(M_taskPxLib | 106)
#define S_taskPxLib_CHANGE_SS_POLICY            (M_taskPxLib | 107)
#define S_taskPxLib_NOT_CONFIG_SCHED_SPORADIC   (M_taskPxLib | 108)
#define S_rawFsLib_VOLUME_NOT_AVAILABLE		(M_rawFsLib | 1)
#define S_rawFsLib_END_OF_DEVICE		(M_rawFsLib | 2)
#define S_rawFsLib_NO_FREE_FILE_DESCRIPTORS	(M_rawFsLib | 3)
#define S_rawFsLib_INVALID_NUMBER_OF_BYTES	(M_rawFsLib | 4)
#define S_rawFsLib_ILLEGAL_NAME			(M_rawFsLib | 5)
#define S_rawFsLib_NOT_FILE			(M_rawFsLib | 6)
#define S_rawFsLib_READ_ONLY			(M_rawFsLib | 7)
#define S_rawFsLib_FD_OBSOLETE			(M_rawFsLib | 8)
#define S_rawFsLib_NO_BLOCK_DEVICE		(M_rawFsLib | 9)
#define S_rawFsLib_BAD_SEEK			(M_rawFsLib | 10)
#define S_rawFsLib_INVALID_PARAMETER		(M_rawFsLib | 11)
#define S_rawFsLib_32BIT_OVERFLOW		(M_rawFsLib | 12)
#define S_rawFsLib_WRITE_ONLY			(M_rawFsLib | 13)
#define S_remLib_ALL_PORTS_IN_USE		(M_remLib | 1)
#define S_remLib_RSH_ERROR			(M_remLib | 2)
#define S_remLib_IDENTITY_TOO_BIG		(M_remLib | 3)
#define S_remLib_RSH_STDERR_SETUP_FAILED	(M_remLib | 4)
#define S_remLib_RCMD_INPUT_ERROR               (M_remLib | 5)
#define S_resolvLib_NO_RECOVERY       (M_resolvLib | 1)
#define S_resolvLib_TRY_AGAIN         (M_resolvLib | 2)
#define S_resolvLib_HOST_NOT_FOUND    (M_resolvLib | 3)
#define S_resolvLib_NO_DATA           (M_resolvLib | 4)
#define S_resolvLib_BUFFER_2_SMALL    (M_resolvLib | 5)
#define S_resolvLib_INVALID_PARAMETER (M_resolvLib | 6)
#define S_resolvLib_INVALID_ADDRESS   (M_resolvLib | 7)
#define S_routeLib_ILLEGAL_INTERNET_ADDRESS		(M_routeLib | 1)
#define S_routeLib_ILLEGAL_NETWORK_NUMBER		(M_routeLib | 2)
#define S_rpcLib_RPC_SUCCESS		(M_rpcClntStat | (int) RPC_SUCCESS)
#define S_rpcLib_RPC_CANTENCODEARGS	(M_rpcClntStat | (int) RPC_CANTENCODEARGS)
#define S_rpcLib_RPC_CANTDECODERES	(M_rpcClntStat | (int) RPC_CANTDECODERES)
#define S_rpcLib_RPC_CANTSEND		(M_rpcClntStat | (int) RPC_CANTSEND)
#define S_rpcLib_RPC_CANTRECV		(M_rpcClntStat | (int) RPC_CANTRECV)
#define S_rpcLib_RPC_TIMEDOUT		(M_rpcClntStat | (int) RPC_TIMEDOUT)
#define S_rpcLib_RPC_VERSMISMATCH	(M_rpcClntStat | (int) RPC_VERSMISMATCH)
#define S_rpcLib_RPC_AUTHERROR		(M_rpcClntStat | (int) RPC_AUTHERROR)
#define S_rpcLib_RPC_PROGUNAVAIL	(M_rpcClntStat | (int) RPC_PROGUNAVAIL)
#define S_rpcLib_RPC_PROGVERSMISMATCH	(M_rpcClntStat | (int) RPC_PROGVERSMISMATCH)
#define S_rpcLib_RPC_PROCUNAVAIL	(M_rpcClntStat | (int) RPC_PROCUNAVAIL)
#define S_rpcLib_RPC_CANTDECODEARGS	(M_rpcClntStat | (int) RPC_CANTDECODEARGS)
#define S_rpcLib_RPC_SYSTEMERROR	(M_rpcClntStat | (int) RPC_SYSTEMERROR)
#define S_rpcLib_RPC_UNKNOWNHOST	(M_rpcClntStat | (int) RPC_UNKNOWNHOST)
#define S_rpcLib_RPC_PMAPFAILURE	(M_rpcClntStat | (int) RPC_PMAPFAILURE)
#define S_rpcLib_RPC_PROGNOTREGISTERED	(M_rpcClntStat | (int) RPC_PROGNOTREGISTERED)
#define S_rpcLib_RPC_FAILED		(M_rpcClntStat | (int) RPC_FAILED)
#define S_rtpLib_INVALID_FILE                   (M_rtpLib | 1)
#define S_rtpLib_INVALID_OPTION                 (M_rtpLib | 2)
#define S_rtpLib_ACCESS_DENIED                  (M_rtpLib | 3)
#define S_rtpLib_INVALID_RTP_ID			(M_rtpLib | 4)
#define S_rtpLib_NO_SYMBOL_TABLE		(M_rtpLib | 5)
#define S_rtpLib_INVALID_SEGMENT_START_ADDRESS	(M_rtpLib | 6)
#define S_rtpLib_INVALID_SYMBOL_REGISTR_POLICY	(M_rtpLib | 7)
#define S_rtpLib_INSTANTIATE_FAILED             (M_rtpLib | 8)
#define S_rtpLib_INVALID_TASK_OPTION            (M_rtpLib | 9)
#define S_rtpLib_RTP_NAME_LENGTH_EXCEEDED	(M_rtpLib | 10)	/* rtpInfoGet */
#define S_rtpLib_NO_SYMBOL_TABLE_SUPPORT	(M_rtpLib | 11)
#define S_sdLib_NOT_IMPLEMENTED                      (M_sdLib |  1)
#define S_sdLib_NAME_NOT_VALID                       (M_sdLib |  2)
#define S_sdLib_VIRT_PAGES_NOT_AVAILABLE             (M_sdLib |  3)
#define S_sdLib_PHYS_PAGES_NOT_AVAILABLE             (M_sdLib |  4)
#define S_sdLib_ARG_LIST_IS_NULL                     (M_sdLib |  5)
#define S_sdLib_VIRT_ADDR_PTR_IS_NULL                (M_sdLib |  6)
#define S_sdLib_SIZE_IS_NULL                         (M_sdLib |  7)
#define S_sdLib_INVALID_OPTIONS                      (M_sdLib |  8)
#define S_sdLib_INVALID_MMU_ATTR                     (M_sdLib |  9)
#define S_sdLib_NOT_MAPPED                           (M_sdLib | 10)
#define S_sdLib_ADDR_NOT_ALIGNED                     (M_sdLib | 11)
#define S_sdLib_CLIENT_COUNT_NOT_NULL                (M_sdLib | 12)
#define S_sdLib_INVALID_SD_ID                        (M_sdLib | 13)
#define S_sdLib_SD_IS_PRIVATE                        (M_sdLib | 14)
#define S_sdLib_PHYS_ADDR_OUT_OF_RANGE               (M_sdLib | 15)
#define S_selectLib_NO_SELECT_SUPPORT_IN_DRIVER  (M_selectLib | 1)
#define S_selectLib_NO_SELECT_CONTEXT		 (M_selectLib | 2)
#define S_semLib_INVALID_STATE			(M_semLib | 101)
#define S_semLib_INVALID_OPTION			(M_semLib | 102)
#define S_semLib_INVALID_QUEUE_TYPE		(M_semLib | 103)
#define S_semLib_INVALID_OPERATION		(M_semLib | 104)
#define S_semLib_INVALID_INITIAL_COUNT  	(M_semLib | 105)
#define S_semLib_COUNT_OVERFLOW                 (M_semLib | 106)
#define S_shellInterpCmdLib_UNKNOWN_CMD		(M_shellInterpCmdLib | 1)
#define S_shellInterpCmdLib_UNKNOWN_TOPIC	(M_shellInterpCmdLib | 2)
#define S_shellInterpCmdLib_WRONG_CMD		(M_shellInterpCmdLib | 3)
#define S_shellLib_NO_INTERP		(M_shellLib | 1)
#define S_shellLib_INTERP_EXISTS	(M_shellLib | 2)
#define S_shellLib_NOT_SHELL_TASK	(M_shellLib | 3)
#define S_shellLib_SHELL_TASK_EXISTS	(M_shellLib | 4)
#define S_shellLib_SHELL_TASK_MAX	(M_shellLib | 5)
#define S_shellLib_NO_SHELL_CMD		(M_shellLib | 6)
#define S_shellLib_NO_USER_DATA		(M_shellLib | 7)
#define S_shellLib_NO_LED_MODE		(M_shellLib | 8)
#define S_shellLib_INTERP_INIT_ERROR	(M_shellLib | 9)
#define S_shellLib_TOO_MANY_SESSIONS	(M_shellLib | 10)
#define S_shellLib_LEX_ERROR		(M_shellLib | 20)
#define S_shellLib_SYNTAX_ERROR		(M_shellLib | 21)
#define S_shellLib_INTERNAL_ERROR	(M_shellLib | 22)
#define S_shellLib_UNMATCHED_QUOTE	(M_shellLib | 30)
#define S_shellLib_MISSING_ARG		(M_shellLib | 31)
#define S_shellLib_UNKNOWN_OPT		(M_shellLib | 32)
#define S_shellLib_ARG_ERROR		(M_shellLib | 33)
#define S_shellLib_CONFIG_ERROR		(M_shellLib | 40)
#define S_shellLib_CTX_ALREADY_ATTACHED	(M_shellLib | 41)
#define	S_shlLib_ID_SPACE_EXHAUSTED		(M_shlLib | 1)
#define	S_shlLib_INVALID_SH_INITFLG_CHANGE	(M_shlLib | 2)
#define	S_shlLib_INVALID_GOTT_INDEX		(M_shlLib | 3)
#define	S_shlLib_INVALID_SHL_ID			(M_shlLib | 4)
#define	S_shlLib_INVALID_PARAMETER		(M_shlLib | 5)
#define	S_shlLib_SHL_ACCESS_DENIED		(M_shlLib | 6)
#define S_sntpcLib_INVALID_PARAMETER         (M_sntpcLib | 1)
#define S_sntpcLib_INVALID_ADDRESS           (M_sntpcLib | 2)
#define S_sntpcLib_TIMEOUT                   (M_sntpcLib | 3)
#define S_sntpcLib_VERSION_UNSUPPORTED       (M_sntpcLib | 4)
#define S_sntpcLib_SERVER_UNSYNC             (M_sntpcLib | 5)
#define S_sntpsLib_INVALID_PARAMETER         (M_sntpsLib | 1)
#define S_spinLockLib_NOT_SPIN_LOCK_CALLABLE    (M_spinLockLib | 1)
#define S_spinLockLib_INVALID_OPERATION         (M_spinLockLib | 2)
#define S_spinLockLib_LOCK_IN_RECOVERY          (M_spinLockLib | 3)
#define S_spinLockLib_LOCK_UNAVAILABLE          (M_spinLockLib | 4)
#define S_spinLockLib_LOCK_TIMEOUT              (M_spinLockLib | 5)
#define S_symLib_SYMBOL_NOT_FOUND	(M_symLib | 1)
#define S_symLib_NAME_CLASH		(M_symLib | 2)
#define S_symLib_TABLE_NOT_EMPTY	(M_symLib | 3)
#define S_symLib_SYMBOL_STILL_IN_TABLE	(M_symLib | 4) /* obsoleted */
#define S_symLib_INVALID_SYMBOL_NAME	(M_symLib | 5)
#define S_symLib_INVALID_SYMTAB_ID	(M_symLib | 12)
#define S_symLib_INVALID_SYM_ID_PTR     (M_symLib | 13)
#define S_symLib_INVALID_ARGS		(M_symLib | 14)
#define S_syscallLib_UNKNOWN_GROUP          (M_syscallLib | 1)
#define S_syscallLib_GROUP_EXISTS           (M_syscallLib | 2)
#define S_syscallLib_INVALID_ROUTINE_COUNT  (M_syscallLib | 3)
#define S_syscallLib_NO_ROUTINES_TBL        (M_syscallLib | 4)
#define S_syscallLib_INVALID_USER_SP        (M_syscallLib | 5)
#define S_syscallLib_VECTOR_INIT_FAILED     (M_syscallLib | 6)
#define S_taskLib_NAME_NOT_FOUND		(M_taskLib | 101)
#define S_taskLib_TASK_HOOK_TABLE_FULL		(M_taskLib | 102)
#define S_taskLib_TASK_HOOK_NOT_FOUND		(M_taskLib | 103)
#define S_taskLib_TASK_SWAP_HOOK_REFERENCED	(M_taskLib | 104)
#define S_taskLib_TASK_SWAP_HOOK_SET		(M_taskLib | 105)
#define S_taskLib_TASK_SWAP_HOOK_CLEAR		(M_taskLib | 106)
#define S_taskLib_TASK_VAR_NOT_FOUND		(M_taskLib | 107)
#define S_taskLib_TASK_UNDELAYED		(M_taskLib | 108)
#define S_taskLib_ILLEGAL_PRIORITY		(M_taskLib | 109)
#define S_taskLib_ILLEGAL_OPTIONS		(M_taskLib | 110)
#define S_taskLib_NO_TCB			(M_taskLib | 111)
#define S_taskLib_ILLEGAL_OPERATION		(M_taskLib | 112)
#define S_taskLib_ILLEGAL_STACK_INFO            (M_taskLib | 113)
#define S_taskLib_STOPPED_DELETE_SAFE_TASK      (M_taskLib | 114)
#define S_tffsLib_BAD_FUNCTION        (M_tffsLib | 1)
#define S_tffsLib_FILE_NOT_FOUND      (M_tffsLib | 2)
#define S_tffsLib_PATH_NOT_FOUND      (M_tffsLib | 3)
#define S_tffsLib_TOO_MANY_OPEN_FILES (M_tffsLib |4)
#define S_tffsLib_NO_WRITE_ACCESS     (M_tffsLib | 5)
#define S_tffsLib_BAD_FILE_HANDLE     (M_tffsLib | 6)
#define S_tffsLib_DRIVE_NOT_AVAILABLE (M_tffsLib | 9)
#define S_tffsLib_NON_FAT_FORMAT      (M_tffsLib | 10)
#define S_tffsLib_FORMAT_NOT_SUPPORTED (M_tffsLib | 11)
#define S_tffsLib_NO_MORE_FILES       (M_tffsLib | 18)
#define S_tffsLib_WRITE_PROTECT       (M_tffsLib | 19)
#define S_tffsLib_BAD_DRIVE_HANDLE    (M_tffsLib | 20)
#define S_tffsLib_DRIVE_NOT_READY     (M_tffsLib | 21)
#define S_tffsLib_UNKNOWN_CMD         (M_tffsLib | 22)
#define S_tffsLib_BAD_FORMAT          (M_tffsLib | 23)
#define S_tffsLib_BAD_LENGTH          (M_tffsLib | 24)
#define S_tffsLib_DATA_ERROR          (M_tffsLib | 25)
#define S_tffsLib_UNKNOWN_MEDIA       (M_tffsLib | 26)
#define S_tffsLib_SECTOR_NOT_FOUND    (M_tffsLib | 27)
#define S_tffsLib_OUT_OF_PAPER        (M_tffsLib | 28)
#define S_tffsLib_WRITE_FAULT         (M_tffsLib | 29)
#define S_tffsLib_READ_FAULT          (M_tffsLib | 30)
#define S_tffsLib_GENERAL_FAILURE     (M_tffsLib | 31)
#define S_tffsLib_DISK_CHANGE         (M_tffsLib | 34)
#define S_tffsLib_VPP_FAILURE         (M_tffsLib | 50)
#define S_tffsLib_BAD_PARAMETER       (M_tffsLib | 51)
#define S_tffsLib_NO_SPACE_IN_VOLUME  (M_tffsLib | 52)
#define S_tffsLib_INVALID_FAT_CHAIN   (M_tffsLib | 53)
#define S_tffsLib_ROOT_DIR_FULL       (M_tffsLib | 54)
#define S_tffsLib_NOT_MOUNTED         (M_tffsLib | 55)
#define S_tffsLib_PATH_IS_ROOTDIR     (M_tffsLib | 56)
#define S_tffsLib_NOT_A_DIR           (M_tffsLib | 57)
#define S_tffsLib_DIR_NOT_EMPTY       (M_tffsLib | 58)
#define S_tffsLib_FILE_IS_A_DIR       (M_tffsLib | 59)
#define S_tffsLib_ADAPTER_NOT_FOUND   (M_tffsLib | 60)
#define S_tffsLib_FORMATTING_ERROR    (M_tffsLib | 62)
#define S_tffsLib_NOT_ENOUGH_MEMORY   (M_tffsLib | 63)
#define S_tffsLib_VOLUME_TOO_SMALL    (M_tffsLib | 64)
#define S_tffsLib_BUFFERING_ERROR     (M_tffsLib | 65)
#define S_tffsLib_FILE_ALREADY_EXISTS (M_tffsLib | 80)
#define S_tffsLib_INCOMPLETE          (M_tffsLib | 100)
#define S_tffsLib_TIMED_OUT           (M_tffsLib | 101)
#define S_tffsLib_TOO_MANY_COMPONENTS (M_tffsLib | 102)
#define S_tftpLib_INVALID_ARGUMENT	(M_tftpLib | 1)
#define S_tftpLib_INVALID_DESCRIPTOR	(M_tftpLib | 2)
#define S_tftpLib_INVALID_COMMAND	(M_tftpLib | 3)
#define S_tftpLib_INVALID_MODE		(M_tftpLib | 4)
#define S_tftpLib_UNKNOWN_HOST		(M_tftpLib | 5)
#define S_tftpLib_NOT_CONNECTED		(M_tftpLib | 6)
#define S_tftpLib_TIMED_OUT		(M_tftpLib | 7)
#define S_tftpLib_TFTP_ERROR		(M_tftpLib | 8)
#define S_unldLib_MODULE_NOT_FOUND		(M_unldLib | 1) /* obsoleted */
#define S_unldLib_TEXT_IN_USE			(M_unldLib | 2)
#define S_unldLib_INVALID_UNLOAD_FLAG		(M_unldLib | 3)
#define S_unldLib_ILLEGAL_FLAGS_COMBINATION	(M_unldLib | 4)
#define S_unldLib_USR_TERM_ERROR                (M_unldLib | 5)
#define S_usrLib_NOT_ENOUGH_ARGS	(M_usrLib | 1)
#define S_vmLib_NOT_PAGE_ALIGNED		(M_vmLib | 1)
#define S_vmLib_BAD_STATE_PARAM			(M_vmLib | 2)
#define S_vmLib_BAD_MASK_PARAM			(M_vmLib | 3)
#define S_vmLib_ADDR_IN_GLOBAL_SPACE		(M_vmLib | 4)
#define S_vmLib_TEXT_PROTECTION_UNAVAILABLE	(M_vmLib | 5)
#define S_vmLib_KERNEL_TEXT_NOT_ALIGNED		(M_vmLib | 6)
#define S_vmLib_FUNCTION_UNSUPPORTED		(M_vmLib | 7)
#define S_vmLib_PHYS_PAGES_ALREADY_MAPPED	(M_vmLib | 8)
#define S_vmLib_NOALIAS_SUPPORT_NOT_INCLUDED	(M_vmLib | 9)
#define S_vxCpuLib_INVALID_ARGUMENT	(M_vxCpuLib | 1)
#define S_vxCpuLib_NO_CPU_AVAILABLE	(M_vxCpuLib | 2)
#define S_vxdbgLib_INVALID_PARAMS       (M_vxdbgLib | 1)  /* params invalid */
#define S_vxdbgLib_INVALID_MEM_ACCESS   (M_vxdbgLib | 2)  /* memory fault */
#define S_vxdbgLib_INVALID_CTX          (M_vxdbgLib | 5)  /* bad context */
#define S_vxdbgLib_INVALID_BP           (M_vxdbgLib | 8)  /* no such bp */
#define S_vxdbgLib_INVALID_EVENT_TYPE   (M_vxdbgLib | 9)  /* invalid event */
#define S_vxdbgLib_NO_HW_REGS           (M_vxdbgLib | 14) /* no hardware regs */
#define S_vxdbgLib_HOOK_ALREADY_EXISTS  (M_vxdbgLib | 15)
#define S_vxdbgLib_HW_REGS_FULL         (M_vxdbgLib | 16) /* hw breakpoint */
#define S_vxdbgLib_INVALID_HW_BP        (M_vxdbgLib | 17) /* invalid hw bp */
#define S_vxdbgLib_INVALID_BP_DELETE_CLASS (M_vxdbgLib | 18) /* invalid bp */
#define	S_vxdbgLib_INVALID_ALIGNMENT	(M_vxdbgLib | 19) /* memory alignment */
#define	S_vxdbgLib_NOT_INITIALIZED	(M_vxdbgLib | 20) /* VxDBG library is */
#define S_vxdbgLib_INVALID_CLIENT_ID    (M_vxdbgLib | 21) /* invalid client */
#define S_vxdbgLib_UNSUPPORTED_HW_BP_SIZE (M_vxdbgLib | 22) /* unsupported */
#define S_vxdbgLib_UNSUPPORTED_HW_BP_ACCESS_TYPE (M_vxdbgLib | 23)
#define S_vxdbgLib_NO_HW_BP_SUPPORT (M_vxdbgLib | 24)     /* no hw bp support */
#define S_vxdbgLib_HW_BP_SUPPORT_DISABLED (M_vxdbgLib | 25)
#define	S_vxdbgLib_NOT_ENABLED	(M_vxdbgLib | 26)
#define S_wdLib_INVALID_PARAMETER (M_wdLib | 1)
#define S_zbufLib_ID_INVALID            (M_mbufLib | 1)
#define S_zbufLib_ID_EMPTY              (M_mbufLib | 2)
#define S_zbufLib_SEGMENT_NOT_FOUND     (M_mbufLib | 3)
#define S_zbufLib_LENGTH_INVALID        (M_mbufLib | 4)
#define S_zbufLib_OFFSET_INVALID        (M_mbufLib | 5)
#define	EPERM		1		/* Not owner */
#define	ENOENT		2		/* No such file or directory */
#define	ESRCH		3		/* No such process */
#define	EINTR		4		/* Interrupted system call */
#define	EIO		5		/* I/O error */
#define	ENXIO		6		/* No such device or address */
#define	E2BIG		7		/* Arg list too long */
#define	ENOEXEC		8		/* Exec format error */
#define	EBADF		9		/* Bad file number */
#define	ECHILD		10		/* No children */
#define	EAGAIN		11		/* No more processes */
#define	ENOMEM		12		/* Not enough core */
#define	EACCES		13		/* Permission denied */
#define	EFAULT		14		/* Bad address */
#define	ENOTEMPTY	15		/* Directory not empty */
#define	EBUSY		16		/* Mount device busy */
#define	EEXIST		17		/* File exists */
#define	EXDEV		18		/* Cross-device link */
#define	ENODEV		19		/* No such device */
#define	ENOTDIR		20		/* Not a directory */
#define	EISDIR		21		/* Is a directory */
#define	EINVAL		22		/* Invalid argument */
#define	ENFILE		23		/* File table overflow */
#define	EMFILE		24		/* Too many open files */
#define	ENOTTY		25		/* Not a typewriter */
#define	ENAMETOOLONG	26		/* File name too long */
#define	EFBIG		27		/* File too large */
#define	ENOSPC		28		/* No space left on device */
#define	ESPIPE		29		/* Illegal seek */
#define	EROFS		30		/* Read-only file system */
#define	EMLINK		31		/* Too many links */
#define	EPIPE		32		/* Broken pipe */
#define	EDEADLK		33		/* Resource deadlock avoided */
#define	ENOLCK		34		/* No locks available */
#define	ENOTSUP		35		/* Unsupported value */
#define	EMSGSIZE	36		/* Message size */
#define	EDOM		37		/* Argument too large */
#define	ERANGE		38		/* Result too large */
#define EDOOM           39              /* Task deletion attempt in progress */
#define	EDESTADDRREQ	40		/* Destination address required */
#define	EPROTOTYPE	41		/* Protocol wrong type for socket */
#define	ENOPROTOOPT	42		/* Protocol not available */
#define	EPROTONOSUPPORT	43		/* Protocol not supported */
#define	ESOCKTNOSUPPORT	44		/* Socket type not supported */
#define	EOPNOTSUPP	45		/* Operation not supported on socket */
#define	EPFNOSUPPORT	46		/* Protocol family not supported */
#define	EAFNOSUPPORT	47		/* Addr family not supported */
#define	EADDRINUSE	48		/* Address already in use */
#define	EADDRNOTAVAIL	49		/* Can't assign requested address */
#define	ENOTSOCK	50		/* Socket operation on non-socket */
#define	ENETUNREACH	51		/* Network is unreachable */
#define	ENETRESET	52		/* Network dropped connection on reset */
#define	ECONNABORTED	53		/* Software caused connection abort */
#define	ECONNRESET	54		/* Connection reset by peer */
#define	ENOBUFS		55		/* No buffer space available */
#define	EISCONN		56		/* Socket is already connected */
#define	ENOTCONN	57		/* Socket is not connected */
#define	ESHUTDOWN	58		/* Can't send after socket shutdown */
#define	ETOOMANYREFS	59		/* Too many references: can't splice */
#define	ETIMEDOUT	60		/* Connection timed out */
#define	ECONNREFUSED	61		/* Connection refused */
#define	ENETDOWN	62		/* Network is down */
#define	ETXTBSY		63		/* Text file busy */
#define	ELOOP		64		/* Too many levels of symbolic links */
#define	EHOSTUNREACH	65		/* No route to host */
#define	ENOTBLK		66		/* Block device required */
#define	EHOSTDOWN	67		/* Host is down */
#define	EINPROGRESS	68		/* Operation now in progress */
#define	EALREADY	69		/* Operation already in progress */
#define	EWOULDBLOCK	70		/* Operation would block */
#define	ENOSYS		71		/* Function not implemented */
#define	ECANCELED	72		/* Operation canceled */
#define ERSVD73         73              /* Reserved (73) */
#define ENOSR           74              /* Insufficient memory */
#define ENOSTR          75              /* STREAMS device required */
#define EPROTO          76              /* Generic STREAMS error */
#define EBADMSG         77              /* Invalid STREAMS message */
#define ENODATA         78              /* Missing expected message data */
#define ETIME           79              /* STREAMS timeout occurred */
#define ENOMSG          80              /* Unexpected message type */ 
#define EFPOS		81		/* File positioning error */
#define EILSEQ		82		/* Illegal byte sequence. */
#define EDQUOT          83              /* routing error */
#define	EIDRM		84		/* Identifier removed */
#define	EOVERFLOW	85		/* Value too large for data type */
#define EMULTIHOP	86		/* Reserved (EMULTIHOP) */
#define ENOLINK		87		/* Reserved (ENOLINK) */
#define ESTALE		88		/* Reserved (ESTALE) */
#define	ERRMAX		89
#define ERRNO_PX_FLAG		(1<<15)

SYMBOL statTbl [] =
    {
    {{NULL},"S_errno_EPERM", (char *) (M_errno | EPERM),0,0,0},
    {{NULL},"S_errno_ENOENT", (char *) (M_errno | ENOENT),0,0,0},
    {{NULL},"S_errno_ESRCH", (char *) (M_errno | ESRCH),0,0,0},
    {{NULL},"S_errno_EINTR", (char *) (M_errno | EINTR),0,0,0},
    {{NULL},"S_errno_EIO", (char *) (M_errno | EIO),0,0,0},
    {{NULL},"S_errno_ENXIO", (char *) (M_errno | ENXIO),0,0,0},
    {{NULL},"S_errno_E2BIG", (char *) (M_errno | E2BIG),0,0,0},
    {{NULL},"S_errno_ENOEXEC", (char *) (M_errno | ENOEXEC),0,0,0},
    {{NULL},"S_errno_EBADF", (char *) (M_errno | EBADF),0,0,0},
    {{NULL},"S_errno_ECHILD", (char *) (M_errno | ECHILD),0,0,0},
    {{NULL},"S_errno_EAGAIN", (char *) (M_errno | EAGAIN),0,0,0},
    {{NULL},"S_errno_ENOMEM", (char *) (M_errno | ENOMEM),0,0,0},
    {{NULL},"S_errno_EACCES", (char *) (M_errno | EACCES),0,0,0},
    {{NULL},"S_errno_EFAULT", (char *) (M_errno | EFAULT),0,0,0},
    {{NULL},"S_errno_ENOTEMPTY", (char *) (M_errno | ENOTEMPTY),0,0,0},
    {{NULL},"S_errno_EBUSY", (char *) (M_errno | EBUSY),0,0,0},
    {{NULL},"S_errno_EEXIST", (char *) (M_errno | EEXIST),0,0,0},
    {{NULL},"S_errno_EXDEV", (char *) (M_errno | EXDEV),0,0,0},
    {{NULL},"S_errno_ENODEV", (char *) (M_errno | ENODEV),0,0,0},
    {{NULL},"S_errno_ENOTDIR", (char *) (M_errno | ENOTDIR),0,0,0},
    {{NULL},"S_errno_EISDIR", (char *) (M_errno | EISDIR),0,0,0},
    {{NULL},"S_errno_EINVAL", (char *) (M_errno | EINVAL),0,0,0},
    {{NULL},"S_errno_ENFILE", (char *) (M_errno | ENFILE),0,0,0},
    {{NULL},"S_errno_EMFILE", (char *) (M_errno | EMFILE),0,0,0},
    {{NULL},"S_errno_ENOTTY", (char *) (M_errno | ENOTTY),0,0,0},
    {{NULL},"S_errno_ENAMETOOLONG", (char *) (M_errno | ENAMETOOLONG),0,0,0},
    {{NULL},"S_errno_EFBIG", (char *) (M_errno | EFBIG),0,0,0},
    {{NULL},"S_errno_ENOSPC", (char *) (M_errno | ENOSPC),0,0,0},
    {{NULL},"S_errno_ESPIPE", (char *) (M_errno | ESPIPE),0,0,0},
    {{NULL},"S_errno_EROFS", (char *) (M_errno | EROFS),0,0,0},
    {{NULL},"S_errno_EMLINK", (char *) (M_errno | EMLINK),0,0,0},
    {{NULL},"S_errno_EPIPE", (char *) (M_errno | EPIPE),0,0,0},
    {{NULL},"S_errno_EDEADLK", (char *) (M_errno | EDEADLK),0,0,0},
    {{NULL},"S_errno_ENOLCK", (char *) (M_errno | ENOLCK),0,0,0},
    {{NULL},"S_errno_ENOTSUP", (char *) (M_errno | ENOTSUP),0,0,0},
    {{NULL},"S_errno_EMSGSIZE", (char *) (M_errno | EMSGSIZE),0,0,0},
    {{NULL},"S_errno_EDOM", (char *) (M_errno | EDOM),0,0,0},
    {{NULL},"S_errno_ERANGE", (char *) (M_errno | ERANGE),0,0,0},
    {{NULL},"S_errno_EDOOM", (char *) (M_errno | EDOOM),0,0,0},
    {{NULL},"S_errno_EDESTADDRREQ", (char *) (M_errno | EDESTADDRREQ),0,0,0},
    {{NULL},"S_errno_EPROTOTYPE", (char *) (M_errno | EPROTOTYPE),0,0,0},
    {{NULL},"S_errno_ENOPROTOOPT", (char *) (M_errno | ENOPROTOOPT),0,0,0},
    {{NULL},"S_errno_EPROTONOSUPPORT", (char *) (M_errno | EPROTONOSUPPORT),0,0,0},
    {{NULL},"S_errno_ESOCKTNOSUPPORT", (char *) (M_errno | ESOCKTNOSUPPORT),0,0,0},
    {{NULL},"S_errno_EOPNOTSUPP", (char *) (M_errno | EOPNOTSUPP),0,0,0},
    {{NULL},"S_errno_EPFNOSUPPORT", (char *) (M_errno | EPFNOSUPPORT),0,0,0},
    {{NULL},"S_errno_EAFNOSUPPORT", (char *) (M_errno | EAFNOSUPPORT),0,0,0},
    {{NULL},"S_errno_EADDRINUSE", (char *) (M_errno | EADDRINUSE),0,0,0},
    {{NULL},"S_errno_EADDRNOTAVAIL", (char *) (M_errno | EADDRNOTAVAIL),0,0,0},
    {{NULL},"S_errno_ENOTSOCK", (char *) (M_errno | ENOTSOCK),0,0,0},
    {{NULL},"S_errno_ENETUNREACH", (char *) (M_errno | ENETUNREACH),0,0,0},
    {{NULL},"S_errno_ENETRESET", (char *) (M_errno | ENETRESET),0,0,0},
    {{NULL},"S_errno_ECONNABORTED", (char *) (M_errno | ECONNABORTED),0,0,0},
    {{NULL},"S_errno_ECONNRESET", (char *) (M_errno | ECONNRESET),0,0,0},
    {{NULL},"S_errno_ENOBUFS", (char *) (M_errno | ENOBUFS),0,0,0},
    {{NULL},"S_errno_EISCONN", (char *) (M_errno | EISCONN),0,0,0},
    {{NULL},"S_errno_ENOTCONN", (char *) (M_errno | ENOTCONN),0,0,0},
    {{NULL},"S_errno_ESHUTDOWN", (char *) (M_errno | ESHUTDOWN),0,0,0},
    {{NULL},"S_errno_ETOOMANYREFS", (char *) (M_errno | ETOOMANYREFS),0,0,0},
    {{NULL},"S_errno_ETIMEDOUT", (char *) (M_errno | ETIMEDOUT),0,0,0},
    {{NULL},"S_errno_ECONNREFUSED", (char *) (M_errno | ECONNREFUSED),0,0,0},
    {{NULL},"S_errno_ENETDOWN", (char *) (M_errno | ENETDOWN),0,0,0},
    {{NULL},"S_errno_ETXTBSY", (char *) (M_errno | ETXTBSY),0,0,0},
    {{NULL},"S_errno_ELOOP", (char *) (M_errno | ELOOP),0,0,0},
    {{NULL},"S_errno_EHOSTUNREACH", (char *) (M_errno | EHOSTUNREACH),0,0,0},
    {{NULL},"S_errno_ENOTBLK", (char *) (M_errno | ENOTBLK),0,0,0},
    {{NULL},"S_errno_EHOSTDOWN", (char *) (M_errno | EHOSTDOWN),0,0,0},
    {{NULL},"S_errno_EINPROGRESS", (char *) (M_errno | EINPROGRESS),0,0,0},
    {{NULL},"S_errno_EALREADY", (char *) (M_errno | EALREADY),0,0,0},
    {{NULL},"S_errno_EWOULDBLOCK", (char *) (M_errno | EWOULDBLOCK),0,0,0},
    {{NULL},"S_errno_ENOSYS", (char *) (M_errno | ENOSYS),0,0,0},
    {{NULL},"S_errno_ECANCELED", (char *) (M_errno | ECANCELED),0,0,0},
    {{NULL},"S_errno_ERSVD73", (char *) (M_errno | ERSVD73),0,0,0},
    {{NULL},"S_errno_ENOSR", (char *) (M_errno | ENOSR),0,0,0},
    {{NULL},"S_errno_ENOSTR", (char *) (M_errno | ENOSTR),0,0,0},
    {{NULL},"S_errno_EPROTO", (char *) (M_errno | EPROTO),0,0,0},
    {{NULL},"S_errno_EBADMSG", (char *) (M_errno | EBADMSG),0,0,0},
    {{NULL},"S_errno_ENODATA", (char *) (M_errno | ENODATA),0,0,0},
    {{NULL},"S_errno_ETIME", (char *) (M_errno | ETIME),0,0,0},
    {{NULL},"S_errno_ENOMSG", (char *) (M_errno | ENOMSG),0,0,0},
    {{NULL},"S_errno_EFPOS", (char *) (M_errno | EFPOS),0,0,0},
    {{NULL},"S_errno_EILSEQ", (char *) (M_errno | EILSEQ),0,0,0},
    {{NULL},"S_errno_EDQUOT", (char *) (M_errno | EDQUOT),0,0,0},
    {{NULL},"S_errno_EIDRM", (char *) (M_errno | EIDRM),0,0,0},
    {{NULL},"S_errno_EOVERFLOW", (char *) (M_errno | EOVERFLOW),0,0,0},
    {{NULL},"S_errno_EMULTIHOP", (char *) (M_errno | EMULTIHOP),0,0,0},
    {{NULL},"S_errno_ENOLINK", (char *) (M_errno | ENOLINK),0,0,0},
    {{NULL},"S_errno_ESTALE", (char *) (M_errno | ESTALE),0,0,0},
    {{NULL},"S_errno_ERRMAX", (char *) (M_errno | ERRMAX),0,0,0},
    {{NULL},"S_errno_ERRNO_PX_FLAG", (char *) (M_errno | ERRNO_PX_FLAG),0,0,0},
    {{NULL},"S_adrSpaceLib_LIB_NOT_INITIALIZED", (char *) S_adrSpaceLib_LIB_NOT_INITIALIZED,0,0,0},
    {{NULL},"S_adrSpaceLib_CANNOT_REINITIALIZE", (char *) S_adrSpaceLib_CANNOT_REINITIALIZE,0,0,0},
    {{NULL},"S_adrSpaceLib_PARAMETER_NOT_ALIGNED", (char *) S_adrSpaceLib_PARAMETER_NOT_ALIGNED,0,0,0},
    {{NULL},"S_adrSpaceLib_REGION_NOT_AVAILABLE", (char *) S_adrSpaceLib_REGION_NOT_AVAILABLE,0,0,0},
    {{NULL},"S_adrSpaceLib_VIRT_ADRS_NOT_ALIGNED", (char *) S_adrSpaceLib_VIRT_ADRS_NOT_ALIGNED,0,0,0},
    {{NULL},"S_adrSpaceLib_SIZE_IS_INVALID", (char *) S_adrSpaceLib_SIZE_IS_INVALID,0,0,0},
    {{NULL},"S_adrSpaceLib_INVALID_PARAMETER", (char *) S_adrSpaceLib_INVALID_PARAMETER,0,0,0},
    {{NULL},"S_adrSpaceLib_VIRTUAL_OVERLAP", (char *) S_adrSpaceLib_VIRTUAL_OVERLAP,0,0,0},
    {{NULL},"S_adrSpaceLib_PHYSICAL_OVERLAP", (char *) S_adrSpaceLib_PHYSICAL_OVERLAP,0,0,0},
    {{NULL},"S_adrSpaceLib_ADDRESS_OUT_OF_RANGE", (char *) S_adrSpaceLib_ADDRESS_OUT_OF_RANGE,0,0,0},
    {{NULL},"S_adrSpaceLib_INSUFFICIENT_SPACE_IN_RGN", (char *) S_adrSpaceLib_INSUFFICIENT_SPACE_IN_RGN,0,0,0},
    {{NULL},"S_adrSpaceLib_REGION_CONFLICT", (char *) S_adrSpaceLib_REGION_CONFLICT,0,0,0},
    {{NULL},"S_adrSpaceLib_MMU_LESS_NONIDENTITY", (char *) S_adrSpaceLib_MMU_LESS_NONIDENTITY,0,0,0},
    {{NULL},"S_adrSpaceLib_NO_PHYS_PAGES", (char *) S_adrSpaceLib_NO_PHYS_PAGES,0,0,0},
    {{NULL},"S_adrSpaceLib_NO_CONTIG_PHYS_PAGES", (char *) S_adrSpaceLib_NO_CONTIG_PHYS_PAGES,0,0,0},
    {{NULL},"S_adrSpaceLib_MMU_NOT_ENABLED", (char *) S_adrSpaceLib_MMU_NOT_ENABLED,0,0,0},
    {{NULL},"S_adrSpaceLib_INVALID_REGION", (char *) S_adrSpaceLib_INVALID_REGION,0,0,0},
    {{NULL},"S_adrSpaceLib_REGION_NOT_CONFIGURED", (char *) S_adrSpaceLib_REGION_NOT_CONFIGURED,0,0,0},
    {{NULL},"S_adrSpaceLib_INVALID_CONTEXT", (char *) S_adrSpaceLib_INVALID_CONTEXT,0,0,0},
    {{NULL},"S_arpLib_INVALID_ARGUMENT", (char *) S_arpLib_INVALID_ARGUMENT,0,0,0},
    {{NULL},"S_arpLib_INVALID_HOST", (char *) S_arpLib_INVALID_HOST,0,0,0},
    {{NULL},"S_arpLib_INVALID_ENET_ADDRESS", (char *) S_arpLib_INVALID_ENET_ADDRESS,0,0,0},
    {{NULL},"S_arpLib_INVALID_FLAG", (char *) S_arpLib_INVALID_FLAG,0,0,0},
    {{NULL},"S_bootLoadLib_ROUTINE_NOT_INSTALLED", (char *) S_bootLoadLib_ROUTINE_NOT_INSTALLED,0,0,0},
    {{NULL},"S_cacheLib_INVALID_CACHE", (char *) S_cacheLib_INVALID_CACHE,0,0,0},
    {{NULL},"S_cacheLib_UNSUPPORTED", (char *) S_cacheLib_UNSUPPORTED,0,0,0},
    {{NULL},"S_cacheLib_DMA32_RAM_UNSUPPORTED", (char *) S_cacheLib_DMA32_RAM_UNSUPPORTED,0,0,0},
    {{NULL},"S_cacheLib_QOS_CACHE_LEVEL_ERROR", (char *) S_cacheLib_QOS_CACHE_LEVEL_ERROR,0,0,0},
    {{NULL},"S_cacheLib_QOS_NOT_INITIALIZED", (char *) S_cacheLib_QOS_NOT_INITIALIZED,0,0,0},
    {{NULL},"S_cacheLib_QOS_CPUSET_ERROR", (char *) S_cacheLib_QOS_CPUSET_ERROR,0,0,0},
    {{NULL},"S_cacheLib_QOS_OVERALLOCATION", (char *) S_cacheLib_QOS_OVERALLOCATION,0,0,0},
    {{NULL},"S_cacheLib_QOS_MASK_UNAVAILABLE", (char *) S_cacheLib_QOS_MASK_UNAVAILABLE,0,0,0},
    {{NULL},"S_cacheLib_QOS_NO_FREE_COSID", (char *) S_cacheLib_QOS_NO_FREE_COSID,0,0,0},
    {{NULL},"S_cacheLib_QOS_INVALID_BITMASK", (char *) S_cacheLib_QOS_INVALID_BITMASK,0,0,0},
    {{NULL},"S_cacheLib_QOS_INVALID_COSID", (char *) S_cacheLib_QOS_INVALID_COSID,0,0,0},
    {{NULL},"S_cacheLib_QOS_UNSUPPORTED", (char *) S_cacheLib_QOS_UNSUPPORTED,0,0,0},
    {{NULL},"S_classLib_CLASS_ID_ERROR", (char *) S_classLib_CLASS_ID_ERROR,0,0,0},
    {{NULL},"S_classLib_NO_CLASS_DESTROY", (char *) S_classLib_NO_CLASS_DESTROY,0,0,0},
    {{NULL},"S_condVarLib_INVALID_QUEUE_TYPE", (char *) S_condVarLib_INVALID_QUEUE_TYPE,0,0,0},
    {{NULL},"S_condVarLib_INVALID_OPERATION", (char *) S_condVarLib_INVALID_OPERATION,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_HOOK_TABLE_FULL", (char *) S_coreDumpLib_CORE_DUMP_HOOK_TABLE_FULL,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_HOOK_NOT_FOUND", (char *) S_coreDumpLib_CORE_DUMP_HOOK_NOT_FOUND,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_INVALID_DEVICE", (char *) S_coreDumpLib_CORE_DUMP_INVALID_DEVICE,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_DEVICE_READ_ERROR", (char *) S_coreDumpLib_CORE_DUMP_DEVICE_READ_ERROR,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_DEVICE_WRITE_ERROR", (char *) S_coreDumpLib_CORE_DUMP_DEVICE_WRITE_ERROR,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_DEVICE_ERASE_ERROR", (char *) S_coreDumpLib_CORE_DUMP_DEVICE_ERASE_ERROR,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_DEVICE_OPEN_ERROR", (char *) S_coreDumpLib_CORE_DUMP_DEVICE_OPEN_ERROR,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_DEVICE_CLOSE_ERROR", (char *) S_coreDumpLib_CORE_DUMP_DEVICE_CLOSE_ERROR,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_INVALID_ARGS", (char *) S_coreDumpLib_CORE_DUMP_INVALID_ARGS,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_INVALID_CORE_DUMP", (char *) S_coreDumpLib_CORE_DUMP_INVALID_CORE_DUMP,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_STORAGE_NOT_FORMATED", (char *) S_coreDumpLib_CORE_DUMP_STORAGE_NOT_FORMATED,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_DEVICE_NOT_INITIALIZED", (char *) S_coreDumpLib_CORE_DUMP_DEVICE_NOT_INITIALIZED,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_TOO_MANY_CORE_DUMP", (char *) S_coreDumpLib_CORE_DUMP_TOO_MANY_CORE_DUMP,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_COMPRESSION_ERROR", (char *) S_coreDumpLib_CORE_DUMP_COMPRESSION_ERROR,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_FILTER_TABLE_FULL", (char *) S_coreDumpLib_CORE_DUMP_FILTER_TABLE_FULL,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_GENERATE_ALREADY_RUNNING", (char *) S_coreDumpLib_CORE_DUMP_GENERATE_ALREADY_RUNNING,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_PATH_TOO_LONG", (char *) S_coreDumpLib_CORE_DUMP_PATH_TOO_LONG,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_GENERATE_NOT_RUNNING", (char *) S_coreDumpLib_CORE_DUMP_GENERATE_NOT_RUNNING,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_DEVICE_TOO_SMALL", (char *) S_coreDumpLib_CORE_DUMP_DEVICE_TOO_SMALL,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_FILTER_NOT_FOUND", (char *) S_coreDumpLib_CORE_DUMP_FILTER_NOT_FOUND,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_CKSUM_VERIFY_ERROR", (char *) S_coreDumpLib_CORE_DUMP_CKSUM_VERIFY_ERROR,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_VARIABLES_CORRUPTED", (char *) S_coreDumpLib_CORE_DUMP_VARIABLES_CORRUPTED,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_STREAM_DEV_ALREADY_INITIALIZED", (char *) S_coreDumpLib_CORE_DUMP_STREAM_DEV_ALREADY_INITIALIZED,0,0,0},
    {{NULL},"S_coreDumpLib_CORE_DUMP_RAW_DEV_ALREADY_INITIALIZED", (char *) S_coreDumpLib_CORE_DUMP_RAW_DEV_ALREADY_INITIALIZED,0,0,0},
    {{NULL},"S_coreDumpLib_TASK_HOOK_ALREADY_INSTALLED", (char *) S_coreDumpLib_TASK_HOOK_ALREADY_INSTALLED,0,0,0},
    {{NULL},"S_coreDumpLib_INVALID_TASK_HOOK", (char *) S_coreDumpLib_INVALID_TASK_HOOK,0,0,0},
    {{NULL},"S_coreDumpLib_COPY_HOOK_ALREADY_INSTALLED", (char *) S_coreDumpLib_COPY_HOOK_ALREADY_INSTALLED,0,0,0},
    {{NULL},"S_coreDumpLib_INVALID_COPY_HOOK", (char *) S_coreDumpLib_INVALID_COPY_HOOK,0,0,0},
    {{NULL},"S_coreDumpLib_MODULE_HOOK_ALREADY_INSTALLED", (char *) S_coreDumpLib_MODULE_HOOK_ALREADY_INSTALLED,0,0,0},
    {{NULL},"S_coreDumpLib_INVALID_MODULE_HOOK", (char *) S_coreDumpLib_INVALID_MODULE_HOOK,0,0,0},
    {{NULL},"S_devMemLib_PHYS_ADDR_OUT_OF_RANGE", (char *) S_devMemLib_PHYS_ADDR_OUT_OF_RANGE,0,0,0},
    {{NULL},"S_devMemLib_PHYS_ADDR_NOT_ALIGNED", (char *) S_devMemLib_PHYS_ADDR_NOT_ALIGNED,0,0,0},
    {{NULL},"S_devMemLib_INVALID_SIZE", (char *) S_devMemLib_INVALID_SIZE,0,0,0},
    {{NULL},"S_devMemLib_INVALID_MMU_ATTR", (char *) S_devMemLib_INVALID_MMU_ATTR,0,0,0},
    {{NULL},"S_erfLib_INVALID_PARAMETER", (char *) S_erfLib_INVALID_PARAMETER,0,0,0},
    {{NULL},"S_erfLib_MEMORY_ERROR", (char *) S_erfLib_MEMORY_ERROR,0,0,0},
    {{NULL},"S_erfLib_INIT_ERROR", (char *) S_erfLib_INIT_ERROR,0,0,0},
    {{NULL},"S_erfLib_TOO_MANY_USER_CATS", (char *) S_erfLib_TOO_MANY_USER_CATS,0,0,0},
    {{NULL},"S_erfLib_TOO_MANY_USER_TYPES", (char *) S_erfLib_TOO_MANY_USER_TYPES,0,0,0},
    {{NULL},"S_erfLib_HANDLER_NOT_FOUND", (char *) S_erfLib_HANDLER_NOT_FOUND,0,0,0},
    {{NULL},"S_erfLib_QUEUE_EMPTY", (char *) S_erfLib_QUEUE_EMPTY,0,0,0},
    {{NULL},"S_erfLib_QUEUE_FULL", (char *) S_erfLib_QUEUE_FULL,0,0,0},
    {{NULL},"S_erfLib_QUEUE_ALREADY_CREATED", (char *) S_erfLib_QUEUE_ALREADY_CREATED,0,0,0},
    {{NULL},"S_erfLib_AUTO_UNREG_ERROR", (char *) S_erfLib_AUTO_UNREG_ERROR,0,0,0},
    {{NULL},"S_dsmLib_UNKNOWN_INSTRUCTION", (char *) S_dsmLib_UNKNOWN_INSTRUCTION,0,0,0},
    {{NULL},"S_edrLib_NOT_INITIALIZED", (char *) S_edrLib_NOT_INITIALIZED,0,0,0},
    {{NULL},"S_edrLib_ERRLOG_CORRUPTED", (char *) S_edrLib_ERRLOG_CORRUPTED,0,0,0},
    {{NULL},"S_edrLib_ERRLOG_INCOMPATIBLE", (char *) S_edrLib_ERRLOG_INCOMPATIBLE,0,0,0},
    {{NULL},"S_edrLib_PROTECTION_FAILURE", (char *) S_edrLib_PROTECTION_FAILURE,0,0,0},
    {{NULL},"S_edrLib_PMREGION_ERROR", (char *) S_edrLib_PMREGION_ERROR,0,0,0},
    {{NULL},"S_edrLib_INJECT_HOOK_TABLE_FULL", (char *) S_edrLib_INJECT_HOOK_TABLE_FULL,0,0,0},
    {{NULL},"S_edrLib_INJECT_HOOK_NOT_FOUND", (char *) S_edrLib_INJECT_HOOK_NOT_FOUND,0,0,0},
    {{NULL},"S_edrLib_TEXT_HOOK_TABLE_FULL", (char *) S_edrLib_TEXT_HOOK_TABLE_FULL,0,0,0},
    {{NULL},"S_edrLib_TEXT_HOOK_NOT_FOUND", (char *) S_edrLib_TEXT_HOOK_NOT_FOUND,0,0,0},
    {{NULL},"S_edrLib_PP_HOOK_TABLE_FULL", (char *) S_edrLib_PP_HOOK_TABLE_FULL,0,0,0},
    {{NULL},"S_edrLib_PP_HOOK_NOT_FOUND", (char *) S_edrLib_PP_HOOK_NOT_FOUND,0,0,0},
    {{NULL},"S_edrLib_INVALID_OPTION", (char *) S_edrLib_INVALID_OPTION,0,0,0},
    {{NULL},"S_errnoLib_NO_STAT_SYM_TBL", (char *) S_errnoLib_NO_STAT_SYM_TBL,0,0,0},
    {{NULL},"S_eventLib_TIMEOUT", (char *) S_eventLib_TIMEOUT,0,0,0},
    {{NULL},"S_eventLib_NOT_ALL_EVENTS", (char *) S_eventLib_NOT_ALL_EVENTS,0,0,0},
    {{NULL},"S_eventLib_ALREADY_REGISTERED", (char *) S_eventLib_ALREADY_REGISTERED,0,0,0},
    {{NULL},"S_eventLib_EVENTSEND_FAILED", (char *) S_eventLib_EVENTSEND_FAILED,0,0,0},
    {{NULL},"S_eventLib_ZERO_EVENTS", (char *) S_eventLib_ZERO_EVENTS,0,0,0},
    {{NULL},"S_eventLib_TASK_NOT_REGISTERED", (char *) S_eventLib_TASK_NOT_REGISTERED,0,0,0},
    {{NULL},"S_eventLib_NULL_TASKID_AT_INT_LEVEL", (char *) S_eventLib_NULL_TASKID_AT_INT_LEVEL,0,0,0},
    {{NULL},"S_excLib_EXCEPTION_STACK_OVERFLOW", (char *) S_excLib_EXCEPTION_STACK_OVERFLOW,0,0,0},
    {{NULL},"S_excLib_INTERRUPT_STACK_OVERFLOW", (char *) S_excLib_INTERRUPT_STACK_OVERFLOW,0,0,0},
    {{NULL},"S_fsimLib_EBASE", (char *) S_fsimLib_EBASE,0,0,0},
    {{NULL},"S_fsimLib_EPARAM", (char *) S_fsimLib_EPARAM,0,0,0},
    {{NULL},"S_fsimLib_EMEM", (char *) S_fsimLib_EMEM,0,0,0},
    {{NULL},"S_fsimLib_EIO", (char *) S_fsimLib_EIO,0,0,0},
    {{NULL},"S_fsimLib_EREBOOT", (char *) S_fsimLib_EREBOOT,0,0,0},
    {{NULL},"S_fsimLib_EBADBLOCK", (char *) S_fsimLib_EBADBLOCK,0,0,0},
    {{NULL},"S_fsimLib_ECHIP", (char *) S_fsimLib_ECHIP,0,0,0},
    {{NULL},"S_fsimLib_ENOTRUNNING", (char *) S_fsimLib_ENOTRUNNING,0,0,0},
    {{NULL},"S_fsimLib_ENOTSTARTED", (char *) S_fsimLib_ENOTSTARTED,0,0,0},
    {{NULL},"S_fsimLib_EDEV", (char *) S_fsimLib_EDEV,0,0,0},
    {{NULL},"S_fsimLib_EECC_REC", (char *) S_fsimLib_EECC_REC,0,0,0},
    {{NULL},"S_fsimLib_EECC_NOTREC", (char *) S_fsimLib_EECC_NOTREC,0,0,0},
    {{NULL},"S_fsimLib_EECC_NOTREC_FAKE", (char *) S_fsimLib_EECC_NOTREC_FAKE,0,0,0},
    {{NULL},"S_fsimLib_ENOTREC", (char *) S_fsimLib_ENOTREC,0,0,0},
    {{NULL},"S_fsimLib_EID", (char *) S_fsimLib_EID,0,0,0},
    {{NULL},"S_ftlLib_INVALID_PARAM", (char *) S_ftlLib_INVALID_PARAM,0,0,0},
    {{NULL},"S_ftlLib_NO_DEV", (char *) S_ftlLib_NO_DEV,0,0,0},
    {{NULL},"S_ftlLib_DEV_TOO_SMALL", (char *) S_ftlLib_DEV_TOO_SMALL,0,0,0},
    {{NULL},"S_ftlLib_NO_VALID_FTL_ID", (char *) S_ftlLib_NO_VALID_FTL_ID,0,0,0},
    {{NULL},"S_ftlLib_NO_VALID_BBMT", (char *) S_ftlLib_NO_VALID_BBMT,0,0,0},
    {{NULL},"S_ftlLib_DATA_ERROR_ECC_UNRECV", (char *) S_ftlLib_DATA_ERROR_ECC_UNRECV,0,0,0},
    {{NULL},"S_ftlLib_BAD_BLOCK_MAP", (char *) S_ftlLib_BAD_BLOCK_MAP,0,0,0},
    {{NULL},"S_ftlLib_BAD_PAGE_MAP", (char *) S_ftlLib_BAD_PAGE_MAP,0,0,0},
    {{NULL},"S_ftlLib_NO_FREE_REPL_BLK", (char *) S_ftlLib_NO_FREE_REPL_BLK,0,0,0},
    {{NULL},"S_ftpLib_ILLEGAL_VALUE", (char *) S_ftpLib_ILLEGAL_VALUE,0,0,0},
    {{NULL},"S_ftpLib_TRANSIENT_RETRY_LIMIT_EXCEEDED", (char *) S_ftpLib_TRANSIENT_RETRY_LIMIT_EXCEEDED,0,0,0},
    {{NULL},"S_ftpLib_FATAL_TRANSIENT_RESPONSE", (char *) S_ftpLib_FATAL_TRANSIENT_RESPONSE,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_STATUS_221", (char *) S_ftpLib_REMOTE_SERVER_STATUS_221,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_STATUS_226", (char *) S_ftpLib_REMOTE_SERVER_STATUS_226,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_STATUS_257", (char *) S_ftpLib_REMOTE_SERVER_STATUS_257,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_422", (char *) S_ftpLib_REMOTE_SERVER_ERROR_422,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_425", (char *) S_ftpLib_REMOTE_SERVER_ERROR_425,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_450", (char *) S_ftpLib_REMOTE_SERVER_ERROR_450,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_451", (char *) S_ftpLib_REMOTE_SERVER_ERROR_451,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_452", (char *) S_ftpLib_REMOTE_SERVER_ERROR_452,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_500", (char *) S_ftpLib_REMOTE_SERVER_ERROR_500,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_501", (char *) S_ftpLib_REMOTE_SERVER_ERROR_501,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_502", (char *) S_ftpLib_REMOTE_SERVER_ERROR_502,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_503", (char *) S_ftpLib_REMOTE_SERVER_ERROR_503,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_504", (char *) S_ftpLib_REMOTE_SERVER_ERROR_504,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_520", (char *) S_ftpLib_REMOTE_SERVER_ERROR_520,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_521", (char *) S_ftpLib_REMOTE_SERVER_ERROR_521,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_530", (char *) S_ftpLib_REMOTE_SERVER_ERROR_530,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_550", (char *) S_ftpLib_REMOTE_SERVER_ERROR_550,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_551", (char *) S_ftpLib_REMOTE_SERVER_ERROR_551,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_552", (char *) S_ftpLib_REMOTE_SERVER_ERROR_552,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_553", (char *) S_ftpLib_REMOTE_SERVER_ERROR_553,0,0,0},
    {{NULL},"S_ftpLib_REMOTE_SERVER_ERROR_554", (char *) S_ftpLib_REMOTE_SERVER_ERROR_554,0,0,0},
    {{NULL},"S_hashLib_KEY_CLASH", (char *) S_hashLib_KEY_CLASH,0,0,0},
    {{NULL},"S_hookLib_HOOK_TABLE_FULL", (char *) S_hookLib_HOOK_TABLE_FULL,0,0,0},
    {{NULL},"S_hookLib_HOOK_NOT_FOUND", (char *) S_hookLib_HOOK_NOT_FOUND,0,0,0},
    {{NULL},"S_hookLib_HOOK_TABLE_NULL", (char *) S_hookLib_HOOK_TABLE_NULL,0,0,0},
    {{NULL},"S_hostLib_UNKNOWN_HOST", (char *) S_hostLib_UNKNOWN_HOST,0,0,0},
    {{NULL},"S_hostLib_HOST_ALREADY_ENTERED", (char *) S_hostLib_HOST_ALREADY_ENTERED,0,0,0},
    {{NULL},"S_hostLib_INVALID_PARAMETER", (char *) S_hostLib_INVALID_PARAMETER,0,0,0},
    {{NULL},"S_hostLib_NETDB_INTERNAL", (char *) S_hostLib_NETDB_INTERNAL,0,0,0},
    {{NULL},"S_hostLib_HOST_NOT_FOUND", (char *) S_hostLib_HOST_NOT_FOUND,0,0,0},
    {{NULL},"S_hostLib_TRY_AGAIN", (char *) S_hostLib_TRY_AGAIN,0,0,0},
    {{NULL},"S_hostLib_NO_RECOVERY", (char *) S_hostLib_NO_RECOVERY,0,0,0},
    {{NULL},"S_inetLib_ILLEGAL_INTERNET_ADDRESS", (char *) S_inetLib_ILLEGAL_INTERNET_ADDRESS,0,0,0},
    {{NULL},"S_inetLib_ILLEGAL_NETWORK_NUMBER", (char *) S_inetLib_ILLEGAL_NETWORK_NUMBER,0,0,0},
    {{NULL},"S_intLib_NOT_ISR_CALLABLE", (char *) S_intLib_NOT_ISR_CALLABLE,0,0,0},
    {{NULL},"S_intLib_VEC_TABLE_WP_UNAVAILABLE", (char *) S_intLib_VEC_TABLE_WP_UNAVAILABLE,0,0,0},
    {{NULL},"S_ioLib_MEDIA_CHANGED", (char *) S_ioLib_MEDIA_CHANGED,0,0,0},
    {{NULL},"S_ipcom_ERR_FAILED", (char *) S_ipcom_ERR_FAILED,0,0,0},
    {{NULL},"S_ipcom_ERR_NO_MEMORY", (char *) S_ipcom_ERR_NO_MEMORY,0,0,0},
    {{NULL},"S_ipcom_ERR_NOT_FOUND", (char *) S_ipcom_ERR_NOT_FOUND,0,0,0},
    {{NULL},"S_ipcom_ERR_NOT_SUPPORTED", (char *) S_ipcom_ERR_NOT_SUPPORTED,0,0,0},
    {{NULL},"S_ipcom_ERR_PERMISSION_DENIED", (char *) S_ipcom_ERR_PERMISSION_DENIED,0,0,0},
    {{NULL},"S_ipcom_ERR_ALREADY_OPEN", (char *) S_ipcom_ERR_ALREADY_OPEN,0,0,0},
    {{NULL},"S_ipcom_ERR_ALREADY_CLOSED", (char *) S_ipcom_ERR_ALREADY_CLOSED,0,0,0},
    {{NULL},"S_ipcom_ERR_ALREADY_INSTALLED", (char *) S_ipcom_ERR_ALREADY_INSTALLED,0,0,0},
    {{NULL},"S_ipcom_ERR_ALREADY_STARTED", (char *) S_ipcom_ERR_ALREADY_STARTED,0,0,0},
    {{NULL},"S_ipcom_ERR_NOT_OPENED", (char *) S_ipcom_ERR_NOT_OPENED,0,0,0},
    {{NULL},"S_ipcom_ERR_NOT_CLOSED", (char *) S_ipcom_ERR_NOT_CLOSED,0,0,0},
    {{NULL},"S_ipcom_ERR_NOT_INSTALLED", (char *) S_ipcom_ERR_NOT_INSTALLED,0,0,0},
    {{NULL},"S_ipcom_ERR_NOT_STARTED", (char *) S_ipcom_ERR_NOT_STARTED,0,0,0},
    {{NULL},"S_ipcom_ERR_INVALID_ARG", (char *) S_ipcom_ERR_INVALID_ARG,0,0,0},
    {{NULL},"S_ipcom_ERR_INVALID_CONFIG", (char *) S_ipcom_ERR_INVALID_CONFIG,0,0,0},
    {{NULL},"S_ipcom_ERR_INVALID_VERSION", (char *) S_ipcom_ERR_INVALID_VERSION,0,0,0},
    {{NULL},"S_ipcom_ERR_INVALID_ALIGNMENT", (char *) S_ipcom_ERR_INVALID_ALIGNMENT,0,0,0},
    {{NULL},"S_ipcom_ERR_INVALID_INTERFACE", (char *) S_ipcom_ERR_INVALID_INTERFACE,0,0,0},
    {{NULL},"S_ipcom_ERR_NO_ROUTE", (char *) S_ipcom_ERR_NO_ROUTE,0,0,0},
    {{NULL},"S_ipcom_ERR_DEAD_ROUTE", (char *) S_ipcom_ERR_DEAD_ROUTE,0,0,0},
    {{NULL},"S_ipcom_ERR_INVALID_ROUTE", (char *) S_ipcom_ERR_INVALID_ROUTE,0,0,0},
    {{NULL},"S_ipcom_ERR_INVALID_MASK", (char *) S_ipcom_ERR_INVALID_MASK,0,0,0},
    {{NULL},"S_ipcom_ERR_INVALID_RTCLIENT", (char *) S_ipcom_ERR_INVALID_RTCLIENT,0,0,0},
    {{NULL},"S_ipcom_ERR_DUPLICATE", (char *) S_ipcom_ERR_DUPLICATE,0,0,0},
    {{NULL},"S_ipcom_ERR_LOCKED", (char *) S_ipcom_ERR_LOCKED,0,0,0},
    {{NULL},"S_ipcom_ERR_END", (char *) S_ipcom_ERR_END,0,0,0},
    {{NULL},"S_ipcom_ERR_READONLY", (char *) S_ipcom_ERR_READONLY,0,0,0},
    {{NULL},"S_ipcom_ERR_INVALID_TAG_VALUE", (char *) S_ipcom_ERR_INVALID_TAG_VALUE,0,0,0},
    {{NULL},"S_ipcom_ERR_UNSUPPORTED_TAG", (char *) S_ipcom_ERR_UNSUPPORTED_TAG,0,0,0},
    {{NULL},"S_ipcom_ERR_INVALID_PACKET", (char *) S_ipcom_ERR_INVALID_PACKET,0,0,0},
    {{NULL},"S_ipcom_ERR_BAD_PACKET", (char *) S_ipcom_ERR_BAD_PACKET,0,0,0},
    {{NULL},"S_ipcom_ERR_IGNORED_PACKET", (char *) S_ipcom_ERR_IGNORED_PACKET,0,0,0},
    {{NULL},"S_ipcom_ERR_SOCKCALLFAILED", (char *) S_ipcom_ERR_SOCKCALLFAILED,0,0,0},
    {{NULL},"S_ipcom_ERR_REACHED_MIN", (char *) S_ipcom_ERR_REACHED_MIN,0,0,0},
    {{NULL},"S_ipcom_ERR_REACHED_MAX", (char *) S_ipcom_ERR_REACHED_MAX,0,0,0},
    {{NULL},"S_ipcom_ERR_TIMEOUT", (char *) S_ipcom_ERR_TIMEOUT,0,0,0},
    {{NULL},"S_ipcom_ERR_WOULDBLOCK", (char *) S_ipcom_ERR_WOULDBLOCK,0,0,0},
    {{NULL},"S_ipcom_ERR_INTERRUPT", (char *) S_ipcom_ERR_INTERRUPT,0,0,0},
    {{NULL},"S_ipcom_ERR_PENDING", (char *) S_ipcom_ERR_PENDING,0,0,0},
    {{NULL},"S_ipcom_ERR_AUTH_FAILED", (char *) S_ipcom_ERR_AUTH_FAILED,0,0,0},
    {{NULL},"S_ipcom_ERR_AUTH_UNKNOWN", (char *) S_ipcom_ERR_AUTH_UNKNOWN,0,0,0},
    {{NULL},"S_ipcom_ENOMEDIUM", (char *) S_ipcom_ENOMEDIUM,0,0,0},
    {{NULL},"S_ipcom_EMEDIUMTYPE", (char *) S_ipcom_EMEDIUMTYPE,0,0,0},
    {{NULL},"S_ipcom_ENODATA", (char *) S_ipcom_ENODATA,0,0,0},
    {{NULL},"S_ipcom_ECOMM", (char *) S_ipcom_ECOMM,0,0,0},
    {{NULL},"S_ipcom_EINTERNAL", (char *) S_ipcom_EINTERNAL,0,0,0},
    {{NULL},"S_ipcom_ENOSUPPORT", (char *) S_ipcom_ENOSUPPORT,0,0,0},
    {{NULL},"S_ipcom_EINITFAILED", (char *) S_ipcom_EINITFAILED,0,0,0},
    {{NULL},"S_ipcom_ECONFIG", (char *) S_ipcom_ECONFIG,0,0,0},
    {{NULL},"S_ipcom_ENOTOME", (char *) S_ipcom_ENOTOME,0,0,0},
    {{NULL},"S_ipcom_ENOTFOUND", (char *) S_ipcom_ENOTFOUND,0,0,0},
    {{NULL},"S_ipcom_EFIREWALL", (char *) S_ipcom_EFIREWALL,0,0,0},
    {{NULL},"S_isrLib_ISR_NOT_INIT", (char *) S_isrLib_ISR_NOT_INIT,0,0,0},
    {{NULL},"S_isrLib_INVALID_PARAM", (char *) S_isrLib_INVALID_PARAM,0,0,0},
    {{NULL},"S_loadElfLib_HDR_READ", (char *) S_loadElfLib_HDR_READ,0,0,0},
    {{NULL},"S_loadElfLib_HDR_ERROR", (char *) S_loadElfLib_HDR_ERROR,0,0,0},
    {{NULL},"S_loadElfLib_PHDR_MALLOC", (char *) S_loadElfLib_PHDR_MALLOC,0,0,0},
    {{NULL},"S_loadElfLib_PHDR_READ", (char *) S_loadElfLib_PHDR_READ,0,0,0},
    {{NULL},"S_loadElfLib_SHDR_MALLOC", (char *) S_loadElfLib_SHDR_MALLOC,0,0,0},
    {{NULL},"S_loadElfLib_SHDR_READ", (char *) S_loadElfLib_SHDR_READ,0,0,0},
    {{NULL},"S_loadElfLib_READ_SECTIONS", (char *) S_loadElfLib_READ_SECTIONS,0,0,0},
    {{NULL},"S_loadElfLib_LOAD_SECTIONS", (char *) S_loadElfLib_LOAD_SECTIONS,0,0,0},
    {{NULL},"S_loadElfLib_LOAD_PROG", (char *) S_loadElfLib_LOAD_PROG,0,0,0},
    {{NULL},"S_loadElfLib_SYMTAB", (char *) S_loadElfLib_SYMTAB,0,0,0},
    {{NULL},"S_loadElfLib_RELA_SECTION", (char *) S_loadElfLib_RELA_SECTION,0,0,0},
    {{NULL},"S_loadElfLib_SCN_READ", (char *) S_loadElfLib_SCN_READ,0,0,0},
    {{NULL},"S_loadElfLib_SDA_MALLOC", (char *) S_loadElfLib_SDA_MALLOC,0,0,0},
    {{NULL},"S_loadElfLib_SST_READ", (char *) S_loadElfLib_SST_READ,0,0,0},
    {{NULL},"S_loadElfLib_JMPADDR_ERROR", (char *) S_loadElfLib_JMPADDR_ERROR,0,0,0},
    {{NULL},"S_loadElfLib_GPREL_REFERENCE", (char *) S_loadElfLib_GPREL_REFERENCE,0,0,0},
    {{NULL},"S_loadElfLib_UNRECOGNIZED_RELOCENTRY", (char *) S_loadElfLib_UNRECOGNIZED_RELOCENTRY,0,0,0},
    {{NULL},"S_loadElfLib_RELOC", (char *) S_loadElfLib_RELOC,0,0,0},
    {{NULL},"S_loadElfLib_UNSUPPORTED", (char *) S_loadElfLib_UNSUPPORTED,0,0,0},
    {{NULL},"S_loadElfLib_REL_SECTION", (char *) S_loadElfLib_REL_SECTION,0,0,0},
    {{NULL},"S_loadElfLib_INVALID_ARGUMENT", (char *) S_loadElfLib_INVALID_ARGUMENT,0,0,0},
    {{NULL},"S_loadElfLib_RELOCATION_OFFSET_TOO_LARGE", (char *) S_loadElfLib_RELOCATION_OFFSET_TOO_LARGE,0,0,0},
    {{NULL},"S_loadElfLib_RELOCATION_UNIT_NOT_INSTALLED", (char *) S_loadElfLib_RELOCATION_UNIT_NOT_INSTALLED,0,0,0},
    {{NULL},"S_loadElfLib_SIG_SECTION_ERROR", (char *) S_loadElfLib_SIG_SECTION_ERROR,0,0,0},
    {{NULL},"S_loadElfLib_SIG_KEY_INVALID", (char *) S_loadElfLib_SIG_KEY_INVALID,0,0,0},
    {{NULL},"S_loadLib_ROUTINE_NOT_INSTALLED", (char *) S_loadLib_ROUTINE_NOT_INSTALLED,0,0,0},
    {{NULL},"S_loadLib_TOO_MANY_SYMBOLS", (char *) S_loadLib_TOO_MANY_SYMBOLS,0,0,0},
    {{NULL},"S_loadLib_ILLEGAL_FLAGS_COMBINATION", (char *) S_loadLib_ILLEGAL_FLAGS_COMBINATION,0,0,0},
    {{NULL},"S_loadLib_INVALID_ARGUMENT", (char *) S_loadLib_INVALID_ARGUMENT,0,0,0},
    {{NULL},"S_loadLib_UNDEFINED_REFERENCES", (char *) S_loadLib_UNDEFINED_REFERENCES,0,0,0},
    {{NULL},"S_loadLib_UNSPECIFIED_SEGMENT_ADDRESS", (char *) S_loadLib_UNSPECIFIED_SEGMENT_ADDRESS,0,0,0},
    {{NULL},"S_loadLib_INVALID_LOAD_FLAG", (char *) S_loadLib_INVALID_LOAD_FLAG,0,0,0},
    {{NULL},"S_loadLib_SDA_NOT_SUPPORTED", (char *) S_loadLib_SDA_NOT_SUPPORTED,0,0,0},
    {{NULL},"S_loadLib_MISSING_SYMBOL_TABLE", (char *) S_loadLib_MISSING_SYMBOL_TABLE,0,0,0},
    {{NULL},"S_loadLib_ABI_MISMATCH", (char *) S_loadLib_ABI_MISMATCH,0,0,0},
    {{NULL},"S_loadLib_ISA_MISMATCH", (char *) S_loadLib_ISA_MISMATCH,0,0,0},
    {{NULL},"S_loadLib_INCOMPATIBLE_MODULE", (char *) S_loadLib_INCOMPATIBLE_MODULE,0,0,0},
    {{NULL},"S_loadLib_USR_INIT_ERROR", (char *) S_loadLib_USR_INIT_ERROR,0,0,0},
    {{NULL},"S_loadLib_ALREADY_LOADED", (char *) S_loadLib_ALREADY_LOADED,0,0,0},
    {{NULL},"S_m2Lib_INVALID_PARAMETER", (char *) S_m2Lib_INVALID_PARAMETER,0,0,0},
    {{NULL},"S_m2Lib_ENTRY_NOT_FOUND", (char *) S_m2Lib_ENTRY_NOT_FOUND,0,0,0},
    {{NULL},"S_m2Lib_TCPCONN_FD_NOT_FOUND", (char *) S_m2Lib_TCPCONN_FD_NOT_FOUND,0,0,0},
    {{NULL},"S_m2Lib_INVALID_VAR_TO_SET", (char *) S_m2Lib_INVALID_VAR_TO_SET,0,0,0},
    {{NULL},"S_m2Lib_CANT_CREATE_SYS_SEM", (char *) S_m2Lib_CANT_CREATE_SYS_SEM,0,0,0},
    {{NULL},"S_m2Lib_CANT_CREATE_IF_SEM", (char *) S_m2Lib_CANT_CREATE_IF_SEM,0,0,0},
    {{NULL},"S_m2Lib_CANT_CREATE_ROUTE_SEM", (char *) S_m2Lib_CANT_CREATE_ROUTE_SEM,0,0,0},
    {{NULL},"S_m2Lib_ARP_PHYSADDR_NOT_SPECIFIED", (char *) S_m2Lib_ARP_PHYSADDR_NOT_SPECIFIED,0,0,0},
    {{NULL},"S_m2Lib_IF_TBL_IS_EMPTY", (char *) S_m2Lib_IF_TBL_IS_EMPTY,0,0,0},
    {{NULL},"S_m2Lib_IF_CNFG_CHANGED", (char *) S_m2Lib_IF_CNFG_CHANGED,0,0,0},
    {{NULL},"S_m2Lib_TOO_BIG", (char *) S_m2Lib_TOO_BIG,0,0,0},
    {{NULL},"S_m2Lib_BAD_VALUE", (char *) S_m2Lib_BAD_VALUE,0,0,0},
    {{NULL},"S_m2Lib_READ_ONLY", (char *) S_m2Lib_READ_ONLY,0,0,0},
    {{NULL},"S_m2Lib_GEN_ERR", (char *) S_m2Lib_GEN_ERR,0,0,0},
    {{NULL},"S_memLib_INVALID_NBYTES", (char *) S_memLib_INVALID_NBYTES,0,0,0},
    {{NULL},"S_memLib_BLOCK_ERROR", (char *) S_memLib_BLOCK_ERROR,0,0,0},
    {{NULL},"S_memLib_NO_PARTITION_DESTROY", (char *) S_memLib_NO_PARTITION_DESTROY,0,0,0},
    {{NULL},"S_memLib_PAGE_SIZE_UNAVAILABLE", (char *) S_memLib_PAGE_SIZE_UNAVAILABLE,0,0,0},
    {{NULL},"S_memLib_WRONG_PART_ID", (char *) S_memLib_WRONG_PART_ID,0,0,0},
    {{NULL},"S_memLib_INVALID_ADDRESS", (char *) S_memLib_INVALID_ADDRESS,0,0,0},
    {{NULL},"S_memLib_INVALID_ALIGNMENT", (char *) S_memLib_INVALID_ALIGNMENT,0,0,0},
    {{NULL},"S_memLib_FUNC_NOT_AVAILABLE", (char *) S_memLib_FUNC_NOT_AVAILABLE,0,0,0},
    {{NULL},"S_memLib_MEM_ALLOC_ERROR_NO_ALLOC_SET", (char *) S_memLib_MEM_ALLOC_ERROR_NO_ALLOC_SET,0,0,0},
    {{NULL},"S_memLib_RTP_MEM_ALLOC_ERROR_NO_ALLOC_SET", (char *) S_memLib_RTP_MEM_ALLOC_ERROR_NO_ALLOC_SET,0,0,0},
    {{NULL},"S_memLib_RTP_MEM_FREE_ERROR_NO_ALLOC_SET", (char *) S_memLib_RTP_MEM_FREE_ERROR_NO_ALLOC_SET,0,0,0},
    {{NULL},"S_miiLib_PHY_LINK_DOWN", (char *) S_miiLib_PHY_LINK_DOWN,0,0,0},
    {{NULL},"S_miiLib_PHY_NULL", (char *) S_miiLib_PHY_NULL,0,0,0},
    {{NULL},"S_miiLib_PHY_NO_ABLE", (char *) S_miiLib_PHY_NO_ABLE,0,0,0},
    {{NULL},"S_miiLib_PHY_AN_FAIL", (char *) S_miiLib_PHY_AN_FAIL,0,0,0},
    {{NULL},"S_mmuLib_INVALID_PAGE_SIZE", (char *) S_mmuLib_INVALID_PAGE_SIZE,0,0,0},
    {{NULL},"S_mmuLib_NO_DESCRIPTOR", (char *) S_mmuLib_NO_DESCRIPTOR,0,0,0},
    {{NULL},"S_mmuLib_INVALID_DESCRIPTOR", (char *) S_mmuLib_INVALID_DESCRIPTOR,0,0,0},
    {{NULL},"S_mmuLib_OUT_OF_PMEGS", (char *) S_mmuLib_OUT_OF_PMEGS,0,0,0},
    {{NULL},"S_mmuLib_VIRT_ADDR_OUT_OF_BOUNDS", (char *) S_mmuLib_VIRT_ADDR_OUT_OF_BOUNDS,0,0,0},
    {{NULL},"S_mmuLib_TLB_LOCKED_PAGE", (char *) S_mmuLib_TLB_LOCKED_PAGE,0,0,0},
    {{NULL},"S_mmuLib_TLB_PAGE_NOT_LOCKED", (char *) S_mmuLib_TLB_PAGE_NOT_LOCKED,0,0,0},
    {{NULL},"S_mmuLib_LOCK_NO_MORE_TLB_RESOURCES", (char *) S_mmuLib_LOCK_NO_MORE_TLB_RESOURCES,0,0,0},
    {{NULL},"S_mmuLib_NOT_CONTIGUOUS_ADDR", (char *) S_mmuLib_NOT_CONTIGUOUS_ADDR,0,0,0},
    {{NULL},"S_mmuLib_NOT_CONTIGUOUS_STATE", (char *) S_mmuLib_NOT_CONTIGUOUS_STATE,0,0,0},
    {{NULL},"S_mmuLib_ISR_CALL_BLOCKED", (char *) S_mmuLib_ISR_CALL_BLOCKED,0,0,0},
    {{NULL},"S_mmuLib_MARKED_ISR_CALLABLE", (char *) S_mmuLib_MARKED_ISR_CALLABLE,0,0,0},
    {{NULL},"S_mmuLib_NOT_GLOBAL_PAGE", (char *) S_mmuLib_NOT_GLOBAL_PAGE,0,0,0},
    {{NULL},"S_mmulib_LOCK_REQUIRED", (char *) S_mmulib_LOCK_REQUIRED,0,0,0},
    {{NULL},"S_mmulib_INVALID_PHYS_ADDR", (char *) S_mmulib_INVALID_PHYS_ADDR,0,0,0},
    {{NULL},"S_mmulib_VIRT_ADDR_ALREADY_MAPPED", (char *) S_mmulib_VIRT_ADDR_ALREADY_MAPPED,0,0,0},
    {{NULL},"S_mmuLib_INVALID_UNION_INIT", (char *) S_mmuLib_INVALID_UNION_INIT,0,0,0},
    {{NULL},"S_mmuLib_INVALID_ATTR", (char *) S_mmuLib_INVALID_ATTR,0,0,0},
    {{NULL},"S_mmuLib_INVALID_GLOBAL_PAGE_OP", (char *) S_mmuLib_INVALID_GLOBAL_PAGE_OP,0,0,0},
    {{NULL},"S_moduleLib_MODULE_NOT_FOUND", (char *) S_moduleLib_MODULE_NOT_FOUND,0,0,0},
    {{NULL},"S_moduleLib_HOOK_NOT_FOUND", (char *) S_moduleLib_HOOK_NOT_FOUND,0,0,0},
    {{NULL},"S_moduleLib_BAD_CHECKSUM", (char *) S_moduleLib_BAD_CHECKSUM,0,0,0},
    {{NULL},"S_moduleLib_MAX_MODULES_LOADED", (char *) S_moduleLib_MAX_MODULES_LOADED,0,0,0},
    {{NULL},"S_moduleLib_INVALID_SECTION_ID", (char *) S_moduleLib_INVALID_SECTION_ID,0,0,0},
    {{NULL},"S_moduleLib_INVALID_MODULE_ID", (char *) S_moduleLib_INVALID_MODULE_ID,0,0,0},
    {{NULL},"S_msgQLib_INVALID_MSG_LENGTH", (char *) S_msgQLib_INVALID_MSG_LENGTH,0,0,0},
    {{NULL},"S_msgQLib_NON_ZERO_TIMEOUT_AT_INT_LEVEL", (char *) S_msgQLib_NON_ZERO_TIMEOUT_AT_INT_LEVEL,0,0,0},
    {{NULL},"S_msgQLib_INVALID_QUEUE_TYPE", (char *) S_msgQLib_INVALID_QUEUE_TYPE,0,0,0},
    {{NULL},"S_msgQLib_ILLEGAL_OPTIONS", (char *) S_msgQLib_ILLEGAL_OPTIONS,0,0,0},
    {{NULL},"S_msgQLib_ILLEGAL_PRIORITY", (char *) S_msgQLib_ILLEGAL_PRIORITY,0,0,0},
    {{NULL},"S_msgQLib_UNSUPPORTED_OPERATION", (char *) S_msgQLib_UNSUPPORTED_OPERATION,0,0,0},
    {{NULL},"S_msgQLib_INVALID_MSG_COUNT", (char *) S_msgQLib_INVALID_MSG_COUNT,0,0,0},
    {{NULL},"S_muxLib_LOAD_FAILED", (char *) S_muxLib_LOAD_FAILED,0,0,0},
    {{NULL},"S_muxLib_NO_DEVICE", (char *) S_muxLib_NO_DEVICE,0,0,0},
    {{NULL},"S_muxLib_INVALID_ARGS", (char *) S_muxLib_INVALID_ARGS,0,0,0},
    {{NULL},"S_muxLib_ALLOC_FAILED", (char *) S_muxLib_ALLOC_FAILED,0,0,0},
    {{NULL},"S_muxLib_ALREADY_BOUND", (char *) S_muxLib_ALREADY_BOUND,0,0,0},
    {{NULL},"S_muxLib_UNLOAD_FAILED", (char *) S_muxLib_UNLOAD_FAILED,0,0,0},
    {{NULL},"S_muxLib_NOT_A_TK_DEVICE", (char *) S_muxLib_NOT_A_TK_DEVICE,0,0,0},
    {{NULL},"S_muxLib_NO_TK_DEVICE", (char *) S_muxLib_NO_TK_DEVICE,0,0,0},
    {{NULL},"S_muxLib_END_BIND_FAILED", (char *) S_muxLib_END_BIND_FAILED,0,0,0},
    {{NULL},"S_muxLib_MISSING_WRAPPERS", (char *) S_muxLib_MISSING_WRAPPERS,0,0,0},
    {{NULL},"S_muxLib_END_SUSPEND_FAILED", (char *) S_muxLib_END_SUSPEND_FAILED,0,0,0},
    {{NULL},"S_muxLib_NO_LAUNCH_CAPABILITY", (char *) S_muxLib_NO_LAUNCH_CAPABILITY,0,0,0},
    {{NULL},"S_muxLib_LAUNCH_OVERFLOW", (char *) S_muxLib_LAUNCH_OVERFLOW,0,0,0},
    {{NULL},"S_muxLib_LAUNCH_MISSED", (char *) S_muxLib_LAUNCH_MISSED,0,0,0},
    {{NULL},"S_muxLib_LAUNCH_SETUP_FAILED", (char *) S_muxLib_LAUNCH_SETUP_FAILED,0,0,0},
    {{NULL},"S_netBufLib_MEMSIZE_INVALID", (char *) S_netBufLib_MEMSIZE_INVALID,0,0,0},
    {{NULL},"S_netBufLib_CLSIZE_INVALID", (char *) S_netBufLib_CLSIZE_INVALID,0,0,0},
    {{NULL},"S_netBufLib_NO_SYSTEM_MEMORY", (char *) S_netBufLib_NO_SYSTEM_MEMORY,0,0,0},
    {{NULL},"S_netBufLib_MEM_UNALIGNED", (char *) S_netBufLib_MEM_UNALIGNED,0,0,0},
    {{NULL},"S_netBufLib_MEMSIZE_UNALIGNED", (char *) S_netBufLib_MEMSIZE_UNALIGNED,0,0,0},
    {{NULL},"S_netBufLib_MEMAREA_INVALID", (char *) S_netBufLib_MEMAREA_INVALID,0,0,0},
    {{NULL},"S_netBufLib_MBLK_INVALID", (char *) S_netBufLib_MBLK_INVALID,0,0,0},
    {{NULL},"S_netBufLib_NETPOOL_INVALID", (char *) S_netBufLib_NETPOOL_INVALID,0,0,0},
    {{NULL},"S_netBufLib_INVALID_ARGUMENT", (char *) S_netBufLib_INVALID_ARGUMENT,0,0,0},
    {{NULL},"S_netBufLib_NO_POOL_MEMORY", (char *) S_netBufLib_NO_POOL_MEMORY,0,0,0},
    {{NULL},"S_netBufLib_LIB_NOT_INITIALIZED", (char *) S_netBufLib_LIB_NOT_INITIALIZED,0,0,0},
    {{NULL},"S_netBufLib_POOL_FEATURE_NOT_SUPPORTED", (char *) S_netBufLib_POOL_FEATURE_NOT_SUPPORTED,0,0,0},
    {{NULL},"S_netBufLib_DUPLICATE_POOL", (char *) S_netBufLib_DUPLICATE_POOL,0,0,0},
    {{NULL},"S_netBufLib_POOL_RELEASED", (char *) S_netBufLib_POOL_RELEASED,0,0,0},
    {{NULL},"S_netBufLib_POOL_RELEASE_IGNORE", (char *) S_netBufLib_POOL_RELEASE_IGNORE,0,0,0},
    {{NULL},"S_netDrv_INVALID_NUMBER_OF_BYTES", (char *) S_netDrv_INVALID_NUMBER_OF_BYTES,0,0,0},
    {{NULL},"S_netDrv_SEND_ERROR", (char *) S_netDrv_SEND_ERROR,0,0,0},
    {{NULL},"S_netDrv_RECV_ERROR", (char *) S_netDrv_RECV_ERROR,0,0,0},
    {{NULL},"S_netDrv_UNKNOWN_REQUEST", (char *) S_netDrv_UNKNOWN_REQUEST,0,0,0},
    {{NULL},"S_netDrv_BAD_SEEK", (char *) S_netDrv_BAD_SEEK,0,0,0},
    {{NULL},"S_netDrv_SEEK_PAST_EOF_ERROR", (char *) S_netDrv_SEEK_PAST_EOF_ERROR,0,0,0},
    {{NULL},"S_netDrv_BAD_EOF_POSITION", (char *) S_netDrv_BAD_EOF_POSITION,0,0,0},
    {{NULL},"S_netDrv_SEEK_FATAL_ERROR", (char *) S_netDrv_SEEK_FATAL_ERROR,0,0,0},
    {{NULL},"S_netDrv_WRITE_ONLY_CANNOT_READ", (char *) S_netDrv_WRITE_ONLY_CANNOT_READ,0,0,0},
    {{NULL},"S_netDrv_READ_ONLY_CANNOT_WRITE", (char *) S_netDrv_READ_ONLY_CANNOT_WRITE,0,0,0},
    {{NULL},"S_netDrv_READ_ERROR", (char *) S_netDrv_READ_ERROR,0,0,0},
    {{NULL},"S_netDrv_WRITE_ERROR", (char *) S_netDrv_WRITE_ERROR,0,0,0},
    {{NULL},"S_netDrv_NO_SUCH_FILE_OR_DIR", (char *) S_netDrv_NO_SUCH_FILE_OR_DIR,0,0,0},
    {{NULL},"S_netDrv_PERMISSION_DENIED", (char *) S_netDrv_PERMISSION_DENIED,0,0,0},
    {{NULL},"S_netDrv_IS_A_DIRECTORY", (char *) S_netDrv_IS_A_DIRECTORY,0,0,0},
    {{NULL},"S_netDrv_UNIX_FILE_ERROR", (char *) S_netDrv_UNIX_FILE_ERROR,0,0,0},
    {{NULL},"S_netDrv_ILLEGAL_VALUE", (char *) S_netDrv_ILLEGAL_VALUE,0,0,0},
    {{NULL},"S_mountLib_ILLEGAL_MODE", (char *) S_mountLib_ILLEGAL_MODE,0,0,0},
    {{NULL},"S_nfsLib_NFS_AUTH_UNIX_FAILED", (char *) S_nfsLib_NFS_AUTH_UNIX_FAILED,0,0,0},
    {{NULL},"S_nfsLib_NFS_INAPPLICABLE_FILE_TYPE", (char *) S_nfsLib_NFS_INAPPLICABLE_FILE_TYPE,0,0,0},
    {{NULL},"S_nfsLib_NFS_OK", (char *) S_nfsLib_NFS_OK,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_PERM", (char *) S_nfsLib_NFSERR_PERM,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_NOENT", (char *) S_nfsLib_NFSERR_NOENT,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_IO", (char *) S_nfsLib_NFSERR_IO,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_NXIO", (char *) S_nfsLib_NFSERR_NXIO,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_ACCESS", (char *) S_nfsLib_NFSERR_ACCESS,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_EXIST", (char *) S_nfsLib_NFSERR_EXIST,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_NODEV", (char *) S_nfsLib_NFSERR_NODEV,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_NOTDIR", (char *) S_nfsLib_NFSERR_NOTDIR,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_ISDIR", (char *) S_nfsLib_NFSERR_ISDIR,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_INVAL", (char *) S_nfsLib_NFSERR_INVAL,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_FBIG", (char *) S_nfsLib_NFSERR_FBIG,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_NOSPC", (char *) S_nfsLib_NFSERR_NOSPC,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_ROFS", (char *) S_nfsLib_NFSERR_ROFS,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_NAMETOOLONG", (char *) S_nfsLib_NFSERR_NAMETOOLONG,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_NOTEMPTY", (char *) S_nfsLib_NFSERR_NOTEMPTY,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_DQUOT", (char *) S_nfsLib_NFSERR_DQUOT,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_STALE", (char *) S_nfsLib_NFSERR_STALE,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_WFLUSH", (char *) S_nfsLib_NFSERR_WFLUSH,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_REMOTE", (char *) S_nfsLib_NFSERR_REMOTE,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_BADHANDLE", (char *) S_nfsLib_NFSERR_BADHANDLE,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_NOT_SYNC", (char *) S_nfsLib_NFSERR_NOT_SYNC,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_BAD_COOKIE", (char *) S_nfsLib_NFSERR_BAD_COOKIE,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_NOTSUPP", (char *) S_nfsLib_NFSERR_NOTSUPP,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_TOOSMALL", (char *) S_nfsLib_NFSERR_TOOSMALL,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_SERVERFAULT", (char *) S_nfsLib_NFSERR_SERVERFAULT,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_BADTYPE", (char *) S_nfsLib_NFSERR_BADTYPE,0,0,0},
    {{NULL},"S_nfsLib_NFSERR_JUKEBOX", (char *) S_nfsLib_NFSERR_JUKEBOX,0,0,0},
    {{NULL},"S_nfsDrv_INVALID_NUMBER_OF_BYTES", (char *) S_nfsDrv_INVALID_NUMBER_OF_BYTES,0,0,0},
    {{NULL},"S_nfsDrv_BAD_FLAG_MODE", (char *) S_nfsDrv_BAD_FLAG_MODE,0,0,0},
    {{NULL},"S_nfsDrv_CREATE_NO_FILE_NAME", (char *) S_nfsDrv_CREATE_NO_FILE_NAME,0,0,0},
    {{NULL},"S_nfsDrv_FATAL_ERR_FLUSH_INVALID_CACHE", (char *) S_nfsDrv_FATAL_ERR_FLUSH_INVALID_CACHE,0,0,0},
    {{NULL},"S_nfsDrv_WRITE_ONLY_CANNOT_READ", (char *) S_nfsDrv_WRITE_ONLY_CANNOT_READ,0,0,0},
    {{NULL},"S_nfsDrv_READ_ONLY_CANNOT_WRITE", (char *) S_nfsDrv_READ_ONLY_CANNOT_WRITE,0,0,0},
    {{NULL},"S_nfsDrv_NOT_AN_NFS_DEVICE", (char *) S_nfsDrv_NOT_AN_NFS_DEVICE,0,0,0},
    {{NULL},"S_nfsDrv_NO_HOST_NAME_SPECIFIED", (char *) S_nfsDrv_NO_HOST_NAME_SPECIFIED,0,0,0},
    {{NULL},"S_nfsDrv_PERMISSION_DENIED", (char *) S_nfsDrv_PERMISSION_DENIED,0,0,0},
    {{NULL},"S_nfsDrv_NO_SUCH_FILE_OR_DIR", (char *) S_nfsDrv_NO_SUCH_FILE_OR_DIR,0,0,0},
    {{NULL},"S_nfsDrv_IS_A_DIRECTORY", (char *) S_nfsDrv_IS_A_DIRECTORY,0,0,0},
    {{NULL},"S_objLib_OBJ_ID_ERROR", (char *) S_objLib_OBJ_ID_ERROR,0,0,0},
    {{NULL},"S_objLib_OBJ_UNAVAILABLE", (char *) S_objLib_OBJ_UNAVAILABLE,0,0,0},
    {{NULL},"S_objLib_OBJ_DELETED", (char *) S_objLib_OBJ_DELETED,0,0,0},
    {{NULL},"S_objLib_OBJ_TIMEOUT", (char *) S_objLib_OBJ_TIMEOUT,0,0,0},
    {{NULL},"S_objLib_OBJ_NO_METHOD", (char *) S_objLib_OBJ_NO_METHOD,0,0,0},
    {{NULL},"S_objLib_OBJ_NO_ACCESS_RIGHTS", (char *) S_objLib_OBJ_NO_ACCESS_RIGHTS,0,0,0},
    {{NULL},"S_objLib_OBJ_NAME_TRUNCATED", (char *) S_objLib_OBJ_NAME_TRUNCATED,0,0,0},
    {{NULL},"S_objLib_OBJ_NAME_CLASH", (char *) S_objLib_OBJ_NAME_CLASH,0,0,0},
    {{NULL},"S_objLib_OBJ_NOT_NAMED", (char *) S_objLib_OBJ_NOT_NAMED,0,0,0},
    {{NULL},"S_objLib_OBJ_ILLEGAL_CLASS_TYPE", (char *) S_objLib_OBJ_ILLEGAL_CLASS_TYPE,0,0,0},
    {{NULL},"S_objLib_OBJ_OPERATION_UNSUPPORTED", (char *) S_objLib_OBJ_OPERATION_UNSUPPORTED,0,0,0},
    {{NULL},"S_objLib_OBJ_INVALID_OWNER", (char *) S_objLib_OBJ_INVALID_OWNER,0,0,0},
    {{NULL},"S_objLib_OBJ_RENAME_NOT_ALLOWED", (char *) S_objLib_OBJ_RENAME_NOT_ALLOWED,0,0,0},
    {{NULL},"S_objLib_OBJ_DESTROY_ERROR", (char *) S_objLib_OBJ_DESTROY_ERROR,0,0,0},
    {{NULL},"S_objLib_OBJ_HANDLE_TBL_FULL", (char *) S_objLib_OBJ_HANDLE_TBL_FULL,0,0,0},
    {{NULL},"S_objLib_OBJ_NOT_FOUND", (char *) S_objLib_OBJ_NOT_FOUND,0,0,0},
    {{NULL},"S_objLib_OBJ_INVALID_ARGUMENT", (char *) S_objLib_OBJ_INVALID_ARGUMENT,0,0,0},
    {{NULL},"S_objLib_OBJ_LIB_NOT_INITIALIZED", (char *) S_objLib_OBJ_LIB_NOT_INITIALIZED,0,0,0},
    {{NULL},"S_objLib_ACCESS_DENIED", (char *) S_objLib_ACCESS_DENIED,0,0,0},
    {{NULL},"S_pingLib_NOT_INITIALIZED", (char *) S_pingLib_NOT_INITIALIZED,0,0,0},
    {{NULL},"S_pingLib_TIMEOUT", (char *) S_pingLib_TIMEOUT,0,0,0},
    {{NULL},"S_poolLib_ARG_NOT_VALID", (char *) S_poolLib_ARG_NOT_VALID,0,0,0},
    {{NULL},"S_poolLib_INVALID_POOL_ID", (char *) S_poolLib_INVALID_POOL_ID,0,0,0},
    {{NULL},"S_poolLib_NOT_POOL_ITEM", (char *) S_poolLib_NOT_POOL_ITEM,0,0,0},
    {{NULL},"S_poolLib_UNUSED_ITEM", (char *) S_poolLib_UNUSED_ITEM,0,0,0},
    {{NULL},"S_poolLib_POOL_IN_USE", (char *) S_poolLib_POOL_IN_USE,0,0,0},
    {{NULL},"S_poolLib_STATIC_POOL_EMPTY", (char *) S_poolLib_STATIC_POOL_EMPTY,0,0,0},
    {{NULL},"S_poolLib_INVALID_BLK_ADDR", (char *) S_poolLib_INVALID_BLK_ADDR,0,0,0},
    {{NULL},"S_poolLib_BLOCK_TOO_SMALL", (char *) S_poolLib_BLOCK_TOO_SMALL,0,0,0},
    {{NULL},"S_poolLib_INT_CTX_POOL_EMPTY", (char *) S_poolLib_INT_CTX_POOL_EMPTY,0,0,0},
    {{NULL},"S_coprocLib_ALLOC_FAILED", (char *) S_coprocLib_ALLOC_FAILED,0,0,0},
    {{NULL},"S_coprocLib_COPROC_ENABLE_FAILED", (char *) S_coprocLib_COPROC_ENABLE_FAILED,0,0,0},
    {{NULL},"S_coprocLib_COPROC_DISABLE_FAILED", (char *) S_coprocLib_COPROC_DISABLE_FAILED,0,0,0},
    {{NULL},"S_coprocLib_EXCHANDLER_REGISTER_FAILED", (char *) S_coprocLib_EXCHANDLER_REGISTER_FAILED,0,0,0},
    {{NULL},"S_coprocLib_HOOK_ATTACH_FAILED", (char *) S_coprocLib_HOOK_ATTACH_FAILED,0,0,0},
    {{NULL},"S_coprocLib_INVALID_ARGUMENT", (char *) S_coprocLib_INVALID_ARGUMENT,0,0,0},
    {{NULL},"S_coprocLib_INVALID_OPERATION", (char *) S_coprocLib_INVALID_OPERATION,0,0,0},
    {{NULL},"S_coprocLib_NO_COPROC_SUPPORT", (char *) S_coprocLib_NO_COPROC_SUPPORT,0,0,0},
    {{NULL},"S_loadRtpLib_INVALID_ARGUMENT", (char *) S_loadRtpLib_INVALID_ARGUMENT,0,0,0},
    {{NULL},"S_loadRtpLib_INVALID_OPTION", (char *) S_loadRtpLib_INVALID_OPTION,0,0,0},
    {{NULL},"S_loadRtpLib_SYMTBL_DESTROY_INCOMPLETE", (char *) S_loadRtpLib_SYMTBL_DESTROY_INCOMPLETE,0,0,0},
    {{NULL},"S_loadRtpLib_TOO_MANY_SEGMENTS", (char *) S_loadRtpLib_TOO_MANY_SEGMENTS,0,0,0},
    {{NULL},"S_loadRtpLib_NO_LOADABLE_SEGMENT", (char *) S_loadRtpLib_NO_LOADABLE_SEGMENT,0,0,0},
    {{NULL},"S_loadRtpLib_ADDRESS_OVERFLOW", (char *) S_loadRtpLib_ADDRESS_OVERFLOW,0,0,0},
    {{NULL},"S_loadRtpLib_SEGMENT_READ", (char *) S_loadRtpLib_SEGMENT_READ,0,0,0},
    {{NULL},"S_loadRtpLib_COMMON_SYMBOL", (char *) S_loadRtpLib_COMMON_SYMBOL,0,0,0},
    {{NULL},"S_loadRtpLib_UNDEFINED_SYMBOL", (char *) S_loadRtpLib_UNDEFINED_SYMBOL,0,0,0},
    {{NULL},"S_loadRtpLib_NO_RELOCATION_SECTION", (char *) S_loadRtpLib_NO_RELOCATION_SECTION,0,0,0},
    {{NULL},"S_loadRtpLib_NOT_EXECUTABLE", (char *) S_loadRtpLib_NOT_EXECUTABLE,0,0,0},
    {{NULL},"S_loadRtpLib_NO_ENTRY_POINT", (char *) S_loadRtpLib_NO_ENTRY_POINT,0,0,0},
    {{NULL},"S_loadRtpLib_NO_PROG_HDR", (char *) S_loadRtpLib_NO_PROG_HDR,0,0,0},
    {{NULL},"S_loadRtpLib_FIRST_LOAD_SEG_NOT_EXECUTABLE", (char *) S_loadRtpLib_FIRST_LOAD_SEG_NOT_EXECUTABLE,0,0,0},
    {{NULL},"S_loadRtpLib_SECOND_LOAD_SEG_NOT_WRITEABLE", (char *) S_loadRtpLib_SECOND_LOAD_SEG_NOT_WRITEABLE,0,0,0},
    {{NULL},"S_loadRtpLib_DATA_SEG_BEFORE_TEXT_SEG", (char *) S_loadRtpLib_DATA_SEG_BEFORE_TEXT_SEG,0,0,0},
    {{NULL},"S_loadRtpLib_TOO_FEW_SEGMENTS", (char *) S_loadRtpLib_TOO_FEW_SEGMENTS,0,0,0},
    {{NULL},"S_loadRtpLib_INVALID_SEGMENTS", (char *) S_loadRtpLib_INVALID_SEGMENTS,0,0,0},
    {{NULL},"S_loadRtpLib_DYNAMIC_SEGMENTS_NOT_SUPPORTED", (char *) S_loadRtpLib_DYNAMIC_SEGMENTS_NOT_SUPPORTED,0,0,0},
    {{NULL},"S_loadRtpLib_INSUFFICIENT_MEMORY", (char *) S_loadRtpLib_INSUFFICIENT_MEMORY,0,0,0},
    {{NULL},"S_pgPoolLib_INVALID_PAGE_SIZE", (char *) S_pgPoolLib_INVALID_PAGE_SIZE,0,0,0},
    {{NULL},"S_pgPoolLib_INVALID_PAGE_COUNT", (char *) S_pgPoolLib_INVALID_PAGE_COUNT,0,0,0},
    {{NULL},"S_pgPoolLib_INVALID_ALIGNMENT", (char *) S_pgPoolLib_INVALID_ALIGNMENT,0,0,0},
    {{NULL},"S_pgPoolLib_NOT_ENOUGH_FREE_PAGES", (char *) S_pgPoolLib_NOT_ENOUGH_FREE_PAGES,0,0,0},
    {{NULL},"S_pgPoolLib_PAGE_RANGE_OUT_OF_POOL", (char *) S_pgPoolLib_PAGE_RANGE_OUT_OF_POOL,0,0,0},
    {{NULL},"S_pgPoolLib_PAGE_OVERLAP", (char *) S_pgPoolLib_PAGE_OVERLAP,0,0,0},
    {{NULL},"S_pgPoolLib_PAGES_NOT_FREE", (char *) S_pgPoolLib_PAGES_NOT_FREE,0,0,0},
    {{NULL},"S_pgPoolLib_PAGES_NOT_ALLOCATED", (char *) S_pgPoolLib_PAGES_NOT_ALLOCATED,0,0,0},
    {{NULL},"S_pgPoolLib_INVALID_POOL_TYPE", (char *) S_pgPoolLib_INVALID_POOL_TYPE,0,0,0},
    {{NULL},"S_pgPoolLib_INVALID_STATE", (char *) S_pgPoolLib_INVALID_STATE,0,0,0},
    {{NULL},"S_pgPoolLib_ALLOC_ERROR_NO_ALLOC_SET", (char *) S_pgPoolLib_ALLOC_ERROR_NO_ALLOC_SET,0,0,0},
    {{NULL},"S_taskPxLib_ILLEGAL_PRIORITY", (char *) S_taskPxLib_ILLEGAL_PRIORITY,0,0,0},
    {{NULL},"S_taskPxLib_ILLEGAL_POLICY", (char *) S_taskPxLib_ILLEGAL_POLICY,0,0,0},
    {{NULL},"S_taskPxLib_NOT_ENOUGH_ATTRS", (char *) S_taskPxLib_NOT_ENOUGH_ATTRS,0,0,0},
    {{NULL},"S_taskPxLib_INVALID_INITBUDGET", (char *) S_taskPxLib_INVALID_INITBUDGET,0,0,0},
    {{NULL},"S_taskPxLib_INVALID_MAXREPL", (char *) S_taskPxLib_INVALID_MAXREPL,0,0,0},
    {{NULL},"S_taskPxLib_NOT_SPECIFY_POLICY", (char *) S_taskPxLib_NOT_SPECIFY_POLICY,0,0,0},
    {{NULL},"S_taskPxLib_CHANGE_SS_POLICY", (char *) S_taskPxLib_CHANGE_SS_POLICY,0,0,0},
    {{NULL},"S_taskPxLib_NOT_CONFIG_SCHED_SPORADIC", (char *) S_taskPxLib_NOT_CONFIG_SCHED_SPORADIC,0,0,0},
    {{NULL},"S_rawFsLib_VOLUME_NOT_AVAILABLE", (char *) S_rawFsLib_VOLUME_NOT_AVAILABLE,0,0,0},
    {{NULL},"S_rawFsLib_END_OF_DEVICE", (char *) S_rawFsLib_END_OF_DEVICE,0,0,0},
    {{NULL},"S_rawFsLib_NO_FREE_FILE_DESCRIPTORS", (char *) S_rawFsLib_NO_FREE_FILE_DESCRIPTORS,0,0,0},
    {{NULL},"S_rawFsLib_INVALID_NUMBER_OF_BYTES", (char *) S_rawFsLib_INVALID_NUMBER_OF_BYTES,0,0,0},
    {{NULL},"S_rawFsLib_ILLEGAL_NAME", (char *) S_rawFsLib_ILLEGAL_NAME,0,0,0},
    {{NULL},"S_rawFsLib_NOT_FILE", (char *) S_rawFsLib_NOT_FILE,0,0,0},
    {{NULL},"S_rawFsLib_READ_ONLY", (char *) S_rawFsLib_READ_ONLY,0,0,0},
    {{NULL},"S_rawFsLib_FD_OBSOLETE", (char *) S_rawFsLib_FD_OBSOLETE,0,0,0},
    {{NULL},"S_rawFsLib_NO_BLOCK_DEVICE", (char *) S_rawFsLib_NO_BLOCK_DEVICE,0,0,0},
    {{NULL},"S_rawFsLib_BAD_SEEK", (char *) S_rawFsLib_BAD_SEEK,0,0,0},
    {{NULL},"S_rawFsLib_INVALID_PARAMETER", (char *) S_rawFsLib_INVALID_PARAMETER,0,0,0},
    {{NULL},"S_rawFsLib_32BIT_OVERFLOW", (char *) S_rawFsLib_32BIT_OVERFLOW,0,0,0},
    {{NULL},"S_rawFsLib_WRITE_ONLY", (char *) S_rawFsLib_WRITE_ONLY,0,0,0},
    {{NULL},"S_remLib_ALL_PORTS_IN_USE", (char *) S_remLib_ALL_PORTS_IN_USE,0,0,0},
    {{NULL},"S_remLib_RSH_ERROR", (char *) S_remLib_RSH_ERROR,0,0,0},
    {{NULL},"S_remLib_IDENTITY_TOO_BIG", (char *) S_remLib_IDENTITY_TOO_BIG,0,0,0},
    {{NULL},"S_remLib_RSH_STDERR_SETUP_FAILED", (char *) S_remLib_RSH_STDERR_SETUP_FAILED,0,0,0},
    {{NULL},"S_remLib_RCMD_INPUT_ERROR", (char *) S_remLib_RCMD_INPUT_ERROR,0,0,0},
    {{NULL},"S_resolvLib_NO_RECOVERY", (char *) S_resolvLib_NO_RECOVERY,0,0,0},
    {{NULL},"S_resolvLib_TRY_AGAIN", (char *) S_resolvLib_TRY_AGAIN,0,0,0},
    {{NULL},"S_resolvLib_HOST_NOT_FOUND", (char *) S_resolvLib_HOST_NOT_FOUND,0,0,0},
    {{NULL},"S_resolvLib_NO_DATA", (char *) S_resolvLib_NO_DATA,0,0,0},
    {{NULL},"S_resolvLib_BUFFER_2_SMALL", (char *) S_resolvLib_BUFFER_2_SMALL,0,0,0},
    {{NULL},"S_resolvLib_INVALID_PARAMETER", (char *) S_resolvLib_INVALID_PARAMETER,0,0,0},
    {{NULL},"S_resolvLib_INVALID_ADDRESS", (char *) S_resolvLib_INVALID_ADDRESS,0,0,0},
    {{NULL},"S_routeLib_ILLEGAL_INTERNET_ADDRESS", (char *) S_routeLib_ILLEGAL_INTERNET_ADDRESS,0,0,0},
    {{NULL},"S_routeLib_ILLEGAL_NETWORK_NUMBER", (char *) S_routeLib_ILLEGAL_NETWORK_NUMBER,0,0,0},
    {{NULL},"S_rpcLib_RPC_SUCCESS", (char *) S_rpcLib_RPC_SUCCESS,0,0,0},
    {{NULL},"S_rpcLib_RPC_CANTENCODEARGS", (char *) S_rpcLib_RPC_CANTENCODEARGS,0,0,0},
    {{NULL},"S_rpcLib_RPC_CANTDECODERES", (char *) S_rpcLib_RPC_CANTDECODERES,0,0,0},
    {{NULL},"S_rpcLib_RPC_CANTSEND", (char *) S_rpcLib_RPC_CANTSEND,0,0,0},
    {{NULL},"S_rpcLib_RPC_CANTRECV", (char *) S_rpcLib_RPC_CANTRECV,0,0,0},
    {{NULL},"S_rpcLib_RPC_TIMEDOUT", (char *) S_rpcLib_RPC_TIMEDOUT,0,0,0},
    {{NULL},"S_rpcLib_RPC_VERSMISMATCH", (char *) S_rpcLib_RPC_VERSMISMATCH,0,0,0},
    {{NULL},"S_rpcLib_RPC_AUTHERROR", (char *) S_rpcLib_RPC_AUTHERROR,0,0,0},
    {{NULL},"S_rpcLib_RPC_PROGUNAVAIL", (char *) S_rpcLib_RPC_PROGUNAVAIL,0,0,0},
    {{NULL},"S_rpcLib_RPC_PROGVERSMISMATCH", (char *) S_rpcLib_RPC_PROGVERSMISMATCH,0,0,0},
    {{NULL},"S_rpcLib_RPC_PROCUNAVAIL", (char *) S_rpcLib_RPC_PROCUNAVAIL,0,0,0},
    {{NULL},"S_rpcLib_RPC_CANTDECODEARGS", (char *) S_rpcLib_RPC_CANTDECODEARGS,0,0,0},
    {{NULL},"S_rpcLib_RPC_SYSTEMERROR", (char *) S_rpcLib_RPC_SYSTEMERROR,0,0,0},
    {{NULL},"S_rpcLib_RPC_UNKNOWNHOST", (char *) S_rpcLib_RPC_UNKNOWNHOST,0,0,0},
    {{NULL},"S_rpcLib_RPC_PMAPFAILURE", (char *) S_rpcLib_RPC_PMAPFAILURE,0,0,0},
    {{NULL},"S_rpcLib_RPC_PROGNOTREGISTERED", (char *) S_rpcLib_RPC_PROGNOTREGISTERED,0,0,0},
    {{NULL},"S_rpcLib_RPC_FAILED", (char *) S_rpcLib_RPC_FAILED,0,0,0},
    {{NULL},"S_rtpLib_INVALID_FILE", (char *) S_rtpLib_INVALID_FILE,0,0,0},
    {{NULL},"S_rtpLib_INVALID_OPTION", (char *) S_rtpLib_INVALID_OPTION,0,0,0},
    {{NULL},"S_rtpLib_ACCESS_DENIED", (char *) S_rtpLib_ACCESS_DENIED,0,0,0},
    {{NULL},"S_rtpLib_INVALID_RTP_ID", (char *) S_rtpLib_INVALID_RTP_ID,0,0,0},
    {{NULL},"S_rtpLib_NO_SYMBOL_TABLE", (char *) S_rtpLib_NO_SYMBOL_TABLE,0,0,0},
    {{NULL},"S_rtpLib_INVALID_SEGMENT_START_ADDRESS", (char *) S_rtpLib_INVALID_SEGMENT_START_ADDRESS,0,0,0},
    {{NULL},"S_rtpLib_INVALID_SYMBOL_REGISTR_POLICY", (char *) S_rtpLib_INVALID_SYMBOL_REGISTR_POLICY,0,0,0},
    {{NULL},"S_rtpLib_INSTANTIATE_FAILED", (char *) S_rtpLib_INSTANTIATE_FAILED,0,0,0},
    {{NULL},"S_rtpLib_INVALID_TASK_OPTION", (char *) S_rtpLib_INVALID_TASK_OPTION,0,0,0},
    {{NULL},"S_rtpLib_RTP_NAME_LENGTH_EXCEEDED", (char *) S_rtpLib_RTP_NAME_LENGTH_EXCEEDED,0,0,0},
    {{NULL},"S_rtpLib_NO_SYMBOL_TABLE_SUPPORT", (char *) S_rtpLib_NO_SYMBOL_TABLE_SUPPORT,0,0,0},
    {{NULL},"S_sdLib_NOT_IMPLEMENTED", (char *) S_sdLib_NOT_IMPLEMENTED,0,0,0},
    {{NULL},"S_sdLib_NAME_NOT_VALID", (char *) S_sdLib_NAME_NOT_VALID,0,0,0},
    {{NULL},"S_sdLib_VIRT_PAGES_NOT_AVAILABLE", (char *) S_sdLib_VIRT_PAGES_NOT_AVAILABLE,0,0,0},
    {{NULL},"S_sdLib_PHYS_PAGES_NOT_AVAILABLE", (char *) S_sdLib_PHYS_PAGES_NOT_AVAILABLE,0,0,0},
    {{NULL},"S_sdLib_ARG_LIST_IS_NULL", (char *) S_sdLib_ARG_LIST_IS_NULL,0,0,0},
    {{NULL},"S_sdLib_VIRT_ADDR_PTR_IS_NULL", (char *) S_sdLib_VIRT_ADDR_PTR_IS_NULL,0,0,0},
    {{NULL},"S_sdLib_SIZE_IS_NULL", (char *) S_sdLib_SIZE_IS_NULL,0,0,0},
    {{NULL},"S_sdLib_INVALID_OPTIONS", (char *) S_sdLib_INVALID_OPTIONS,0,0,0},
    {{NULL},"S_sdLib_INVALID_MMU_ATTR", (char *) S_sdLib_INVALID_MMU_ATTR,0,0,0},
    {{NULL},"S_sdLib_NOT_MAPPED", (char *) S_sdLib_NOT_MAPPED,0,0,0},
    {{NULL},"S_sdLib_ADDR_NOT_ALIGNED", (char *) S_sdLib_ADDR_NOT_ALIGNED,0,0,0},
    {{NULL},"S_sdLib_CLIENT_COUNT_NOT_NULL", (char *) S_sdLib_CLIENT_COUNT_NOT_NULL,0,0,0},
    {{NULL},"S_sdLib_INVALID_SD_ID", (char *) S_sdLib_INVALID_SD_ID,0,0,0},
    {{NULL},"S_sdLib_SD_IS_PRIVATE", (char *) S_sdLib_SD_IS_PRIVATE,0,0,0},
    {{NULL},"S_sdLib_PHYS_ADDR_OUT_OF_RANGE", (char *) S_sdLib_PHYS_ADDR_OUT_OF_RANGE,0,0,0},
    {{NULL},"S_selectLib_NO_SELECT_SUPPORT_IN_DRIVER", (char *) S_selectLib_NO_SELECT_SUPPORT_IN_DRIVER,0,0,0},
    {{NULL},"S_selectLib_NO_SELECT_CONTEXT", (char *) S_selectLib_NO_SELECT_CONTEXT,0,0,0},
    {{NULL},"S_semLib_INVALID_STATE", (char *) S_semLib_INVALID_STATE,0,0,0},
    {{NULL},"S_semLib_INVALID_OPTION", (char *) S_semLib_INVALID_OPTION,0,0,0},
    {{NULL},"S_semLib_INVALID_QUEUE_TYPE", (char *) S_semLib_INVALID_QUEUE_TYPE,0,0,0},
    {{NULL},"S_semLib_INVALID_OPERATION", (char *) S_semLib_INVALID_OPERATION,0,0,0},
    {{NULL},"S_semLib_INVALID_INITIAL_COUNT", (char *) S_semLib_INVALID_INITIAL_COUNT,0,0,0},
    {{NULL},"S_semLib_COUNT_OVERFLOW", (char *) S_semLib_COUNT_OVERFLOW,0,0,0},
    {{NULL},"S_shellInterpCmdLib_UNKNOWN_CMD", (char *) S_shellInterpCmdLib_UNKNOWN_CMD,0,0,0},
    {{NULL},"S_shellInterpCmdLib_UNKNOWN_TOPIC", (char *) S_shellInterpCmdLib_UNKNOWN_TOPIC,0,0,0},
    {{NULL},"S_shellInterpCmdLib_WRONG_CMD", (char *) S_shellInterpCmdLib_WRONG_CMD,0,0,0},
    {{NULL},"S_shellLib_NO_INTERP", (char *) S_shellLib_NO_INTERP,0,0,0},
    {{NULL},"S_shellLib_INTERP_EXISTS", (char *) S_shellLib_INTERP_EXISTS,0,0,0},
    {{NULL},"S_shellLib_NOT_SHELL_TASK", (char *) S_shellLib_NOT_SHELL_TASK,0,0,0},
    {{NULL},"S_shellLib_SHELL_TASK_EXISTS", (char *) S_shellLib_SHELL_TASK_EXISTS,0,0,0},
    {{NULL},"S_shellLib_SHELL_TASK_MAX", (char *) S_shellLib_SHELL_TASK_MAX,0,0,0},
    {{NULL},"S_shellLib_NO_SHELL_CMD", (char *) S_shellLib_NO_SHELL_CMD,0,0,0},
    {{NULL},"S_shellLib_NO_USER_DATA", (char *) S_shellLib_NO_USER_DATA,0,0,0},
    {{NULL},"S_shellLib_NO_LED_MODE", (char *) S_shellLib_NO_LED_MODE,0,0,0},
    {{NULL},"S_shellLib_INTERP_INIT_ERROR", (char *) S_shellLib_INTERP_INIT_ERROR,0,0,0},
    {{NULL},"S_shellLib_TOO_MANY_SESSIONS", (char *) S_shellLib_TOO_MANY_SESSIONS,0,0,0},
    {{NULL},"S_shellLib_LEX_ERROR", (char *) S_shellLib_LEX_ERROR,0,0,0},
    {{NULL},"S_shellLib_SYNTAX_ERROR", (char *) S_shellLib_SYNTAX_ERROR,0,0,0},
    {{NULL},"S_shellLib_INTERNAL_ERROR", (char *) S_shellLib_INTERNAL_ERROR,0,0,0},
    {{NULL},"S_shellLib_UNMATCHED_QUOTE", (char *) S_shellLib_UNMATCHED_QUOTE,0,0,0},
    {{NULL},"S_shellLib_MISSING_ARG", (char *) S_shellLib_MISSING_ARG,0,0,0},
    {{NULL},"S_shellLib_UNKNOWN_OPT", (char *) S_shellLib_UNKNOWN_OPT,0,0,0},
    {{NULL},"S_shellLib_ARG_ERROR", (char *) S_shellLib_ARG_ERROR,0,0,0},
    {{NULL},"S_shellLib_CONFIG_ERROR", (char *) S_shellLib_CONFIG_ERROR,0,0,0},
    {{NULL},"S_shellLib_CTX_ALREADY_ATTACHED", (char *) S_shellLib_CTX_ALREADY_ATTACHED,0,0,0},
    {{NULL},"S_shlLib_ID_SPACE_EXHAUSTED", (char *) S_shlLib_ID_SPACE_EXHAUSTED,0,0,0},
    {{NULL},"S_shlLib_INVALID_SH_INITFLG_CHANGE", (char *) S_shlLib_INVALID_SH_INITFLG_CHANGE,0,0,0},
    {{NULL},"S_shlLib_INVALID_GOTT_INDEX", (char *) S_shlLib_INVALID_GOTT_INDEX,0,0,0},
    {{NULL},"S_shlLib_INVALID_SHL_ID", (char *) S_shlLib_INVALID_SHL_ID,0,0,0},
    {{NULL},"S_shlLib_INVALID_PARAMETER", (char *) S_shlLib_INVALID_PARAMETER,0,0,0},
    {{NULL},"S_shlLib_SHL_ACCESS_DENIED", (char *) S_shlLib_SHL_ACCESS_DENIED,0,0,0},
    {{NULL},"S_sntpcLib_INVALID_PARAMETER", (char *) S_sntpcLib_INVALID_PARAMETER,0,0,0},
    {{NULL},"S_sntpcLib_INVALID_ADDRESS", (char *) S_sntpcLib_INVALID_ADDRESS,0,0,0},
    {{NULL},"S_sntpcLib_TIMEOUT", (char *) S_sntpcLib_TIMEOUT,0,0,0},
    {{NULL},"S_sntpcLib_VERSION_UNSUPPORTED", (char *) S_sntpcLib_VERSION_UNSUPPORTED,0,0,0},
    {{NULL},"S_sntpcLib_SERVER_UNSYNC", (char *) S_sntpcLib_SERVER_UNSYNC,0,0,0},
    {{NULL},"S_sntpsLib_INVALID_PARAMETER", (char *) S_sntpsLib_INVALID_PARAMETER,0,0,0},
    {{NULL},"S_spinLockLib_NOT_SPIN_LOCK_CALLABLE", (char *) S_spinLockLib_NOT_SPIN_LOCK_CALLABLE,0,0,0},
    {{NULL},"S_spinLockLib_INVALID_OPERATION", (char *) S_spinLockLib_INVALID_OPERATION,0,0,0},
    {{NULL},"S_spinLockLib_LOCK_IN_RECOVERY", (char *) S_spinLockLib_LOCK_IN_RECOVERY,0,0,0},
    {{NULL},"S_spinLockLib_LOCK_UNAVAILABLE", (char *) S_spinLockLib_LOCK_UNAVAILABLE,0,0,0},
    {{NULL},"S_spinLockLib_LOCK_TIMEOUT", (char *) S_spinLockLib_LOCK_TIMEOUT,0,0,0},
    {{NULL},"S_symLib_SYMBOL_NOT_FOUND", (char *) S_symLib_SYMBOL_NOT_FOUND,0,0,0},
    {{NULL},"S_symLib_NAME_CLASH", (char *) S_symLib_NAME_CLASH,0,0,0},
    {{NULL},"S_symLib_TABLE_NOT_EMPTY", (char *) S_symLib_TABLE_NOT_EMPTY,0,0,0},
    {{NULL},"S_symLib_SYMBOL_STILL_IN_TABLE", (char *) S_symLib_SYMBOL_STILL_IN_TABLE,0,0,0},
    {{NULL},"S_symLib_INVALID_SYMBOL_NAME", (char *) S_symLib_INVALID_SYMBOL_NAME,0,0,0},
    {{NULL},"S_symLib_INVALID_SYMTAB_ID", (char *) S_symLib_INVALID_SYMTAB_ID,0,0,0},
    {{NULL},"S_symLib_INVALID_SYM_ID_PTR", (char *) S_symLib_INVALID_SYM_ID_PTR,0,0,0},
    {{NULL},"S_symLib_INVALID_ARGS", (char *) S_symLib_INVALID_ARGS,0,0,0},
    {{NULL},"S_syscallLib_UNKNOWN_GROUP", (char *) S_syscallLib_UNKNOWN_GROUP,0,0,0},
    {{NULL},"S_syscallLib_GROUP_EXISTS", (char *) S_syscallLib_GROUP_EXISTS,0,0,0},
    {{NULL},"S_syscallLib_INVALID_ROUTINE_COUNT", (char *) S_syscallLib_INVALID_ROUTINE_COUNT,0,0,0},
    {{NULL},"S_syscallLib_NO_ROUTINES_TBL", (char *) S_syscallLib_NO_ROUTINES_TBL,0,0,0},
    {{NULL},"S_syscallLib_INVALID_USER_SP", (char *) S_syscallLib_INVALID_USER_SP,0,0,0},
    {{NULL},"S_syscallLib_VECTOR_INIT_FAILED", (char *) S_syscallLib_VECTOR_INIT_FAILED,0,0,0},
    {{NULL},"S_taskLib_NAME_NOT_FOUND", (char *) S_taskLib_NAME_NOT_FOUND,0,0,0},
    {{NULL},"S_taskLib_TASK_HOOK_TABLE_FULL", (char *) S_taskLib_TASK_HOOK_TABLE_FULL,0,0,0},
    {{NULL},"S_taskLib_TASK_HOOK_NOT_FOUND", (char *) S_taskLib_TASK_HOOK_NOT_FOUND,0,0,0},
    {{NULL},"S_taskLib_TASK_SWAP_HOOK_REFERENCED", (char *) S_taskLib_TASK_SWAP_HOOK_REFERENCED,0,0,0},
    {{NULL},"S_taskLib_TASK_SWAP_HOOK_SET", (char *) S_taskLib_TASK_SWAP_HOOK_SET,0,0,0},
    {{NULL},"S_taskLib_TASK_SWAP_HOOK_CLEAR", (char *) S_taskLib_TASK_SWAP_HOOK_CLEAR,0,0,0},
    {{NULL},"S_taskLib_TASK_VAR_NOT_FOUND", (char *) S_taskLib_TASK_VAR_NOT_FOUND,0,0,0},
    {{NULL},"S_taskLib_TASK_UNDELAYED", (char *) S_taskLib_TASK_UNDELAYED,0,0,0},
    {{NULL},"S_taskLib_ILLEGAL_PRIORITY", (char *) S_taskLib_ILLEGAL_PRIORITY,0,0,0},
    {{NULL},"S_taskLib_ILLEGAL_OPTIONS", (char *) S_taskLib_ILLEGAL_OPTIONS,0,0,0},
    {{NULL},"S_taskLib_NO_TCB", (char *) S_taskLib_NO_TCB,0,0,0},
    {{NULL},"S_taskLib_ILLEGAL_OPERATION", (char *) S_taskLib_ILLEGAL_OPERATION,0,0,0},
    {{NULL},"S_taskLib_ILLEGAL_STACK_INFO", (char *) S_taskLib_ILLEGAL_STACK_INFO,0,0,0},
    {{NULL},"S_taskLib_STOPPED_DELETE_SAFE_TASK", (char *) S_taskLib_STOPPED_DELETE_SAFE_TASK,0,0,0},
    {{NULL},"S_tffsLib_BAD_FUNCTION", (char *) S_tffsLib_BAD_FUNCTION,0,0,0},
    {{NULL},"S_tffsLib_FILE_NOT_FOUND", (char *) S_tffsLib_FILE_NOT_FOUND,0,0,0},
    {{NULL},"S_tffsLib_PATH_NOT_FOUND", (char *) S_tffsLib_PATH_NOT_FOUND,0,0,0},
    {{NULL},"S_tffsLib_TOO_MANY_OPEN_FILES", (char *) S_tffsLib_TOO_MANY_OPEN_FILES,0,0,0},
    {{NULL},"S_tffsLib_NO_WRITE_ACCESS", (char *) S_tffsLib_NO_WRITE_ACCESS,0,0,0},
    {{NULL},"S_tffsLib_BAD_FILE_HANDLE", (char *) S_tffsLib_BAD_FILE_HANDLE,0,0,0},
    {{NULL},"S_tffsLib_DRIVE_NOT_AVAILABLE", (char *) S_tffsLib_DRIVE_NOT_AVAILABLE,0,0,0},
    {{NULL},"S_tffsLib_NON_FAT_FORMAT", (char *) S_tffsLib_NON_FAT_FORMAT,0,0,0},
    {{NULL},"S_tffsLib_FORMAT_NOT_SUPPORTED", (char *) S_tffsLib_FORMAT_NOT_SUPPORTED,0,0,0},
    {{NULL},"S_tffsLib_NO_MORE_FILES", (char *) S_tffsLib_NO_MORE_FILES,0,0,0},
    {{NULL},"S_tffsLib_WRITE_PROTECT", (char *) S_tffsLib_WRITE_PROTECT,0,0,0},
    {{NULL},"S_tffsLib_BAD_DRIVE_HANDLE", (char *) S_tffsLib_BAD_DRIVE_HANDLE,0,0,0},
    {{NULL},"S_tffsLib_DRIVE_NOT_READY", (char *) S_tffsLib_DRIVE_NOT_READY,0,0,0},
    {{NULL},"S_tffsLib_UNKNOWN_CMD", (char *) S_tffsLib_UNKNOWN_CMD,0,0,0},
    {{NULL},"S_tffsLib_BAD_FORMAT", (char *) S_tffsLib_BAD_FORMAT,0,0,0},
    {{NULL},"S_tffsLib_BAD_LENGTH", (char *) S_tffsLib_BAD_LENGTH,0,0,0},
    {{NULL},"S_tffsLib_DATA_ERROR", (char *) S_tffsLib_DATA_ERROR,0,0,0},
    {{NULL},"S_tffsLib_UNKNOWN_MEDIA", (char *) S_tffsLib_UNKNOWN_MEDIA,0,0,0},
    {{NULL},"S_tffsLib_SECTOR_NOT_FOUND", (char *) S_tffsLib_SECTOR_NOT_FOUND,0,0,0},
    {{NULL},"S_tffsLib_OUT_OF_PAPER", (char *) S_tffsLib_OUT_OF_PAPER,0,0,0},
    {{NULL},"S_tffsLib_WRITE_FAULT", (char *) S_tffsLib_WRITE_FAULT,0,0,0},
    {{NULL},"S_tffsLib_READ_FAULT", (char *) S_tffsLib_READ_FAULT,0,0,0},
    {{NULL},"S_tffsLib_GENERAL_FAILURE", (char *) S_tffsLib_GENERAL_FAILURE,0,0,0},
    {{NULL},"S_tffsLib_DISK_CHANGE", (char *) S_tffsLib_DISK_CHANGE,0,0,0},
    {{NULL},"S_tffsLib_VPP_FAILURE", (char *) S_tffsLib_VPP_FAILURE,0,0,0},
    {{NULL},"S_tffsLib_BAD_PARAMETER", (char *) S_tffsLib_BAD_PARAMETER,0,0,0},
    {{NULL},"S_tffsLib_NO_SPACE_IN_VOLUME", (char *) S_tffsLib_NO_SPACE_IN_VOLUME,0,0,0},
    {{NULL},"S_tffsLib_INVALID_FAT_CHAIN", (char *) S_tffsLib_INVALID_FAT_CHAIN,0,0,0},
    {{NULL},"S_tffsLib_ROOT_DIR_FULL", (char *) S_tffsLib_ROOT_DIR_FULL,0,0,0},
    {{NULL},"S_tffsLib_NOT_MOUNTED", (char *) S_tffsLib_NOT_MOUNTED,0,0,0},
    {{NULL},"S_tffsLib_PATH_IS_ROOTDIR", (char *) S_tffsLib_PATH_IS_ROOTDIR,0,0,0},
    {{NULL},"S_tffsLib_NOT_A_DIR", (char *) S_tffsLib_NOT_A_DIR,0,0,0},
    {{NULL},"S_tffsLib_DIR_NOT_EMPTY", (char *) S_tffsLib_DIR_NOT_EMPTY,0,0,0},
    {{NULL},"S_tffsLib_FILE_IS_A_DIR", (char *) S_tffsLib_FILE_IS_A_DIR,0,0,0},
    {{NULL},"S_tffsLib_ADAPTER_NOT_FOUND", (char *) S_tffsLib_ADAPTER_NOT_FOUND,0,0,0},
    {{NULL},"S_tffsLib_FORMATTING_ERROR", (char *) S_tffsLib_FORMATTING_ERROR,0,0,0},
    {{NULL},"S_tffsLib_NOT_ENOUGH_MEMORY", (char *) S_tffsLib_NOT_ENOUGH_MEMORY,0,0,0},
    {{NULL},"S_tffsLib_VOLUME_TOO_SMALL", (char *) S_tffsLib_VOLUME_TOO_SMALL,0,0,0},
    {{NULL},"S_tffsLib_BUFFERING_ERROR", (char *) S_tffsLib_BUFFERING_ERROR,0,0,0},
    {{NULL},"S_tffsLib_FILE_ALREADY_EXISTS", (char *) S_tffsLib_FILE_ALREADY_EXISTS,0,0,0},
    {{NULL},"S_tffsLib_INCOMPLETE", (char *) S_tffsLib_INCOMPLETE,0,0,0},
    {{NULL},"S_tffsLib_TIMED_OUT", (char *) S_tffsLib_TIMED_OUT,0,0,0},
    {{NULL},"S_tffsLib_TOO_MANY_COMPONENTS", (char *) S_tffsLib_TOO_MANY_COMPONENTS,0,0,0},
    {{NULL},"S_tftpLib_INVALID_ARGUMENT", (char *) S_tftpLib_INVALID_ARGUMENT,0,0,0},
    {{NULL},"S_tftpLib_INVALID_DESCRIPTOR", (char *) S_tftpLib_INVALID_DESCRIPTOR,0,0,0},
    {{NULL},"S_tftpLib_INVALID_COMMAND", (char *) S_tftpLib_INVALID_COMMAND,0,0,0},
    {{NULL},"S_tftpLib_INVALID_MODE", (char *) S_tftpLib_INVALID_MODE,0,0,0},
    {{NULL},"S_tftpLib_UNKNOWN_HOST", (char *) S_tftpLib_UNKNOWN_HOST,0,0,0},
    {{NULL},"S_tftpLib_NOT_CONNECTED", (char *) S_tftpLib_NOT_CONNECTED,0,0,0},
    {{NULL},"S_tftpLib_TIMED_OUT", (char *) S_tftpLib_TIMED_OUT,0,0,0},
    {{NULL},"S_tftpLib_TFTP_ERROR", (char *) S_tftpLib_TFTP_ERROR,0,0,0},
    {{NULL},"S_unldLib_MODULE_NOT_FOUND", (char *) S_unldLib_MODULE_NOT_FOUND,0,0,0},
    {{NULL},"S_unldLib_TEXT_IN_USE", (char *) S_unldLib_TEXT_IN_USE,0,0,0},
    {{NULL},"S_unldLib_INVALID_UNLOAD_FLAG", (char *) S_unldLib_INVALID_UNLOAD_FLAG,0,0,0},
    {{NULL},"S_unldLib_ILLEGAL_FLAGS_COMBINATION", (char *) S_unldLib_ILLEGAL_FLAGS_COMBINATION,0,0,0},
    {{NULL},"S_unldLib_USR_TERM_ERROR", (char *) S_unldLib_USR_TERM_ERROR,0,0,0},
    {{NULL},"S_usrLib_NOT_ENOUGH_ARGS", (char *) S_usrLib_NOT_ENOUGH_ARGS,0,0,0},
    {{NULL},"S_vmLib_NOT_PAGE_ALIGNED", (char *) S_vmLib_NOT_PAGE_ALIGNED,0,0,0},
    {{NULL},"S_vmLib_BAD_STATE_PARAM", (char *) S_vmLib_BAD_STATE_PARAM,0,0,0},
    {{NULL},"S_vmLib_BAD_MASK_PARAM", (char *) S_vmLib_BAD_MASK_PARAM,0,0,0},
    {{NULL},"S_vmLib_ADDR_IN_GLOBAL_SPACE", (char *) S_vmLib_ADDR_IN_GLOBAL_SPACE,0,0,0},
    {{NULL},"S_vmLib_TEXT_PROTECTION_UNAVAILABLE", (char *) S_vmLib_TEXT_PROTECTION_UNAVAILABLE,0,0,0},
    {{NULL},"S_vmLib_KERNEL_TEXT_NOT_ALIGNED", (char *) S_vmLib_KERNEL_TEXT_NOT_ALIGNED,0,0,0},
    {{NULL},"S_vmLib_FUNCTION_UNSUPPORTED", (char *) S_vmLib_FUNCTION_UNSUPPORTED,0,0,0},
    {{NULL},"S_vmLib_PHYS_PAGES_ALREADY_MAPPED", (char *) S_vmLib_PHYS_PAGES_ALREADY_MAPPED,0,0,0},
    {{NULL},"S_vmLib_NOALIAS_SUPPORT_NOT_INCLUDED", (char *) S_vmLib_NOALIAS_SUPPORT_NOT_INCLUDED,0,0,0},
    {{NULL},"S_vxCpuLib_INVALID_ARGUMENT", (char *) S_vxCpuLib_INVALID_ARGUMENT,0,0,0},
    {{NULL},"S_vxCpuLib_NO_CPU_AVAILABLE", (char *) S_vxCpuLib_NO_CPU_AVAILABLE,0,0,0},
    {{NULL},"S_vxdbgLib_INVALID_PARAMS", (char *) S_vxdbgLib_INVALID_PARAMS,0,0,0},
    {{NULL},"S_vxdbgLib_INVALID_MEM_ACCESS", (char *) S_vxdbgLib_INVALID_MEM_ACCESS,0,0,0},
    {{NULL},"S_vxdbgLib_INVALID_CTX", (char *) S_vxdbgLib_INVALID_CTX,0,0,0},
    {{NULL},"S_vxdbgLib_INVALID_BP", (char *) S_vxdbgLib_INVALID_BP,0,0,0},
    {{NULL},"S_vxdbgLib_INVALID_EVENT_TYPE", (char *) S_vxdbgLib_INVALID_EVENT_TYPE,0,0,0},
    {{NULL},"S_vxdbgLib_NO_HW_REGS", (char *) S_vxdbgLib_NO_HW_REGS,0,0,0},
    {{NULL},"S_vxdbgLib_HOOK_ALREADY_EXISTS", (char *) S_vxdbgLib_HOOK_ALREADY_EXISTS,0,0,0},
    {{NULL},"S_vxdbgLib_HW_REGS_FULL", (char *) S_vxdbgLib_HW_REGS_FULL,0,0,0},
    {{NULL},"S_vxdbgLib_INVALID_HW_BP", (char *) S_vxdbgLib_INVALID_HW_BP,0,0,0},
    {{NULL},"S_vxdbgLib_INVALID_BP_DELETE_CLASS", (char *) S_vxdbgLib_INVALID_BP_DELETE_CLASS,0,0,0},
    {{NULL},"S_vxdbgLib_INVALID_ALIGNMENT", (char *) S_vxdbgLib_INVALID_ALIGNMENT,0,0,0},
    {{NULL},"S_vxdbgLib_NOT_INITIALIZED", (char *) S_vxdbgLib_NOT_INITIALIZED,0,0,0},
    {{NULL},"S_vxdbgLib_INVALID_CLIENT_ID", (char *) S_vxdbgLib_INVALID_CLIENT_ID,0,0,0},
    {{NULL},"S_vxdbgLib_UNSUPPORTED_HW_BP_SIZE", (char *) S_vxdbgLib_UNSUPPORTED_HW_BP_SIZE,0,0,0},
    {{NULL},"S_vxdbgLib_UNSUPPORTED_HW_BP_ACCESS_TYPE", (char *) S_vxdbgLib_UNSUPPORTED_HW_BP_ACCESS_TYPE,0,0,0},
    {{NULL},"S_vxdbgLib_NO_HW_BP_SUPPORT", (char *) S_vxdbgLib_NO_HW_BP_SUPPORT,0,0,0},
    {{NULL},"S_vxdbgLib_HW_BP_SUPPORT_DISABLED", (char *) S_vxdbgLib_HW_BP_SUPPORT_DISABLED,0,0,0},
    {{NULL},"S_vxdbgLib_NOT_ENABLED", (char *) S_vxdbgLib_NOT_ENABLED,0,0,0},
    {{NULL},"S_wdLib_INVALID_PARAMETER", (char *) S_wdLib_INVALID_PARAMETER,0,0,0},
    {{NULL},"S_zbufLib_ID_INVALID", (char *) S_zbufLib_ID_INVALID,0,0,0},
    {{NULL},"S_zbufLib_ID_EMPTY", (char *) S_zbufLib_ID_EMPTY,0,0,0},
    {{NULL},"S_zbufLib_SEGMENT_NOT_FOUND", (char *) S_zbufLib_SEGMENT_NOT_FOUND,0,0,0},
    {{NULL},"S_zbufLib_LENGTH_INVALID", (char *) S_zbufLib_LENGTH_INVALID,0,0,0},
    {{NULL},"S_zbufLib_OFFSET_INVALID", (char *) S_zbufLib_OFFSET_INVALID,0,0,0},
    };

ULONG statTblSize = NELEMENTS (statTbl);
