Symbol fsMonitorInit {
}
Symbol .TOC. {
}
Symbol semMCreate {
}
Symbol xbdEventCategory {
}
Symbol xbdEventPrimaryInsert {
}
Symbol erfHandlerRegister {
}
Symbol xbdEventSecondaryInsert {
}
Symbol xbdEventSoftInsert {
}
Symbol fsmInitialized {
}
Symbol fsmUnmountHookAdd {
}
Symbol _func_fsmUnmountHookAddRtn {
}
Symbol semTake {
}
Symbol semGive {
}
Symbol strncpy {
}
Symbol fsmNameMap {
}
Symbol strncmp {
}
Symbol memset {
}
Symbol devName {
}
Symbol xbdPartitionDevCreate {
}
Symbol _func_rawFsDevInitRtn {
}
Symbol printf {
}
Symbol fsmProbeInstall {
}
Symbol memSysPartId {
}
Symbol memPartAlloc {
}
Symbol fsmProbeUninstall {
}
Symbol memPartFree {
}
Symbol __errno {
}
Symbol strlen {
}
Symbol fsmNameInstall {
}
Symbol errnoSet {
}
Symbol fsmNameUninstall {
}
Symbol fsmGetDriver {
}
Symbol strstr {
}
Symbol partitionExist {
}
Symbol fsmGetVolume {
}
Symbol hookAddToTail {
}
Symbol fsmUnmountHookDelete {
}
Symbol hookDelete {
}
Symbol fsmUnmountHookRun {
}
Symbol fsEventUtilLibInit {
}
Symbol erfCategoryAllocate {
}
Symbol erfTypeAllocate {
}
Symbol strcmp {
}
Symbol erfHandlerUnregister {
}
Symbol fsPathAddedEventSetup {
}
Symbol semBCreate {
}
Symbol semDelete {
}
Symbol fsPathAddedEventRaise {
}
Symbol erfEventRaise {
}
Symbol fsWaitForPath {
}
Symbol fsPathAddEventHandler {
}
Symbol partLibCreate {
}
Symbol ioctl {
}
Symbol malloc {
}
Symbol printErr {
}
Symbol bzero {
}
Symbol write {
}
Symbol lseek {
}
Symbol read {
}
Symbol free {
}
Symbol xbdCreatePartition {
}
Symbol open {
}
Symbol close {
}
Symbol snprintf {
}
Symbol partLibCreateSz {
}
Symbol xbdCreatePartitionSz {
}
Symbol partLibCreateEx {
}
Symbol xbdCreatePartitionEx {
}
Symbol xbdPartitionFun {
}
Symbol xbdBlkDevLibInit {
}
Symbol xbdBlkDevServTskStkSz {
}
Symbol xbdBlkDevServTskPri {
}
Symbol xbdBlkDevCreate {
}
Symbol xbdEventInstantiated {
}
Symbol taskSpawn {
}
Symbol xbdAttach {
}
Symbol bio_done {
}
Symbol taskPrioritySet {
}
Symbol xbdEventMediaChanged {
}
Symbol xbdDetach {
}
Symbol devUnmap {
}
Symbol xbdEventRemove {
}
Symbol xbdBlkDevDelete {
}
Symbol devMap {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol xbdBlkDevCreateSync {
}
Symbol strncat {
}
Symbol gptCreatePartDev {
}
Symbol xbdMapGet {
}
Symbol lstFirst {
}
Symbol xpFuncs {
}
Symbol lstNext {
}
Symbol xbdGptPartDevCreate {
}
Symbol xbdBlockSize {
}
Symbol xbdNBlocks {
}
Symbol bio_alloc {
}
Symbol bio_free {
}
Symbol map_uninit {
}
Symbol map_init {
}
Symbol gptMbrParse {
}
Symbol gptParse {
}
Symbol logMsg {
}
Symbol gptRemove {
}
Symbol xbdStrategy {
}
Symbol bcopy {
}
Symbol getHiddenSectorsFromDPT {
}
Symbol xbdPartitionDevOffsetGet {
}
Symbol xbdPartitionDevSizeGet {
}
Symbol funcXbdBlkCacheStrategy {
}
Symbol xbdIoctl {
}
Symbol xbdDump {
}
Symbol xbdRamDiskDevCreate {
}
Symbol xrd_funcs {
}
Symbol xbdRamDiskDevDelete {
}
Symbol uuid_time {
}
Symbol clock_gettime {
}
Symbol uuid_node {
}
Symbol rand {
}
Symbol uuidGen {
}
Symbol memcpy {
}
Symbol uuid_is_nil {
}
Symbol memcmp {
}
Symbol uuid_compare {
}
Symbol uuid_create {
}
Symbol uuid_create_nil {
}
Symbol uuid_equal {
}
Symbol uuid_from_string {
}
Symbol sscanf {
}
Symbol uuid_hash {
}
Symbol uuid_enc_le {
}
Symbol uuid_dec_le {
}
Symbol uuid_enc_be {
}
Symbol uuid_dec_be {
}
Symbol uuid_to_string {
}
Symbol sprintf {
}
Symbol map_del {
}
Symbol map_add {
}
Symbol lstPrevious {
}
Symbol lstInsert {
}
Symbol map_remove {
}
Symbol lstDelete {
}
Symbol map_alloc {
}
Symbol map_find {
}
Symbol map_first {
}
Symbol map_last {
}
Symbol lstLast {
}
Symbol map_free {
}
Symbol lstCount {
}
Symbol lstInit {
}
Symbol lstAdd {
}
Symbol map_show {
}
Symbol __stdout {
}
Symbol __swbuf {
}
Symbol gptMapDebug {
}
Symbol uuidStr {
}
Symbol gptShowMbr {
}
Symbol devGetByName {
}
Symbol gptShowPartHdr {
}
Symbol gptShowPartTable {
}
Symbol gptShowMap {
}
Symbol le_uuid_dec {
}
Symbol le_uuid_enc {
}
Symbol gptRead {
}
Symbol gptMapWrite {
}
Symbol gptPartsGet {
}
Symbol gptExtParse {
}
Symbol gptAdd {
}
Symbol gptDestroy {
}
Symbol gptCreate {
}
Symbol gptRecover {
}
Symbol gptMigrate {
}
Symbol gptCheckMap {
}
Symbol xbdCreateGptPartition {
}
Symbol xbdAddGptPartition {
}
Symbol xbdGptPartStart {
}
Symbol xbdGptPartAdd {
}
Symbol xbdGptPartFin {
}
Symbol xbdGptPartVecAdd {
}
Symbol gptCoreDebug {
}
Symbol _func_dosFsFmtRtn {
}
Symbol hrfsFmtRtn {
}
Symbol _func_lf_advlock {
}
Symbol _func_dosFsShowRtn {
}
Symbol fsDeviceValidateMount {
}
Symbol strdup {
}
Symbol iosDevFind {
}
Symbol fsDeviceRename {
}
Symbol fsTypeToName {
}
Symbol deviceFsInfoShow {
}
Symbol fstatfs64 {
}
Symbol fstatfs {
}
ObjectFile libfsCommon.a::fsMonitor.o {
	NAME Object file fsMonitor.o from archive libfsCommon.a
	EXPORTS fsMonitorInit fsmInitialized fsmUnmountHookAdd fsmNameMap fsmProbeInstall fsmProbeUninstall fsmNameInstall fsmNameUninstall fsmGetDriver fsmGetVolume fsmUnmountHookDelete fsmUnmountHookRun
	IMPORTS .TOC. semMCreate xbdEventCategory xbdEventPrimaryInsert erfHandlerRegister xbdEventSecondaryInsert xbdEventSoftInsert _func_fsmUnmountHookAddRtn semTake semGive strncpy strncmp memset devName xbdPartitionDevCreate _func_rawFsDevInitRtn printf memSysPartId memPartAlloc memPartFree __errno strlen errnoSet strstr partitionExist hookAddToTail hookDelete
	DECLARES 
	USES 
}
Module fsMonitor.o {
	OBJECT += libfsCommon.a::fsMonitor.o
}
ObjectFile libfsCommon.a::fsEventUtilLib.o {
	NAME Object file fsEventUtilLib.o from archive libfsCommon.a
	EXPORTS fsEventUtilLibInit fsPathAddedEventSetup fsPathAddedEventRaise fsWaitForPath fsPathAddEventHandler
	IMPORTS .TOC. erfCategoryAllocate erfTypeAllocate strcmp semGive erfHandlerUnregister semBCreate erfHandlerRegister semDelete erfEventRaise semTake
	DECLARES 
	USES 
}
Module fsEventUtilLib.o {
	OBJECT += libfsCommon.a::fsEventUtilLib.o
}
ObjectFile libfsCommon.a::partLib.o {
	NAME Object file partLib.o from archive libfsCommon.a
	EXPORTS partLibCreate xbdCreatePartition partLibCreateSz xbdCreatePartitionSz partLibCreateEx xbdCreatePartitionEx xbdPartitionFun
	IMPORTS .TOC. ioctl __errno printf malloc printErr bzero write lseek read free open fsmNameMap fsPathAddedEventSetup fsWaitForPath close snprintf
	DECLARES 
	USES 
}
Module partLib.o {
	OBJECT += libfsCommon.a::partLib.o
}
ObjectFile libfsCommon.a::xbdBlkDev.o {
	NAME Object file xbdBlkDev.o from archive libfsCommon.a
	EXPORTS xbdBlkDevLibInit xbdBlkDevServTskStkSz xbdBlkDevServTskPri xbdBlkDevCreate xbdBlkDevDelete xbdBlkDevCreateSync
	IMPORTS .TOC. strlen __errno malloc semMCreate semBCreate strncpy xbdEventCategory xbdEventInstantiated erfHandlerRegister taskSpawn xbdAttach xbdEventPrimaryInsert erfEventRaise semDelete free bio_done semTake taskPrioritySet semGive xbdEventMediaChanged xbdDetach devUnmap xbdEventRemove xbdEventSoftInsert devName devMap sysClkRateGet taskDelay strncmp erfHandlerUnregister
	DECLARES 
	USES 
}
Module xbdBlkDev.o {
	OBJECT += libfsCommon.a::xbdBlkDev.o
}
ObjectFile libfsCommon.a::xbdPartition.o {
	NAME Object file xbdPartition.o from archive libfsCommon.a
	EXPORTS gptCreatePartDev xpFuncs xbdGptPartDevCreate partitionExist xbdPartitionDevCreate getHiddenSectorsFromDPT xbdPartitionDevOffsetGet xbdPartitionDevSizeGet
	IMPORTS .TOC. strncpy snprintf strlen strncat xbdMapGet lstFirst xbdAttach xbdEventCategory xbdEventSecondaryInsert erfEventRaise lstNext xbdBlockSize xbdNBlocks devMap devUnmap devName malloc memset semMCreate semTake semBCreate xbdEventRemove erfHandlerRegister xbdEventMediaChanged bio_alloc semGive xbdDetach bio_free erfHandlerUnregister semDelete free map_uninit map_init gptMbrParse gptParse logMsg gptRemove xbdStrategy bcopy bio_done funcXbdBlkCacheStrategy xbdEventSoftInsert xbdIoctl xbdDump
	DECLARES 
	USES 
}
Module xbdPartition.o {
	OBJECT += libfsCommon.a::xbdPartition.o
}
ObjectFile libfsCommon.a::xbdRamDisk.o {
	NAME Object file xbdRamDisk.o from archive libfsCommon.a
	EXPORTS xbdRamDiskDevCreate xrd_funcs xbdRamDiskDevDelete
	IMPORTS .TOC. strlen __errno malloc bzero semMCreate xbdEventSecondaryInsert xbdEventPrimaryInsert xbdAttach semDelete free snprintf fsmNameMap fsPathAddedEventSetup xbdEventCategory erfEventRaise fsWaitForPath xbdEventRemove xbdEventSoftInsert devName xbdEventInstantiated semTake bio_done bcopy semGive devMap xbdDetach devUnmap
	DECLARES 
	USES 
}
Module xbdRamDisk.o {
	OBJECT += libfsCommon.a::xbdRamDisk.o
}
ObjectFile libfsCommon.a::gptUuid.o {
	NAME Object file gptUuid.o from archive libfsCommon.a
	EXPORTS uuid_time uuid_node uuidGen uuid_is_nil uuid_compare uuid_create uuid_create_nil uuid_equal uuid_from_string uuid_hash uuid_enc_le uuid_dec_le uuid_enc_be uuid_dec_be uuid_to_string
	IMPORTS .TOC. clock_gettime rand memcpy memset memcmp bzero strlen sscanf sprintf
	DECLARES 
	USES 
}
Module gptUuid.o {
	OBJECT += libfsCommon.a::gptUuid.o
}
ObjectFile libfsCommon.a::gptMap.o {
	NAME Object file gptMap.o from archive libfsCommon.a
	EXPORTS map_del map_add map_remove map_alloc map_find map_first map_last map_free map_uninit map_init map_show gptMapDebug
	IMPORTS .TOC. malloc bio_free memset free lstFirst lstNext lstPrevious lstInsert lstDelete lstLast lstCount lstInit lstAdd printf __stdout __swbuf
	DECLARES 
	USES 
}
Module gptMap.o {
	OBJECT += libfsCommon.a::gptMap.o
}
ObjectFile libfsCommon.a::gpt.o {
	NAME Object file gpt.o from archive libfsCommon.a
	EXPORTS uuidStr gptShowMbr gptShowPartHdr gptShowPartTable gptShowMap le_uuid_dec le_uuid_enc gptRead gptMapWrite gptPartsGet gptParse gptExtParse gptMbrParse gptAdd gptDestroy gptCreate gptRecover gptRemove gptMigrate gptCheckMap xbdCreateGptPartition xbdAddGptPartition xbdGptPartStart xbdGptPartAdd xbdGptPartFin xbdGptPartVecAdd gptCoreDebug
	IMPORTS .TOC. uuid_equal memset uuid_to_string devGetByName xbdMapGet map_find printf lstCount logMsg map_show semGive xbdBlockSize bio_alloc semBCreate xbdStrategy semTake semDelete bio_free lstFirst lstNext memcmp map_add uuid_is_nil xbdNBlocks map_alloc xbdIoctl bzero map_first map_uninit map_free map_last memcpy uuid_create uuid_create_nil lstPrevious map_remove fsmNameMap fsPathAddedEventSetup fsWaitForPath map_init xbdGptPartDevCreate snprintf
	DECLARES 
	USES 
}
Module gpt.o {
	OBJECT += libfsCommon.a::gpt.o
}
ObjectFile libfsCommon.a::gptShow.o {
	NAME Object file gptShow.o from archive libfsCommon.a
	EXPORTS uuidStr gptShowMbr gptShowPartHdr gptShowPartTable gptShowMap
	IMPORTS .TOC. uuid_equal memset uuid_to_string devGetByName xbdMapGet map_find printf lstCount logMsg map_show
	DECLARES 
	USES 
}
Module gptShow.o {
	OBJECT += libfsCommon.a::gptShow.o
}
ObjectFile libfsCommon.a::fsBind.o {
	NAME Object file fsBind.o from archive libfsCommon.a
	EXPORTS hrfsFmtRtn _func_lf_advlock _func_dosFsShowRtn _func_rawFsDevInitRtn _func_fsmUnmountHookAddRtn
	IMPORTS 
	DECLARES _func_dosFsFmtRtn
	USES 
}
Module fsBind.o {
	OBJECT += libfsCommon.a::fsBind.o
}
ObjectFile libfsCommon.a::fsUtilityFuncs.o {
	NAME Object file fsUtilityFuncs.o from archive libfsCommon.a
	EXPORTS fsDeviceValidateMount fsDeviceRename
	IMPORTS .TOC. sysClkRateGet strdup taskDelay iosDevFind open close printf free fsmNameInstall ioctl
	DECLARES 
	USES 
}
Module fsUtilityFuncs.o {
	OBJECT += libfsCommon.a::fsUtilityFuncs.o
}
ObjectFile libfsCommon.a::fsMagic.o {
	NAME Object file fsMagic.o from archive libfsCommon.a
	EXPORTS fsTypeToName deviceFsInfoShow
	IMPORTS .TOC. open printf fstatfs64 fstatfs close
	DECLARES 
	USES 
}
Module fsMagic.o {
	OBJECT += libfsCommon.a::fsMagic.o
}
Library libfsCommon.a {
	MODULES libfsCommon.a::fsMonitor.o libfsCommon.a::fsEventUtilLib.o libfsCommon.a::partLib.o libfsCommon.a::xbdBlkDev.o libfsCommon.a::xbdPartition.o libfsCommon.a::xbdRamDisk.o libfsCommon.a::gptUuid.o libfsCommon.a::gptMap.o libfsCommon.a::gpt.o libfsCommon.a::gptShow.o libfsCommon.a::fsBind.o libfsCommon.a::fsUtilityFuncs.o libfsCommon.a::fsMagic.o
}
Symbol fsMonitorInit {
}
Symbol .TOC. {
}
Symbol semMCreate {
}
Symbol xbdEventCategory {
}
Symbol xbdEventPrimaryInsert {
}
Symbol erfHandlerRegister {
}
Symbol xbdEventSecondaryInsert {
}
Symbol xbdEventSoftInsert {
}
Symbol fsmInitialized {
}
Symbol fsmUnmountHookAdd {
}
Symbol _func_fsmUnmountHookAddRtn {
}
Symbol semTake {
}
Symbol semGive {
}
Symbol strncpy {
}
Symbol fsmNameMap {
}
Symbol strncmp {
}
Symbol memset {
}
Symbol devName {
}
Symbol xbdPartitionDevCreate {
}
Symbol _func_rawFsDevInitRtn {
}
Symbol printf {
}
Symbol fsmProbeInstall {
}
Symbol memSysPartId {
}
Symbol memPartAlloc {
}
Symbol fsmProbeUninstall {
}
Symbol memPartFree {
}
Symbol __errno {
}
Symbol strlen {
}
Symbol fsmNameInstall {
}
Symbol errnoSet {
}
Symbol fsmNameUninstall {
}
Symbol fsmGetDriver {
}
Symbol strstr {
}
Symbol partitionExist {
}
Symbol fsmGetVolume {
}
Symbol hookAddToTail {
}
Symbol fsmUnmountHookDelete {
}
Symbol hookDelete {
}
Symbol fsmUnmountHookRun {
}
Symbol fsEventUtilLibInit {
}
Symbol erfCategoryAllocate {
}
Symbol erfTypeAllocate {
}
Symbol strcmp {
}
Symbol erfHandlerUnregister {
}
Symbol fsPathAddedEventSetup {
}
Symbol semBCreate {
}
Symbol semDelete {
}
Symbol fsPathAddedEventRaise {
}
Symbol erfEventRaise {
}
Symbol fsWaitForPath {
}
Symbol fsPathAddEventHandler {
}
Symbol partLibCreate {
}
Symbol ioctl {
}
Symbol malloc {
}
Symbol printErr {
}
Symbol bzero {
}
Symbol write {
}
Symbol lseek {
}
Symbol read {
}
Symbol free {
}
Symbol xbdCreatePartition {
}
Symbol open {
}
Symbol close {
}
Symbol snprintf {
}
Symbol partLibCreateSz {
}
Symbol xbdCreatePartitionSz {
}
Symbol partLibCreateEx {
}
Symbol xbdCreatePartitionEx {
}
Symbol xbdPartitionFun {
}
Symbol xbdBlkDevLibInit {
}
Symbol xbdBlkDevServTskStkSz {
}
Symbol xbdBlkDevServTskPri {
}
Symbol xbdBlkDevCreate {
}
Symbol xbdEventInstantiated {
}
Symbol taskSpawn {
}
Symbol xbdAttach {
}
Symbol bio_done {
}
Symbol taskPrioritySet {
}
Symbol xbdEventMediaChanged {
}
Symbol xbdDetach {
}
Symbol devUnmap {
}
Symbol xbdEventRemove {
}
Symbol xbdBlkDevDelete {
}
Symbol devMap {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol xbdBlkDevCreateSync {
}
Symbol strncat {
}
Symbol gptCreatePartDev {
}
Symbol xbdMapGet {
}
Symbol lstFirst {
}
Symbol xpFuncs {
}
Symbol lstNext {
}
Symbol xbdGptPartDevCreate {
}
Symbol xbdBlockSize {
}
Symbol xbdNBlocks {
}
Symbol bio_alloc {
}
Symbol bio_free {
}
Symbol map_uninit {
}
Symbol map_init {
}
Symbol gptMbrParse {
}
Symbol gptParse {
}
Symbol logMsg {
}
Symbol gptRemove {
}
Symbol xbdStrategy {
}
Symbol bcopy {
}
Symbol getHiddenSectorsFromDPT {
}
Symbol xbdPartitionDevOffsetGet {
}
Symbol xbdPartitionDevSizeGet {
}
Symbol funcXbdBlkCacheStrategy {
}
Symbol xbdIoctl {
}
Symbol xbdDump {
}
Symbol xbdRamDiskDevCreate {
}
Symbol xrd_funcs {
}
Symbol xbdRamDiskDevDelete {
}
Symbol uuid_time {
}
Symbol clock_gettime {
}
Symbol uuid_node {
}
Symbol rand {
}
Symbol uuidGen {
}
Symbol memcpy {
}
Symbol uuid_is_nil {
}
Symbol memcmp {
}
Symbol uuid_compare {
}
Symbol uuid_create {
}
Symbol uuid_create_nil {
}
Symbol uuid_equal {
}
Symbol uuid_from_string {
}
Symbol sscanf {
}
Symbol uuid_hash {
}
Symbol uuid_enc_le {
}
Symbol uuid_dec_le {
}
Symbol uuid_enc_be {
}
Symbol uuid_dec_be {
}
Symbol uuid_to_string {
}
Symbol sprintf {
}
Symbol map_del {
}
Symbol map_add {
}
Symbol lstPrevious {
}
Symbol lstInsert {
}
Symbol map_remove {
}
Symbol lstDelete {
}
Symbol map_alloc {
}
Symbol map_find {
}
Symbol map_first {
}
Symbol map_last {
}
Symbol lstLast {
}
Symbol map_free {
}
Symbol lstCount {
}
Symbol lstInit {
}
Symbol lstAdd {
}
Symbol map_show {
}
Symbol __stdout {
}
Symbol __swbuf {
}
Symbol gptMapDebug {
}
Symbol uuidStr {
}
Symbol gptShowMbr {
}
Symbol devGetByName {
}
Symbol gptShowPartHdr {
}
Symbol gptShowPartTable {
}
Symbol gptShowMap {
}
Symbol le_uuid_dec {
}
Symbol le_uuid_enc {
}
Symbol gptRead {
}
Symbol gptMapWrite {
}
Symbol gptPartsGet {
}
Symbol gptExtParse {
}
Symbol gptAdd {
}
Symbol gptDestroy {
}
Symbol gptCreate {
}
Symbol gptRecover {
}
Symbol gptMigrate {
}
Symbol gptCheckMap {
}
Symbol xbdCreateGptPartition {
}
Symbol xbdAddGptPartition {
}
Symbol xbdGptPartStart {
}
Symbol xbdGptPartAdd {
}
Symbol xbdGptPartFin {
}
Symbol xbdGptPartVecAdd {
}
Symbol gptCoreDebug {
}
Symbol _func_dosFsFmtRtn {
}
Symbol hrfsFmtRtn {
}
Symbol _func_lf_advlock {
}
Symbol _func_dosFsShowRtn {
}
Symbol fsDeviceValidateMount {
}
Symbol strdup {
}
Symbol iosDevFind {
}
Symbol fsDeviceRename {
}
Symbol fsTypeToName {
}
Symbol deviceFsInfoShow {
}
Symbol fstatfs64 {
}
Symbol fstatfs {
}
ObjectFile libfsCommon.a::fsMonitor.o {
	NAME Object file fsMonitor.o from archive libfsCommon.a
	EXPORTS fsMonitorInit fsmInitialized fsmUnmountHookAdd fsmNameMap fsmProbeInstall fsmProbeUninstall fsmNameInstall fsmNameUninstall fsmGetDriver fsmGetVolume fsmUnmountHookDelete fsmUnmountHookRun
	IMPORTS .TOC. semMCreate xbdEventCategory xbdEventPrimaryInsert erfHandlerRegister xbdEventSecondaryInsert xbdEventSoftInsert _func_fsmUnmountHookAddRtn semTake semGive strncpy strncmp memset devName xbdPartitionDevCreate _func_rawFsDevInitRtn printf memSysPartId memPartAlloc memPartFree __errno strlen errnoSet strstr partitionExist hookAddToTail hookDelete
	DECLARES 
	USES 
}
Module fsMonitor.o {
	OBJECT += libfsCommon.a::fsMonitor.o
}
ObjectFile libfsCommon.a::fsEventUtilLib.o {
	NAME Object file fsEventUtilLib.o from archive libfsCommon.a
	EXPORTS fsEventUtilLibInit fsPathAddedEventSetup fsPathAddedEventRaise fsWaitForPath fsPathAddEventHandler
	IMPORTS .TOC. erfCategoryAllocate erfTypeAllocate strcmp semGive erfHandlerUnregister semBCreate erfHandlerRegister semDelete erfEventRaise semTake
	DECLARES 
	USES 
}
Module fsEventUtilLib.o {
	OBJECT += libfsCommon.a::fsEventUtilLib.o
}
ObjectFile libfsCommon.a::partLib.o {
	NAME Object file partLib.o from archive libfsCommon.a
	EXPORTS partLibCreate xbdCreatePartition partLibCreateSz xbdCreatePartitionSz partLibCreateEx xbdCreatePartitionEx xbdPartitionFun
	IMPORTS .TOC. ioctl __errno printf malloc printErr bzero write lseek read free open fsmNameMap fsPathAddedEventSetup fsWaitForPath close snprintf
	DECLARES 
	USES 
}
Module partLib.o {
	OBJECT += libfsCommon.a::partLib.o
}
ObjectFile libfsCommon.a::xbdBlkDev.o {
	NAME Object file xbdBlkDev.o from archive libfsCommon.a
	EXPORTS xbdBlkDevLibInit xbdBlkDevServTskStkSz xbdBlkDevServTskPri xbdBlkDevCreate xbdBlkDevDelete xbdBlkDevCreateSync
	IMPORTS .TOC. strlen __errno malloc semMCreate semBCreate strncpy xbdEventCategory xbdEventInstantiated erfHandlerRegister taskSpawn xbdAttach xbdEventPrimaryInsert erfEventRaise semDelete free bio_done semTake taskPrioritySet semGive xbdEventMediaChanged xbdDetach devUnmap xbdEventRemove xbdEventSoftInsert devName devMap sysClkRateGet taskDelay strncmp erfHandlerUnregister
	DECLARES 
	USES 
}
Module xbdBlkDev.o {
	OBJECT += libfsCommon.a::xbdBlkDev.o
}
ObjectFile libfsCommon.a::xbdPartition.o {
	NAME Object file xbdPartition.o from archive libfsCommon.a
	EXPORTS gptCreatePartDev xpFuncs xbdGptPartDevCreate partitionExist xbdPartitionDevCreate getHiddenSectorsFromDPT xbdPartitionDevOffsetGet xbdPartitionDevSizeGet
	IMPORTS .TOC. strncpy snprintf strlen strncat xbdMapGet lstFirst xbdAttach xbdEventCategory xbdEventSecondaryInsert erfEventRaise lstNext xbdBlockSize xbdNBlocks devMap devUnmap devName malloc memset semMCreate semTake semBCreate xbdEventRemove erfHandlerRegister xbdEventMediaChanged bio_alloc semGive xbdDetach bio_free erfHandlerUnregister semDelete free map_uninit map_init gptMbrParse gptParse logMsg gptRemove xbdStrategy bcopy bio_done funcXbdBlkCacheStrategy xbdEventSoftInsert xbdIoctl xbdDump
	DECLARES 
	USES 
}
Module xbdPartition.o {
	OBJECT += libfsCommon.a::xbdPartition.o
}
ObjectFile libfsCommon.a::xbdRamDisk.o {
	NAME Object file xbdRamDisk.o from archive libfsCommon.a
	EXPORTS xbdRamDiskDevCreate xrd_funcs xbdRamDiskDevDelete
	IMPORTS .TOC. strlen __errno malloc bzero semMCreate xbdEventSecondaryInsert xbdEventPrimaryInsert xbdAttach semDelete free snprintf fsmNameMap fsPathAddedEventSetup xbdEventCategory erfEventRaise fsWaitForPath xbdEventRemove xbdEventSoftInsert devName xbdEventInstantiated semTake bio_done bcopy semGive devMap xbdDetach devUnmap
	DECLARES 
	USES 
}
Module xbdRamDisk.o {
	OBJECT += libfsCommon.a::xbdRamDisk.o
}
ObjectFile libfsCommon.a::gptUuid.o {
	NAME Object file gptUuid.o from archive libfsCommon.a
	EXPORTS uuid_time uuid_node uuidGen uuid_is_nil uuid_compare uuid_create uuid_create_nil uuid_equal uuid_from_string uuid_hash uuid_enc_le uuid_dec_le uuid_enc_be uuid_dec_be uuid_to_string
	IMPORTS .TOC. clock_gettime rand memcpy memset memcmp bzero strlen sscanf sprintf
	DECLARES 
	USES 
}
Module gptUuid.o {
	OBJECT += libfsCommon.a::gptUuid.o
}
ObjectFile libfsCommon.a::gptMap.o {
	NAME Object file gptMap.o from archive libfsCommon.a
	EXPORTS map_del map_add map_remove map_alloc map_find map_first map_last map_free map_uninit map_init map_show gptMapDebug
	IMPORTS .TOC. malloc bio_free memset free lstFirst lstNext lstPrevious lstInsert lstDelete lstLast lstCount lstInit lstAdd printf __stdout __swbuf
	DECLARES 
	USES 
}
Module gptMap.o {
	OBJECT += libfsCommon.a::gptMap.o
}
ObjectFile libfsCommon.a::gpt.o {
	NAME Object file gpt.o from archive libfsCommon.a
	EXPORTS uuidStr gptShowMbr gptShowPartHdr gptShowPartTable gptShowMap le_uuid_dec le_uuid_enc gptRead gptMapWrite gptPartsGet gptParse gptExtParse gptMbrParse gptAdd gptDestroy gptCreate gptRecover gptRemove gptMigrate gptCheckMap xbdCreateGptPartition xbdAddGptPartition xbdGptPartStart xbdGptPartAdd xbdGptPartFin xbdGptPartVecAdd gptCoreDebug
	IMPORTS .TOC. uuid_equal memset uuid_to_string devGetByName xbdMapGet map_find printf lstCount logMsg map_show semGive xbdBlockSize bio_alloc semBCreate xbdStrategy semTake semDelete bio_free lstFirst lstNext memcmp map_add uuid_is_nil xbdNBlocks map_alloc xbdIoctl bzero map_first map_uninit map_free map_last memcpy uuid_create uuid_create_nil lstPrevious map_remove fsmNameMap fsPathAddedEventSetup fsWaitForPath map_init xbdGptPartDevCreate snprintf
	DECLARES 
	USES 
}
Module gpt.o {
	OBJECT += libfsCommon.a::gpt.o
}
ObjectFile libfsCommon.a::gptShow.o {
	NAME Object file gptShow.o from archive libfsCommon.a
	EXPORTS uuidStr gptShowMbr gptShowPartHdr gptShowPartTable gptShowMap
	IMPORTS .TOC. uuid_equal memset uuid_to_string devGetByName xbdMapGet map_find printf lstCount logMsg map_show
	DECLARES 
	USES 
}
Module gptShow.o {
	OBJECT += libfsCommon.a::gptShow.o
}
ObjectFile libfsCommon.a::fsBind.o {
	NAME Object file fsBind.o from archive libfsCommon.a
	EXPORTS hrfsFmtRtn _func_lf_advlock _func_dosFsShowRtn _func_rawFsDevInitRtn _func_fsmUnmountHookAddRtn
	IMPORTS 
	DECLARES _func_dosFsFmtRtn
	USES 
}
Module fsBind.o {
	OBJECT += libfsCommon.a::fsBind.o
}
ObjectFile libfsCommon.a::fsUtilityFuncs.o {
	NAME Object file fsUtilityFuncs.o from archive libfsCommon.a
	EXPORTS fsDeviceValidateMount fsDeviceRename
	IMPORTS .TOC. sysClkRateGet strdup taskDelay iosDevFind open close printf free fsmNameInstall ioctl
	DECLARES 
	USES 
}
Module fsUtilityFuncs.o {
	OBJECT += libfsCommon.a::fsUtilityFuncs.o
}
ObjectFile libfsCommon.a::fsMagic.o {
	NAME Object file fsMagic.o from archive libfsCommon.a
	EXPORTS fsTypeToName deviceFsInfoShow
	IMPORTS .TOC. open printf fstatfs64 fstatfs close
	DECLARES 
	USES 
}
Module fsMagic.o {
	OBJECT += libfsCommon.a::fsMagic.o
}
Library libfsCommon.a {
	MODULES libfsCommon.a::fsMonitor.o libfsCommon.a::fsEventUtilLib.o libfsCommon.a::partLib.o libfsCommon.a::xbdBlkDev.o libfsCommon.a::xbdPartition.o libfsCommon.a::xbdRamDisk.o libfsCommon.a::gptUuid.o libfsCommon.a::gptMap.o libfsCommon.a::gpt.o libfsCommon.a::gptShow.o libfsCommon.a::fsBind.o libfsCommon.a::fsUtilityFuncs.o libfsCommon.a::fsMagic.o
}
Symbol fsMonitorInit {
}
Symbol .TOC. {
}
Symbol semMCreate {
}
Symbol xbdEventCategory {
}
Symbol xbdEventPrimaryInsert {
}
Symbol erfHandlerRegister {
}
Symbol xbdEventSecondaryInsert {
}
Symbol xbdEventSoftInsert {
}
Symbol fsmInitialized {
}
Symbol fsmUnmountHookAdd {
}
Symbol _func_fsmUnmountHookAddRtn {
}
Symbol semTake {
}
Symbol semGive {
}
Symbol strncpy {
}
Symbol fsmNameMap {
}
Symbol strncmp {
}
Symbol memset {
}
Symbol devName {
}
Symbol xbdPartitionDevCreate {
}
Symbol _func_rawFsDevInitRtn {
}
Symbol printf {
}
Symbol fsmProbeInstall {
}
Symbol memSysPartId {
}
Symbol memPartAlloc {
}
Symbol fsmProbeUninstall {
}
Symbol memPartFree {
}
Symbol __errno {
}
Symbol strlen {
}
Symbol fsmNameInstall {
}
Symbol errnoSet {
}
Symbol fsmNameUninstall {
}
Symbol fsmGetDriver {
}
Symbol strstr {
}
Symbol partitionExist {
}
Symbol fsmGetVolume {
}
Symbol hookAddToTail {
}
Symbol fsmUnmountHookDelete {
}
Symbol hookDelete {
}
Symbol fsmUnmountHookRun {
}
Symbol fsEventUtilLibInit {
}
Symbol erfCategoryAllocate {
}
Symbol erfTypeAllocate {
}
Symbol strcmp {
}
Symbol erfHandlerUnregister {
}
Symbol fsPathAddedEventSetup {
}
Symbol semBCreate {
}
Symbol semDelete {
}
Symbol fsPathAddedEventRaise {
}
Symbol erfEventRaise {
}
Symbol fsWaitForPath {
}
Symbol fsPathAddEventHandler {
}
Symbol partLibCreate {
}
Symbol ioctl {
}
Symbol malloc {
}
Symbol printErr {
}
Symbol bzero {
}
Symbol write {
}
Symbol lseek {
}
Symbol read {
}
Symbol free {
}
Symbol xbdCreatePartition {
}
Symbol open {
}
Symbol close {
}
Symbol snprintf {
}
Symbol partLibCreateSz {
}
Symbol xbdCreatePartitionSz {
}
Symbol partLibCreateEx {
}
Symbol xbdCreatePartitionEx {
}
Symbol xbdPartitionFun {
}
Symbol xbdBlkDevLibInit {
}
Symbol xbdBlkDevServTskStkSz {
}
Symbol xbdBlkDevServTskPri {
}
Symbol xbdBlkDevCreate {
}
Symbol xbdEventInstantiated {
}
Symbol taskSpawn {
}
Symbol xbdAttach {
}
Symbol bio_done {
}
Symbol taskPrioritySet {
}
Symbol xbdEventMediaChanged {
}
Symbol xbdDetach {
}
Symbol devUnmap {
}
Symbol xbdEventRemove {
}
Symbol xbdBlkDevDelete {
}
Symbol devMap {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol xbdBlkDevCreateSync {
}
Symbol strncat {
}
Symbol gptCreatePartDev {
}
Symbol xbdMapGet {
}
Symbol lstFirst {
}
Symbol xpFuncs {
}
Symbol lstNext {
}
Symbol xbdGptPartDevCreate {
}
Symbol xbdBlockSize {
}
Symbol xbdNBlocks {
}
Symbol bio_alloc {
}
Symbol bio_free {
}
Symbol map_uninit {
}
Symbol map_init {
}
Symbol gptMbrParse {
}
Symbol gptParse {
}
Symbol logMsg {
}
Symbol gptRemove {
}
Symbol xbdStrategy {
}
Symbol bcopy {
}
Symbol getHiddenSectorsFromDPT {
}
Symbol xbdPartitionDevOffsetGet {
}
Symbol xbdPartitionDevSizeGet {
}
Symbol funcXbdBlkCacheStrategy {
}
Symbol xbdIoctl {
}
Symbol xbdDump {
}
Symbol xbdRamDiskDevCreate {
}
Symbol xrd_funcs {
}
Symbol xbdRamDiskDevDelete {
}
Symbol uuid_time {
}
Symbol clock_gettime {
}
Symbol uuid_node {
}
Symbol rand {
}
Symbol uuidGen {
}
Symbol memcpy {
}
Symbol uuid_is_nil {
}
Symbol memcmp {
}
Symbol uuid_compare {
}
Symbol uuid_create {
}
Symbol uuid_create_nil {
}
Symbol uuid_equal {
}
Symbol uuid_from_string {
}
Symbol sscanf {
}
Symbol uuid_hash {
}
Symbol uuid_enc_le {
}
Symbol uuid_dec_le {
}
Symbol uuid_enc_be {
}
Symbol uuid_dec_be {
}
Symbol uuid_to_string {
}
Symbol sprintf {
}
Symbol map_del {
}
Symbol map_add {
}
Symbol lstPrevious {
}
Symbol lstInsert {
}
Symbol map_remove {
}
Symbol lstDelete {
}
Symbol map_alloc {
}
Symbol map_find {
}
Symbol map_first {
}
Symbol map_last {
}
Symbol lstLast {
}
Symbol map_free {
}
Symbol lstCount {
}
Symbol lstInit {
}
Symbol lstAdd {
}
Symbol map_show {
}
Symbol __stdout {
}
Symbol __swbuf {
}
Symbol gptMapDebug {
}
Symbol uuidStr {
}
Symbol gptShowMbr {
}
Symbol devGetByName {
}
Symbol gptShowPartHdr {
}
Symbol gptShowPartTable {
}
Symbol gptShowMap {
}
Symbol le_uuid_dec {
}
Symbol le_uuid_enc {
}
Symbol gptRead {
}
Symbol gptMapWrite {
}
Symbol gptPartsGet {
}
Symbol gptExtParse {
}
Symbol gptAdd {
}
Symbol gptDestroy {
}
Symbol gptCreate {
}
Symbol gptRecover {
}
Symbol gptMigrate {
}
Symbol gptCheckMap {
}
Symbol xbdCreateGptPartition {
}
Symbol xbdAddGptPartition {
}
Symbol xbdGptPartStart {
}
Symbol xbdGptPartAdd {
}
Symbol xbdGptPartFin {
}
Symbol xbdGptPartVecAdd {
}
Symbol gptCoreDebug {
}
Symbol _func_dosFsFmtRtn {
}
Symbol hrfsFmtRtn {
}
Symbol _func_lf_advlock {
}
Symbol _func_dosFsShowRtn {
}
Symbol fsDeviceValidateMount {
}
Symbol strdup {
}
Symbol iosDevFind {
}
Symbol fsDeviceRename {
}
Symbol fsTypeToName {
}
Symbol deviceFsInfoShow {
}
Symbol fstatfs64 {
}
Symbol fstatfs {
}
ObjectFile libfsCommon.a::fsMonitor.o {
	NAME Object file fsMonitor.o from archive libfsCommon.a
	EXPORTS fsMonitorInit fsmInitialized fsmUnmountHookAdd fsmNameMap fsmProbeInstall fsmProbeUninstall fsmNameInstall fsmNameUninstall fsmGetDriver fsmGetVolume fsmUnmountHookDelete fsmUnmountHookRun
	IMPORTS .TOC. semMCreate xbdEventCategory xbdEventPrimaryInsert erfHandlerRegister xbdEventSecondaryInsert xbdEventSoftInsert _func_fsmUnmountHookAddRtn semTake semGive strncpy strncmp memset devName xbdPartitionDevCreate _func_rawFsDevInitRtn printf memSysPartId memPartAlloc memPartFree __errno strlen errnoSet strstr partitionExist hookAddToTail hookDelete
	DECLARES 
	USES 
}
Module fsMonitor.o {
	OBJECT += libfsCommon.a::fsMonitor.o
}
ObjectFile libfsCommon.a::fsEventUtilLib.o {
	NAME Object file fsEventUtilLib.o from archive libfsCommon.a
	EXPORTS fsEventUtilLibInit fsPathAddedEventSetup fsPathAddedEventRaise fsWaitForPath fsPathAddEventHandler
	IMPORTS .TOC. erfCategoryAllocate erfTypeAllocate strcmp semGive erfHandlerUnregister semBCreate erfHandlerRegister semDelete erfEventRaise semTake
	DECLARES 
	USES 
}
Module fsEventUtilLib.o {
	OBJECT += libfsCommon.a::fsEventUtilLib.o
}
ObjectFile libfsCommon.a::partLib.o {
	NAME Object file partLib.o from archive libfsCommon.a
	EXPORTS partLibCreate xbdCreatePartition partLibCreateSz xbdCreatePartitionSz partLibCreateEx xbdCreatePartitionEx xbdPartitionFun
	IMPORTS .TOC. ioctl __errno printf malloc printErr bzero write lseek read free open fsmNameMap fsPathAddedEventSetup fsWaitForPath close snprintf
	DECLARES 
	USES 
}
Module partLib.o {
	OBJECT += libfsCommon.a::partLib.o
}
ObjectFile libfsCommon.a::xbdBlkDev.o {
	NAME Object file xbdBlkDev.o from archive libfsCommon.a
	EXPORTS xbdBlkDevLibInit xbdBlkDevServTskStkSz xbdBlkDevServTskPri xbdBlkDevCreate xbdBlkDevDelete xbdBlkDevCreateSync
	IMPORTS .TOC. strlen __errno malloc semMCreate semBCreate strncpy xbdEventCategory xbdEventInstantiated erfHandlerRegister taskSpawn xbdAttach xbdEventPrimaryInsert erfEventRaise semDelete free bio_done semTake taskPrioritySet semGive xbdEventMediaChanged xbdDetach devUnmap xbdEventRemove xbdEventSoftInsert devName devMap sysClkRateGet taskDelay strncmp erfHandlerUnregister
	DECLARES 
	USES 
}
Module xbdBlkDev.o {
	OBJECT += libfsCommon.a::xbdBlkDev.o
}
ObjectFile libfsCommon.a::xbdPartition.o {
	NAME Object file xbdPartition.o from archive libfsCommon.a
	EXPORTS gptCreatePartDev xpFuncs xbdGptPartDevCreate partitionExist xbdPartitionDevCreate getHiddenSectorsFromDPT xbdPartitionDevOffsetGet xbdPartitionDevSizeGet
	IMPORTS .TOC. strncpy snprintf strlen strncat xbdMapGet lstFirst xbdAttach xbdEventCategory xbdEventSecondaryInsert erfEventRaise lstNext xbdBlockSize xbdNBlocks devMap devUnmap devName malloc memset semMCreate semTake semBCreate xbdEventRemove erfHandlerRegister xbdEventMediaChanged bio_alloc semGive xbdDetach bio_free erfHandlerUnregister semDelete free map_uninit map_init gptMbrParse gptParse logMsg gptRemove xbdStrategy bcopy bio_done funcXbdBlkCacheStrategy xbdEventSoftInsert xbdIoctl xbdDump
	DECLARES 
	USES 
}
Module xbdPartition.o {
	OBJECT += libfsCommon.a::xbdPartition.o
}
ObjectFile libfsCommon.a::xbdRamDisk.o {
	NAME Object file xbdRamDisk.o from archive libfsCommon.a
	EXPORTS xbdRamDiskDevCreate xrd_funcs xbdRamDiskDevDelete
	IMPORTS .TOC. strlen __errno malloc bzero semMCreate xbdEventSecondaryInsert xbdEventPrimaryInsert xbdAttach semDelete free snprintf fsmNameMap fsPathAddedEventSetup xbdEventCategory erfEventRaise fsWaitForPath xbdEventRemove xbdEventSoftInsert devName xbdEventInstantiated semTake bio_done bcopy semGive devMap xbdDetach devUnmap
	DECLARES 
	USES 
}
Module xbdRamDisk.o {
	OBJECT += libfsCommon.a::xbdRamDisk.o
}
ObjectFile libfsCommon.a::gptUuid.o {
	NAME Object file gptUuid.o from archive libfsCommon.a
	EXPORTS uuid_time uuid_node uuidGen uuid_is_nil uuid_compare uuid_create uuid_create_nil uuid_equal uuid_from_string uuid_hash uuid_enc_le uuid_dec_le uuid_enc_be uuid_dec_be uuid_to_string
	IMPORTS .TOC. clock_gettime rand memcpy memset memcmp bzero strlen sscanf sprintf
	DECLARES 
	USES 
}
Module gptUuid.o {
	OBJECT += libfsCommon.a::gptUuid.o
}
ObjectFile libfsCommon.a::gptMap.o {
	NAME Object file gptMap.o from archive libfsCommon.a
	EXPORTS map_del map_add map_remove map_alloc map_find map_first map_last map_free map_uninit map_init map_show gptMapDebug
	IMPORTS .TOC. malloc bio_free memset free lstFirst lstNext lstPrevious lstInsert lstDelete lstLast lstCount lstInit lstAdd printf __stdout __swbuf
	DECLARES 
	USES 
}
Module gptMap.o {
	OBJECT += libfsCommon.a::gptMap.o
}
ObjectFile libfsCommon.a::gpt.o {
	NAME Object file gpt.o from archive libfsCommon.a
	EXPORTS uuidStr gptShowMbr gptShowPartHdr gptShowPartTable gptShowMap le_uuid_dec le_uuid_enc gptRead gptMapWrite gptPartsGet gptParse gptExtParse gptMbrParse gptAdd gptDestroy gptCreate gptRecover gptRemove gptMigrate gptCheckMap xbdCreateGptPartition xbdAddGptPartition xbdGptPartStart xbdGptPartAdd xbdGptPartFin xbdGptPartVecAdd gptCoreDebug
	IMPORTS .TOC. uuid_equal memset uuid_to_string devGetByName xbdMapGet map_find printf lstCount logMsg map_show semGive xbdBlockSize bio_alloc semBCreate xbdStrategy semTake semDelete bio_free lstFirst lstNext memcmp map_add uuid_is_nil xbdNBlocks map_alloc xbdIoctl bzero map_first map_uninit map_free map_last memcpy uuid_create uuid_create_nil lstPrevious map_remove fsmNameMap fsPathAddedEventSetup fsWaitForPath map_init xbdGptPartDevCreate snprintf
	DECLARES 
	USES 
}
Module gpt.o {
	OBJECT += libfsCommon.a::gpt.o
}
ObjectFile libfsCommon.a::gptShow.o {
	NAME Object file gptShow.o from archive libfsCommon.a
	EXPORTS uuidStr gptShowMbr gptShowPartHdr gptShowPartTable gptShowMap
	IMPORTS .TOC. uuid_equal memset uuid_to_string devGetByName xbdMapGet map_find printf lstCount logMsg map_show
	DECLARES 
	USES 
}
Module gptShow.o {
	OBJECT += libfsCommon.a::gptShow.o
}
ObjectFile libfsCommon.a::fsBind.o {
	NAME Object file fsBind.o from archive libfsCommon.a
	EXPORTS hrfsFmtRtn _func_lf_advlock _func_dosFsShowRtn _func_rawFsDevInitRtn _func_fsmUnmountHookAddRtn
	IMPORTS 
	DECLARES _func_dosFsFmtRtn
	USES 
}
Module fsBind.o {
	OBJECT += libfsCommon.a::fsBind.o
}
ObjectFile libfsCommon.a::fsUtilityFuncs.o {
	NAME Object file fsUtilityFuncs.o from archive libfsCommon.a
	EXPORTS fsDeviceValidateMount fsDeviceRename
	IMPORTS .TOC. sysClkRateGet strdup taskDelay iosDevFind open close printf free fsmNameInstall ioctl
	DECLARES 
	USES 
}
Module fsUtilityFuncs.o {
	OBJECT += libfsCommon.a::fsUtilityFuncs.o
}
ObjectFile libfsCommon.a::fsMagic.o {
	NAME Object file fsMagic.o from archive libfsCommon.a
	EXPORTS fsTypeToName deviceFsInfoShow
	IMPORTS .TOC. open printf fstatfs64 fstatfs close
	DECLARES 
	USES 
}
Module fsMagic.o {
	OBJECT += libfsCommon.a::fsMagic.o
}
Library libfsCommon.a {
	MODULES libfsCommon.a::fsMonitor.o libfsCommon.a::fsEventUtilLib.o libfsCommon.a::partLib.o libfsCommon.a::xbdBlkDev.o libfsCommon.a::xbdPartition.o libfsCommon.a::xbdRamDisk.o libfsCommon.a::gptUuid.o libfsCommon.a::gptMap.o libfsCommon.a::gpt.o libfsCommon.a::gptShow.o libfsCommon.a::fsBind.o libfsCommon.a::fsUtilityFuncs.o libfsCommon.a::fsMagic.o
}
