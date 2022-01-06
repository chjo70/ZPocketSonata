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
Symbol vxCpuConfigured {
}
Symbol spinLockIsrTake {
}
Symbol intCpuLock {
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
Symbol intCpuUnlock {
}
Symbol vxAtomic32Sub {
}
Symbol spinLockIsrHeld {
}
Symbol spinLockRestrict {
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
Symbol spinLockDbgDisable {
}
Symbol spinLockNdTimedInit {
}
Symbol spinLockNdTimedTake {
}
Symbol sysClkRateGet {
}
Symbol vxAbsTicksGet {
}
Symbol atomic32Get {
}
Symbol atomic32Cas {
}
Symbol errnoSet {
}
Symbol spinLockNdTimedGive {
}
Symbol spinLockNdTimedPrevOwnerGet {
}
ObjectFile libspl.a::kernelLockLib.o {
	NAME Object file kernelLockLib.o from archive libspl.a
	EXPORTS kernelLockInit kernelStateLock kernelLockOwnedByMe kernelLockOwnerGet
	IMPORTS .TOC. intCpuMicroLock vxCpuIndexGet intCpuMicroUnlock
	DECLARES 
	USES 
}
Module kernelLockLib.o {
	OBJECT += libspl.a::kernelLockLib.o
}
ObjectFile libspl.a::spinLockIsrNdLib.o {
	NAME Object file spinLockIsrNdLib.o from archive libspl.a
	EXPORTS spinLockIsrNdInit spinlockIsrNdInit
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module spinLockIsrNdLib.o {
	OBJECT += libspl.a::spinLockIsrNdLib.o
}
ObjectFile libspl.a::spinLockSmpLib.o {
	NAME Object file spinLockSmpLib.o from archive libspl.a
	EXPORTS spinLockIsrInit spinLockIsrTake rtSpinlockMaxSpin spinLockIsrHeld spinLockRestrict spinLockIsrGive spinLockTaskInit spinLockTaskTake spinLockTaskGive spinLockDbgDisable
	IMPORTS .TOC. vxCpuConfigured intCpuLock vxCpuIndexGet vxKernelVars vxAtomic32Cas vxAtomic32Set vxAtomic32Add intCpuUnlock vxAtomic32Sub intCpuMicroLock intCpuMicroUnlock kernelLockOwnerGet taskCpuUnlockInternal evtAction vxAtomicInc vxAtomicGet eventPointSwHandle vxAtomicSet
	DECLARES 
	USES 
}
Module spinLockSmpLib.o {
	OBJECT += libspl.a::spinLockSmpLib.o
}
ObjectFile libspl.a::spinLockNdTimedLib.o {
	NAME Object file spinLockNdTimedLib.o from archive libspl.a
	EXPORTS spinLockNdTimedInit spinLockNdTimedTake spinLockNdTimedGive spinLockNdTimedPrevOwnerGet
	IMPORTS .TOC. sysClkRateGet intCpuLock vxAbsTicksGet atomic32Get atomic32Cas intCpuUnlock errnoSet
	DECLARES 
	USES 
}
Module spinLockNdTimedLib.o {
	OBJECT += libspl.a::spinLockNdTimedLib.o
}
Library libspl.a {
	MODULES libspl.a::kernelLockLib.o libspl.a::spinLockIsrNdLib.o libspl.a::spinLockSmpLib.o libspl.a::spinLockNdTimedLib.o
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
Symbol vxCpuConfigured {
}
Symbol spinLockIsrTake {
}
Symbol intCpuLock {
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
Symbol intCpuUnlock {
}
Symbol vxAtomic32Sub {
}
Symbol spinLockIsrHeld {
}
Symbol spinLockRestrict {
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
Symbol spinLockDbgDisable {
}
Symbol spinLockNdTimedInit {
}
Symbol spinLockNdTimedTake {
}
Symbol sysClkRateGet {
}
Symbol vxAbsTicksGet {
}
Symbol atomic32Get {
}
Symbol atomic32Cas {
}
Symbol errnoSet {
}
Symbol spinLockNdTimedGive {
}
Symbol spinLockNdTimedPrevOwnerGet {
}
ObjectFile libspl.a::kernelLockLib.o {
	NAME Object file kernelLockLib.o from archive libspl.a
	EXPORTS kernelLockInit kernelStateLock kernelLockOwnedByMe kernelLockOwnerGet
	IMPORTS .TOC. intCpuMicroLock vxCpuIndexGet intCpuMicroUnlock
	DECLARES 
	USES 
}
Module kernelLockLib.o {
	OBJECT += libspl.a::kernelLockLib.o
}
ObjectFile libspl.a::spinLockIsrNdLib.o {
	NAME Object file spinLockIsrNdLib.o from archive libspl.a
	EXPORTS spinLockIsrNdInit spinlockIsrNdInit
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module spinLockIsrNdLib.o {
	OBJECT += libspl.a::spinLockIsrNdLib.o
}
ObjectFile libspl.a::spinLockSmpLib.o {
	NAME Object file spinLockSmpLib.o from archive libspl.a
	EXPORTS spinLockIsrInit spinLockIsrTake rtSpinlockMaxSpin spinLockIsrHeld spinLockRestrict spinLockIsrGive spinLockTaskInit spinLockTaskTake spinLockTaskGive spinLockDbgDisable
	IMPORTS .TOC. vxCpuConfigured intCpuLock vxCpuIndexGet vxKernelVars vxAtomic32Cas vxAtomic32Set vxAtomic32Add intCpuUnlock vxAtomic32Sub intCpuMicroLock intCpuMicroUnlock kernelLockOwnerGet taskCpuUnlockInternal evtAction vxAtomicInc vxAtomicGet eventPointSwHandle vxAtomicSet
	DECLARES 
	USES 
}
Module spinLockSmpLib.o {
	OBJECT += libspl.a::spinLockSmpLib.o
}
ObjectFile libspl.a::spinLockNdTimedLib.o {
	NAME Object file spinLockNdTimedLib.o from archive libspl.a
	EXPORTS spinLockNdTimedInit spinLockNdTimedTake spinLockNdTimedGive spinLockNdTimedPrevOwnerGet
	IMPORTS .TOC. sysClkRateGet intCpuLock vxAbsTicksGet atomic32Get atomic32Cas intCpuUnlock errnoSet
	DECLARES 
	USES 
}
Module spinLockNdTimedLib.o {
	OBJECT += libspl.a::spinLockNdTimedLib.o
}
Library libspl.a {
	MODULES libspl.a::kernelLockLib.o libspl.a::spinLockIsrNdLib.o libspl.a::spinLockSmpLib.o libspl.a::spinLockNdTimedLib.o
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
Symbol vxCpuConfigured {
}
Symbol spinLockIsrTake {
}
Symbol intCpuLock {
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
Symbol intCpuUnlock {
}
Symbol vxAtomic32Sub {
}
Symbol spinLockIsrHeld {
}
Symbol spinLockRestrict {
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
Symbol spinLockDbgDisable {
}
Symbol spinLockNdTimedInit {
}
Symbol spinLockNdTimedTake {
}
Symbol sysClkRateGet {
}
Symbol vxAbsTicksGet {
}
Symbol atomic32Get {
}
Symbol atomic32Cas {
}
Symbol errnoSet {
}
Symbol spinLockNdTimedGive {
}
Symbol spinLockNdTimedPrevOwnerGet {
}
ObjectFile libspl.a::kernelLockLib.o {
	NAME Object file kernelLockLib.o from archive libspl.a
	EXPORTS kernelLockInit kernelStateLock kernelLockOwnedByMe kernelLockOwnerGet
	IMPORTS .TOC. intCpuMicroLock vxCpuIndexGet intCpuMicroUnlock
	DECLARES 
	USES 
}
Module kernelLockLib.o {
	OBJECT += libspl.a::kernelLockLib.o
}
ObjectFile libspl.a::spinLockIsrNdLib.o {
	NAME Object file spinLockIsrNdLib.o from archive libspl.a
	EXPORTS spinLockIsrNdInit spinlockIsrNdInit
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module spinLockIsrNdLib.o {
	OBJECT += libspl.a::spinLockIsrNdLib.o
}
ObjectFile libspl.a::spinLockSmpLib.o {
	NAME Object file spinLockSmpLib.o from archive libspl.a
	EXPORTS spinLockIsrInit spinLockIsrTake rtSpinlockMaxSpin spinLockIsrHeld spinLockRestrict spinLockIsrGive spinLockTaskInit spinLockTaskTake spinLockTaskGive spinLockDbgDisable
	IMPORTS .TOC. vxCpuConfigured intCpuLock vxCpuIndexGet vxKernelVars vxAtomic32Cas vxAtomic32Set vxAtomic32Add intCpuUnlock vxAtomic32Sub intCpuMicroLock intCpuMicroUnlock kernelLockOwnerGet taskCpuUnlockInternal evtAction vxAtomicInc vxAtomicGet eventPointSwHandle vxAtomicSet
	DECLARES 
	USES 
}
Module spinLockSmpLib.o {
	OBJECT += libspl.a::spinLockSmpLib.o
}
ObjectFile libspl.a::spinLockNdTimedLib.o {
	NAME Object file spinLockNdTimedLib.o from archive libspl.a
	EXPORTS spinLockNdTimedInit spinLockNdTimedTake spinLockNdTimedGive spinLockNdTimedPrevOwnerGet
	IMPORTS .TOC. sysClkRateGet intCpuLock vxAbsTicksGet atomic32Get atomic32Cas intCpuUnlock errnoSet
	DECLARES 
	USES 
}
Module spinLockNdTimedLib.o {
	OBJECT += libspl.a::spinLockNdTimedLib.o
}
Library libspl.a {
	MODULES libspl.a::kernelLockLib.o libspl.a::spinLockIsrNdLib.o libspl.a::spinLockSmpLib.o libspl.a::spinLockNdTimedLib.o
}
