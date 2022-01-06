Symbol ST_context_init {
}
Symbol .TOC. {
}
Symbol vxAtomicInc {
}
Symbol memory_map_init {
}
Symbol vxAtomicDec {
}
Symbol stKTxtStart {
}
Symbol vmLibInfo {
}
Symbol stKTxtEnd {
}
Symbol memPoolEndAdrs {
}
Symbol ST_context_uninit {
}
Symbol intContext {
}
Symbol vxMemProbe {
}
Symbol stCtxMemValidate {
}
Symbol taskTcb {
}
Symbol vxAtomicGet {
}
Symbol ST_debug_level {
}
Symbol logMsg {
}
Symbol taskClassId {
}
Symbol objVerify {
}
Symbol _func_rtpIdVerify {
}
Symbol vxKernelVars {
}
Symbol vxCpuIndexGet {
}
Symbol map_region_find {
}
Symbol sysMemDescGet {
}
Symbol kernelId {
}
Symbol kernelIdGet {
}
Symbol _func_taskMemCtxSwitch {
}
Symbol __errno {
}
Symbol ST_context_create {
}
Symbol ArchContextCreate {
}
Symbol ST_context_delete {
}
Symbol ST_CallingContextGet {
}
Symbol RtiTools_ContextTopDiscover {
}
Symbol RtiTools_ExclusionRegionsTop {
}
Symbol RtiTools_ContextExclude {
}
Symbol ST_CheckOSFrames {
}
Symbol ST_TraceFunctionEntry {
}
Symbol ST_FrameCrawl {
}
Symbol ST_trace_error {
}
Symbol ST_trace_truncated {
}
Symbol ST_perform_stack_trace {
}
Symbol ST_GetIntContextTop {
}
Symbol printf {
}
Symbol ST_task_in_sys_call {
}
Symbol ST_task_is_rtp_task {
}
Symbol ST_task_is_kernel_task {
}
Symbol ST_task_in_exc_mode {
}
Symbol SUTILS_CONTEXT_LIB_VERSION {
}
Symbol pIsRtpSandbox {
}
Symbol RtiTools_ContextExcludeAdd {
}
Symbol RtiTools_ContextExcludeClear {
}
Symbol RtiTools_ContextExcludePrint {
}
Symbol vxTaskEntry {
}
Symbol intVecBaseGet {
}
Symbol intEnt {
}
Symbol memory_map_lock_take {
}
Symbol map_lock {
}
Symbol spinLockIsrTake {
}
Symbol memory_map_lock_give {
}
Symbol spinLockIsrGive {
}
Symbol memory_map_kernel_node_get {
}
Symbol ST_pidFind {
}
Symbol memory_map_free_map {
}
Symbol free {
}
Symbol memory_map_pid_add {
}
Symbol memory_map_pid_free {
}
Symbol _func_ST_memory_map_region_rtp_find {
}
Symbol ST_memory_map_show {
}
Symbol _func_ST_memory_map_rtp_show {
}
Symbol malloc {
}
Symbol _func_ST_memory_map_module_init {
}
Symbol memory_map_uninit {
}
Symbol _func_ST_memory_map_module_uninit {
}
Symbol strlen {
}
Symbol strrchr {
}
Symbol objNameGet {
}
Symbol snprintf {
}
Symbol _func_rtpShlInfoGet {
}
Symbol _func_moduleSegInfoGet {
}
Symbol calloc {
}
Symbol _func_kernelModuleListIdGet {
}
Symbol semTake {
}
Symbol semGive {
}
Symbol moduleNameGet {
}
Symbol moduleLoadHookAdd {
}
Symbol moduleUnloadHookAdd {
}
Symbol objEach {
}
Symbol _func_rtpInitCompleteHookAdd {
}
Symbol _func_rtpDeleteHookAdd {
}
Symbol _func_rtpShlOpenHook {
}
Symbol _func_rtpShlCloseHook {
}
Symbol _func_ST_sdCreateHookAdd {
}
Symbol _func_ST_sdDeleteHookAdd {
}
Symbol _func_ST_sdCreateHookDelete {
}
Symbol _func_rtpDeleteHookDelete {
}
Symbol _func_rtpInitCompleteHookDelete {
}
Symbol moduleUnloadHookDelete {
}
Symbol moduleLoadHookDelete {
}
Symbol _func_ST_sdDeleteHookDelete {
}
Symbol stacktraceModuleHooksInit {
}
Symbol stacktraceRtpHooksInit {
}
Symbol stacktraceShdHooksInit {
}
Symbol sdCreateHookAdd {
}
Symbol sdCreateHookDelete {
}
Symbol sdDeleteHookAdd {
}
Symbol sdDeleteHookDelete {
}
ObjectFile libstacktrace.a::context_memtest.o {
	NAME Object file context_memtest.o from archive libstacktrace.a
	EXPORTS ST_context_init stKTxtStart stKTxtEnd ST_context_uninit stCtxMemValidate
	IMPORTS .TOC. vxAtomicInc memory_map_init vxAtomicDec vmLibInfo memPoolEndAdrs intContext vxMemProbe taskTcb vxAtomicGet ST_debug_level logMsg taskClassId objVerify _func_rtpIdVerify vxKernelVars vxCpuIndexGet map_region_find sysMemDescGet kernelId
	DECLARES 
	USES 
}
Module context_memtest.o {
	OBJECT += libstacktrace.a::context_memtest.o
}
ObjectFile libstacktrace.a::context.o {
	NAME Object file context.o from archive libstacktrace.a
	EXPORTS ST_debug_level ST_context_create ST_context_delete ST_CallingContextGet ST_trace_error ST_trace_truncated ST_perform_stack_trace ST_task_in_sys_call ST_task_is_rtp_task ST_task_is_kernel_task ST_task_in_exc_mode SUTILS_CONTEXT_LIB_VERSION pIsRtpSandbox
	IMPORTS .TOC. taskTcb taskClassId objVerify _func_rtpIdVerify kernelIdGet stKTxtStart memPoolEndAdrs _func_taskMemCtxSwitch logMsg __errno ArchContextCreate stCtxMemValidate RtiTools_ContextTopDiscover RtiTools_ExclusionRegionsTop RtiTools_ContextExclude ST_CheckOSFrames ST_TraceFunctionEntry ST_FrameCrawl ST_GetIntContextTop printf
	DECLARES 
	USES 
}
Module context.o {
	OBJECT += libstacktrace.a::context.o
}
ObjectFile libstacktrace.a::context_region.o {
	NAME Object file context_region.o from archive libstacktrace.a
	EXPORTS RtiTools_ContextExcludeAdd RtiTools_ExclusionRegionsTop RtiTools_ContextExcludeClear RtiTools_ContextExcludePrint RtiTools_ContextExclude
	IMPORTS .TOC. logMsg
	DECLARES 
	USES 
}
Module context_region.o {
	OBJECT += libstacktrace.a::context_region.o
}
ObjectFile libstacktrace.a::ppc_os.o {
	NAME Object file ppc_os.o from archive libstacktrace.a
	EXPORTS ArchContextCreate RtiTools_ContextTopDiscover ST_TraceFunctionEntry ST_CheckOSFrames ST_GetIntContextTop
	IMPORTS .TOC. taskTcb vxTaskEntry intContext vmLibInfo intVecBaseGet intEnt
	DECLARES 
	USES 
}
Module ppc_os.o {
	OBJECT += libstacktrace.a::ppc_os.o
}
ObjectFile libstacktrace.a::ppc_crawl.o {
	NAME Object file ppc_crawl.o from archive libstacktrace.a
	EXPORTS ST_FrameCrawl
	IMPORTS .TOC. stCtxMemValidate
	DECLARES 
	USES 
}
Module ppc_crawl.o {
	OBJECT += libstacktrace.a::ppc_crawl.o
}
ObjectFile libstacktrace.a::memory_map_vx.o {
	NAME Object file memory_map_vx.o from archive libstacktrace.a
	EXPORTS memory_map_lock_take map_lock memory_map_lock_give memory_map_kernel_node_get ST_pidFind memory_map_free_map memory_map_pid_add memory_map_pid_free map_region_find _func_ST_memory_map_region_rtp_find ST_memory_map_show _func_ST_memory_map_rtp_show memory_map_init _func_ST_memory_map_module_init memory_map_uninit _func_ST_memory_map_module_uninit
	IMPORTS .TOC. spinLockIsrTake spinLockIsrGive free printf malloc kernelIdGet logMsg
	DECLARES 
	USES 
}
Module memory_map_vx.o {
	OBJECT += libstacktrace.a::memory_map_vx.o
}
ObjectFile libstacktrace.a::memory_map_module_vx.o {
	NAME Object file memory_map_module_vx.o from archive libstacktrace.a
	EXPORTS _func_ST_sdCreateHookAdd _func_ST_sdDeleteHookAdd _func_ST_sdCreateHookDelete _func_ST_sdDeleteHookDelete stacktraceModuleHooksInit stacktraceRtpHooksInit
	IMPORTS .TOC. free strlen strrchr logMsg malloc objNameGet snprintf memory_map_lock_take memory_map_lock_give memory_map_pid_free _func_rtpIdVerify memory_map_pid_add kernelIdGet _func_rtpShlInfoGet ST_pidFind printf _func_moduleSegInfoGet calloc memory_map_kernel_node_get _func_kernelModuleListIdGet semTake semGive moduleNameGet moduleLoadHookAdd moduleUnloadHookAdd objEach _func_rtpInitCompleteHookAdd _func_rtpDeleteHookAdd _func_rtpShlOpenHook _func_rtpShlCloseHook _func_rtpDeleteHookDelete _func_rtpInitCompleteHookDelete memory_map_free_map moduleUnloadHookDelete moduleLoadHookDelete _func_ST_memory_map_module_init _func_ST_memory_map_module_uninit _func_ST_memory_map_region_rtp_find _func_ST_memory_map_rtp_show
	DECLARES 
	USES 
}
Module memory_map_module_vx.o {
	OBJECT += libstacktrace.a::memory_map_module_vx.o
}
ObjectFile libstacktrace.a::memory_map_shd_vx.o {
	NAME Object file memory_map_shd_vx.o from archive libstacktrace.a
	EXPORTS stacktraceShdHooksInit
	IMPORTS .TOC. sdCreateHookAdd _func_ST_sdCreateHookAdd sdCreateHookDelete sdDeleteHookAdd sdDeleteHookDelete _func_ST_sdCreateHookDelete _func_ST_sdDeleteHookAdd _func_ST_sdDeleteHookDelete
	DECLARES 
	USES 
}
Module memory_map_shd_vx.o {
	OBJECT += libstacktrace.a::memory_map_shd_vx.o
}
Library libstacktrace.a {
	MODULES libstacktrace.a::context_memtest.o libstacktrace.a::context.o libstacktrace.a::context_region.o libstacktrace.a::ppc_os.o libstacktrace.a::ppc_crawl.o libstacktrace.a::memory_map_vx.o libstacktrace.a::memory_map_module_vx.o libstacktrace.a::memory_map_shd_vx.o
}
Symbol ST_context_init {
}
Symbol .TOC. {
}
Symbol vxAtomicInc {
}
Symbol memory_map_init {
}
Symbol vxAtomicDec {
}
Symbol stKTxtStart {
}
Symbol vmLibInfo {
}
Symbol stKTxtEnd {
}
Symbol memPoolEndAdrs {
}
Symbol ST_context_uninit {
}
Symbol intContext {
}
Symbol vxMemProbe {
}
Symbol stCtxMemValidate {
}
Symbol taskTcb {
}
Symbol vxAtomicGet {
}
Symbol ST_debug_level {
}
Symbol logMsg {
}
Symbol taskClassId {
}
Symbol objVerify {
}
Symbol _func_rtpIdVerify {
}
Symbol vxKernelVars {
}
Symbol vxCpuIndexGet {
}
Symbol map_region_find {
}
Symbol sysMemDescGet {
}
Symbol kernelId {
}
Symbol kernelIdGet {
}
Symbol _func_taskMemCtxSwitch {
}
Symbol __errno {
}
Symbol ST_context_create {
}
Symbol ArchContextCreate {
}
Symbol ST_context_delete {
}
Symbol ST_CallingContextGet {
}
Symbol RtiTools_ContextTopDiscover {
}
Symbol RtiTools_ExclusionRegionsTop {
}
Symbol RtiTools_ContextExclude {
}
Symbol ST_CheckOSFrames {
}
Symbol ST_TraceFunctionEntry {
}
Symbol ST_FrameCrawl {
}
Symbol ST_trace_error {
}
Symbol ST_trace_truncated {
}
Symbol ST_perform_stack_trace {
}
Symbol ST_GetIntContextTop {
}
Symbol printf {
}
Symbol ST_task_in_sys_call {
}
Symbol ST_task_is_rtp_task {
}
Symbol ST_task_is_kernel_task {
}
Symbol ST_task_in_exc_mode {
}
Symbol SUTILS_CONTEXT_LIB_VERSION {
}
Symbol pIsRtpSandbox {
}
Symbol RtiTools_ContextExcludeAdd {
}
Symbol RtiTools_ContextExcludeClear {
}
Symbol RtiTools_ContextExcludePrint {
}
Symbol vxTaskEntry {
}
Symbol intVecBaseGet {
}
Symbol intEnt {
}
Symbol memory_map_lock_take {
}
Symbol map_lock {
}
Symbol spinLockIsrTake {
}
Symbol memory_map_lock_give {
}
Symbol spinLockIsrGive {
}
Symbol memory_map_kernel_node_get {
}
Symbol ST_pidFind {
}
Symbol memory_map_free_map {
}
Symbol free {
}
Symbol memory_map_pid_add {
}
Symbol memory_map_pid_free {
}
Symbol _func_ST_memory_map_region_rtp_find {
}
Symbol ST_memory_map_show {
}
Symbol _func_ST_memory_map_rtp_show {
}
Symbol malloc {
}
Symbol _func_ST_memory_map_module_init {
}
Symbol memory_map_uninit {
}
Symbol _func_ST_memory_map_module_uninit {
}
Symbol strlen {
}
Symbol strrchr {
}
Symbol objNameGet {
}
Symbol snprintf {
}
Symbol _func_rtpShlInfoGet {
}
Symbol _func_moduleSegInfoGet {
}
Symbol calloc {
}
Symbol _func_kernelModuleListIdGet {
}
Symbol semTake {
}
Symbol semGive {
}
Symbol moduleNameGet {
}
Symbol moduleLoadHookAdd {
}
Symbol moduleUnloadHookAdd {
}
Symbol objEach {
}
Symbol _func_rtpInitCompleteHookAdd {
}
Symbol _func_rtpDeleteHookAdd {
}
Symbol _func_rtpShlOpenHook {
}
Symbol _func_rtpShlCloseHook {
}
Symbol _func_ST_sdCreateHookAdd {
}
Symbol _func_ST_sdDeleteHookAdd {
}
Symbol _func_ST_sdCreateHookDelete {
}
Symbol _func_rtpDeleteHookDelete {
}
Symbol _func_rtpInitCompleteHookDelete {
}
Symbol moduleUnloadHookDelete {
}
Symbol moduleLoadHookDelete {
}
Symbol _func_ST_sdDeleteHookDelete {
}
Symbol stacktraceModuleHooksInit {
}
Symbol stacktraceRtpHooksInit {
}
Symbol stacktraceShdHooksInit {
}
Symbol sdCreateHookAdd {
}
Symbol sdCreateHookDelete {
}
Symbol sdDeleteHookAdd {
}
Symbol sdDeleteHookDelete {
}
ObjectFile libstacktrace.a::context_memtest.o {
	NAME Object file context_memtest.o from archive libstacktrace.a
	EXPORTS ST_context_init stKTxtStart stKTxtEnd ST_context_uninit stCtxMemValidate
	IMPORTS .TOC. vxAtomicInc memory_map_init vxAtomicDec vmLibInfo memPoolEndAdrs intContext vxMemProbe taskTcb vxAtomicGet ST_debug_level logMsg taskClassId objVerify _func_rtpIdVerify vxKernelVars vxCpuIndexGet map_region_find sysMemDescGet kernelId
	DECLARES 
	USES 
}
Module context_memtest.o {
	OBJECT += libstacktrace.a::context_memtest.o
}
ObjectFile libstacktrace.a::context.o {
	NAME Object file context.o from archive libstacktrace.a
	EXPORTS ST_debug_level ST_context_create ST_context_delete ST_CallingContextGet ST_trace_error ST_trace_truncated ST_perform_stack_trace ST_task_in_sys_call ST_task_is_rtp_task ST_task_is_kernel_task ST_task_in_exc_mode SUTILS_CONTEXT_LIB_VERSION pIsRtpSandbox
	IMPORTS .TOC. taskTcb taskClassId objVerify _func_rtpIdVerify kernelIdGet stKTxtStart memPoolEndAdrs _func_taskMemCtxSwitch logMsg __errno ArchContextCreate stCtxMemValidate RtiTools_ContextTopDiscover RtiTools_ExclusionRegionsTop RtiTools_ContextExclude ST_CheckOSFrames ST_TraceFunctionEntry ST_FrameCrawl ST_GetIntContextTop printf
	DECLARES 
	USES 
}
Module context.o {
	OBJECT += libstacktrace.a::context.o
}
ObjectFile libstacktrace.a::context_region.o {
	NAME Object file context_region.o from archive libstacktrace.a
	EXPORTS RtiTools_ContextExcludeAdd RtiTools_ExclusionRegionsTop RtiTools_ContextExcludeClear RtiTools_ContextExcludePrint RtiTools_ContextExclude
	IMPORTS .TOC. logMsg
	DECLARES 
	USES 
}
Module context_region.o {
	OBJECT += libstacktrace.a::context_region.o
}
ObjectFile libstacktrace.a::ppc_os.o {
	NAME Object file ppc_os.o from archive libstacktrace.a
	EXPORTS ArchContextCreate RtiTools_ContextTopDiscover ST_TraceFunctionEntry ST_CheckOSFrames ST_GetIntContextTop
	IMPORTS .TOC. taskTcb vxTaskEntry intContext vmLibInfo intVecBaseGet intEnt
	DECLARES 
	USES 
}
Module ppc_os.o {
	OBJECT += libstacktrace.a::ppc_os.o
}
ObjectFile libstacktrace.a::ppc_crawl.o {
	NAME Object file ppc_crawl.o from archive libstacktrace.a
	EXPORTS ST_FrameCrawl
	IMPORTS .TOC. stCtxMemValidate
	DECLARES 
	USES 
}
Module ppc_crawl.o {
	OBJECT += libstacktrace.a::ppc_crawl.o
}
ObjectFile libstacktrace.a::memory_map_vx.o {
	NAME Object file memory_map_vx.o from archive libstacktrace.a
	EXPORTS memory_map_lock_take map_lock memory_map_lock_give memory_map_kernel_node_get ST_pidFind memory_map_free_map memory_map_pid_add memory_map_pid_free map_region_find _func_ST_memory_map_region_rtp_find ST_memory_map_show _func_ST_memory_map_rtp_show memory_map_init _func_ST_memory_map_module_init memory_map_uninit _func_ST_memory_map_module_uninit
	IMPORTS .TOC. spinLockIsrTake spinLockIsrGive free printf malloc kernelIdGet logMsg
	DECLARES 
	USES 
}
Module memory_map_vx.o {
	OBJECT += libstacktrace.a::memory_map_vx.o
}
ObjectFile libstacktrace.a::memory_map_module_vx.o {
	NAME Object file memory_map_module_vx.o from archive libstacktrace.a
	EXPORTS _func_ST_sdCreateHookAdd _func_ST_sdDeleteHookAdd _func_ST_sdCreateHookDelete _func_ST_sdDeleteHookDelete stacktraceModuleHooksInit stacktraceRtpHooksInit
	IMPORTS .TOC. free strlen strrchr logMsg malloc objNameGet snprintf memory_map_lock_take memory_map_lock_give memory_map_pid_free _func_rtpIdVerify memory_map_pid_add kernelIdGet _func_rtpShlInfoGet ST_pidFind printf _func_moduleSegInfoGet calloc memory_map_kernel_node_get _func_kernelModuleListIdGet semTake semGive moduleNameGet moduleLoadHookAdd moduleUnloadHookAdd objEach _func_rtpInitCompleteHookAdd _func_rtpDeleteHookAdd _func_rtpShlOpenHook _func_rtpShlCloseHook _func_rtpDeleteHookDelete _func_rtpInitCompleteHookDelete memory_map_free_map moduleUnloadHookDelete moduleLoadHookDelete _func_ST_memory_map_module_init _func_ST_memory_map_module_uninit _func_ST_memory_map_region_rtp_find _func_ST_memory_map_rtp_show
	DECLARES 
	USES 
}
Module memory_map_module_vx.o {
	OBJECT += libstacktrace.a::memory_map_module_vx.o
}
ObjectFile libstacktrace.a::memory_map_shd_vx.o {
	NAME Object file memory_map_shd_vx.o from archive libstacktrace.a
	EXPORTS stacktraceShdHooksInit
	IMPORTS .TOC. sdCreateHookAdd _func_ST_sdCreateHookAdd sdCreateHookDelete sdDeleteHookAdd sdDeleteHookDelete _func_ST_sdCreateHookDelete _func_ST_sdDeleteHookAdd _func_ST_sdDeleteHookDelete
	DECLARES 
	USES 
}
Module memory_map_shd_vx.o {
	OBJECT += libstacktrace.a::memory_map_shd_vx.o
}
Library libstacktrace.a {
	MODULES libstacktrace.a::context_memtest.o libstacktrace.a::context.o libstacktrace.a::context_region.o libstacktrace.a::ppc_os.o libstacktrace.a::ppc_crawl.o libstacktrace.a::memory_map_vx.o libstacktrace.a::memory_map_module_vx.o libstacktrace.a::memory_map_shd_vx.o
}
Symbol ST_context_init {
}
Symbol .TOC. {
}
Symbol vxAtomicInc {
}
Symbol memory_map_init {
}
Symbol vxAtomicDec {
}
Symbol stKTxtStart {
}
Symbol vmLibInfo {
}
Symbol stKTxtEnd {
}
Symbol memPoolEndAdrs {
}
Symbol ST_context_uninit {
}
Symbol intContext {
}
Symbol vxMemProbe {
}
Symbol stCtxMemValidate {
}
Symbol taskTcb {
}
Symbol vxAtomicGet {
}
Symbol ST_debug_level {
}
Symbol logMsg {
}
Symbol taskClassId {
}
Symbol objVerify {
}
Symbol _func_rtpIdVerify {
}
Symbol vxKernelVars {
}
Symbol vxCpuIndexGet {
}
Symbol map_region_find {
}
Symbol sysMemDescGet {
}
Symbol kernelId {
}
Symbol kernelIdGet {
}
Symbol _func_taskMemCtxSwitch {
}
Symbol __errno {
}
Symbol ST_context_create {
}
Symbol ArchContextCreate {
}
Symbol ST_context_delete {
}
Symbol ST_CallingContextGet {
}
Symbol RtiTools_ContextTopDiscover {
}
Symbol RtiTools_ExclusionRegionsTop {
}
Symbol RtiTools_ContextExclude {
}
Symbol ST_CheckOSFrames {
}
Symbol ST_TraceFunctionEntry {
}
Symbol ST_FrameCrawl {
}
Symbol ST_trace_error {
}
Symbol ST_trace_truncated {
}
Symbol ST_perform_stack_trace {
}
Symbol ST_GetIntContextTop {
}
Symbol printf {
}
Symbol ST_task_in_sys_call {
}
Symbol ST_task_is_rtp_task {
}
Symbol ST_task_is_kernel_task {
}
Symbol ST_task_in_exc_mode {
}
Symbol SUTILS_CONTEXT_LIB_VERSION {
}
Symbol pIsRtpSandbox {
}
Symbol RtiTools_ContextExcludeAdd {
}
Symbol RtiTools_ContextExcludeClear {
}
Symbol RtiTools_ContextExcludePrint {
}
Symbol vxTaskEntry {
}
Symbol intVecBaseGet {
}
Symbol intEnt {
}
Symbol memory_map_lock_take {
}
Symbol map_lock {
}
Symbol spinLockIsrTake {
}
Symbol memory_map_lock_give {
}
Symbol spinLockIsrGive {
}
Symbol memory_map_kernel_node_get {
}
Symbol ST_pidFind {
}
Symbol memory_map_free_map {
}
Symbol free {
}
Symbol memory_map_pid_add {
}
Symbol memory_map_pid_free {
}
Symbol _func_ST_memory_map_region_rtp_find {
}
Symbol ST_memory_map_show {
}
Symbol _func_ST_memory_map_rtp_show {
}
Symbol malloc {
}
Symbol _func_ST_memory_map_module_init {
}
Symbol memory_map_uninit {
}
Symbol _func_ST_memory_map_module_uninit {
}
Symbol strlen {
}
Symbol strrchr {
}
Symbol objNameGet {
}
Symbol snprintf {
}
Symbol _func_rtpShlInfoGet {
}
Symbol _func_moduleSegInfoGet {
}
Symbol calloc {
}
Symbol _func_kernelModuleListIdGet {
}
Symbol semTake {
}
Symbol semGive {
}
Symbol moduleNameGet {
}
Symbol moduleLoadHookAdd {
}
Symbol moduleUnloadHookAdd {
}
Symbol objEach {
}
Symbol _func_rtpInitCompleteHookAdd {
}
Symbol _func_rtpDeleteHookAdd {
}
Symbol _func_rtpShlOpenHook {
}
Symbol _func_rtpShlCloseHook {
}
Symbol _func_ST_sdCreateHookAdd {
}
Symbol _func_ST_sdDeleteHookAdd {
}
Symbol _func_ST_sdCreateHookDelete {
}
Symbol _func_rtpDeleteHookDelete {
}
Symbol _func_rtpInitCompleteHookDelete {
}
Symbol moduleUnloadHookDelete {
}
Symbol moduleLoadHookDelete {
}
Symbol _func_ST_sdDeleteHookDelete {
}
Symbol stacktraceModuleHooksInit {
}
Symbol stacktraceRtpHooksInit {
}
Symbol stacktraceShdHooksInit {
}
Symbol sdCreateHookAdd {
}
Symbol sdCreateHookDelete {
}
Symbol sdDeleteHookAdd {
}
Symbol sdDeleteHookDelete {
}
ObjectFile libstacktrace.a::context_memtest.o {
	NAME Object file context_memtest.o from archive libstacktrace.a
	EXPORTS ST_context_init stKTxtStart stKTxtEnd ST_context_uninit stCtxMemValidate
	IMPORTS .TOC. vxAtomicInc memory_map_init vxAtomicDec vmLibInfo memPoolEndAdrs intContext vxMemProbe taskTcb vxAtomicGet ST_debug_level logMsg taskClassId objVerify _func_rtpIdVerify vxKernelVars vxCpuIndexGet map_region_find sysMemDescGet kernelId
	DECLARES 
	USES 
}
Module context_memtest.o {
	OBJECT += libstacktrace.a::context_memtest.o
}
ObjectFile libstacktrace.a::context.o {
	NAME Object file context.o from archive libstacktrace.a
	EXPORTS ST_debug_level ST_context_create ST_context_delete ST_CallingContextGet ST_trace_error ST_trace_truncated ST_perform_stack_trace ST_task_in_sys_call ST_task_is_rtp_task ST_task_is_kernel_task ST_task_in_exc_mode SUTILS_CONTEXT_LIB_VERSION pIsRtpSandbox
	IMPORTS .TOC. taskTcb taskClassId objVerify _func_rtpIdVerify kernelIdGet stKTxtStart memPoolEndAdrs _func_taskMemCtxSwitch logMsg __errno ArchContextCreate stCtxMemValidate RtiTools_ContextTopDiscover RtiTools_ExclusionRegionsTop RtiTools_ContextExclude ST_CheckOSFrames ST_TraceFunctionEntry ST_FrameCrawl ST_GetIntContextTop printf
	DECLARES 
	USES 
}
Module context.o {
	OBJECT += libstacktrace.a::context.o
}
ObjectFile libstacktrace.a::context_region.o {
	NAME Object file context_region.o from archive libstacktrace.a
	EXPORTS RtiTools_ContextExcludeAdd RtiTools_ExclusionRegionsTop RtiTools_ContextExcludeClear RtiTools_ContextExcludePrint RtiTools_ContextExclude
	IMPORTS .TOC. logMsg
	DECLARES 
	USES 
}
Module context_region.o {
	OBJECT += libstacktrace.a::context_region.o
}
ObjectFile libstacktrace.a::ppc_os.o {
	NAME Object file ppc_os.o from archive libstacktrace.a
	EXPORTS ArchContextCreate RtiTools_ContextTopDiscover ST_TraceFunctionEntry ST_CheckOSFrames ST_GetIntContextTop
	IMPORTS .TOC. taskTcb vxTaskEntry intContext vmLibInfo intVecBaseGet intEnt
	DECLARES 
	USES 
}
Module ppc_os.o {
	OBJECT += libstacktrace.a::ppc_os.o
}
ObjectFile libstacktrace.a::ppc_crawl.o {
	NAME Object file ppc_crawl.o from archive libstacktrace.a
	EXPORTS ST_FrameCrawl
	IMPORTS .TOC. stCtxMemValidate
	DECLARES 
	USES 
}
Module ppc_crawl.o {
	OBJECT += libstacktrace.a::ppc_crawl.o
}
ObjectFile libstacktrace.a::memory_map_vx.o {
	NAME Object file memory_map_vx.o from archive libstacktrace.a
	EXPORTS memory_map_lock_take map_lock memory_map_lock_give memory_map_kernel_node_get ST_pidFind memory_map_free_map memory_map_pid_add memory_map_pid_free map_region_find _func_ST_memory_map_region_rtp_find ST_memory_map_show _func_ST_memory_map_rtp_show memory_map_init _func_ST_memory_map_module_init memory_map_uninit _func_ST_memory_map_module_uninit
	IMPORTS .TOC. spinLockIsrTake spinLockIsrGive free printf malloc kernelIdGet logMsg
	DECLARES 
	USES 
}
Module memory_map_vx.o {
	OBJECT += libstacktrace.a::memory_map_vx.o
}
ObjectFile libstacktrace.a::memory_map_module_vx.o {
	NAME Object file memory_map_module_vx.o from archive libstacktrace.a
	EXPORTS _func_ST_sdCreateHookAdd _func_ST_sdDeleteHookAdd _func_ST_sdCreateHookDelete _func_ST_sdDeleteHookDelete stacktraceModuleHooksInit stacktraceRtpHooksInit
	IMPORTS .TOC. free strlen strrchr logMsg malloc objNameGet snprintf memory_map_lock_take memory_map_lock_give memory_map_pid_free _func_rtpIdVerify memory_map_pid_add kernelIdGet _func_rtpShlInfoGet ST_pidFind printf _func_moduleSegInfoGet calloc memory_map_kernel_node_get _func_kernelModuleListIdGet semTake semGive moduleNameGet moduleLoadHookAdd moduleUnloadHookAdd objEach _func_rtpInitCompleteHookAdd _func_rtpDeleteHookAdd _func_rtpShlOpenHook _func_rtpShlCloseHook _func_rtpDeleteHookDelete _func_rtpInitCompleteHookDelete memory_map_free_map moduleUnloadHookDelete moduleLoadHookDelete _func_ST_memory_map_module_init _func_ST_memory_map_module_uninit _func_ST_memory_map_region_rtp_find _func_ST_memory_map_rtp_show
	DECLARES 
	USES 
}
Module memory_map_module_vx.o {
	OBJECT += libstacktrace.a::memory_map_module_vx.o
}
ObjectFile libstacktrace.a::memory_map_shd_vx.o {
	NAME Object file memory_map_shd_vx.o from archive libstacktrace.a
	EXPORTS stacktraceShdHooksInit
	IMPORTS .TOC. sdCreateHookAdd _func_ST_sdCreateHookAdd sdCreateHookDelete sdDeleteHookAdd sdDeleteHookDelete _func_ST_sdCreateHookDelete _func_ST_sdDeleteHookAdd _func_ST_sdDeleteHookDelete
	DECLARES 
	USES 
}
Module memory_map_shd_vx.o {
	OBJECT += libstacktrace.a::memory_map_shd_vx.o
}
Library libstacktrace.a {
	MODULES libstacktrace.a::context_memtest.o libstacktrace.a::context.o libstacktrace.a::context_region.o libstacktrace.a::ppc_os.o libstacktrace.a::ppc_crawl.o libstacktrace.a::memory_map_vx.o libstacktrace.a::memory_map_module_vx.o libstacktrace.a::memory_map_shd_vx.o
}
