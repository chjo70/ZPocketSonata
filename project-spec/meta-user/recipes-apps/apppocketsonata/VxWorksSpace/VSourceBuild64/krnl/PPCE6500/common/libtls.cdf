Symbol absSymbols_Tls {
}
Symbol .TOC. {
}
Symbol tlsLibInit {
}
Symbol memset {
}
Symbol __tlsTaskCreateHook {
}
Symbol taskCreateHookAdd {
}
Symbol __tlsTaskDeleteHook {
}
Symbol taskDeleteHookAdd {
}
Symbol _func_logMsg {
}
Symbol tlsModuleAdd {
}
Symbol __tlsLockIsInitialized {
}
Symbol __tlsLockSem {
}
Symbol semMInit {
}
Symbol semTake {
}
Symbol __tlsMaxModule {
}
Symbol __ppTlsModule {
}
Symbol realloc {
}
Symbol malloc {
}
Symbol semGive {
}
Symbol tlsModuleRemove {
}
Symbol free {
}
Symbol tlsTaskInit {
}
Symbol taskIdSelf {
}
Symbol tlsTaskModuleAdd {
}
Symbol _vx_offset_TLS_MODULE_DESC_valid {
}
Symbol _vx_offset_TLS_MODULE_DESC_refCnt {
}
Symbol _vx_offset_TLS_MODULE_DESC_addr {
}
Symbol _vx_offset_TLS_MODULE_DESC_alignment {
}
Symbol _vx_offset_TLS_MODULE_DESC_size {
}
Symbol _vx_offset_TLS_MODULE_DESC_moduleId {
}
Symbol _vx_offset_TLS_TASK_MODULE_DESC_pTlsModule {
}
Symbol _vx_offset_TLS_TASK_MODULE_DESC_addr {
}
Symbol _vx_offset_sizeof_TLS_TASK_MODULE_DESC {
}
Symbol _vx_offset_TLS_VAR_offset {
}
Symbol _vx_offset_TLS_VAR_module_id {
}
Symbol _vx_offset_TLS_VAR_size {
}
Symbol __pStaticModTlsDesc {
}
Symbol tlsByTaskLookup {
}
Symbol tlsTaskModuleRemove {
}
Symbol memalign {
}
Symbol memcpy {
}
Symbol __tls_lookup {
}
Symbol _sigCtxSave {
}
Symbol edrErrorInjectStub {
}
Symbol edrKernelFatalPolicyHandler {
}
Symbol taskStackAllot {
}
ObjectFile libtls.a::tlsLib.o {
	NAME Object file tlsLib.o from archive libtls.a
	EXPORTS absSymbols_Tls tlsLibInit tlsModuleAdd __tlsMaxModule __ppTlsModule tlsModuleRemove tlsTaskInit _vx_offset_TLS_MODULE_DESC_valid _vx_offset_TLS_MODULE_DESC_refCnt _vx_offset_TLS_MODULE_DESC_addr _vx_offset_TLS_MODULE_DESC_alignment _vx_offset_TLS_MODULE_DESC_size _vx_offset_TLS_MODULE_DESC_moduleId _vx_offset_TLS_TASK_MODULE_DESC_pTlsModule _vx_offset_TLS_TASK_MODULE_DESC_addr _vx_offset_sizeof_TLS_TASK_MODULE_DESC _vx_offset_TLS_VAR_offset _vx_offset_TLS_VAR_module_id _vx_offset_TLS_VAR_size __pStaticModTlsDesc
	IMPORTS .TOC. memset __tlsTaskCreateHook taskCreateHookAdd __tlsTaskDeleteHook taskDeleteHookAdd _func_logMsg __tlsLockIsInitialized __tlsLockSem semMInit semTake realloc malloc semGive free taskIdSelf tlsTaskModuleAdd
	DECLARES 
	USES 
}
Module tlsLib.o {
	OBJECT += libtls.a::tlsLib.o
}
ObjectFile libtls.a::tlsLookupLib.o {
	NAME Object file tlsLookupLib.o from archive libtls.a
	EXPORTS tlsByTaskLookup tlsTaskModuleRemove __tlsLockIsInitialized tlsTaskModuleAdd __tls_lookup __tlsTaskCreateHook __tlsTaskDeleteHook
	IMPORTS .TOC. free semTake semGive __tlsMaxModule realloc memset semMInit __ppTlsModule memalign memcpy taskIdSelf _sigCtxSave edrErrorInjectStub edrKernelFatalPolicyHandler taskStackAllot __pStaticModTlsDesc
	DECLARES __tlsLockSem
	USES 
}
Module tlsLookupLib.o {
	OBJECT += libtls.a::tlsLookupLib.o
}
Library libtls.a {
	MODULES libtls.a::tlsLib.o libtls.a::tlsLookupLib.o
}
Symbol absSymbols_Tls {
}
Symbol .TOC. {
}
Symbol tlsLibInit {
}
Symbol memset {
}
Symbol __tlsTaskCreateHook {
}
Symbol taskCreateHookAdd {
}
Symbol __tlsTaskDeleteHook {
}
Symbol taskDeleteHookAdd {
}
Symbol _func_logMsg {
}
Symbol tlsModuleAdd {
}
Symbol __tlsLockIsInitialized {
}
Symbol __tlsLockSem {
}
Symbol semMInit {
}
Symbol semTake {
}
Symbol __tlsMaxModule {
}
Symbol __ppTlsModule {
}
Symbol realloc {
}
Symbol malloc {
}
Symbol semGive {
}
Symbol tlsModuleRemove {
}
Symbol free {
}
Symbol tlsTaskInit {
}
Symbol taskIdSelf {
}
Symbol tlsTaskModuleAdd {
}
Symbol _vx_offset_TLS_MODULE_DESC_valid {
}
Symbol _vx_offset_TLS_MODULE_DESC_refCnt {
}
Symbol _vx_offset_TLS_MODULE_DESC_addr {
}
Symbol _vx_offset_TLS_MODULE_DESC_alignment {
}
Symbol _vx_offset_TLS_MODULE_DESC_size {
}
Symbol _vx_offset_TLS_MODULE_DESC_moduleId {
}
Symbol _vx_offset_TLS_TASK_MODULE_DESC_pTlsModule {
}
Symbol _vx_offset_TLS_TASK_MODULE_DESC_addr {
}
Symbol _vx_offset_sizeof_TLS_TASK_MODULE_DESC {
}
Symbol _vx_offset_TLS_VAR_offset {
}
Symbol _vx_offset_TLS_VAR_module_id {
}
Symbol _vx_offset_TLS_VAR_size {
}
Symbol __pStaticModTlsDesc {
}
Symbol tlsByTaskLookup {
}
Symbol tlsTaskModuleRemove {
}
Symbol memalign {
}
Symbol memcpy {
}
Symbol __tls_lookup {
}
Symbol _sigCtxSave {
}
Symbol edrErrorInjectStub {
}
Symbol edrKernelFatalPolicyHandler {
}
Symbol taskStackAllot {
}
ObjectFile libtls.a::tlsLib.o {
	NAME Object file tlsLib.o from archive libtls.a
	EXPORTS absSymbols_Tls tlsLibInit tlsModuleAdd __tlsMaxModule __ppTlsModule tlsModuleRemove tlsTaskInit _vx_offset_TLS_MODULE_DESC_valid _vx_offset_TLS_MODULE_DESC_refCnt _vx_offset_TLS_MODULE_DESC_addr _vx_offset_TLS_MODULE_DESC_alignment _vx_offset_TLS_MODULE_DESC_size _vx_offset_TLS_MODULE_DESC_moduleId _vx_offset_TLS_TASK_MODULE_DESC_pTlsModule _vx_offset_TLS_TASK_MODULE_DESC_addr _vx_offset_sizeof_TLS_TASK_MODULE_DESC _vx_offset_TLS_VAR_offset _vx_offset_TLS_VAR_module_id _vx_offset_TLS_VAR_size __pStaticModTlsDesc
	IMPORTS .TOC. memset __tlsTaskCreateHook taskCreateHookAdd __tlsTaskDeleteHook taskDeleteHookAdd _func_logMsg __tlsLockIsInitialized __tlsLockSem semMInit semTake realloc malloc semGive free taskIdSelf tlsTaskModuleAdd
	DECLARES 
	USES 
}
Module tlsLib.o {
	OBJECT += libtls.a::tlsLib.o
}
ObjectFile libtls.a::tlsLookupLib.o {
	NAME Object file tlsLookupLib.o from archive libtls.a
	EXPORTS tlsByTaskLookup tlsTaskModuleRemove __tlsLockIsInitialized tlsTaskModuleAdd __tls_lookup __tlsTaskCreateHook __tlsTaskDeleteHook
	IMPORTS .TOC. free semTake semGive __tlsMaxModule realloc memset semMInit __ppTlsModule memalign memcpy taskIdSelf _sigCtxSave edrErrorInjectStub edrKernelFatalPolicyHandler taskStackAllot __pStaticModTlsDesc
	DECLARES __tlsLockSem
	USES 
}
Module tlsLookupLib.o {
	OBJECT += libtls.a::tlsLookupLib.o
}
Library libtls.a {
	MODULES libtls.a::tlsLib.o libtls.a::tlsLookupLib.o
}
Symbol absSymbols_Tls {
}
Symbol .TOC. {
}
Symbol tlsLibInit {
}
Symbol memset {
}
Symbol __tlsTaskCreateHook {
}
Symbol taskCreateHookAdd {
}
Symbol __tlsTaskDeleteHook {
}
Symbol taskDeleteHookAdd {
}
Symbol _func_logMsg {
}
Symbol tlsModuleAdd {
}
Symbol __tlsLockIsInitialized {
}
Symbol __tlsLockSem {
}
Symbol semMInit {
}
Symbol semTake {
}
Symbol __tlsMaxModule {
}
Symbol __ppTlsModule {
}
Symbol realloc {
}
Symbol malloc {
}
Symbol semGive {
}
Symbol tlsModuleRemove {
}
Symbol free {
}
Symbol tlsTaskInit {
}
Symbol taskIdSelf {
}
Symbol tlsTaskModuleAdd {
}
Symbol _vx_offset_TLS_MODULE_DESC_valid {
}
Symbol _vx_offset_TLS_MODULE_DESC_refCnt {
}
Symbol _vx_offset_TLS_MODULE_DESC_addr {
}
Symbol _vx_offset_TLS_MODULE_DESC_alignment {
}
Symbol _vx_offset_TLS_MODULE_DESC_size {
}
Symbol _vx_offset_TLS_MODULE_DESC_moduleId {
}
Symbol _vx_offset_TLS_TASK_MODULE_DESC_pTlsModule {
}
Symbol _vx_offset_TLS_TASK_MODULE_DESC_addr {
}
Symbol _vx_offset_sizeof_TLS_TASK_MODULE_DESC {
}
Symbol _vx_offset_TLS_VAR_offset {
}
Symbol _vx_offset_TLS_VAR_module_id {
}
Symbol _vx_offset_TLS_VAR_size {
}
Symbol __pStaticModTlsDesc {
}
Symbol tlsByTaskLookup {
}
Symbol tlsTaskModuleRemove {
}
Symbol memalign {
}
Symbol memcpy {
}
Symbol __tls_lookup {
}
Symbol _sigCtxSave {
}
Symbol edrErrorInjectStub {
}
Symbol edrKernelFatalPolicyHandler {
}
Symbol taskStackAllot {
}
ObjectFile libtls.a::tlsLib.o {
	NAME Object file tlsLib.o from archive libtls.a
	EXPORTS absSymbols_Tls tlsLibInit tlsModuleAdd __tlsMaxModule __ppTlsModule tlsModuleRemove tlsTaskInit _vx_offset_TLS_MODULE_DESC_valid _vx_offset_TLS_MODULE_DESC_refCnt _vx_offset_TLS_MODULE_DESC_addr _vx_offset_TLS_MODULE_DESC_alignment _vx_offset_TLS_MODULE_DESC_size _vx_offset_TLS_MODULE_DESC_moduleId _vx_offset_TLS_TASK_MODULE_DESC_pTlsModule _vx_offset_TLS_TASK_MODULE_DESC_addr _vx_offset_sizeof_TLS_TASK_MODULE_DESC _vx_offset_TLS_VAR_offset _vx_offset_TLS_VAR_module_id _vx_offset_TLS_VAR_size __pStaticModTlsDesc
	IMPORTS .TOC. memset __tlsTaskCreateHook taskCreateHookAdd __tlsTaskDeleteHook taskDeleteHookAdd _func_logMsg __tlsLockIsInitialized __tlsLockSem semMInit semTake realloc malloc semGive free taskIdSelf tlsTaskModuleAdd
	DECLARES 
	USES 
}
Module tlsLib.o {
	OBJECT += libtls.a::tlsLib.o
}
ObjectFile libtls.a::tlsLookupLib.o {
	NAME Object file tlsLookupLib.o from archive libtls.a
	EXPORTS tlsByTaskLookup tlsTaskModuleRemove __tlsLockIsInitialized tlsTaskModuleAdd __tls_lookup __tlsTaskCreateHook __tlsTaskDeleteHook
	IMPORTS .TOC. free semTake semGive __tlsMaxModule realloc memset semMInit __ppTlsModule memalign memcpy taskIdSelf _sigCtxSave edrErrorInjectStub edrKernelFatalPolicyHandler taskStackAllot __pStaticModTlsDesc
	DECLARES __tlsLockSem
	USES 
}
Module tlsLookupLib.o {
	OBJECT += libtls.a::tlsLookupLib.o
}
Library libtls.a {
	MODULES libtls.a::tlsLib.o libtls.a::tlsLookupLib.o
}
