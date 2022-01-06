/* offsetMacrosP.h - structure member offsets definition file */

/* Copyright (c) 2008 Wind River Systems, Inc. */

/* THIS FILE IS AUTO_GENERATED. PLEASE DO NOT EDIT. */

/*
* This file provides macros for the offsets of various structure
* members as well as for the size of those structures. Those offsets
* macros are primarily intended to be used in assembly code.
*/

#ifndef __OffsetGen__offsetMacrosP__INCLUDED__
#define __OffsetGen__offsetMacrosP__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/* defines */


/* Structure size and member offsets for WIND_SOCKET structure */

#define WIND_SOCKET_so_type_OFFSET       	0x8
#define WIND_SOCKET_so_options_OFFSET    	0xa
#define WIND_SOCKET_so_linger_OFFSET     	0xc
#define WIND_SOCKET_so_state_OFFSET      	0xe
#define WIND_SOCKET_so_pcb_OFFSET        	0x10
#define WIND_SOCKET_so_qlen_OFFSET       	0x58
#define WIND_SOCKET_so_qlimit_OFFSET     	0x5c
#define WIND_SOCKET_so_fd_OFFSET         	0x74

/* Structure size and member offsets for HANDLE structure */

#define HANDLE_magic_OFFSET          	0x0
#define HANDLE_safeCnt_OFFSET        	0x8
#define HANDLE_attributes_OFFSET     	0xc
#define HANDLE_type_OFFSET           	0xe
#define HANDLE_contextType_OFFSET    	0xf
#define HANDLE_context_OFFSET        	0x10
#define HANDLE_objSize_OFFSET        	0x18

/* Structure size and member offsets for MEM_PART_STATS structure */

#define MEM_PART_STATS_numBytesFree_OFFSET        	0x0
#define MEM_PART_STATS_numBlocksFree_OFFSET       	0x8
#define MEM_PART_STATS_maxBlockSizeFree_OFFSET    	0x10
#define MEM_PART_STATS_numBytesAlloc_OFFSET       	0x18
#define MEM_PART_STATS_numBlocksAlloc_OFFSET      	0x20
#define MEM_PART_STATS_maxBytesAlloc_OFFSET       	0x28

/* Structure size and member offsets for OBJ_CLASS structure */

#define OBJ_CLASS_handle_OFFSET            	0x0
#define OBJ_CLASS_objClassType_OFFSET      	0x18
#define OBJ_CLASS_options_OFFSET           	0x1c
#define OBJ_CLASS_objSize_OFFSET           	0x20
#define OBJ_CLASS_createRtn_OFFSET         	0x28
#define OBJ_CLASS_destroyRtn_OFFSET        	0x30
#define OBJ_CLASS_showRtn_OFFSET           	0x38
#define OBJ_CLASS_objMemAllocRtn_OFFSET    	0x40
#define OBJ_CLASS_objMemFreeRtn_OFFSET     	0x48
#define OBJ_CLASS_objPartId_OFFSET         	0x50
#define OBJ_CLASS_objPrivList_OFFSET       	0x58
#define OBJ_CLASS_objPubList_OFFSET        	0x68
#define OBJ_CLASS_pClassSem_OFFSET         	0x78

/* Structure size and member offsets for WIND_OBJ structure */

#define WIND_OBJ_handle_OFFSET           	0x0
#define WIND_OBJ_ownerList_OFFSET        	0x18
#define WIND_OBJ_ownerNode_OFFSET        	0x28
#define WIND_OBJ_classNode_OFFSET        	0x38
#define WIND_OBJ_ownerId_OFFSET          	0x48
#define WIND_OBJ_ownerRtpId_OFFSET       	0x50
#define WIND_OBJ_name_OFFSET             	0x58
#define WIND_OBJ_pObjClass_OFFSET        	0x60
#define WIND_OBJ_objHandleList_OFFSET    	0x68
#define WIND_OBJ_refCnt_OFFSET           	0x78
#define WIND_OBJ_accessCnt_OFFSET        	0x7a
#define WIND_OBJ_SIZEOF                  	0x80

/* Structure size and member offsets for PAGE_MGR_OBJ structure */

#define PAGE_MGR_OBJ_virtPgPoolId_OFFSET    	0x0
#define PAGE_MGR_OBJ_physPgPoolId_OFFSET    	0x8
#define PAGE_MGR_OBJ_vmContextId_OFFSET     	0x18
#define PAGE_MGR_OBJ_mmapList_OFFSET        	0x20
#define PAGE_MGR_OBJ_options_OFFSET         	0x30

/* Structure size and member offsets for WIND_TCB structure */

#define WIND_TCB_objCore_OFFSET           	0x0
#define WIND_TCB_timeout_OFFSET           	0x90
#define WIND_TCB_qNode_OFFSET             	0xa0
#define WIND_TCB_pExcStackBase_OFFSET     	0xc0
#define WIND_TCB_pExcStackEnd_OFFSET      	0xc8
#define WIND_TCB_pExcStackStart_OFFSET    	0xd0
#define WIND_TCB_excCnt_OFFSET            	0xd8
#define WIND_TCB_status_OFFSET            	0xdc
#define WIND_TCB_priority_OFFSET          	0xe0
#define WIND_TCB_priNormal_OFFSET         	0xe4
#define WIND_TCB_lockCnt_OFFSET           	0xe8
#define WIND_TCB_priMutexCnt_OFFSET       	0xec
#define WIND_TCB_priInheritCnt_OFFSET     	0xf0
#define WIND_TCB_priDrop_OFFSET           	0xf4
#define WIND_TCB_pPriMutex_OFFSET         	0xf8
#define WIND_TCB_rtpId_OFFSET             	0x108
#define WIND_TCB_pUTcb_OFFSET             	0x110
#define WIND_TCB_options_OFFSET           	0x118
#define WIND_TCB_pPendQ_OFFSET            	0x120
#define WIND_TCB_swapInMask_OFFSET        	0x128
#define WIND_TCB_swapOutMask_OFFSET       	0x12a
#define WIND_TCB_safeCnt_OFFSET           	0x12c
#define WIND_TCB_safetyQHead_OFFSET       	0x130
#define WIND_TCB_entry_OFFSET             	0x150
#define WIND_TCB_pStackBase_OFFSET        	0x158
#define WIND_TCB_pStackEnd_OFFSET         	0x160
#define WIND_TCB_pEdrInfo_OFFSET          	0x168
#define WIND_TCB_errorStatus_OFFSET       	0x170
#define WIND_TCB_taskTicks_OFFSET         	0x190
#define WIND_TCB_pCoprocTbl_OFFSET        	0x1a8
#define WIND_TCB_events_OFFSET            	0x1d4
#define WIND_TCB_pExcRegSet_OFFSET        	0x208
#define WIND_TCB_pDbgInfo_OFFSET          	0x218
#define WIND_TCB_cpuTimeInfo_OFFSET       	0x270
#define WIND_TCB_pPwrMgmtPState_OFFSET    	0x280
#define WIND_TCB_pSchedInfo_OFFSET        	0x288
#define WIND_TCB_windSmpInfo_OFFSET       	0x298
#define WIND_TCB_pTlsDesc_OFFSET          	0x4a8

/* Coprocessor option flags */

#define VX_coproc8Task_OFFSET    	0x80000000
#define VX_fpTask_OFFSET         	0x1000000
#define VX_coproc1Task_OFFSET    	0x1000000
#define VX_altivecTask_OFFSET    	0x2000000
#define VX_coproc2Task_OFFSET    	0x2000000
#define VX_speTask_OFFSET        	0x4000000
#define VX_coproc3Task_OFFSET    	0x4000000
#define VX_coproc4Task_OFFSET    	0x8000000
#define VX_coproc5Task_OFFSET    	0x10000000
#define VX_coproc6Task_OFFSET    	0x20000000
#define VX_coproc7Task_OFFSET    	0x40000000

/* Structure size and member offsets for SEMAPHORE structure */

#define SEMAPHORE_semType_OFFSET              	0x80
#define SEMAPHORE_options_OFFSET              	0x81
#define SEMAPHORE_recurse_OFFSET              	0x82
#define SEMAPHORE_priInheritFlag_OFFSET       	0x84
#define SEMAPHORE_qHead_OFFSET                	0x88
#define SEMAPHORE_count_OFFSET                	0xa8
#define SEMAPHORE_events_OFFSET               	0xb0
#define SEMAPHORE_events_registered_OFFSET    	0xb8
#define SEMAPHORE_events_options_OFFSET       	0xbc
#define SEMAPHORE_SIZEOF                      	0xc0

/* Structure size and member offsets for SEM_RW_LIST_ENTRY structure */

#define SEM_RW_LIST_ENTRY_SIZEOF           	0x10

/* Structure size and member offsets for SEM_RW_EXT structure */

#define SEM_RW_EXT_SIZEOF           	0x28

/* Structure size and member offsets for PSEMAPHORE structure */

#define PSEMAPHORE_objCore_OFFSET    	0x0
#define PSEMAPHORE_wSemId_OFFSET     	0x80
#define PSEMAPHORE_pSelf_OFFSET      	0x88

/* Structure size and member offsets for MSG_Q_HEAD structure */

#define MSG_Q_HEAD_list_OFFSET     	0x0
#define MSG_Q_HEAD_count_OFFSET    	0x10
#define MSG_Q_HEAD_pendQ_OFFSET    	0x18

/* Structure size and member offsets for MSG_Q structure */

#define MSG_Q_msgQ_OFFSET            	0x80
#define MSG_Q_freeQ_OFFSET           	0xb8
#define MSG_Q_maxMsgs_OFFSET         	0xf0
#define MSG_Q_maxMsgLength_OFFSET    	0xf8
#define MSG_Q_sendTimeouts_OFFSET    	0x100
#define MSG_Q_recvTimeouts_OFFSET    	0x104
#define MSG_Q_events_OFFSET          	0x108
#define MSG_Q_options_OFFSET         	0x138
#define MSG_Q_SIZEOF                 	0x140

/* Structure size and member offsets for POSIX_MSG_Q_DES structure */

#define POSIX_MSG_Q_DES_f_data_OFFSET    	0x0
#define POSIX_MSG_Q_DES_f_flag_OFFSET    	0x8

/* Structure size and member offsets for POSIX_MSG_Q structure */

#define POSIX_MSG_Q_msgq_cond_read_OFFSET    	0x80
#define POSIX_MSG_Q_msgq_cond_data_OFFSET    	0xa0
#define POSIX_MSG_Q_msgq_attr_OFFSET         	0x210

/* Structure size and member offsets for POSIX_MSG_Q_ATTR structure */

#define POSIX_MSG_Q_ATTR_mq_maxmsg_OFFSET     	0x0
#define POSIX_MSG_Q_ATTR_mq_msgsize_OFFSET    	0x8
#define POSIX_MSG_Q_ATTR_mq_flags_OFFSET      	0x10
#define POSIX_MSG_Q_ATTR_mq_curmsgs_OFFSET    	0x18

/* Structure size and member offsets for SYMBOL structure */

#define SYMBOL_name_OFFSET      	0x8
#define SYMBOL_value_OFFSET     	0x10
#define SYMBOL_symRef_OFFSET    	0x18
#define SYMBOL_group_OFFSET     	0x20
#define SYMBOL_type_OFFSET      	0x22

/* Structure size and member offsets for COMMON_SYM structure */

#define COMMON_SYM_pSymbol_OFFSET    	0x8

/* Structure size and member offsets for UNDEF_SYM structure */

#define UNDEF_SYM_name_OFFSET    	0x8

/* Structure size and member offsets for WDOG structure */

#define WDOG_timeout_OFFSET          	0x90
#define WDOG_wdRoutine_OFFSET        	0xa0
#define WDOG_wdParameter_OFFSET      	0xa8
#define WDOG_status_OFFSET           	0xb0
#define WDOG_deferStartCnt_OFFSET    	0xb2
#define WDOG_SIZEOF                  	0xb8

/* Structure size and member offsets for MSG_NODE structure */

#define MSG_NODE_msgLength_OFFSET    	0x8
#define MSG_NODE_message_OFFSET      	0x18
#define MSG_NODE_SIZEOF              	0x18

/* Structure size and member offsets for HOOK_TBL structure */

#define HOOK_TBL_maxEntries_OFFSET    	0xc0
#define HOOK_TBL_hookTableA_OFFSET    	0xf0

/* Structure size and member offsets for Q_FIFO_G_HEAD structure */

#define Q_FIFO_G_HEAD_pFifoQ_OFFSET    	0x10

/* Structure size and member offsets for DL_NODE structure */

#define DL_NODE_next_OFFSET    	0x0

/* Structure size and member offsets for DL_LIST structure */

#define DL_LIST_head_OFFSET    	0x0

/* Structure size and member offsets for DEV_HDR structure */

#define DEV_HDR_name_OFFSET      	0x10
#define DEV_HDR_drvNum_OFFSET    	0x30

/* Structure size and member offsets for FD_ENTRY structure */

#define FD_ENTRY_pDevHdr_OFFSET    	0x80
#define FD_ENTRY_value_OFFSET      	0x88
#define FD_ENTRY_refCnt_OFFSET     	0x98
#define FD_ENTRY_SIZEOF            	0xb0

/* Structure size and member offsets for DRV_ENTRY structure */

#define DRV_ENTRY_de_delete_OFFSET    	0x0
#define DRV_ENTRY_de_open_OFFSET      	0x8
#define DRV_ENTRY_de_close_OFFSET     	0x10
#define DRV_ENTRY_de_read_OFFSET      	0x18
#define DRV_ENTRY_de_write_OFFSET     	0x20
#define DRV_ENTRY_de_ioctl_OFFSET     	0x28
#define DRV_ENTRY_de_inuse_OFFSET     	0x38

/* Structure size and member offsets for WIND_RTP structure */

#define WIND_RTP_kernelRtpCmn_OFFSET     	0x80
#define WIND_RTP_rtpNode_OFFSET          	0xa8
#define WIND_RTP_semId_OFFSET            	0xb8
#define WIND_RTP_pPathName_OFFSET        	0xc8
#define WIND_RTP_pArgv_OFFSET            	0xd0
#define WIND_RTP_pEnv_OFFSET             	0xd8
#define WIND_RTP_status_OFFSET           	0xe0
#define WIND_RTP_options_OFFSET          	0xe4
#define WIND_RTP_entrAddr_OFFSET         	0xe8
#define WIND_RTP_initTaskId_OFFSET       	0xf0
#define WIND_RTP_symTabId_OFFSET         	0xf8
#define WIND_RTP_binaryInfo_OFFSET       	0x100
#define WIND_RTP_taskCnt_OFFSET          	0x21c
#define WIND_RTP_fdTable_OFFSET          	0x248
#define WIND_RTP_fdTableSize_OFFSET      	0x250
#define WIND_RTP_defPath_OFFSET          	0x258
#define WIND_RTP_defPathLen_OFFSET       	0x260
#define WIND_RTP_taskExitRtn_OFFSET      	0x268
#define WIND_RTP_sigReturnRtn_OFFSET     	0x270
#define WIND_RTP_signalInfo_OFFSET       	0x278
#define WIND_RTP_pSigQFreeHead_OFFSET    	0xcc0
#define WIND_RTP_sigwaitQ_OFFSET         	0xcc8
#define WIND_RTP_parentRtpId_OFFSET      	0xce8
#define WIND_RTP_lockTaskId_OFFSET       	0x1518
#define WIND_RTP_cpuTimeInfo_OFFSET      	0x1540
#define WIND_RTP_pSchedInfo_OFFSET       	0x1550

/* Structure size and member offsets for KERNEL_RTP_CMN structure */

#define KERNEL_RTP_CMN_vmContextId_OFFSET       	0x0
#define KERNEL_RTP_CMN_pgMgrId_OFFSET           	0x8
#define KERNEL_RTP_CMN_sharedDataList_OFFSET    	0x10
#define KERNEL_RTP_CMN_pWdbInfo_OFFSET          	0x20

/* Structure size and member offsets for RTP_SIG_CTX structure */

#define RTP_SIG_CTX_ctx_regset_OFFSET    	0x58

/* Structure size and member offsets for RTP_IMAGE_INFO structure */

#define RTP_IMAGE_INFO_segs_OFFSET    	0x30

/* Structure size and member offsets for RTP_SEG_INFO structure */

#define RTP_SEG_INFO_vaddr_OFFSET     	0x0
#define RTP_SEG_INFO_memsz_OFFSET     	0x8
#define RTP_SEG_INFO_filesz_OFFSET    	0x10
#define RTP_SEG_INFO_flags_OFFSET     	0x18
#define RTP_SEG_INFO_SIZEOF           	0x20

/* Structure size and member offsets for RTP_IMAGE_INFO structure */

#define RTP_IMAGE_INFO_textStart_OFFSET    	0x0
#define RTP_IMAGE_INFO_textSize_OFFSET     	0x8
#define RTP_IMAGE_INFO_dataStart_OFFSET    	0x10
#define RTP_IMAGE_INFO_dataSize_OFFSET     	0x18
#define RTP_IMAGE_INFO_bssStart_OFFSET     	0x20
#define RTP_IMAGE_INFO_bssSize_OFFSET      	0x28

/* Structure size and member offsets for PARTITION structure */

#define PARTITION_avlSize_OFFSET                       	0x80
#define PARTITION_freeSizeNodeNb_OFFSET                	0x94
#define PARTITION_sem_OFFSET                           	0x98
#define PARTITION_totalWords_OFFSET                    	0x158
#define PARTITION_options_OFFSET                       	0x160
#define PARTITION_sectionHdrLst_OFFSET                 	0x168
#define PARTITION_curBlocksFreed_OFFSET                	0x1a0
#define PARTITION_curWordsFreed_OFFSET                 	0x1a8
#define PARTITION_curBlocksAllocated_OFFSET            	0x1b0
#define PARTITION_curWordsAllocated_OFFSET             	0x1b8
#define PARTITION_cumBlocksAllocated_OFFSET            	0x1c0
#define PARTITION_cumWordsAllocated_OFFSET             	0x1c8
#define PARTITION_maxWordsAllocated_OFFSET             	0x1d0
#define PARTITION_curBlocksAllocatedInternal_OFFSET    	0x1d8
#define PARTITION_curWordsAllocatedInternal_OFFSET     	0x1e0

/* Structure size and member offsets for MEM_SECTION_HDR structure */

#define MEM_SECTION_HDR_size_OFFSET    	0x8

/* Structure size and member offsets for RBUFF_TYPE structure */

#define RBUFF_TYPE_buffDesc_OFFSET     	0x0
#define RBUFF_TYPE_buffRead_OFFSET     	0x130
#define RBUFF_TYPE_buffWrite_OFFSET    	0x138
#define RBUFF_TYPE_dataRead_OFFSET     	0x140
#define RBUFF_TYPE_dataWrite_OFFSET    	0x148
#define RBUFF_TYPE_info_OFFSET         	0x168

/* Structure size and member offsets for RBUFF_BUFF_TYPE structure */

#define RBUFF_BUFF_TYPE_next_OFFSET              	0x0
#define RBUFF_BUFF_TYPE_spaceAvail_OFFSET        	0x8
#define RBUFF_BUFF_TYPE_dataStart_OFFSET         	0x10
#define RBUFF_BUFF_TYPE_dataEnd_OFFSET           	0x18
#define RBUFF_BUFF_TYPE_dataLen_OFFSET           	0x20
#define RBUFF_BUFF_TYPE_uncommitedRead_OFFSET    	0x28
#define RBUFF_BUFF_TYPE_prev_OFFSET              	0x30

/* Structure size and member offsets for RBUFF_INFO_TYPE structure */

#define RBUFF_INFO_TYPE_srcPart_OFFSET             	0x0
#define RBUFF_INFO_TYPE_options_OFFSET             	0x8
#define RBUFF_INFO_TYPE_buffSize_OFFSET            	0x10
#define RBUFF_INFO_TYPE_currBuffs_OFFSET           	0x18
#define RBUFF_INFO_TYPE_threshold_OFFSET           	0x20
#define RBUFF_INFO_TYPE_minBuffs_OFFSET            	0x28
#define RBUFF_INFO_TYPE_maxBuffs_OFFSET            	0x2c
#define RBUFF_INFO_TYPE_maxBuffsActual_OFFSET      	0x30
#define RBUFF_INFO_TYPE_emptyBuffs_OFFSET          	0x34
#define RBUFF_INFO_TYPE_dataContent_OFFSET         	0x38
#define RBUFF_INFO_TYPE_writesSinceReset_OFFSET    	0x40
#define RBUFF_INFO_TYPE_readsSinceReset_OFFSET     	0x44
#define RBUFF_INFO_TYPE_timesExtended_OFFSET       	0x48
#define RBUFF_INFO_TYPE_timesXThreshold_OFFSET     	0x4c
#define RBUFF_INFO_TYPE_bytesWritten_OFFSET        	0x50
#define RBUFF_INFO_TYPE_bytesRead_OFFSET           	0x58
#define RBUFF_INFO_TYPE_bytesPeak_OFFSET           	0x60

/* Structure size and member offsets for WV_LOG_LIST structure */

#define WV_LOG_LIST_hdr_wvLogListHead_OFFSET    	0x0
#define WV_LOG_LIST_hdr_memPart_OFFSET          	0x10
#define WV_LOG_LIST_hdr_numLogs_OFFSET          	0x18
#define WV_LOG_LIST_hdr_magic_OFFSET            	0x1c

/* Structure size and member offsets for WV_LOG structure */

#define WV_LOG_node_OFFSET               	0x0
#define WV_LOG_memPart_OFFSET            	0x8
#define WV_LOG_pEvtBuffer_OFFSET         	0x10
#define WV_LOG_pConfigEvent_OFFSET       	0x18
#define WV_LOG_configEventSize_OFFSET    	0x20
#define WV_LOG_pHashTbl_OFFSET           	0x28

/* Structure size and member offsets for WV_HASH_NODE structure */

#define WV_HASH_NODE_pEvent_OFFSET       	0x0
#define WV_HASH_NODE_eventSize_OFFSET    	0x8
#define WV_HASH_NODE_key_OFFSET          	0x10
#define WV_HASH_NODE_next_OFFSET         	0x18

/* Structure size and member offsets for WV_HASH_TBL structure */

#define WV_HASH_TBL_size_OFFSET    	0x0
#define WV_HASH_TBL_tbl_OFFSET     	0x8

/* Structure size and member offsets for TRIGGER structure */

#define TRIGGER_objCore_OFFSET           	0x0
#define TRIGGER_eventId_OFFSET           	0x80
#define TRIGGER_status_OFFSET            	0x82
#define TRIGGER_disable_OFFSET           	0x84
#define TRIGGER_contextType_OFFSET       	0x88
#define TRIGGER_contextId_OFFSET         	0x90
#define TRIGGER_objId_OFFSET             	0x98
#define TRIGGER_chain_OFFSET             	0xa0
#define TRIGGER_conditional_OFFSET       	0xa8
#define TRIGGER_condType_OFFSET          	0xac
#define TRIGGER_condEx1_OFFSET           	0xb0
#define TRIGGER_condOp_OFFSET            	0xb8
#define TRIGGER_condEx2_OFFSET           	0xc0
#define TRIGGER_actionType_OFFSET        	0xc8
#define TRIGGER_actionFunc_OFFSET        	0xd0
#define TRIGGER_actionArg_OFFSET         	0xd8
#define TRIGGER_actionDef_OFFSET         	0xe0
#define TRIGGER_hitCnt_OFFSET            	0xe4
#define TRIGGER_initialState_OFFSET      	0xe8
#define TRIGGER_pDataCollector_OFFSET    	0xf0

/* Structure size and member offsets for WIND_TCB structure */

#define WIND_TCB_excInfo_OFFSET    	0x300
#define WIND_TCB_regs_OFFSET       	0x350

/* Structure size and member offsets for JOB structure */

#define JOB_function_OFFSET    	0x0
#define JOB_arg1_OFFSET        	0x8
#define JOB_arg2_OFFSET        	0x10
#define JOB_isrTag_OFFSET      	0x18

/* Structure size and member offsets for WORK_Q_IX structure */

#define WORK_Q_IX_read_OFFSET       	0x0
#define WORK_Q_IX_bitmask_OFFSET    	0x4
#define WORK_Q_IX_write_OFFSET      	0x8

/* Structure size and member offsets for WIND_ISR structure */

#define WIND_ISR_objCore_OFFSET         	0x0
#define WIND_ISR_isrTag_OFFSET          	0x80
#define WIND_ISR_count_OFFSET           	0x88
#define WIND_ISR_serviceCount_OFFSET    	0x8c
#define WIND_ISR_cpuTime_OFFSET         	0x90
#define WIND_ISR_handlerRtn_OFFSET      	0x98
#define WIND_ISR_arg_OFFSET             	0xa0
#define WIND_ISR_options_OFFSET         	0xa8

/* Structure size and member offsets for SYSCALL_ENTRY_STATE structure */

#define SYSCALL_ENTRY_STATE_args_OFFSET       	0x0
#define SYSCALL_ENTRY_STATE_scn_OFFSET        	0x40
#define SYSCALL_ENTRY_STATE_pUStack_OFFSET    	0x60
#define SYSCALL_ENTRY_STATE_pc_OFFSET         	0x70
#define SYSCALL_ENTRY_STATE_size_OFFSET       	0xb0

/* Structure size and member offsets for WIND_SD structure */

#define WIND_SD_objCore_OFFSET        	0x0
#define WIND_SD_sem_OFFSET            	0x80
#define WIND_SD_options_OFFSET        	0x140
#define WIND_SD_attr_OFFSET           	0x144
#define WIND_SD_size_OFFSET           	0x148
#define WIND_SD_physAdrs_OFFSET       	0x150
#define WIND_SD_virtAdrs_OFFSET       	0x158
#define WIND_SD_clientCount_OFFSET    	0x160

/* Structure size and member offsets for REG_SET structure */

#define REG_SET_sp_OFFSET      	0x8
#define REG_SET_msr_OFFSET     	0x100
#define REG_SET_pc_OFFSET      	0x118
#define REG_SET_cr_OFFSET      	0x120
#define REG_SET_size_OFFSET    	0x148

/* Structure size and member offsets for ESFPPC structure */

#define ESFPPC_vecOffset_OFFSET    	0xa
#define ESFPPC_dear_OFFSET         	0x10
#define ESFPPC_esr_OFFSET          	0x18
#define ESFPPC_iarr_OFFSET         	0x20
#define ESFPPC_regSet_OFFSET       	0x28

/* Offset for syscall entry */

#define syscallEntryBaseOffset_OFFSET    	0x0

/* Structure size and member offsets for SYSCALL_ENTRY_STATE structure */

#define SYSCALL_ENTRY_STATE_retAddrReg_OFFSET         	0x58
#define SYSCALL_ENTRY_STATE_nonVolatileRegs_OFFSET    	0x78

/* Structure size and member offsets for MODULE structure */

#define MODULE_nameWithPath_OFFSET     	0x28
#define MODULE_flags_OFFSET            	0x530
#define MODULE_sectionList_OFFSET      	0x538
#define MODULE_segmentList_OFFSET      	0x548
#define MODULE_format_OFFSET           	0x558
#define MODULE_group_OFFSET            	0x55c
#define MODULE_ctors_OFFSET            	0x560
#define MODULE_dtors_OFFSET            	0x568
#define MODULE_commTotalSize_OFFSET    	0x570
#define MODULE_swapNeeded_OFFSET       	0x574
#define MODULE_undefSymCount_OFFSET    	0x578
#define MODULE_undefSymList_OFFSET     	0x580
#define MODULE_commonSymList_OFFSET    	0x590

/* Structure size and member offsets for SEGMENT structure */

#define SEGMENT_segmentNode_OFFSET    	0x0
#define SEGMENT_address_OFFSET        	0x10
#define SEGMENT_size_OFFSET           	0x18
#define SEGMENT_type_OFFSET           	0x20
#define SEGMENT_flags_OFFSET          	0x24

/* Structure size and member offsets for SECTION_DESC structure */

#define SECTION_DESC_sectionNode_OFFSET     	0x18
#define SECTION_DESC_name_OFFSET            	0x28
#define SECTION_DESC_address_OFFSET         	0x30
#define SECTION_DESC_size_OFFSET            	0x38
#define SECTION_DESC_type_OFFSET            	0x40
#define SECTION_DESC_flags_OFFSET           	0x44
#define SECTION_DESC_alignment_OFFSET       	0x48
#define SECTION_DESC_checksum_OFFSET        	0x50
#define SECTION_DESC_fileChecksum_OFFSET    	0x54

/* Structure size and member offsets for MODLIST_DESC structure */

#define MODLIST_DESC_moduleList_OFFSET    	0x18

/* Structure size and member offsets for N structure */

#define loadNoSymbols_OFFSET    	0x2

/* Structure size and member offsets for L structure */

#define loadLocalSymbols_OFFSET    	0x4

/* Structure size and member offsets for G structure */

#define loadGlobalSymbols_OFFSET    	0x8

/* Structure size and member offsets for A structure */

#define loadAllSymbols_OFFSET    	0xc

/* Structure size and member offsets for M structure */

#define hiddenModule_OFFSET    	0x10

/* Structure size and member offsets for F structure */

#define loadFullyLinked_OFFSET    	0x20

/* Structure size and member offsets for N structure */

#define loadNoDownload_OFFSET    	0x40

/* Structure size and member offsets for F structure */

#define loadForce_OFFSET    	0x80

/* Structure size and member offsets for C structure */

#define loadCommonMatchNone_OFFSET    	0x100
#define loadCommonMatchUser_OFFSET    	0x200
#define loadCommonMatchAll_OFFSET     	0x400
#define loadCommonHeap_OFFSET         	0x800
#define loadCplusXtorAuto_OFFSET      	0x1000
#define loadCplusXtorManual_OFFSET    	0x2000

/* Structure size and member offsets for W structure */

#define loadWeakMatchNone_OFFSET    	0x10000
#define loadWeakMatchAll_OFFSET     	0x20000

/* Structure size and member offsets for F structure */

#define unloadForce_OFFSET    	0x2

/* Structure size and member offsets for C structure */

#define unloadCplusXtorAuto_OFFSET      	0x20
#define unloadCplusXtorManual_OFFSET    	0x40

/* Structure size and member offsets for SYMTAB structure */

#define SYMTAB_nameHashId_OFFSET    	0x18

/* Structure size and member offsets for HASH_TBL structure */

#define HASH_TBL_pHashTbl_OFFSET    	0x28
#define HASH_TBL_elements_OFFSET    	0x38

/* Structure size and member offsets for SL_LIST structure */

#define SL_LIST_head_OFFSET    	0x0

/* Structure size and member offsets for SL_NODE structure */

#define SL_NODE_next_OFFSET    	0x0

/* Structure size and member offsets for SL_LIST structure */

#define SL_LIST_size_OFFSET    	0x10

/* Structure size and member offsets for COPROC_TBL_ENTRY structure */

#define COPROC_TBL_ENTRY_pCtx_OFFSET           	0x0
#define COPROC_TBL_ENTRY_pDescriptor_OFFSET    	0x8
#define COPROC_TBL_ENTRY_pTask_OFFSET          	0x10
#define COPROC_TBL_ENTRY_size_OFFSET           	0x18

/* Structure size and member offsets for COPROC_DESC structure */

#define COPROC_DESC_next_OFFSET          	0x0
#define COPROC_DESC_ctxSize_OFFSET       	0x8
#define COPROC_DESC_ctxAlign_OFFSET      	0x10
#define COPROC_DESC_pCtxGetRtn_OFFSET    	0x48
#define COPROC_DESC_pLastEntry_OFFSET    	0x88
#define COPROC_DESC_mask_OFFSET          	0x90

/* Structure size and member offsets for VM_LIB_INFO structure */

#define VM_LIB_INFO_pVmCtxSwitchRtn_OFFSET    	0x50

/* Structure size and member offsets for VM_CONTEXT structure */

#define VM_CONTEXT_mmuTransTbl_OFFSET    	0x80

/* Structure size and member offsets for WIND_VARS structure */

#define WIND_VARS_vars_OFFSET                    	0x0
#define _WIND_VARS_cpu_taskIdCurrent_OFFSET      	0x0
#define _WIND_VARS_cpu_isrIdCurrent_OFFSET       	0x8
#define _WIND_VARS_cpu_errno_OFFSET              	0x10
#define _WIND_VARS_cpu_intCnt_OFFSET             	0x14
#define _WIND_VARS_cpu_vxIntStackBase_OFFSET     	0x18
#define _WIND_VARS_cpu_vxIntStackEnd_OFFSET      	0x20
#define _WIND_VARS_cpu_workQIx_OFFSET            	0x28
#define _WIND_VARS_cpu_workQIsEmpty_OFFSET       	0x34
#define _WIND_VARS_cpu_spinLockIsrCnt_OFFSET     	0x38
#define _WIND_VARS_cpu_spinLockTaskCnt_OFFSET    	0x3c
#define _WIND_VARS_cpu_idleTaskId_OFFSET         	0x40
#define _WIND_VARS_cpu_kernelIsIdle_OFFSET       	0x48
#define _WIND_VARS_cpu_reschedMode_OFFSET        	0x4c
#define _WIND_VARS_cpu_my_tkt_OFFSET             	0x50
#define _WIND_VARS_cpu_windPwrOffState_OFFSET    	0x58
#define _WIND_VARS_cpu_reserved1_OFFSET          	0x60
#define _WIND_VARS_cpu_reserved2_OFFSET          	0x68
#define _WIND_VARS_cpu_archVars_OFFSET           	0x70
#define WIND_VARS_SIZEOF                         	0x80

/* Structure size and member offsets for VX_KERNEL_LOCK structure */

#define VX_KERNEL_LOCK_tkt_ctrAligned_OFFSET    	0x0
#define VX_KERNEL_LOCK_tkt_ctr_OFFSET           	0x0
#define VX_KERNEL_LOCK_svc_ctr_OFFSET           	0x100
#define VX_KERNEL_LOCK_cpuIndex_OFFSET          	0x108
#define VX_KERNEL_LOCK_flags_OFFSET             	0x10c

/* Structure size and member offsets for WIND_SMP_INFO structure */

#define WIND_SMP_INFO_affinity_OFFSET          	0x0
#define WIND_SMP_INFO_cpuIndex_OFFSET          	0x4
#define WIND_SMP_INFO_readyQExt_OFFSET         	0x8
#define WIND_SMP_INFO_stateSaveQHead_OFFSET    	0x10
#define WIND_SMP_INFO_stateRequest_OFFSET      	0x30

/* Structure size and member offsets for TLS_DESC structure */

#define TLS_DESC_maxModules_OFFSET        	0x0
#define TLS_DESC_pTlsTaskModule_OFFSET    	0x8
#define TLS_DESC_addr_OFFSET              	0x10

/* Structure size and member offsets for MMU_LIB_FUNCS structure */

#define MMU_LIB_FUNCS_mmuCurrentSet_OFFSET    	0x40

/* Structure size and member offsets for WRS_CONFIG_CPU_PPCE structure */

#define _WRS_CONFIG_CPU_PPCE6500_OFFSET    	0x1

#ifdef __cplusplus
}
#endif

#endif /* __INCoffsetsh */
