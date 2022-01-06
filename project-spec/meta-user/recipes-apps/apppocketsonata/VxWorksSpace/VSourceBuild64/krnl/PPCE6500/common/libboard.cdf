Symbol .TOC. {
}
Symbol boardLibInit {
}
Symbol datasetIterate {
}
Symbol boardInit {
}
Symbol boardReset {
}
Symbol boardInfoShow {
}
Symbol boardFlagCheck {
}
Symbol sysUsDelay {
}
Symbol sysMsDelay {
}
Symbol sysDelay {
}
Symbol sysToMonitor {
}
Symbol intContext {
}
Symbol kernelLockOwnedByMe {
}
Symbol taskCpuLock {
}
Symbol vxCpuIndexGet {
}
Symbol vxCpuEnabledGet {
}
Symbol cpcInvoke {
}
Symbol sysProcNumGet {
}
Symbol sysProcNum {
}
Symbol sysProcNumSet {
}
Symbol sysModel {
}
Symbol sysMemSizeGet {
}
Symbol sysMemDescGet {
}
Symbol sysCpuEnable {
}
Symbol sysCpuAvailableGet {
}
Symbol sysWarmBootLibInit {
}
Symbol sysWarmBootFunc {
}
Symbol sysWarmBootSlaveDisable {
}
Symbol sysWarmBootSlaveEnable {
}
Symbol warmBootLibInit {
}
Symbol warmBootStart {
}
Symbol warmBootSlaveDisable {
}
Symbol warmBootSlaveEnable {
}
Symbol warmBootDataEndGet {
}
Symbol warmBootDataAlign {
}
Symbol wrs_kernel_bss_end {
}
Symbol warmBootCRC {
}
Symbol warmBootBackup {
}
Symbol wrs_kernel_data_start {
}
Symbol wrs_kernel_data_end {
}
Symbol bcopy {
}
Symbol wrs_kernel_text_start {
}
Symbol wrs_kernel_text_end {
}
Symbol warmBootCheck {
}
Symbol warmBootRestore {
}
Symbol vmTranslate {
}
Symbol vxFdtDtbAddressGet {
}
Symbol vxCpuIdGet {
}
Symbol bootKernelStub {
}
Symbol vxCpuSlaveInit {
}
ObjectFile libboard.a::boardLib.o {
	NAME Object file boardLib.o from archive libboard.a
	EXPORTS boardLibInit boardInit boardReset boardInfoShow boardFlagCheck sysUsDelay sysMsDelay sysDelay sysToMonitor sysProcNumGet sysProcNumSet sysModel sysMemSizeGet sysCpuEnable sysCpuAvailableGet
	IMPORTS .TOC. datasetIterate intContext kernelLockOwnedByMe taskCpuLock vxCpuIndexGet vxCpuEnabledGet cpcInvoke sysProcNum sysMemDescGet
	DECLARES sysWarmBootLibInit sysWarmBootFunc sysWarmBootSlaveDisable sysWarmBootSlaveEnable
	USES 
}
Module boardLib.o {
	OBJECT += libboard.a::boardLib.o
}
ObjectFile libboard.a::warmBootLib.o {
	NAME Object file warmBootLib.o from archive libboard.a
	EXPORTS warmBootLibInit warmBootStart warmBootSlaveDisable warmBootSlaveEnable warmBootDataEndGet warmBootCRC warmBootBackup warmBootCheck warmBootRestore
	IMPORTS .TOC. sysWarmBootFunc sysWarmBootSlaveDisable sysWarmBootSlaveEnable warmBootDataAlign wrs_kernel_bss_end wrs_kernel_data_start wrs_kernel_data_end bcopy wrs_kernel_text_start wrs_kernel_text_end vmTranslate vxCpuIndexGet vxFdtDtbAddressGet vxCpuIdGet bootKernelStub vxCpuSlaveInit
	DECLARES 
	USES 
}
Module warmBootLib.o {
	OBJECT += libboard.a::warmBootLib.o
}
Library libboard.a {
	MODULES libboard.a::boardLib.o libboard.a::warmBootLib.o
}
Symbol .TOC. {
}
Symbol boardLibInit {
}
Symbol datasetIterate {
}
Symbol boardInit {
}
Symbol boardReset {
}
Symbol boardInfoShow {
}
Symbol boardFlagCheck {
}
Symbol sysUsDelay {
}
Symbol sysMsDelay {
}
Symbol sysDelay {
}
Symbol sysToMonitor {
}
Symbol intContext {
}
Symbol kernelLockOwnedByMe {
}
Symbol taskCpuLock {
}
Symbol vxCpuIndexGet {
}
Symbol vxCpuEnabledGet {
}
Symbol cpcInvoke {
}
Symbol sysProcNumGet {
}
Symbol sysProcNum {
}
Symbol sysProcNumSet {
}
Symbol sysModel {
}
Symbol sysMemSizeGet {
}
Symbol sysMemDescGet {
}
Symbol sysCpuEnable {
}
Symbol sysCpuAvailableGet {
}
Symbol sysWarmBootLibInit {
}
Symbol sysWarmBootFunc {
}
Symbol sysWarmBootSlaveDisable {
}
Symbol sysWarmBootSlaveEnable {
}
Symbol warmBootLibInit {
}
Symbol warmBootStart {
}
Symbol warmBootSlaveDisable {
}
Symbol warmBootSlaveEnable {
}
Symbol warmBootDataEndGet {
}
Symbol warmBootDataAlign {
}
Symbol wrs_kernel_bss_end {
}
Symbol warmBootCRC {
}
Symbol warmBootBackup {
}
Symbol wrs_kernel_data_start {
}
Symbol wrs_kernel_data_end {
}
Symbol bcopy {
}
Symbol wrs_kernel_text_start {
}
Symbol wrs_kernel_text_end {
}
Symbol warmBootCheck {
}
Symbol warmBootRestore {
}
Symbol vmTranslate {
}
Symbol vxFdtDtbAddressGet {
}
Symbol vxCpuIdGet {
}
Symbol bootKernelStub {
}
Symbol vxCpuSlaveInit {
}
ObjectFile libboard.a::boardLib.o {
	NAME Object file boardLib.o from archive libboard.a
	EXPORTS boardLibInit boardInit boardReset boardInfoShow boardFlagCheck sysUsDelay sysMsDelay sysDelay sysToMonitor sysProcNumGet sysProcNumSet sysModel sysMemSizeGet sysCpuEnable sysCpuAvailableGet
	IMPORTS .TOC. datasetIterate intContext kernelLockOwnedByMe taskCpuLock vxCpuIndexGet vxCpuEnabledGet cpcInvoke sysProcNum sysMemDescGet
	DECLARES sysWarmBootLibInit sysWarmBootFunc sysWarmBootSlaveDisable sysWarmBootSlaveEnable
	USES 
}
Module boardLib.o {
	OBJECT += libboard.a::boardLib.o
}
ObjectFile libboard.a::warmBootLib.o {
	NAME Object file warmBootLib.o from archive libboard.a
	EXPORTS warmBootLibInit warmBootStart warmBootSlaveDisable warmBootSlaveEnable warmBootDataEndGet warmBootCRC warmBootBackup warmBootCheck warmBootRestore
	IMPORTS .TOC. sysWarmBootFunc sysWarmBootSlaveDisable sysWarmBootSlaveEnable warmBootDataAlign wrs_kernel_bss_end wrs_kernel_data_start wrs_kernel_data_end bcopy wrs_kernel_text_start wrs_kernel_text_end vmTranslate vxCpuIndexGet vxFdtDtbAddressGet vxCpuIdGet bootKernelStub vxCpuSlaveInit
	DECLARES 
	USES 
}
Module warmBootLib.o {
	OBJECT += libboard.a::warmBootLib.o
}
Library libboard.a {
	MODULES libboard.a::boardLib.o libboard.a::warmBootLib.o
}
Symbol .TOC. {
}
Symbol boardLibInit {
}
Symbol datasetIterate {
}
Symbol boardInit {
}
Symbol boardReset {
}
Symbol boardInfoShow {
}
Symbol boardFlagCheck {
}
Symbol sysUsDelay {
}
Symbol sysMsDelay {
}
Symbol sysDelay {
}
Symbol sysToMonitor {
}
Symbol intContext {
}
Symbol kernelLockOwnedByMe {
}
Symbol taskCpuLock {
}
Symbol vxCpuIndexGet {
}
Symbol vxCpuEnabledGet {
}
Symbol cpcInvoke {
}
Symbol sysProcNumGet {
}
Symbol sysProcNum {
}
Symbol sysProcNumSet {
}
Symbol sysModel {
}
Symbol sysMemSizeGet {
}
Symbol sysMemDescGet {
}
Symbol sysCpuEnable {
}
Symbol sysCpuAvailableGet {
}
Symbol sysWarmBootLibInit {
}
Symbol sysWarmBootFunc {
}
Symbol sysWarmBootSlaveDisable {
}
Symbol sysWarmBootSlaveEnable {
}
Symbol warmBootLibInit {
}
Symbol warmBootStart {
}
Symbol warmBootSlaveDisable {
}
Symbol warmBootSlaveEnable {
}
Symbol warmBootDataEndGet {
}
Symbol warmBootDataAlign {
}
Symbol wrs_kernel_bss_end {
}
Symbol warmBootCRC {
}
Symbol warmBootBackup {
}
Symbol wrs_kernel_data_start {
}
Symbol wrs_kernel_data_end {
}
Symbol bcopy {
}
Symbol wrs_kernel_text_start {
}
Symbol wrs_kernel_text_end {
}
Symbol warmBootCheck {
}
Symbol warmBootRestore {
}
Symbol vmTranslate {
}
Symbol vxFdtDtbAddressGet {
}
Symbol vxCpuIdGet {
}
Symbol bootKernelStub {
}
Symbol vxCpuSlaveInit {
}
ObjectFile libboard.a::boardLib.o {
	NAME Object file boardLib.o from archive libboard.a
	EXPORTS boardLibInit boardInit boardReset boardInfoShow boardFlagCheck sysUsDelay sysMsDelay sysDelay sysToMonitor sysProcNumGet sysProcNumSet sysModel sysMemSizeGet sysCpuEnable sysCpuAvailableGet
	IMPORTS .TOC. datasetIterate intContext kernelLockOwnedByMe taskCpuLock vxCpuIndexGet vxCpuEnabledGet cpcInvoke sysProcNum sysMemDescGet
	DECLARES sysWarmBootLibInit sysWarmBootFunc sysWarmBootSlaveDisable sysWarmBootSlaveEnable
	USES 
}
Module boardLib.o {
	OBJECT += libboard.a::boardLib.o
}
ObjectFile libboard.a::warmBootLib.o {
	NAME Object file warmBootLib.o from archive libboard.a
	EXPORTS warmBootLibInit warmBootStart warmBootSlaveDisable warmBootSlaveEnable warmBootDataEndGet warmBootCRC warmBootBackup warmBootCheck warmBootRestore
	IMPORTS .TOC. sysWarmBootFunc sysWarmBootSlaveDisable sysWarmBootSlaveEnable warmBootDataAlign wrs_kernel_bss_end wrs_kernel_data_start wrs_kernel_data_end bcopy wrs_kernel_text_start wrs_kernel_text_end vmTranslate vxCpuIndexGet vxFdtDtbAddressGet vxCpuIdGet bootKernelStub vxCpuSlaveInit
	DECLARES 
	USES 
}
Module warmBootLib.o {
	OBJECT += libboard.a::warmBootLib.o
}
Library libboard.a {
	MODULES libboard.a::boardLib.o libboard.a::warmBootLib.o
}
