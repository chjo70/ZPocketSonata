Symbol jobQueueLibInit {
}
Symbol .TOC. {
}
Symbol jobQueuePost {
}
Symbol spinLockIsrTake {
}
Symbol spinLockIsrGive {
}
Symbol semBGiveScalable {
}
Symbol jobQueueStdPost {
}
Symbol jobQueueProcess {
}
Symbol taskIdSelf {
}
Symbol semBTakeScalable {
}
Symbol jobQueuePriorityMask {
}
Symbol jobQueueInit {
}
Symbol memset {
}
Symbol spinLockIsrInit {
}
Symbol semBInitialize {
}
Symbol jobQueueCreate {
}
Symbol memalign {
}
Symbol free {
}
Symbol jobQueueTask {
}
Symbol jobQueueStdPoolInit {
}
Symbol jobQueueStdJobsAlloc {
}
Symbol _func_netDaemonIxToQId {
}
Symbol _func_netDaemonQIdToIx {
}
Symbol jobQueueProcessFunc {
}
Symbol jobQueueUtilInit {
}
Symbol jobQueueProcessWrapper {
}
Symbol jobQueueQuit {
}
Symbol longjmp {
}
Symbol setjmp {
}
Symbol jobQueueTerminate {
}
Symbol semTerminate {
}
Symbol jobQueueDelete {
}
Symbol jobQueueStdPoolJobsFree {
}
Symbol jobQueueIsRunning {
}
ObjectFile libjobqueue.a::jobQueueLib.o {
	NAME Object file jobQueueLib.o from archive libjobqueue.a
	EXPORTS jobQueueLibInit jobQueuePost jobQueueStdPost jobQueueProcess jobQueuePriorityMask jobQueueInit jobQueueCreate jobQueueTask jobQueueStdPoolInit jobQueueStdJobsAlloc jobQueueProcessFunc
	IMPORTS .TOC. spinLockIsrTake spinLockIsrGive semBGiveScalable taskIdSelf semBTakeScalable memset spinLockIsrInit semBInitialize memalign free
	DECLARES _func_netDaemonIxToQId _func_netDaemonQIdToIx
	USES 
}
Module jobQueueLib.o {
	OBJECT += libjobqueue.a::jobQueueLib.o
}
ObjectFile libjobqueue.a::jobQueueUtilLib.o {
	NAME Object file jobQueueUtilLib.o from archive libjobqueue.a
	EXPORTS jobQueueUtilInit jobQueueProcessWrapper jobQueueQuit jobQueueTerminate jobQueueDelete jobQueueStdPoolJobsFree jobQueueIsRunning
	IMPORTS .TOC. jobQueueProcessFunc spinLockIsrTake spinLockIsrGive jobQueuePost longjmp setjmp jobQueueProcess semTerminate free
	DECLARES 
	USES 
}
Module jobQueueUtilLib.o {
	OBJECT += libjobqueue.a::jobQueueUtilLib.o
}
Library libjobqueue.a {
	MODULES libjobqueue.a::jobQueueLib.o libjobqueue.a::jobQueueUtilLib.o
}
Symbol jobQueueLibInit {
}
Symbol .TOC. {
}
Symbol jobQueuePost {
}
Symbol spinLockIsrTake {
}
Symbol spinLockIsrGive {
}
Symbol semBGiveScalable {
}
Symbol jobQueueStdPost {
}
Symbol jobQueueProcess {
}
Symbol taskIdSelf {
}
Symbol semBTakeScalable {
}
Symbol jobQueuePriorityMask {
}
Symbol jobQueueInit {
}
Symbol memset {
}
Symbol spinLockIsrInit {
}
Symbol semBInitialize {
}
Symbol jobQueueCreate {
}
Symbol memalign {
}
Symbol free {
}
Symbol jobQueueTask {
}
Symbol jobQueueStdPoolInit {
}
Symbol jobQueueStdJobsAlloc {
}
Symbol _func_netDaemonIxToQId {
}
Symbol _func_netDaemonQIdToIx {
}
Symbol jobQueueProcessFunc {
}
Symbol jobQueueUtilInit {
}
Symbol jobQueueProcessWrapper {
}
Symbol jobQueueQuit {
}
Symbol longjmp {
}
Symbol setjmp {
}
Symbol jobQueueTerminate {
}
Symbol semTerminate {
}
Symbol jobQueueDelete {
}
Symbol jobQueueStdPoolJobsFree {
}
Symbol jobQueueIsRunning {
}
ObjectFile libjobqueue.a::jobQueueLib.o {
	NAME Object file jobQueueLib.o from archive libjobqueue.a
	EXPORTS jobQueueLibInit jobQueuePost jobQueueStdPost jobQueueProcess jobQueuePriorityMask jobQueueInit jobQueueCreate jobQueueTask jobQueueStdPoolInit jobQueueStdJobsAlloc jobQueueProcessFunc
	IMPORTS .TOC. spinLockIsrTake spinLockIsrGive semBGiveScalable taskIdSelf semBTakeScalable memset spinLockIsrInit semBInitialize memalign free
	DECLARES _func_netDaemonIxToQId _func_netDaemonQIdToIx
	USES 
}
Module jobQueueLib.o {
	OBJECT += libjobqueue.a::jobQueueLib.o
}
ObjectFile libjobqueue.a::jobQueueUtilLib.o {
	NAME Object file jobQueueUtilLib.o from archive libjobqueue.a
	EXPORTS jobQueueUtilInit jobQueueProcessWrapper jobQueueQuit jobQueueTerminate jobQueueDelete jobQueueStdPoolJobsFree jobQueueIsRunning
	IMPORTS .TOC. jobQueueProcessFunc spinLockIsrTake spinLockIsrGive jobQueuePost longjmp setjmp jobQueueProcess semTerminate free
	DECLARES 
	USES 
}
Module jobQueueUtilLib.o {
	OBJECT += libjobqueue.a::jobQueueUtilLib.o
}
Library libjobqueue.a {
	MODULES libjobqueue.a::jobQueueLib.o libjobqueue.a::jobQueueUtilLib.o
}
Symbol jobQueueLibInit {
}
Symbol .TOC. {
}
Symbol jobQueuePost {
}
Symbol spinLockIsrTake {
}
Symbol spinLockIsrGive {
}
Symbol semBGiveScalable {
}
Symbol jobQueueStdPost {
}
Symbol jobQueueProcess {
}
Symbol taskIdSelf {
}
Symbol semBTakeScalable {
}
Symbol jobQueuePriorityMask {
}
Symbol jobQueueInit {
}
Symbol memset {
}
Symbol spinLockIsrInit {
}
Symbol semBInitialize {
}
Symbol jobQueueCreate {
}
Symbol memalign {
}
Symbol free {
}
Symbol jobQueueTask {
}
Symbol jobQueueStdPoolInit {
}
Symbol jobQueueStdJobsAlloc {
}
Symbol _func_netDaemonIxToQId {
}
Symbol _func_netDaemonQIdToIx {
}
Symbol jobQueueProcessFunc {
}
Symbol jobQueueUtilInit {
}
Symbol jobQueueProcessWrapper {
}
Symbol jobQueueQuit {
}
Symbol longjmp {
}
Symbol setjmp {
}
Symbol jobQueueTerminate {
}
Symbol semTerminate {
}
Symbol jobQueueDelete {
}
Symbol jobQueueStdPoolJobsFree {
}
Symbol jobQueueIsRunning {
}
ObjectFile libjobqueue.a::jobQueueLib.o {
	NAME Object file jobQueueLib.o from archive libjobqueue.a
	EXPORTS jobQueueLibInit jobQueuePost jobQueueStdPost jobQueueProcess jobQueuePriorityMask jobQueueInit jobQueueCreate jobQueueTask jobQueueStdPoolInit jobQueueStdJobsAlloc jobQueueProcessFunc
	IMPORTS .TOC. spinLockIsrTake spinLockIsrGive semBGiveScalable taskIdSelf semBTakeScalable memset spinLockIsrInit semBInitialize memalign free
	DECLARES _func_netDaemonIxToQId _func_netDaemonQIdToIx
	USES 
}
Module jobQueueLib.o {
	OBJECT += libjobqueue.a::jobQueueLib.o
}
ObjectFile libjobqueue.a::jobQueueUtilLib.o {
	NAME Object file jobQueueUtilLib.o from archive libjobqueue.a
	EXPORTS jobQueueUtilInit jobQueueProcessWrapper jobQueueQuit jobQueueTerminate jobQueueDelete jobQueueStdPoolJobsFree jobQueueIsRunning
	IMPORTS .TOC. jobQueueProcessFunc spinLockIsrTake spinLockIsrGive jobQueuePost longjmp setjmp jobQueueProcess semTerminate free
	DECLARES 
	USES 
}
Module jobQueueUtilLib.o {
	OBJECT += libjobqueue.a::jobQueueUtilLib.o
}
Library libjobqueue.a {
	MODULES libjobqueue.a::jobQueueLib.o libjobqueue.a::jobQueueUtilLib.o
}
