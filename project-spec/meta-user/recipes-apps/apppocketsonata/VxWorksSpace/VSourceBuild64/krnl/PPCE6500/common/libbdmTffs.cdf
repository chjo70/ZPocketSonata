Symbol .TOC. {
}
Symbol flTakeMutex {
}
Symbol errnoSet {
}
Symbol flSocketSetBusy {
}
Symbol flNeedVcc {
}
Symbol flDontNeedVcc {
}
Symbol flFreeMutex {
}
Symbol flMediaCheck {
}
Symbol flMount {
}
Symbol fromLEushort {
}
Symbol fromLEulong {
}
Symbol flFormat {
}
Symbol malloc {
}
Symbol free {
}
Symbol flFileSysSectorStart {
}
Symbol memset {
}
Symbol strncmp {
}
Symbol toLEulong {
}
Symbol flIdentifyFlash {
}
Symbol flInit {
}
Symbol flSocketOf {
}
Symbol flCreateMutex {
}
Symbol flSysfunInit {
}
Symbol flRegisterComponents {
}
Symbol flInitSockets {
}
Symbol flInitIdentifyTable {
}
Symbol flInstallTimer {
}
Symbol flCall {
}
Symbol noOfDrives {
}
Symbol flMsecCounter {
}
Symbol flIntervalRoutine {
}
Symbol flGetVolume {
}
Symbol memcpy {
}
Symbol memcmp {
}
Symbol toLEushort {
}
Symbol flCrc16 {
}
Symbol bzero {
}
Symbol flRandByte {
}
Symbol sectorChecksumWrite {
}
Symbol logMsg {
}
Symbol flSocketNoOf {
}
Symbol flBufferOf {
}
Symbol printf {
}
Symbol mountFTL {
}
Symbol spinLockTaskInit {
}
Symbol semBCreate {
}
Symbol sectorChecksum {
}
Symbol memalign {
}
Symbol bcopy {
}
Symbol spinLockTaskTake {
}
Symbol spinLockTaskGive {
}
Symbol sleep {
}
Symbol __assert {
}
Symbol semGive {
}
Symbol tffsWrtLock {
}
Symbol semTake {
}
Symbol tffsWrtUnlock {
}
Symbol formatFTL {
}
Symbol mountValidateSet {
}
Symbol tffsVolStatInit {
}
Symbol vxAtomic32Set {
}
Symbol tffsVolStatShow {
}
Symbol vxAtomic32Get {
}
Symbol noOfTLs {
}
Symbol tlTable {
}
Symbol mountSSFDC {
}
Symbol formatSSFDC {
}
Symbol flIdentifyRegister {
}
Symbol mtdIdentifyTable {
}
Symbol flMap {
}
Symbol flSetPowerOnCallback {
}
Symbol flIntelIdentify {
}
Symbol flNeedVpp {
}
Symbol flDelayLoop {
}
Symbol flDontNeedVpp {
}
Symbol flIntelSize {
}
Symbol flResetCardChanged {
}
Symbol noOfMTDs {
}
Symbol mtdTable {
}
Symbol needCheckRAM {
}
Symbol flWriteProtected {
}
Symbol flSetWindowBusWidth {
}
Symbol flSetWindowSpeed {
}
Symbol flSetWindowSize {
}
Symbol flInitSocket {
}
Symbol flGetMappingContext {
}
Symbol flPollSemId {
}
Symbol tffsDrv {
}
Symbol tffsDevCreate {
}
Symbol semMCreate {
}
Symbol semDelete {
}
Symbol snprintf {
}
Symbol taskSpawn {
}
Symbol tffsDevOptionsSet {
}
Symbol tffsDrvOptionsSet {
}
Symbol tffsRawio {
}
Symbol tffsDiskChangeAnnounce {
}
Symbol tffsDevFormat {
}
Symbol tffsDevStatShow {
}
Symbol sysClkRateGet {
}
Symbol tffsDevRawSpeedShow {
}
Symbol tickGet {
}
Symbol flPollTask {
}
Symbol taskDelay {
}
Symbol flRemoveTimer {
}
Symbol taskDelete {
}
Symbol randBytes {
}
Symbol rand {
}
Symbol flCurrentTime {
}
Symbol time {
}
Symbol localtime {
}
Symbol flCurrentDate {
}
Symbol flAddLongToFarPointer {
}
Symbol copyShort {
}
Symbol copyLong {
}
Symbol tffscmpWords {
}
ObjectFile libbdmTffs.a::fatlite.o {
	NAME Object file fatlite.o from archive libbdmTffs.a
	EXPORTS flFileSysSectorStart flInit flCall flMsecCounter flGetVolume
	IMPORTS .TOC. flTakeMutex errnoSet flSocketSetBusy flNeedVcc flDontNeedVcc flFreeMutex flMediaCheck flMount fromLEushort fromLEulong flFormat malloc free memset strncmp toLEulong flIdentifyFlash flSocketOf flCreateMutex flSysfunInit flRegisterComponents flInitSockets flInitIdentifyTable flInstallTimer noOfDrives flIntervalRoutine
	DECLARES 
	USES 
}
Module fatlite.o {
	OBJECT += libbdmTffs.a::fatlite.o
}
ObjectFile libbdmTffs.a::ftllite.o {
	NAME Object file ftllite.o from archive libbdmTffs.a
	EXPORTS sectorChecksumWrite mountFTL sectorChecksum tffsWrtLock tffsWrtUnlock formatFTL mountValidateSet tffsVolStatInit tffsVolStatShow
	IMPORTS .TOC. memcpy fromLEulong toLEulong memcmp fromLEushort toLEushort flCrc16 errnoSet bzero flRandByte logMsg free malloc flSocketNoOf flBufferOf printf spinLockTaskInit semBCreate memset memalign bcopy spinLockTaskTake spinLockTaskGive sleep __assert semGive semTake vxAtomic32Set flGetVolume vxAtomic32Get
	DECLARES 
	USES 
}
Module ftllite.o {
	OBJECT += libbdmTffs.a::ftllite.o
}
ObjectFile libbdmTffs.a::fltl.o {
	NAME Object file fltl.o from archive libbdmTffs.a
	EXPORTS flMount flFormat
	IMPORTS .TOC. flSocketOf flIdentifyFlash noOfTLs tlTable
	DECLARES 
	USES 
}
Module fltl.o {
	OBJECT += libbdmTffs.a::fltl.o
}
ObjectFile libbdmTffs.a::ssfdc.o {
	NAME Object file ssfdc.o from archive libbdmTffs.a
	EXPORTS mountSSFDC formatSSFDC
	IMPORTS .TOC. memcmp flSocketNoOf flBufferOf malloc free memset
	DECLARES 
	USES 
}
Module ssfdc.o {
	OBJECT += libbdmTffs.a::ssfdc.o
}
ObjectFile libbdmTffs.a::flflash.o {
	NAME Object file flflash.o from archive libbdmTffs.a
	EXPORTS flIdentifyRegister flInitIdentifyTable flIntelIdentify flIntelSize flIdentifyFlash needCheckRAM
	IMPORTS .TOC. flMap memcpy flSetPowerOnCallback flNeedVpp flDelayLoop flDontNeedVpp flResetCardChanged flMediaCheck noOfMTDs mtdTable
	DECLARES mtdIdentifyTable
	USES 
}
Module flflash.o {
	OBJECT += libbdmTffs.a::flflash.o
}
ObjectFile libbdmTffs.a::flsocket.o {
	NAME Object file flsocket.o from archive libbdmTffs.a
	EXPORTS flSocketNoOf flSocketOf flBufferOf flWriteProtected flResetCardChanged flMediaCheck flSetWindowBusWidth flSetWindowSpeed flSetWindowSize flInitSocket flInitSockets noOfDrives flGetMappingContext flMap flSocketSetBusy flNeedVcc flDontNeedVcc flNeedVpp flDontNeedVpp flSetPowerOnCallback flIntervalRoutine
	IMPORTS .TOC. errnoSet malloc
	DECLARES 
	USES 
}
Module flsocket.o {
	OBJECT += libbdmTffs.a::flsocket.o
}
ObjectFile libbdmTffs.a::backgrnd.o {
	NAME Object file backgrnd.o from archive libbdmTffs.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module backgrnd.o {
	OBJECT += libbdmTffs.a::backgrnd.o
}
ObjectFile libbdmTffs.a::tffsDrv.o {
	NAME Object file tffsDrv.o from archive libbdmTffs.a
	EXPORTS tffsDrv tffsDevCreate tffsDevOptionsSet tffsDrvOptionsSet tffsRawio tffsDiskChangeAnnounce tffsDevFormat tffsDevStatShow tffsDevRawSpeedShow
	IMPORTS .TOC. semBCreate flInit semGive fromLEushort fromLEulong flFileSysSectorStart vxAtomic32Set malloc bzero flCall semMCreate free errnoSet semDelete snprintf taskSpawn semTake sysClkRateGet printf vxAtomic32Get memset tickGet
	DECLARES flPollSemId
	USES 
}
Module tffsDrv.o {
	OBJECT += libbdmTffs.a::tffsDrv.o
}
ObjectFile libbdmTffs.a::tffsLib.o {
	NAME Object file tffsLib.o from archive libbdmTffs.a
	EXPORTS flCreateMutex flTakeMutex flFreeMutex flSysfunInit flPollTask flInstallTimer flRemoveTimer flRandByte flCurrentTime flCurrentDate flAddLongToFarPointer
	IMPORTS .TOC. semMCreate semTake semGive sysClkRateGet flPollSemId semDelete taskDelay taskSpawn taskDelete randBytes rand time localtime
	DECLARES 
	USES 
}
Module tffsLib.o {
	OBJECT += libbdmTffs.a::tffsLib.o
}
ObjectFile libbdmTffs.a::flbase.o {
	NAME Object file flbase.o from archive libbdmTffs.a
	EXPORTS toLEushort fromLEushort toLEulong fromLEulong copyShort copyLong tffscmpWords flCrc16
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module flbase.o {
	OBJECT += libbdmTffs.a::flbase.o
}
Library libbdmTffs.a {
	MODULES libbdmTffs.a::fatlite.o libbdmTffs.a::ftllite.o libbdmTffs.a::fltl.o libbdmTffs.a::ssfdc.o libbdmTffs.a::flflash.o libbdmTffs.a::flsocket.o libbdmTffs.a::backgrnd.o libbdmTffs.a::tffsDrv.o libbdmTffs.a::tffsLib.o libbdmTffs.a::flbase.o
}
Symbol .TOC. {
}
Symbol flTakeMutex {
}
Symbol errnoSet {
}
Symbol flSocketSetBusy {
}
Symbol flNeedVcc {
}
Symbol flDontNeedVcc {
}
Symbol flFreeMutex {
}
Symbol flMediaCheck {
}
Symbol flMount {
}
Symbol fromLEushort {
}
Symbol fromLEulong {
}
Symbol flFormat {
}
Symbol malloc {
}
Symbol free {
}
Symbol flFileSysSectorStart {
}
Symbol memset {
}
Symbol strncmp {
}
Symbol toLEulong {
}
Symbol flIdentifyFlash {
}
Symbol flInit {
}
Symbol flSocketOf {
}
Symbol flCreateMutex {
}
Symbol flSysfunInit {
}
Symbol flRegisterComponents {
}
Symbol flInitSockets {
}
Symbol flInitIdentifyTable {
}
Symbol flInstallTimer {
}
Symbol flCall {
}
Symbol noOfDrives {
}
Symbol flMsecCounter {
}
Symbol flIntervalRoutine {
}
Symbol flGetVolume {
}
Symbol memcpy {
}
Symbol memcmp {
}
Symbol toLEushort {
}
Symbol flCrc16 {
}
Symbol bzero {
}
Symbol flRandByte {
}
Symbol sectorChecksumWrite {
}
Symbol logMsg {
}
Symbol flSocketNoOf {
}
Symbol flBufferOf {
}
Symbol printf {
}
Symbol mountFTL {
}
Symbol spinLockTaskInit {
}
Symbol semBCreate {
}
Symbol sectorChecksum {
}
Symbol memalign {
}
Symbol bcopy {
}
Symbol spinLockTaskTake {
}
Symbol spinLockTaskGive {
}
Symbol sleep {
}
Symbol __assert {
}
Symbol semGive {
}
Symbol tffsWrtLock {
}
Symbol semTake {
}
Symbol tffsWrtUnlock {
}
Symbol formatFTL {
}
Symbol mountValidateSet {
}
Symbol tffsVolStatInit {
}
Symbol vxAtomic32Set {
}
Symbol tffsVolStatShow {
}
Symbol vxAtomic32Get {
}
Symbol noOfTLs {
}
Symbol tlTable {
}
Symbol mountSSFDC {
}
Symbol formatSSFDC {
}
Symbol flIdentifyRegister {
}
Symbol mtdIdentifyTable {
}
Symbol flMap {
}
Symbol flSetPowerOnCallback {
}
Symbol flIntelIdentify {
}
Symbol flNeedVpp {
}
Symbol flDelayLoop {
}
Symbol flDontNeedVpp {
}
Symbol flIntelSize {
}
Symbol flResetCardChanged {
}
Symbol noOfMTDs {
}
Symbol mtdTable {
}
Symbol needCheckRAM {
}
Symbol flWriteProtected {
}
Symbol flSetWindowBusWidth {
}
Symbol flSetWindowSpeed {
}
Symbol flSetWindowSize {
}
Symbol flInitSocket {
}
Symbol flGetMappingContext {
}
Symbol flPollSemId {
}
Symbol tffsDrv {
}
Symbol tffsDevCreate {
}
Symbol semMCreate {
}
Symbol semDelete {
}
Symbol snprintf {
}
Symbol taskSpawn {
}
Symbol tffsDevOptionsSet {
}
Symbol tffsDrvOptionsSet {
}
Symbol tffsRawio {
}
Symbol tffsDiskChangeAnnounce {
}
Symbol tffsDevFormat {
}
Symbol tffsDevStatShow {
}
Symbol sysClkRateGet {
}
Symbol tffsDevRawSpeedShow {
}
Symbol tickGet {
}
Symbol flPollTask {
}
Symbol taskDelay {
}
Symbol flRemoveTimer {
}
Symbol taskDelete {
}
Symbol randBytes {
}
Symbol rand {
}
Symbol flCurrentTime {
}
Symbol time {
}
Symbol localtime {
}
Symbol flCurrentDate {
}
Symbol flAddLongToFarPointer {
}
Symbol copyShort {
}
Symbol copyLong {
}
Symbol tffscmpWords {
}
ObjectFile libbdmTffs.a::fatlite.o {
	NAME Object file fatlite.o from archive libbdmTffs.a
	EXPORTS flFileSysSectorStart flInit flCall flMsecCounter flGetVolume
	IMPORTS .TOC. flTakeMutex errnoSet flSocketSetBusy flNeedVcc flDontNeedVcc flFreeMutex flMediaCheck flMount fromLEushort fromLEulong flFormat malloc free memset strncmp toLEulong flIdentifyFlash flSocketOf flCreateMutex flSysfunInit flRegisterComponents flInitSockets flInitIdentifyTable flInstallTimer noOfDrives flIntervalRoutine
	DECLARES 
	USES 
}
Module fatlite.o {
	OBJECT += libbdmTffs.a::fatlite.o
}
ObjectFile libbdmTffs.a::ftllite.o {
	NAME Object file ftllite.o from archive libbdmTffs.a
	EXPORTS sectorChecksumWrite mountFTL sectorChecksum tffsWrtLock tffsWrtUnlock formatFTL mountValidateSet tffsVolStatInit tffsVolStatShow
	IMPORTS .TOC. memcpy fromLEulong toLEulong memcmp fromLEushort toLEushort flCrc16 errnoSet bzero flRandByte logMsg free malloc flSocketNoOf flBufferOf printf spinLockTaskInit semBCreate memset memalign bcopy spinLockTaskTake spinLockTaskGive sleep __assert semGive semTake vxAtomic32Set flGetVolume vxAtomic32Get
	DECLARES 
	USES 
}
Module ftllite.o {
	OBJECT += libbdmTffs.a::ftllite.o
}
ObjectFile libbdmTffs.a::fltl.o {
	NAME Object file fltl.o from archive libbdmTffs.a
	EXPORTS flMount flFormat
	IMPORTS .TOC. flSocketOf flIdentifyFlash noOfTLs tlTable
	DECLARES 
	USES 
}
Module fltl.o {
	OBJECT += libbdmTffs.a::fltl.o
}
ObjectFile libbdmTffs.a::ssfdc.o {
	NAME Object file ssfdc.o from archive libbdmTffs.a
	EXPORTS mountSSFDC formatSSFDC
	IMPORTS .TOC. memcmp flSocketNoOf flBufferOf malloc free memset
	DECLARES 
	USES 
}
Module ssfdc.o {
	OBJECT += libbdmTffs.a::ssfdc.o
}
ObjectFile libbdmTffs.a::flflash.o {
	NAME Object file flflash.o from archive libbdmTffs.a
	EXPORTS flIdentifyRegister flInitIdentifyTable flIntelIdentify flIntelSize flIdentifyFlash needCheckRAM
	IMPORTS .TOC. flMap memcpy flSetPowerOnCallback flNeedVpp flDelayLoop flDontNeedVpp flResetCardChanged flMediaCheck noOfMTDs mtdTable
	DECLARES mtdIdentifyTable
	USES 
}
Module flflash.o {
	OBJECT += libbdmTffs.a::flflash.o
}
ObjectFile libbdmTffs.a::flsocket.o {
	NAME Object file flsocket.o from archive libbdmTffs.a
	EXPORTS flSocketNoOf flSocketOf flBufferOf flWriteProtected flResetCardChanged flMediaCheck flSetWindowBusWidth flSetWindowSpeed flSetWindowSize flInitSocket flInitSockets noOfDrives flGetMappingContext flMap flSocketSetBusy flNeedVcc flDontNeedVcc flNeedVpp flDontNeedVpp flSetPowerOnCallback flIntervalRoutine
	IMPORTS .TOC. errnoSet malloc
	DECLARES 
	USES 
}
Module flsocket.o {
	OBJECT += libbdmTffs.a::flsocket.o
}
ObjectFile libbdmTffs.a::backgrnd.o {
	NAME Object file backgrnd.o from archive libbdmTffs.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module backgrnd.o {
	OBJECT += libbdmTffs.a::backgrnd.o
}
ObjectFile libbdmTffs.a::tffsDrv.o {
	NAME Object file tffsDrv.o from archive libbdmTffs.a
	EXPORTS tffsDrv tffsDevCreate tffsDevOptionsSet tffsDrvOptionsSet tffsRawio tffsDiskChangeAnnounce tffsDevFormat tffsDevStatShow tffsDevRawSpeedShow
	IMPORTS .TOC. semBCreate flInit semGive fromLEushort fromLEulong flFileSysSectorStart vxAtomic32Set malloc bzero flCall semMCreate free errnoSet semDelete snprintf taskSpawn semTake sysClkRateGet printf vxAtomic32Get memset tickGet
	DECLARES flPollSemId
	USES 
}
Module tffsDrv.o {
	OBJECT += libbdmTffs.a::tffsDrv.o
}
ObjectFile libbdmTffs.a::tffsLib.o {
	NAME Object file tffsLib.o from archive libbdmTffs.a
	EXPORTS flCreateMutex flTakeMutex flFreeMutex flSysfunInit flPollTask flInstallTimer flRemoveTimer flRandByte flCurrentTime flCurrentDate flAddLongToFarPointer
	IMPORTS .TOC. semMCreate semTake semGive sysClkRateGet flPollSemId semDelete taskDelay taskSpawn taskDelete randBytes rand time localtime
	DECLARES 
	USES 
}
Module tffsLib.o {
	OBJECT += libbdmTffs.a::tffsLib.o
}
ObjectFile libbdmTffs.a::flbase.o {
	NAME Object file flbase.o from archive libbdmTffs.a
	EXPORTS toLEushort fromLEushort toLEulong fromLEulong copyShort copyLong tffscmpWords flCrc16
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module flbase.o {
	OBJECT += libbdmTffs.a::flbase.o
}
Library libbdmTffs.a {
	MODULES libbdmTffs.a::fatlite.o libbdmTffs.a::ftllite.o libbdmTffs.a::fltl.o libbdmTffs.a::ssfdc.o libbdmTffs.a::flflash.o libbdmTffs.a::flsocket.o libbdmTffs.a::backgrnd.o libbdmTffs.a::tffsDrv.o libbdmTffs.a::tffsLib.o libbdmTffs.a::flbase.o
}
Symbol .TOC. {
}
Symbol flTakeMutex {
}
Symbol errnoSet {
}
Symbol flSocketSetBusy {
}
Symbol flNeedVcc {
}
Symbol flDontNeedVcc {
}
Symbol flFreeMutex {
}
Symbol flMediaCheck {
}
Symbol flMount {
}
Symbol fromLEushort {
}
Symbol fromLEulong {
}
Symbol flFormat {
}
Symbol malloc {
}
Symbol free {
}
Symbol flFileSysSectorStart {
}
Symbol memset {
}
Symbol strncmp {
}
Symbol toLEulong {
}
Symbol flIdentifyFlash {
}
Symbol flInit {
}
Symbol flSocketOf {
}
Symbol flCreateMutex {
}
Symbol flSysfunInit {
}
Symbol flRegisterComponents {
}
Symbol flInitSockets {
}
Symbol flInitIdentifyTable {
}
Symbol flInstallTimer {
}
Symbol flCall {
}
Symbol noOfDrives {
}
Symbol flMsecCounter {
}
Symbol flIntervalRoutine {
}
Symbol flGetVolume {
}
Symbol memcpy {
}
Symbol memcmp {
}
Symbol toLEushort {
}
Symbol flCrc16 {
}
Symbol bzero {
}
Symbol flRandByte {
}
Symbol sectorChecksumWrite {
}
Symbol logMsg {
}
Symbol flSocketNoOf {
}
Symbol flBufferOf {
}
Symbol printf {
}
Symbol mountFTL {
}
Symbol spinLockTaskInit {
}
Symbol semBCreate {
}
Symbol sectorChecksum {
}
Symbol memalign {
}
Symbol bcopy {
}
Symbol spinLockTaskTake {
}
Symbol spinLockTaskGive {
}
Symbol sleep {
}
Symbol __assert {
}
Symbol semGive {
}
Symbol tffsWrtLock {
}
Symbol semTake {
}
Symbol tffsWrtUnlock {
}
Symbol formatFTL {
}
Symbol mountValidateSet {
}
Symbol tffsVolStatInit {
}
Symbol vxAtomic32Set {
}
Symbol tffsVolStatShow {
}
Symbol vxAtomic32Get {
}
Symbol noOfTLs {
}
Symbol tlTable {
}
Symbol mountSSFDC {
}
Symbol formatSSFDC {
}
Symbol flIdentifyRegister {
}
Symbol mtdIdentifyTable {
}
Symbol flMap {
}
Symbol flSetPowerOnCallback {
}
Symbol flIntelIdentify {
}
Symbol flNeedVpp {
}
Symbol flDelayLoop {
}
Symbol flDontNeedVpp {
}
Symbol flIntelSize {
}
Symbol flResetCardChanged {
}
Symbol noOfMTDs {
}
Symbol mtdTable {
}
Symbol needCheckRAM {
}
Symbol flWriteProtected {
}
Symbol flSetWindowBusWidth {
}
Symbol flSetWindowSpeed {
}
Symbol flSetWindowSize {
}
Symbol flInitSocket {
}
Symbol flGetMappingContext {
}
Symbol flPollSemId {
}
Symbol tffsDrv {
}
Symbol tffsDevCreate {
}
Symbol semMCreate {
}
Symbol semDelete {
}
Symbol snprintf {
}
Symbol taskSpawn {
}
Symbol tffsDevOptionsSet {
}
Symbol tffsDrvOptionsSet {
}
Symbol tffsRawio {
}
Symbol tffsDiskChangeAnnounce {
}
Symbol tffsDevFormat {
}
Symbol tffsDevStatShow {
}
Symbol sysClkRateGet {
}
Symbol tffsDevRawSpeedShow {
}
Symbol tickGet {
}
Symbol flPollTask {
}
Symbol taskDelay {
}
Symbol flRemoveTimer {
}
Symbol taskDelete {
}
Symbol randBytes {
}
Symbol rand {
}
Symbol flCurrentTime {
}
Symbol time {
}
Symbol localtime {
}
Symbol flCurrentDate {
}
Symbol flAddLongToFarPointer {
}
Symbol copyShort {
}
Symbol copyLong {
}
Symbol tffscmpWords {
}
ObjectFile libbdmTffs.a::fatlite.o {
	NAME Object file fatlite.o from archive libbdmTffs.a
	EXPORTS flFileSysSectorStart flInit flCall flMsecCounter flGetVolume
	IMPORTS .TOC. flTakeMutex errnoSet flSocketSetBusy flNeedVcc flDontNeedVcc flFreeMutex flMediaCheck flMount fromLEushort fromLEulong flFormat malloc free memset strncmp toLEulong flIdentifyFlash flSocketOf flCreateMutex flSysfunInit flRegisterComponents flInitSockets flInitIdentifyTable flInstallTimer noOfDrives flIntervalRoutine
	DECLARES 
	USES 
}
Module fatlite.o {
	OBJECT += libbdmTffs.a::fatlite.o
}
ObjectFile libbdmTffs.a::ftllite.o {
	NAME Object file ftllite.o from archive libbdmTffs.a
	EXPORTS sectorChecksumWrite mountFTL sectorChecksum tffsWrtLock tffsWrtUnlock formatFTL mountValidateSet tffsVolStatInit tffsVolStatShow
	IMPORTS .TOC. memcpy fromLEulong toLEulong memcmp fromLEushort toLEushort flCrc16 errnoSet bzero flRandByte logMsg free malloc flSocketNoOf flBufferOf printf spinLockTaskInit semBCreate memset memalign bcopy spinLockTaskTake spinLockTaskGive sleep __assert semGive semTake vxAtomic32Set flGetVolume vxAtomic32Get
	DECLARES 
	USES 
}
Module ftllite.o {
	OBJECT += libbdmTffs.a::ftllite.o
}
ObjectFile libbdmTffs.a::fltl.o {
	NAME Object file fltl.o from archive libbdmTffs.a
	EXPORTS flMount flFormat
	IMPORTS .TOC. flSocketOf flIdentifyFlash noOfTLs tlTable
	DECLARES 
	USES 
}
Module fltl.o {
	OBJECT += libbdmTffs.a::fltl.o
}
ObjectFile libbdmTffs.a::ssfdc.o {
	NAME Object file ssfdc.o from archive libbdmTffs.a
	EXPORTS mountSSFDC formatSSFDC
	IMPORTS .TOC. memcmp flSocketNoOf flBufferOf malloc free memset
	DECLARES 
	USES 
}
Module ssfdc.o {
	OBJECT += libbdmTffs.a::ssfdc.o
}
ObjectFile libbdmTffs.a::flflash.o {
	NAME Object file flflash.o from archive libbdmTffs.a
	EXPORTS flIdentifyRegister flInitIdentifyTable flIntelIdentify flIntelSize flIdentifyFlash needCheckRAM
	IMPORTS .TOC. flMap memcpy flSetPowerOnCallback flNeedVpp flDelayLoop flDontNeedVpp flResetCardChanged flMediaCheck noOfMTDs mtdTable
	DECLARES mtdIdentifyTable
	USES 
}
Module flflash.o {
	OBJECT += libbdmTffs.a::flflash.o
}
ObjectFile libbdmTffs.a::flsocket.o {
	NAME Object file flsocket.o from archive libbdmTffs.a
	EXPORTS flSocketNoOf flSocketOf flBufferOf flWriteProtected flResetCardChanged flMediaCheck flSetWindowBusWidth flSetWindowSpeed flSetWindowSize flInitSocket flInitSockets noOfDrives flGetMappingContext flMap flSocketSetBusy flNeedVcc flDontNeedVcc flNeedVpp flDontNeedVpp flSetPowerOnCallback flIntervalRoutine
	IMPORTS .TOC. errnoSet malloc
	DECLARES 
	USES 
}
Module flsocket.o {
	OBJECT += libbdmTffs.a::flsocket.o
}
ObjectFile libbdmTffs.a::backgrnd.o {
	NAME Object file backgrnd.o from archive libbdmTffs.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module backgrnd.o {
	OBJECT += libbdmTffs.a::backgrnd.o
}
ObjectFile libbdmTffs.a::tffsDrv.o {
	NAME Object file tffsDrv.o from archive libbdmTffs.a
	EXPORTS tffsDrv tffsDevCreate tffsDevOptionsSet tffsDrvOptionsSet tffsRawio tffsDiskChangeAnnounce tffsDevFormat tffsDevStatShow tffsDevRawSpeedShow
	IMPORTS .TOC. semBCreate flInit semGive fromLEushort fromLEulong flFileSysSectorStart vxAtomic32Set malloc bzero flCall semMCreate free errnoSet semDelete snprintf taskSpawn semTake sysClkRateGet printf vxAtomic32Get memset tickGet
	DECLARES flPollSemId
	USES 
}
Module tffsDrv.o {
	OBJECT += libbdmTffs.a::tffsDrv.o
}
ObjectFile libbdmTffs.a::tffsLib.o {
	NAME Object file tffsLib.o from archive libbdmTffs.a
	EXPORTS flCreateMutex flTakeMutex flFreeMutex flSysfunInit flPollTask flInstallTimer flRemoveTimer flRandByte flCurrentTime flCurrentDate flAddLongToFarPointer
	IMPORTS .TOC. semMCreate semTake semGive sysClkRateGet flPollSemId semDelete taskDelay taskSpawn taskDelete randBytes rand time localtime
	DECLARES 
	USES 
}
Module tffsLib.o {
	OBJECT += libbdmTffs.a::tffsLib.o
}
ObjectFile libbdmTffs.a::flbase.o {
	NAME Object file flbase.o from archive libbdmTffs.a
	EXPORTS toLEushort fromLEushort toLEulong fromLEulong copyShort copyLong tffscmpWords flCrc16
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module flbase.o {
	OBJECT += libbdmTffs.a::flbase.o
}
Library libbdmTffs.a {
	MODULES libbdmTffs.a::fatlite.o libbdmTffs.a::ftllite.o libbdmTffs.a::fltl.o libbdmTffs.a::ssfdc.o libbdmTffs.a::flflash.o libbdmTffs.a::flsocket.o libbdmTffs.a::backgrnd.o libbdmTffs.a::tffsDrv.o libbdmTffs.a::tffsLib.o libbdmTffs.a::flbase.o
}
