Symbol kernelLockInit {
}
Symbol .TOC. {
}
Symbol kernelStateLock {
}
Symbol kernelLockOwnedByMe {
}
Symbol intCpuMicroLock {
}
Symbol vxCpuIndexGet {
}
Symbol intCpuMicroUnlock {
}
Symbol kernelLockOwnerGet {
}
Symbol spinLockIsrNdInit {
}
Symbol spinlockIsrNdInit {
}
Symbol spinLockIsrInit {
}
Symbol intContext {
}
Symbol setjmp {
}
Symbol edrErrorInjectStub {
}
Symbol edrInterruptFatalPolicyHandler {
}
Symbol vxCpuConfigured {
}
Symbol spinLockIsrTake {
}
Symbol intCpuLock {
}
Symbol vxAtomic32Get {
}
Symbol intCpuUnlock {
}
Symbol vxKernelVars {
}
Symbol vxAtomic32Cas {
}
Symbol vxAtomic32Set {
}
Symbol rtSpinlockMaxSpin {
}
Symbol vxAtomic32Add {
}
Symbol vxAtomic32Sub {
}
Symbol intCpuEnable {
}
Symbol edrSystemFatalPolicyHandler {
}
Symbol reboot {
}
Symbol spinLockIsrGive {
}
Symbol taskCpuUnlockInternal {
}
Symbol spinLockTaskInit {
}
Symbol spinLockTaskTake {
}
Symbol evtAction {
}
Symbol vxAtomicInc {
}
Symbol vxAtomicGet {
}
Symbol eventPointSwHandle {
}
Symbol spinLockTaskGive {
}
Symbol vxAtomicSet {
}
Symbol spinLockIsrHeld {
}
Symbol spinLockRestrict {
}
Symbol spinLockDbgDisable {
}
ObjectFile libsplDbg.a::kernelLockLib.o {
	NAME Object file kernelLockLib.o from archive libsplDbg.a
	EXPORTS kernelLockInit kernelStateLock kernelLockOwnedByMe kernelLockOwnerGet
	IMPORTS .TOC. intCpuMicroLock vxCpuIndexGet intCpuMicroUnlock
	DECLARES 
	USES 
}
Module kernelLockLib.o {
	OBJECT += libsplDbg.a::kernelLockLib.o
}
ObjectFile libsplDbg.a::spinLockIsrNdLib.o {
	NAME Object file spinLockIsrNdLib.o from archive libsplDbg.a
	EXPORTS spinLockIsrNdInit spinlockIsrNdInit
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module spinLockIsrNdLib.o {
	OBJECT += libsplDbg.a::spinLockIsrNdLib.o
}
ObjectFile libsplDbg.a::spinLockSmpDbgLib.o {
	NAME Object file spinLockSmpDbgLib.o from archive libsplDbg.a
	EXPORTS spinLockIsrInit spinLockIsrTake rtSpinlockMaxSpin spinLockIsrGive spinLockTaskInit spinLockTaskTake spinLockTaskGive spinLockIsrHeld spinLockRestrict spinLockDbgDisable
	IMPORTS .TOC. intContext setjmp edrErrorInjectStub edrInterruptFatalPolicyHandler vxCpuConfigured intCpuLock vxCpuIndexGet vxAtomic32Get intCpuUnlock vxKernelVars vxAtomic32Cas vxAtomic32Set vxAtomic32Add vxAtomic32Sub intCpuEnable edrSystemFatalPolicyHandler reboot kernelLockOwnerGet taskCpuUnlockInternal intCpuMicroLock intCpuMicroUnlock evtAction vxAtomicInc vxAtomicGet eventPointSwHandle vxAtomicSet
	DECLARES 
	USES 
}
Module spinLockSmpDbgLib.o {
	OBJECT += libsplDbg.a::spinLockSmpDbgLib.o
}
Library libsplDbg.a {
	MODULES libsplDbg.a::kernelLockLib.o libsplDbg.a::spinLockIsrNdLib.o libsplDbg.a::spinLockSmpDbgLib.o
}
Symbol kernelLockInit {
}
Symbol .TOC. {
}
Symbol kernelStateLock {
}
Symbol kernelLockOwnedByMe {
}
Symbol intCpuMicroLock {
}
Symbol vxCpuIndexGet {
}
Symbol intCpuMicroUnlock {
}
Symbol kernelLockOwnerGet {
}
Symbol spinLockIsrNdInit {
}
Symbol spinlockIsrNdInit {
}
Symbol spinLockIsrInit {
}
Symbol intContext {
}
Symbol setjmp {
}
Symbol edrErrorInjectStub {
}
Symbol edrInterruptFatalPolicyHandler {
}
Symbol vxCpuConfigured {
}
Symbol spinLockIsrTake {
}
Symbol intCpuLock {
}
Symbol vxAtomic32Get {
}
Symbol intCpuUnlock {
}
Symbol vxKernelVars {
}
Symbol vxAtomic32Cas {
}
Symbol vxAtomic32Set {
}
Symbol rtSpinlockMaxSpin {
}
Symbol vxAtomic32Add {
}
Symbol vxAtomic32Sub {
}
Symbol intCpuEnable {
}
Symbol edrSystemFatalPolicyHandler {
}
Symbol reboot {
}
Symbol spinLockIsrGive {
}
Symbol taskCpuUnlockInternal {
}
Symbol spinLockTaskInit {
}
Symbol spinLockTaskTake {
}
Symbol evtAction {
}
Symbol vxAtomicInc {
}
Symbol vxAtomicGet {
}
Symbol eventPointSwHandle {
}
Symbol spinLockTaskGive {
}
Symbol vxAtomicSet {
}
Symbol spinLockIsrHeld {
}
Symbol spinLockRestrict {
}
Symbol spinLockDbgDisable {
}
ObjectFile libsplDbg.a::kernelLockLib.o {
	NAME Object file kernelLockLib.o from archive libsplDbg.a
	EXPORTS kernelLockInit kernelStateLock kernelLockOwnedByMe kernelLockOwnerGet
	IMPORTS .TOC. intCpuMicroLock vxCpuIndexGet intCpuMicroUnlock
	DECLARES 
	USES 
}
Module kernelLockLib.o {
	OBJECT += libsplDbg.a::kernelLockLib.o
}
ObjectFile libsplDbg.a::spinLockIsrNdLib.o {
	NAME Object file spinLockIsrNdLib.o from archive libsplDbg.a
	EXPORTS spinLockIsrNdInit spinlockIsrNdInit
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module spinLockIsrNdLib.o {
	OBJECT += libsplDbg.a::spinLockIsrNdLib.o
}
ObjectFile libsplDbg.a::spinLockSmpDbgLib.o {
	NAME Object file spinLockSmpDbgLib.o from archive libsplDbg.a
	EXPORTS spinLockIsrInit spinLockIsrTake rtSpinlockMaxSpin spinLockIsrGive spinLockTaskInit spinLockTaskTake spinLockTaskGive spinLockIsrHeld spinLockRestrict spinLockDbgDisable
	IMPORTS .TOC. intContext setjmp edrErrorInjectStub edrInterruptFatalPolicyHandler vxCpuConfigured intCpuLock vxCpuIndexGet vxAtomic32Get intCpuUnlock vxKernelVars vxAtomic32Cas vxAtomic32Set vxAtomic32Add vxAtomic32Sub intCpuEnable edrSystemFatalPolicyHandler reboot kernelLockOwnerGet taskCpuUnlockInternal intCpuMicroLock intCpuMicroUnlock evtAction vxAtomicInc vxAtomicGet eventPointSwHandle vxAtomicSet
	DECLARES 
	USES 
}
Module spinLockSmpDbgLib.o {
	OBJECT += libsplDbg.a::spinLockSmpDbgLib.o
}
Library libsplDbg.a {
	MODULES libsplDbg.a::kernelLockLib.o libsplDbg.a::spinLockIsrNdLib.o libsplDbg.a::spinLockSmpDbgLib.o
}
Symbol kernelLockInit {
}
Symbol .TOC. {
}
Symbol kernelStateLock {
}
Symbol kernelLockOwnedByMe {
}
Symbol intCpuMicroLock {
}
Symbol vxCpuIndexGet {
}
Symbol intCpuMicroUnlock {
}
Symbol kernelLockOwnerGet {
}
Symbol spinLockIsrNdInit {
}
Symbol spinlockIsrNdInit {
}
Symbol spinLockIsrInit {
}
Symbol intContext {
}
Symbol setjmp {
}
Symbol edrErrorInjectStub {
}
Symbol edrInterruptFatalPolicyHandler {
}
Symbol vxCpuConfigured {
}
Symbol spinLockIsrTake {
}
Symbol intCpuLock {
}
Symbol vxAtomic32Get {
}
Symbol intCpuUnlock {
}
Symbol vxKernelVars {
}
Symbol vxAtomic32Cas {
}
Symbol vxAtomic32Set {
}
Symbol rtSpinlockMaxSpin {
}
Symbol vxAtomic32Add {
}
Symbol vxAtomic32Sub {
}
Symbol intCpuEnable {
}
Symbol edrSystemFatalPolicyHandler {
}
Symbol reboot {
}
Symbol spinLockIsrGive {
}
Symbol taskCpuUnlockInternal {
}
Symbol spinLockTaskInit {
}
Symbol spinLockTaskTake {
}
Symbol evtAction {
}
Symbol vxAtomicInc {
}
Symbol vxAtomicGet {
}
Symbol eventPointSwHandle {
}
Symbol spinLockTaskGive {
}
Symbol vxAtomicSet {
}
Symbol spinLockIsrHeld {
}
Symbol spinLockRestrict {
}
Symbol spinLockDbgDisable {
}
ObjectFile libsplDbg.a::kernelLockLib.o {
	NAME Object file kernelLockLib.o from archive libsplDbg.a
	EXPORTS kernelLockInit kernelStateLock kernelLockOwnedByMe kernelLockOwnerGet
	IMPORTS .TOC. intCpuMicroLock vxCpuIndexGet intCpuMicroUnlock
	DECLARES 
	USES 
}
Module kernelLockLib.o {
	OBJECT += libsplDbg.a::kernelLockLib.o
}
ObjectFile libsplDbg.a::spinLockIsrNdLib.o {
	NAME Object file spinLockIsrNdLib.o from archive libsplDbg.a
	EXPORTS spinLockIsrNdInit spinlockIsrNdInit
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module spinLockIsrNdLib.o {
	OBJECT += libsplDbg.a::spinLockIsrNdLib.o
}
ObjectFile libsplDbg.a::spinLockSmpDbgLib.o {
	NAME Object file spinLockSmpDbgLib.o from archive libsplDbg.a
	EXPORTS spinLockIsrInit spinLockIsrTake rtSpinlockMaxSpin spinLockIsrGive spinLockTaskInit spinLockTaskTake spinLockTaskGive spinLockIsrHeld spinLockRestrict spinLockDbgDisable
	IMPORTS .TOC. intContext setjmp edrErrorInjectStub edrInterruptFatalPolicyHandler vxCpuConfigured intCpuLock vxCpuIndexGet vxAtomic32Get intCpuUnlock vxKernelVars vxAtomic32Cas vxAtomic32Set vxAtomic32Add vxAtomic32Sub intCpuEnable edrSystemFatalPolicyHandler reboot kernelLockOwnerGet taskCpuUnlockInternal intCpuMicroLock intCpuMicroUnlock evtAction vxAtomicInc vxAtomicGet eventPointSwHandle vxAtomicSet
	DECLARES 
	USES 
}
Module spinLockSmpDbgLib.o {
	OBJECT += libsplDbg.a::spinLockSmpDbgLib.o
}
Library libsplDbg.a {
	MODULES libsplDbg.a::kernelLockLib.o libsplDbg.a::spinLockIsrNdLib.o libsplDbg.a::spinLockSmpDbgLib.o
}
