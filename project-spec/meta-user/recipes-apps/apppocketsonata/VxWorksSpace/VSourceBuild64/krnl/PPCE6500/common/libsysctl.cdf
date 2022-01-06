Symbol sysctlInit {
}
Symbol .TOC. {
}
Symbol pSysctlCtxList {
}
Symbol sysctl__children {
}
Symbol sysctl_node {
}
Symbol sysctl_add_oid_internal {
}
Symbol kern_node {
}
Symbol hw_node {
}
Symbol vm_node {
}
Symbol usr_ext_node {
}
Symbol kernSysctlInit {
}
Symbol sysctlCtxList {
}
Symbol strcmp {
}
Symbol sysctl_register_oid {
}
Symbol printf {
}
Symbol errnoSet {
}
Symbol sysctl_ctx_entry_add {
}
Symbol memSysPartId {
}
Symbol memPartAlloc {
}
Symbol bzero {
}
Symbol strlen {
}
Symbol bcopy {
}
Symbol memPartFree {
}
Symbol oidsInList {
}
Symbol vxAtomic32Inc {
}
Symbol semRWLibMaxReaders {
}
Symbol mibMutex {
}
Symbol semRWCreate {
}
Symbol __errno {
}
Symbol snprintf {
}
Symbol edrErrorInjectStub {
}
Symbol taskIdSelf {
}
Symbol edrKernelFatalPolicyHandler {
}
Symbol name_node {
}
Symbol next_node {
}
Symbol oidfmt_node {
}
Symbol ipc_node {
}
Symbol sysctl_unregister_oid {
}
Symbol sysctl_ctx_init {
}
Symbol sysctl_remove_oid {
}
Symbol semWTake {
}
Symbol semGive {
}
Symbol vxAtomic32Dec {
}
Symbol sysctl_ctx_free {
}
Symbol sysctl_ctx_entry_find {
}
Symbol sysctl_add_oid {
}
Symbol sysctl_sysctl_debug_dump_node {
}
Symbol semRTake {
}
Symbol malloc {
}
Symbol free {
}
Symbol sysctl_find_oid {
}
Symbol sysctl_handle_int {
}
Symbol sysctl_handle_long {
}
Symbol sysctl_handle_string {
}
Symbol sysctl_handle_opaque {
}
Symbol sysctl_handle_reg {
}
Symbol kernel_sysctl {
}
Symbol sysctl {
}
Symbol sysctlbyname {
}
Symbol strlcpy {
}
Symbol sysctlnametomib {
}
Symbol _netSysctlCli {
}
Symbol _netSysctl {
}
Symbol sysctlLibInit {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol memcpy {
}
Symbol errnoGet {
}
Symbol strcpy {
}
Symbol __stdout {
}
Symbol fwrite {
}
Symbol __swbuf {
}
Symbol strchr {
}
Symbol __ctype {
}
Symbol strtol {
}
Symbol strtoul {
}
Symbol sscanf {
}
Symbol logMsg {
}
Symbol setbuf {
}
Symbol getoptInit {
}
Symbol getopt_r {
}
Symbol strncmp {
}
Symbol strcat {
}
Symbol Sysctl {
}
Symbol getOptServ {
}
Symbol sysctlScLibInit {
}
Symbol sysctlSc {
}
Symbol scMemValidate {
}
Symbol tickGet {
}
Symbol sysClkRateGet {
}
Symbol sysProcNumGet {
}
Symbol tick64Get {
}
Symbol rtpSysctlSyscall {
}
Symbol syscallGroupTbl {
}
Symbol syscallGroupName {
}
Symbol vxCpuConfiguredGet {
}
Symbol vxCpuEnabledGet {
}
Symbol _func_shlGottSet {
}
Symbol rtpSysctlRegister {
}
Symbol vxWorksVersionMajor {
}
Symbol vxWorksVersionMinor {
}
Symbol vxWorksVersionMaint {
}
Symbol strncpy {
}
Symbol kernelVersion {
}
Symbol creationDate {
}
Symbol sysModel {
}
Symbol bsp_node {
}
Symbol sysBspRev {
}
Symbol syscall_node {
}
ObjectFile libsysctl.a::kern_mib.o {
	NAME Object file kern_mib.o from archive libsysctl.a
	EXPORTS sysctlInit pSysctlCtxList sysctl_node kern_node hw_node vm_node usr_ext_node
	IMPORTS .TOC. sysctl__children sysctl_add_oid_internal kernSysctlInit
	DECLARES sysctlCtxList
	USES 
}
Module kern_mib.o {
	OBJECT += libsysctl.a::kern_mib.o
}
ObjectFile libsysctl.a::kern_sysctl.o {
	NAME Object file kern_sysctl.o from archive libsysctl.a
	EXPORTS sysctl_register_oid sysctl_ctx_entry_add sysctl_add_oid_internal oidsInList kernSysctlInit name_node next_node oidfmt_node ipc_node sysctl_unregister_oid sysctl_ctx_init sysctl_remove_oid sysctl_ctx_free sysctl_ctx_entry_find sysctl_add_oid sysctl_sysctl_debug_dump_node sysctl_find_oid sysctl_handle_int sysctl_handle_long sysctl_handle_string sysctl_handle_opaque sysctl_handle_reg kernel_sysctl sysctl sysctlbyname sysctlnametomib
	IMPORTS .TOC. strcmp printf errnoSet memSysPartId memPartAlloc bzero strlen bcopy memPartFree vxAtomic32Inc semRWLibMaxReaders semRWCreate __errno snprintf edrErrorInjectStub taskIdSelf edrKernelFatalPolicyHandler sysctl_node pSysctlCtxList kern_node semWTake semGive vxAtomic32Dec semRTake malloc free strlcpy
	DECLARES mibMutex sysctl__children
	USES 
}
Module kern_sysctl.o {
	OBJECT += libsysctl.a::kern_sysctl.o
}
ObjectFile libsysctl.a::sysctlFuncBind.o {
	NAME Object file sysctlFuncBind.o from archive libsysctl.a
	EXPORTS 
	IMPORTS 
	DECLARES _netSysctlCli _netSysctl
	USES 
}
Module sysctlFuncBind.o {
	OBJECT += libsysctl.a::sysctlFuncBind.o
}
ObjectFile libsysctl.a::sysctl.o {
	NAME Object file sysctl.o from archive libsysctl.a
	EXPORTS sysctlLibInit Sysctl
	IMPORTS .TOC. __stderr fprintf strlen sysctl memcpy printf errnoGet bcopy strcpy memSysPartId memPartAlloc __stdout fwrite memPartFree _netSysctlCli __swbuf snprintf strchr __ctype strtol strtoul sscanf logMsg setbuf getoptInit getopt_r strncmp strcat bzero getOptServ
	DECLARES 
	USES 
}
Module sysctl.o {
	OBJECT += libsysctl.a::sysctl.o
}
ObjectFile libsysctl.a::sysctlScLib.o {
	NAME Object file sysctlScLib.o from archive libsysctl.a
	EXPORTS sysctlScLibInit sysctlSc
	IMPORTS .TOC. scMemValidate errnoSet sysctl
	DECLARES 
	USES 
}
Module sysctlScLib.o {
	OBJECT += libsysctl.a::sysctlScLib.o
}
ObjectFile libsysctl.a::rtpSysctl.o {
	NAME Object file rtpSysctl.o from archive libsysctl.a
	EXPORTS rtpSysctlSyscall rtpSysctlRegister syscall_node
	IMPORTS .TOC. tickGet sysctl_handle_int sysClkRateGet sysProcNumGet tick64Get syscallGroupTbl syscallGroupName strlen sysctl_handle_string vxCpuConfiguredGet vxCpuEnabledGet semRWLibMaxReaders errnoGet pSysctlCtxList kern_node sysctl_add_oid_internal vxWorksVersionMajor vxWorksVersionMinor vxWorksVersionMaint snprintf strncpy kernelVersion creationDate sysModel bsp_node sysBspRev
	DECLARES _func_shlGottSet
	USES 
}
Module rtpSysctl.o {
	OBJECT += libsysctl.a::rtpSysctl.o
}
Library libsysctl.a {
	MODULES libsysctl.a::kern_mib.o libsysctl.a::kern_sysctl.o libsysctl.a::sysctlFuncBind.o libsysctl.a::sysctl.o libsysctl.a::sysctlScLib.o libsysctl.a::rtpSysctl.o
}
Symbol sysctlInit {
}
Symbol .TOC. {
}
Symbol pSysctlCtxList {
}
Symbol sysctl__children {
}
Symbol sysctl_node {
}
Symbol sysctl_add_oid_internal {
}
Symbol kern_node {
}
Symbol hw_node {
}
Symbol vm_node {
}
Symbol usr_ext_node {
}
Symbol kernSysctlInit {
}
Symbol sysctlCtxList {
}
Symbol strcmp {
}
Symbol sysctl_register_oid {
}
Symbol printf {
}
Symbol errnoSet {
}
Symbol sysctl_ctx_entry_add {
}
Symbol memSysPartId {
}
Symbol memPartAlloc {
}
Symbol bzero {
}
Symbol strlen {
}
Symbol bcopy {
}
Symbol memPartFree {
}
Symbol oidsInList {
}
Symbol vxAtomic32Inc {
}
Symbol semRWLibMaxReaders {
}
Symbol mibMutex {
}
Symbol semRWCreate {
}
Symbol __errno {
}
Symbol snprintf {
}
Symbol edrErrorInjectStub {
}
Symbol taskIdSelf {
}
Symbol edrKernelFatalPolicyHandler {
}
Symbol name_node {
}
Symbol next_node {
}
Symbol oidfmt_node {
}
Symbol ipc_node {
}
Symbol sysctl_unregister_oid {
}
Symbol sysctl_ctx_init {
}
Symbol sysctl_remove_oid {
}
Symbol semWTake {
}
Symbol semGive {
}
Symbol vxAtomic32Dec {
}
Symbol sysctl_ctx_free {
}
Symbol sysctl_ctx_entry_find {
}
Symbol sysctl_add_oid {
}
Symbol sysctl_sysctl_debug_dump_node {
}
Symbol semRTake {
}
Symbol malloc {
}
Symbol free {
}
Symbol sysctl_find_oid {
}
Symbol sysctl_handle_int {
}
Symbol sysctl_handle_long {
}
Symbol sysctl_handle_string {
}
Symbol sysctl_handle_opaque {
}
Symbol sysctl_handle_reg {
}
Symbol kernel_sysctl {
}
Symbol sysctl {
}
Symbol sysctlbyname {
}
Symbol strlcpy {
}
Symbol sysctlnametomib {
}
Symbol _netSysctlCli {
}
Symbol _netSysctl {
}
Symbol sysctlLibInit {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol memcpy {
}
Symbol errnoGet {
}
Symbol strcpy {
}
Symbol __stdout {
}
Symbol fwrite {
}
Symbol __swbuf {
}
Symbol strchr {
}
Symbol __ctype {
}
Symbol strtol {
}
Symbol strtoul {
}
Symbol sscanf {
}
Symbol logMsg {
}
Symbol setbuf {
}
Symbol getoptInit {
}
Symbol getopt_r {
}
Symbol strncmp {
}
Symbol strcat {
}
Symbol Sysctl {
}
Symbol getOptServ {
}
Symbol sysctlScLibInit {
}
Symbol sysctlSc {
}
Symbol scMemValidate {
}
Symbol tickGet {
}
Symbol sysClkRateGet {
}
Symbol sysProcNumGet {
}
Symbol tick64Get {
}
Symbol rtpSysctlSyscall {
}
Symbol syscallGroupTbl {
}
Symbol syscallGroupName {
}
Symbol vxCpuConfiguredGet {
}
Symbol vxCpuEnabledGet {
}
Symbol _func_shlGottSet {
}
Symbol rtpSysctlRegister {
}
Symbol vxWorksVersionMajor {
}
Symbol vxWorksVersionMinor {
}
Symbol vxWorksVersionMaint {
}
Symbol strncpy {
}
Symbol kernelVersion {
}
Symbol creationDate {
}
Symbol sysModel {
}
Symbol bsp_node {
}
Symbol sysBspRev {
}
Symbol syscall_node {
}
ObjectFile libsysctl.a::kern_mib.o {
	NAME Object file kern_mib.o from archive libsysctl.a
	EXPORTS sysctlInit pSysctlCtxList sysctl_node kern_node hw_node vm_node usr_ext_node
	IMPORTS .TOC. sysctl__children sysctl_add_oid_internal kernSysctlInit
	DECLARES sysctlCtxList
	USES 
}
Module kern_mib.o {
	OBJECT += libsysctl.a::kern_mib.o
}
ObjectFile libsysctl.a::kern_sysctl.o {
	NAME Object file kern_sysctl.o from archive libsysctl.a
	EXPORTS sysctl_register_oid sysctl_ctx_entry_add sysctl_add_oid_internal oidsInList kernSysctlInit name_node next_node oidfmt_node ipc_node sysctl_unregister_oid sysctl_ctx_init sysctl_remove_oid sysctl_ctx_free sysctl_ctx_entry_find sysctl_add_oid sysctl_sysctl_debug_dump_node sysctl_find_oid sysctl_handle_int sysctl_handle_long sysctl_handle_string sysctl_handle_opaque sysctl_handle_reg kernel_sysctl sysctl sysctlbyname sysctlnametomib
	IMPORTS .TOC. strcmp printf errnoSet memSysPartId memPartAlloc bzero strlen bcopy memPartFree vxAtomic32Inc semRWLibMaxReaders semRWCreate __errno snprintf edrErrorInjectStub taskIdSelf edrKernelFatalPolicyHandler sysctl_node pSysctlCtxList kern_node semWTake semGive vxAtomic32Dec semRTake malloc free strlcpy
	DECLARES mibMutex sysctl__children
	USES 
}
Module kern_sysctl.o {
	OBJECT += libsysctl.a::kern_sysctl.o
}
ObjectFile libsysctl.a::sysctlFuncBind.o {
	NAME Object file sysctlFuncBind.o from archive libsysctl.a
	EXPORTS 
	IMPORTS 
	DECLARES _netSysctlCli _netSysctl
	USES 
}
Module sysctlFuncBind.o {
	OBJECT += libsysctl.a::sysctlFuncBind.o
}
ObjectFile libsysctl.a::sysctl.o {
	NAME Object file sysctl.o from archive libsysctl.a
	EXPORTS sysctlLibInit Sysctl
	IMPORTS .TOC. __stderr fprintf strlen sysctl memcpy printf errnoGet bcopy strcpy memSysPartId memPartAlloc __stdout fwrite memPartFree _netSysctlCli __swbuf snprintf strchr __ctype strtol strtoul sscanf logMsg setbuf getoptInit getopt_r strncmp strcat bzero getOptServ
	DECLARES 
	USES 
}
Module sysctl.o {
	OBJECT += libsysctl.a::sysctl.o
}
ObjectFile libsysctl.a::sysctlScLib.o {
	NAME Object file sysctlScLib.o from archive libsysctl.a
	EXPORTS sysctlScLibInit sysctlSc
	IMPORTS .TOC. scMemValidate errnoSet sysctl
	DECLARES 
	USES 
}
Module sysctlScLib.o {
	OBJECT += libsysctl.a::sysctlScLib.o
}
ObjectFile libsysctl.a::rtpSysctl.o {
	NAME Object file rtpSysctl.o from archive libsysctl.a
	EXPORTS rtpSysctlSyscall rtpSysctlRegister syscall_node
	IMPORTS .TOC. tickGet sysctl_handle_int sysClkRateGet sysProcNumGet tick64Get syscallGroupTbl syscallGroupName strlen sysctl_handle_string vxCpuConfiguredGet vxCpuEnabledGet semRWLibMaxReaders errnoGet pSysctlCtxList kern_node sysctl_add_oid_internal vxWorksVersionMajor vxWorksVersionMinor vxWorksVersionMaint snprintf strncpy kernelVersion creationDate sysModel bsp_node sysBspRev
	DECLARES _func_shlGottSet
	USES 
}
Module rtpSysctl.o {
	OBJECT += libsysctl.a::rtpSysctl.o
}
Library libsysctl.a {
	MODULES libsysctl.a::kern_mib.o libsysctl.a::kern_sysctl.o libsysctl.a::sysctlFuncBind.o libsysctl.a::sysctl.o libsysctl.a::sysctlScLib.o libsysctl.a::rtpSysctl.o
}
Symbol sysctlInit {
}
Symbol .TOC. {
}
Symbol pSysctlCtxList {
}
Symbol sysctl__children {
}
Symbol sysctl_node {
}
Symbol sysctl_add_oid_internal {
}
Symbol kern_node {
}
Symbol hw_node {
}
Symbol vm_node {
}
Symbol usr_ext_node {
}
Symbol kernSysctlInit {
}
Symbol sysctlCtxList {
}
Symbol strcmp {
}
Symbol sysctl_register_oid {
}
Symbol printf {
}
Symbol errnoSet {
}
Symbol sysctl_ctx_entry_add {
}
Symbol memSysPartId {
}
Symbol memPartAlloc {
}
Symbol bzero {
}
Symbol strlen {
}
Symbol bcopy {
}
Symbol memPartFree {
}
Symbol oidsInList {
}
Symbol vxAtomic32Inc {
}
Symbol semRWLibMaxReaders {
}
Symbol mibMutex {
}
Symbol semRWCreate {
}
Symbol __errno {
}
Symbol snprintf {
}
Symbol edrErrorInjectStub {
}
Symbol taskIdSelf {
}
Symbol edrKernelFatalPolicyHandler {
}
Symbol name_node {
}
Symbol next_node {
}
Symbol oidfmt_node {
}
Symbol ipc_node {
}
Symbol sysctl_unregister_oid {
}
Symbol sysctl_ctx_init {
}
Symbol sysctl_remove_oid {
}
Symbol semWTake {
}
Symbol semGive {
}
Symbol vxAtomic32Dec {
}
Symbol sysctl_ctx_free {
}
Symbol sysctl_ctx_entry_find {
}
Symbol sysctl_add_oid {
}
Symbol sysctl_sysctl_debug_dump_node {
}
Symbol semRTake {
}
Symbol malloc {
}
Symbol free {
}
Symbol sysctl_find_oid {
}
Symbol sysctl_handle_int {
}
Symbol sysctl_handle_long {
}
Symbol sysctl_handle_string {
}
Symbol sysctl_handle_opaque {
}
Symbol sysctl_handle_reg {
}
Symbol kernel_sysctl {
}
Symbol sysctl {
}
Symbol sysctlbyname {
}
Symbol strlcpy {
}
Symbol sysctlnametomib {
}
Symbol _netSysctlCli {
}
Symbol _netSysctl {
}
Symbol sysctlLibInit {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol memcpy {
}
Symbol errnoGet {
}
Symbol strcpy {
}
Symbol __stdout {
}
Symbol fwrite {
}
Symbol __swbuf {
}
Symbol strchr {
}
Symbol __ctype {
}
Symbol strtol {
}
Symbol strtoul {
}
Symbol sscanf {
}
Symbol logMsg {
}
Symbol setbuf {
}
Symbol getoptInit {
}
Symbol getopt_r {
}
Symbol strncmp {
}
Symbol strcat {
}
Symbol Sysctl {
}
Symbol getOptServ {
}
Symbol sysctlScLibInit {
}
Symbol sysctlSc {
}
Symbol scMemValidate {
}
Symbol tickGet {
}
Symbol sysClkRateGet {
}
Symbol sysProcNumGet {
}
Symbol tick64Get {
}
Symbol rtpSysctlSyscall {
}
Symbol syscallGroupTbl {
}
Symbol syscallGroupName {
}
Symbol vxCpuConfiguredGet {
}
Symbol vxCpuEnabledGet {
}
Symbol _func_shlGottSet {
}
Symbol rtpSysctlRegister {
}
Symbol vxWorksVersionMajor {
}
Symbol vxWorksVersionMinor {
}
Symbol vxWorksVersionMaint {
}
Symbol strncpy {
}
Symbol kernelVersion {
}
Symbol creationDate {
}
Symbol sysModel {
}
Symbol bsp_node {
}
Symbol sysBspRev {
}
Symbol syscall_node {
}
ObjectFile libsysctl.a::kern_mib.o {
	NAME Object file kern_mib.o from archive libsysctl.a
	EXPORTS sysctlInit pSysctlCtxList sysctl_node kern_node hw_node vm_node usr_ext_node
	IMPORTS .TOC. sysctl__children sysctl_add_oid_internal kernSysctlInit
	DECLARES sysctlCtxList
	USES 
}
Module kern_mib.o {
	OBJECT += libsysctl.a::kern_mib.o
}
ObjectFile libsysctl.a::kern_sysctl.o {
	NAME Object file kern_sysctl.o from archive libsysctl.a
	EXPORTS sysctl_register_oid sysctl_ctx_entry_add sysctl_add_oid_internal oidsInList kernSysctlInit name_node next_node oidfmt_node ipc_node sysctl_unregister_oid sysctl_ctx_init sysctl_remove_oid sysctl_ctx_free sysctl_ctx_entry_find sysctl_add_oid sysctl_sysctl_debug_dump_node sysctl_find_oid sysctl_handle_int sysctl_handle_long sysctl_handle_string sysctl_handle_opaque sysctl_handle_reg kernel_sysctl sysctl sysctlbyname sysctlnametomib
	IMPORTS .TOC. strcmp printf errnoSet memSysPartId memPartAlloc bzero strlen bcopy memPartFree vxAtomic32Inc semRWLibMaxReaders semRWCreate __errno snprintf edrErrorInjectStub taskIdSelf edrKernelFatalPolicyHandler sysctl_node pSysctlCtxList kern_node semWTake semGive vxAtomic32Dec semRTake malloc free strlcpy
	DECLARES mibMutex sysctl__children
	USES 
}
Module kern_sysctl.o {
	OBJECT += libsysctl.a::kern_sysctl.o
}
ObjectFile libsysctl.a::sysctlFuncBind.o {
	NAME Object file sysctlFuncBind.o from archive libsysctl.a
	EXPORTS 
	IMPORTS 
	DECLARES _netSysctlCli _netSysctl
	USES 
}
Module sysctlFuncBind.o {
	OBJECT += libsysctl.a::sysctlFuncBind.o
}
ObjectFile libsysctl.a::sysctl.o {
	NAME Object file sysctl.o from archive libsysctl.a
	EXPORTS sysctlLibInit Sysctl
	IMPORTS .TOC. __stderr fprintf strlen sysctl memcpy printf errnoGet bcopy strcpy memSysPartId memPartAlloc __stdout fwrite memPartFree _netSysctlCli __swbuf snprintf strchr __ctype strtol strtoul sscanf logMsg setbuf getoptInit getopt_r strncmp strcat bzero getOptServ
	DECLARES 
	USES 
}
Module sysctl.o {
	OBJECT += libsysctl.a::sysctl.o
}
ObjectFile libsysctl.a::sysctlScLib.o {
	NAME Object file sysctlScLib.o from archive libsysctl.a
	EXPORTS sysctlScLibInit sysctlSc
	IMPORTS .TOC. scMemValidate errnoSet sysctl
	DECLARES 
	USES 
}
Module sysctlScLib.o {
	OBJECT += libsysctl.a::sysctlScLib.o
}
ObjectFile libsysctl.a::rtpSysctl.o {
	NAME Object file rtpSysctl.o from archive libsysctl.a
	EXPORTS rtpSysctlSyscall rtpSysctlRegister syscall_node
	IMPORTS .TOC. tickGet sysctl_handle_int sysClkRateGet sysProcNumGet tick64Get syscallGroupTbl syscallGroupName strlen sysctl_handle_string vxCpuConfiguredGet vxCpuEnabledGet semRWLibMaxReaders errnoGet pSysctlCtxList kern_node sysctl_add_oid_internal vxWorksVersionMajor vxWorksVersionMinor vxWorksVersionMaint snprintf strncpy kernelVersion creationDate sysModel bsp_node sysBspRev
	DECLARES _func_shlGottSet
	USES 
}
Module rtpSysctl.o {
	OBJECT += libsysctl.a::rtpSysctl.o
}
Library libsysctl.a {
	MODULES libsysctl.a::kern_mib.o libsysctl.a::kern_sysctl.o libsysctl.a::sysctlFuncBind.o libsysctl.a::sysctl.o libsysctl.a::sysctlScLib.o libsysctl.a::rtpSysctl.o
}
