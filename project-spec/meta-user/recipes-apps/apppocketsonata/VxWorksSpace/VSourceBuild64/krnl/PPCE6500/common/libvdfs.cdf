Symbol .TOC. {
}
Symbol xbdIoctl {
}
Symbol errnoSet {
}
Symbol semTake {
}
Symbol lstDelete {
}
Symbol lstAdd {
}
Symbol semGive {
}
Symbol semDelete {
}
Symbol bio_free {
}
Symbol free {
}
Symbol bzero {
}
Symbol selWakeupListLen {
}
Symbol selWakeupListTerm {
}
Symbol xbdRoot {
}
Symbol lstFirst {
}
Symbol lstNext {
}
Symbol malloc {
}
Symbol semMCreate {
}
Symbol vdFsDevInit {
}
Symbol vdFsDrvNum {
}
Symbol xbdBlockSize {
}
Symbol xbdNBlocks {
}
Symbol iosLock {
}
Symbol iosDevReplaceExt {
}
Symbol iosDevDelCallback {
}
Symbol xbdEventCategory {
}
Symbol xbdEventRemove {
}
Symbol erfHandlerRegister {
}
Symbol xbdEventMediaChanged {
}
Symbol erfHandlerUnregister {
}
Symbol iosUnlock {
}
Symbol fsPathAddedEventRaise {
}
Symbol iosDevDelete {
}
Symbol iosDevSuspend {
}
Symbol lstGet {
}
Symbol printErr {
}
Symbol semCCreate {
}
Symbol semBCreate {
}
Symbol bio_alloc {
}
Symbol calloc {
}
Symbol vdFsAioXferQSizeSet {
}
Symbol ioctl {
}
Symbol vdFsAioXferQSelect {
}
Symbol select {
}
Symbol vdFsAioXferQEntryTake {
}
Symbol bcopy {
}
Symbol vdFsAioXferQSizeGet {
}
Symbol vdFsAioXferQNonEmpty {
}
Symbol vdFsMonitorDevCreate {
}
Symbol vdFsPartMount {
}
Symbol strncpy {
}
Symbol open {
}
Symbol fsPathAddedEventSetup {
}
Symbol close {
}
Symbol fsWaitForPath {
}
Symbol vdFsDiskProbe {
}
Symbol devName {
}
Symbol strcmp {
}
Symbol xbdStrategy {
}
Symbol vdFsInit {
}
Symbol iosDrvInstall {
}
Symbol lstInit {
}
Symbol vdFsPrioUsecTimeout {
}
Symbol sysTimestamp64Freq {
}
Symbol fsmProbeInstall {
}
Symbol _func_rawFsDevInitRtn {
}
Symbol iosDrvRemove {
}
Symbol vdFsVolUnmount {
}
Symbol __errno {
}
Symbol selNodeAdd {
}
Symbol selWakeup {
}
Symbol selNodeDelete {
}
Symbol xbdSize {
}
Symbol selWakeupListInit {
}
Symbol selWakeupAll {
}
Symbol sysTimestamp64Lock {
}
Symbol vdFsPrioSchedEnable {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol sysUsDelay {
}
Symbol taskPriorityGet {
}
ObjectFile libvdfs.a::vdFsLib.o {
	NAME Object file vdFsLib.o from archive libvdfs.a
	EXPORTS vdFsDevInit vdFsDrvNum vdFsAioXferQSizeSet vdFsAioXferQSelect vdFsAioXferQEntryTake vdFsAioXferQSizeGet vdFsAioXferQNonEmpty vdFsMonitorDevCreate vdFsPartMount vdFsDiskProbe vdFsInit vdFsVolUnmount
	IMPORTS .TOC. xbdIoctl errnoSet semTake lstDelete lstAdd semGive semDelete bio_free free bzero selWakeupListLen selWakeupListTerm xbdRoot lstFirst lstNext malloc semMCreate xbdBlockSize xbdNBlocks iosLock iosDevReplaceExt iosDevDelCallback xbdEventCategory xbdEventRemove erfHandlerRegister xbdEventMediaChanged erfHandlerUnregister iosUnlock fsPathAddedEventRaise iosDevDelete iosDevSuspend lstGet printErr semCCreate semBCreate bio_alloc calloc ioctl select bcopy strncpy open fsPathAddedEventSetup close fsWaitForPath devName strcmp xbdStrategy iosDrvInstall lstInit vdFsPrioUsecTimeout sysTimestamp64Freq fsmProbeInstall _func_rawFsDevInitRtn iosDrvRemove __errno selNodeAdd selWakeup selNodeDelete xbdSize selWakeupListInit selWakeupAll sysTimestamp64Lock vdFsPrioSchedEnable sysClkRateGet taskDelay sysUsDelay taskPriorityGet
	DECLARES 
	USES 
}
Module vdFsLib.o {
	OBJECT += libvdfs.a::vdFsLib.o
}
Library libvdfs.a {
	MODULES libvdfs.a::vdFsLib.o
}
Symbol .TOC. {
}
Symbol xbdIoctl {
}
Symbol errnoSet {
}
Symbol semTake {
}
Symbol lstDelete {
}
Symbol lstAdd {
}
Symbol semGive {
}
Symbol semDelete {
}
Symbol bio_free {
}
Symbol free {
}
Symbol bzero {
}
Symbol selWakeupListLen {
}
Symbol selWakeupListTerm {
}
Symbol xbdRoot {
}
Symbol lstFirst {
}
Symbol lstNext {
}
Symbol malloc {
}
Symbol semMCreate {
}
Symbol vdFsDevInit {
}
Symbol vdFsDrvNum {
}
Symbol xbdBlockSize {
}
Symbol xbdNBlocks {
}
Symbol iosLock {
}
Symbol iosDevReplaceExt {
}
Symbol iosDevDelCallback {
}
Symbol xbdEventCategory {
}
Symbol xbdEventRemove {
}
Symbol erfHandlerRegister {
}
Symbol xbdEventMediaChanged {
}
Symbol erfHandlerUnregister {
}
Symbol iosUnlock {
}
Symbol fsPathAddedEventRaise {
}
Symbol iosDevDelete {
}
Symbol iosDevSuspend {
}
Symbol lstGet {
}
Symbol printErr {
}
Symbol semCCreate {
}
Symbol semBCreate {
}
Symbol bio_alloc {
}
Symbol calloc {
}
Symbol vdFsAioXferQSizeSet {
}
Symbol ioctl {
}
Symbol vdFsAioXferQSelect {
}
Symbol select {
}
Symbol vdFsAioXferQEntryTake {
}
Symbol bcopy {
}
Symbol vdFsAioXferQSizeGet {
}
Symbol vdFsAioXferQNonEmpty {
}
Symbol vdFsMonitorDevCreate {
}
Symbol vdFsPartMount {
}
Symbol strncpy {
}
Symbol open {
}
Symbol fsPathAddedEventSetup {
}
Symbol close {
}
Symbol fsWaitForPath {
}
Symbol vdFsDiskProbe {
}
Symbol devName {
}
Symbol strcmp {
}
Symbol xbdStrategy {
}
Symbol vdFsInit {
}
Symbol iosDrvInstall {
}
Symbol lstInit {
}
Symbol vdFsPrioUsecTimeout {
}
Symbol sysTimestamp64Freq {
}
Symbol fsmProbeInstall {
}
Symbol _func_rawFsDevInitRtn {
}
Symbol iosDrvRemove {
}
Symbol vdFsVolUnmount {
}
Symbol __errno {
}
Symbol selNodeAdd {
}
Symbol selWakeup {
}
Symbol selNodeDelete {
}
Symbol xbdSize {
}
Symbol selWakeupListInit {
}
Symbol selWakeupAll {
}
Symbol sysTimestamp64Lock {
}
Symbol vdFsPrioSchedEnable {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol sysUsDelay {
}
Symbol taskPriorityGet {
}
ObjectFile libvdfs.a::vdFsLib.o {
	NAME Object file vdFsLib.o from archive libvdfs.a
	EXPORTS vdFsDevInit vdFsDrvNum vdFsAioXferQSizeSet vdFsAioXferQSelect vdFsAioXferQEntryTake vdFsAioXferQSizeGet vdFsAioXferQNonEmpty vdFsMonitorDevCreate vdFsPartMount vdFsDiskProbe vdFsInit vdFsVolUnmount
	IMPORTS .TOC. xbdIoctl errnoSet semTake lstDelete lstAdd semGive semDelete bio_free free bzero selWakeupListLen selWakeupListTerm xbdRoot lstFirst lstNext malloc semMCreate xbdBlockSize xbdNBlocks iosLock iosDevReplaceExt iosDevDelCallback xbdEventCategory xbdEventRemove erfHandlerRegister xbdEventMediaChanged erfHandlerUnregister iosUnlock fsPathAddedEventRaise iosDevDelete iosDevSuspend lstGet printErr semCCreate semBCreate bio_alloc calloc ioctl select bcopy strncpy open fsPathAddedEventSetup close fsWaitForPath devName strcmp xbdStrategy iosDrvInstall lstInit vdFsPrioUsecTimeout sysTimestamp64Freq fsmProbeInstall _func_rawFsDevInitRtn iosDrvRemove __errno selNodeAdd selWakeup selNodeDelete xbdSize selWakeupListInit selWakeupAll sysTimestamp64Lock vdFsPrioSchedEnable sysClkRateGet taskDelay sysUsDelay taskPriorityGet
	DECLARES 
	USES 
}
Module vdFsLib.o {
	OBJECT += libvdfs.a::vdFsLib.o
}
Library libvdfs.a {
	MODULES libvdfs.a::vdFsLib.o
}
Symbol .TOC. {
}
Symbol xbdIoctl {
}
Symbol errnoSet {
}
Symbol semTake {
}
Symbol lstDelete {
}
Symbol lstAdd {
}
Symbol semGive {
}
Symbol semDelete {
}
Symbol bio_free {
}
Symbol free {
}
Symbol bzero {
}
Symbol selWakeupListLen {
}
Symbol selWakeupListTerm {
}
Symbol xbdRoot {
}
Symbol lstFirst {
}
Symbol lstNext {
}
Symbol malloc {
}
Symbol semMCreate {
}
Symbol vdFsDevInit {
}
Symbol vdFsDrvNum {
}
Symbol xbdBlockSize {
}
Symbol xbdNBlocks {
}
Symbol iosLock {
}
Symbol iosDevReplaceExt {
}
Symbol iosDevDelCallback {
}
Symbol xbdEventCategory {
}
Symbol xbdEventRemove {
}
Symbol erfHandlerRegister {
}
Symbol xbdEventMediaChanged {
}
Symbol erfHandlerUnregister {
}
Symbol iosUnlock {
}
Symbol fsPathAddedEventRaise {
}
Symbol iosDevDelete {
}
Symbol iosDevSuspend {
}
Symbol lstGet {
}
Symbol printErr {
}
Symbol semCCreate {
}
Symbol semBCreate {
}
Symbol bio_alloc {
}
Symbol calloc {
}
Symbol vdFsAioXferQSizeSet {
}
Symbol ioctl {
}
Symbol vdFsAioXferQSelect {
}
Symbol select {
}
Symbol vdFsAioXferQEntryTake {
}
Symbol bcopy {
}
Symbol vdFsAioXferQSizeGet {
}
Symbol vdFsAioXferQNonEmpty {
}
Symbol vdFsMonitorDevCreate {
}
Symbol vdFsPartMount {
}
Symbol strncpy {
}
Symbol open {
}
Symbol fsPathAddedEventSetup {
}
Symbol close {
}
Symbol fsWaitForPath {
}
Symbol vdFsDiskProbe {
}
Symbol devName {
}
Symbol strcmp {
}
Symbol xbdStrategy {
}
Symbol vdFsInit {
}
Symbol iosDrvInstall {
}
Symbol lstInit {
}
Symbol vdFsPrioUsecTimeout {
}
Symbol sysTimestamp64Freq {
}
Symbol fsmProbeInstall {
}
Symbol _func_rawFsDevInitRtn {
}
Symbol iosDrvRemove {
}
Symbol vdFsVolUnmount {
}
Symbol __errno {
}
Symbol selNodeAdd {
}
Symbol selWakeup {
}
Symbol selNodeDelete {
}
Symbol xbdSize {
}
Symbol selWakeupListInit {
}
Symbol selWakeupAll {
}
Symbol sysTimestamp64Lock {
}
Symbol vdFsPrioSchedEnable {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol sysUsDelay {
}
Symbol taskPriorityGet {
}
ObjectFile libvdfs.a::vdFsLib.o {
	NAME Object file vdFsLib.o from archive libvdfs.a
	EXPORTS vdFsDevInit vdFsDrvNum vdFsAioXferQSizeSet vdFsAioXferQSelect vdFsAioXferQEntryTake vdFsAioXferQSizeGet vdFsAioXferQNonEmpty vdFsMonitorDevCreate vdFsPartMount vdFsDiskProbe vdFsInit vdFsVolUnmount
	IMPORTS .TOC. xbdIoctl errnoSet semTake lstDelete lstAdd semGive semDelete bio_free free bzero selWakeupListLen selWakeupListTerm xbdRoot lstFirst lstNext malloc semMCreate xbdBlockSize xbdNBlocks iosLock iosDevReplaceExt iosDevDelCallback xbdEventCategory xbdEventRemove erfHandlerRegister xbdEventMediaChanged erfHandlerUnregister iosUnlock fsPathAddedEventRaise iosDevDelete iosDevSuspend lstGet printErr semCCreate semBCreate bio_alloc calloc ioctl select bcopy strncpy open fsPathAddedEventSetup close fsWaitForPath devName strcmp xbdStrategy iosDrvInstall lstInit vdFsPrioUsecTimeout sysTimestamp64Freq fsmProbeInstall _func_rawFsDevInitRtn iosDrvRemove __errno selNodeAdd selWakeup selNodeDelete xbdSize selWakeupListInit selWakeupAll sysTimestamp64Lock vdFsPrioSchedEnable sysClkRateGet taskDelay sysUsDelay taskPriorityGet
	DECLARES 
	USES 
}
Module vdFsLib.o {
	OBJECT += libvdfs.a::vdFsLib.o
}
Library libvdfs.a {
	MODULES libvdfs.a::vdFsLib.o
}
