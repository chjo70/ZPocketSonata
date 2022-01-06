Symbol vxbMySpiFlashProbe {
}
Symbol .TOC. {
}
Symbol vxbSpiFlashMatch {
}
Symbol vxbFdtDevMatch {
}
Symbol gDevProbeResult {
}
Symbol myDrvCheck {
}
Symbol printf {
}
Symbol gDevAttachResult {
}
Symbol gDevIdentify {
}
Symbol gDevJedec {
}
Symbol gDevDynamic {
}
Symbol spiFlashDynamicIdentify {
}
Symbol vxbDevIvarsGet {
}
Symbol vxFdtPropGet {
}
Symbol vxFdt32ToCpu {
}
Symbol spiFlashRead {
}
Symbol bzero {
}
Symbol vxbSpiDevXfer {
}
Symbol spiFlashCfiDataItemGet {
}
Symbol spiFlashCfiDataGet {
}
Symbol memset {
}
Symbol memcpy {
}
Symbol spiFlashDbgMask {
}
Symbol _func_kprintf {
}
Symbol spiFlashCfiIdentify {
}
Symbol spiFlashJedecIdentify {
}
Symbol spiFlashList {
}
Symbol strncpy {
}
Symbol spiFlashWrite {
}
Symbol spiFlashReadSR {
}
Symbol spiFlashWaitReady {
}
Symbol vxbUsDelay {
}
Symbol spiFlashWriteEn {
}
Symbol spiFlashWriteReg {
}
Symbol spiFlash4BEn {
}
Symbol strcmp {
}
Symbol spiFlashIdentify {
}
Symbol vxbMySpiFlashAttach {
}
Symbol vxbFdtDevGet {
}
Symbol calloc {
}
Symbol vxbDevSoftcSet {
}
Symbol vxbResourceAlloc {
}
Symbol semMCreate {
}
Symbol vxbDevParent {
}
Symbol vxbSpiSpecGet_desc {
}
Symbol vxbDevMethodFind {
}
Symbol vxbSpiFlashEnable {
}
Symbol vxbSpiFlashReset {
}
Symbol vxbSpiFlashRead {
}
Symbol vxbSpiFlashWrite {
}
Symbol vxbSpiFlashErase {
}
Symbol vxbDevUnitGet {
}
Symbol snprintf {
}
Symbol vxbFlashChipAdd {
}
Symbol semDelete {
}
Symbol vxbResourceFree {
}
Symbol free {
}
Symbol spiFlashDataRead {
}
Symbol vxbDevSoftcGet {
}
Symbol semTake {
}
Symbol bcopy {
}
Symbol semGive {
}
Symbol spiFlashWrite1Byte {
}
Symbol spiFlashSstDataWrite {
}
Symbol spiFlashReadFSR {
}
Symbol spiFlashStatusCheck {
}
Symbol spiFlashDataWrite {
}
Symbol spiFlashChipErase {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol spiFlashSectorErase {
}
Symbol spiFlashReadReg {
}
Symbol vxbMySpiFlash_Test {
}
Symbol vxbSpiFlashMethodList {
}
Symbol vxbDevProbe_desc {
}
Symbol vxbDevAttach_desc {
}
Symbol vxbMySpiFlashDrv {
}
Symbol __dataset__driver_vxbMySpiFlashDrv {
}
ObjectFile libmy_qspi_flash_layer.a::vxbMySpiFlash.o {
	NAME Object file vxbMySpiFlash.o from archive libmy_qspi_flash_layer.a
	EXPORTS vxbMySpiFlashProbe vxbSpiFlashMatch gDevProbeResult myDrvCheck gDevAttachResult gDevIdentify gDevJedec gDevDynamic spiFlashDynamicIdentify spiFlashRead spiFlashCfiDataItemGet spiFlashCfiDataGet spiFlashDbgMask spiFlashCfiIdentify spiFlashJedecIdentify spiFlashList spiFlashWrite spiFlashReadSR spiFlashWaitReady spiFlashWriteEn spiFlashWriteReg spiFlash4BEn spiFlashIdentify vxbMySpiFlashAttach vxbSpiFlashEnable vxbSpiFlashReset vxbSpiFlashRead vxbSpiFlashWrite vxbSpiFlashErase spiFlashDataRead spiFlashWrite1Byte spiFlashSstDataWrite spiFlashReadFSR spiFlashStatusCheck spiFlashDataWrite spiFlashChipErase spiFlashSectorErase spiFlashReadReg vxbMySpiFlash_Test vxbSpiFlashMethodList vxbMySpiFlashDrv __dataset__driver_vxbMySpiFlashDrv
	IMPORTS .TOC. vxbFdtDevMatch printf vxbDevIvarsGet vxFdtPropGet vxFdt32ToCpu bzero vxbSpiDevXfer memset memcpy _func_kprintf strncpy vxbUsDelay strcmp vxbFdtDevGet calloc vxbDevSoftcSet vxbResourceAlloc semMCreate vxbDevParent vxbSpiSpecGet_desc vxbDevMethodFind vxbDevUnitGet snprintf vxbFlashChipAdd semDelete vxbResourceFree free vxbDevSoftcGet semTake bcopy semGive sysClkRateGet taskDelay vxbDevProbe_desc vxbDevAttach_desc
	DECLARES 
	USES 
}
Module vxbMySpiFlash.o {
	OBJECT += libmy_qspi_flash_layer.a::vxbMySpiFlash.o
}
Library libmy_qspi_flash_layer.a {
	MODULES libmy_qspi_flash_layer.a::vxbMySpiFlash.o
}
Symbol vxbMySpiFlashProbe {
}
Symbol .TOC. {
}
Symbol vxbSpiFlashMatch {
}
Symbol vxbFdtDevMatch {
}
Symbol gDevProbeResult {
}
Symbol myDrvCheck {
}
Symbol printf {
}
Symbol gDevAttachResult {
}
Symbol gDevIdentify {
}
Symbol gDevJedec {
}
Symbol gDevDynamic {
}
Symbol spiFlashDynamicIdentify {
}
Symbol vxbDevIvarsGet {
}
Symbol vxFdtPropGet {
}
Symbol vxFdt32ToCpu {
}
Symbol spiFlashRead {
}
Symbol bzero {
}
Symbol vxbSpiDevXfer {
}
Symbol spiFlashCfiDataItemGet {
}
Symbol spiFlashCfiDataGet {
}
Symbol memset {
}
Symbol memcpy {
}
Symbol spiFlashDbgMask {
}
Symbol _func_kprintf {
}
Symbol spiFlashCfiIdentify {
}
Symbol spiFlashJedecIdentify {
}
Symbol spiFlashList {
}
Symbol strncpy {
}
Symbol spiFlashWrite {
}
Symbol spiFlashReadSR {
}
Symbol spiFlashWaitReady {
}
Symbol vxbUsDelay {
}
Symbol spiFlashWriteEn {
}
Symbol spiFlashWriteReg {
}
Symbol spiFlash4BEn {
}
Symbol strcmp {
}
Symbol spiFlashIdentify {
}
Symbol vxbMySpiFlashAttach {
}
Symbol vxbFdtDevGet {
}
Symbol calloc {
}
Symbol vxbDevSoftcSet {
}
Symbol vxbResourceAlloc {
}
Symbol semMCreate {
}
Symbol vxbDevParent {
}
Symbol vxbSpiSpecGet_desc {
}
Symbol vxbDevMethodFind {
}
Symbol vxbSpiFlashEnable {
}
Symbol vxbSpiFlashReset {
}
Symbol vxbSpiFlashRead {
}
Symbol vxbSpiFlashWrite {
}
Symbol vxbSpiFlashErase {
}
Symbol vxbDevUnitGet {
}
Symbol snprintf {
}
Symbol vxbFlashChipAdd {
}
Symbol semDelete {
}
Symbol vxbResourceFree {
}
Symbol free {
}
Symbol spiFlashDataRead {
}
Symbol vxbDevSoftcGet {
}
Symbol semTake {
}
Symbol bcopy {
}
Symbol semGive {
}
Symbol spiFlashWrite1Byte {
}
Symbol spiFlashSstDataWrite {
}
Symbol spiFlashReadFSR {
}
Symbol spiFlashStatusCheck {
}
Symbol spiFlashDataWrite {
}
Symbol spiFlashChipErase {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol spiFlashSectorErase {
}
Symbol spiFlashReadReg {
}
Symbol vxbMySpiFlash_Test {
}
Symbol vxbSpiFlashMethodList {
}
Symbol vxbDevProbe_desc {
}
Symbol vxbDevAttach_desc {
}
Symbol vxbMySpiFlashDrv {
}
Symbol __dataset__driver_vxbMySpiFlashDrv {
}
ObjectFile libmy_qspi_flash_layer.a::vxbMySpiFlash.o {
	NAME Object file vxbMySpiFlash.o from archive libmy_qspi_flash_layer.a
	EXPORTS vxbMySpiFlashProbe vxbSpiFlashMatch gDevProbeResult myDrvCheck gDevAttachResult gDevIdentify gDevJedec gDevDynamic spiFlashDynamicIdentify spiFlashRead spiFlashCfiDataItemGet spiFlashCfiDataGet spiFlashDbgMask spiFlashCfiIdentify spiFlashJedecIdentify spiFlashList spiFlashWrite spiFlashReadSR spiFlashWaitReady spiFlashWriteEn spiFlashWriteReg spiFlash4BEn spiFlashIdentify vxbMySpiFlashAttach vxbSpiFlashEnable vxbSpiFlashReset vxbSpiFlashRead vxbSpiFlashWrite vxbSpiFlashErase spiFlashDataRead spiFlashWrite1Byte spiFlashSstDataWrite spiFlashReadFSR spiFlashStatusCheck spiFlashDataWrite spiFlashChipErase spiFlashSectorErase spiFlashReadReg vxbMySpiFlash_Test vxbSpiFlashMethodList vxbMySpiFlashDrv __dataset__driver_vxbMySpiFlashDrv
	IMPORTS .TOC. vxbFdtDevMatch printf vxbDevIvarsGet vxFdtPropGet vxFdt32ToCpu bzero vxbSpiDevXfer memset memcpy _func_kprintf strncpy vxbUsDelay strcmp vxbFdtDevGet calloc vxbDevSoftcSet vxbResourceAlloc semMCreate vxbDevParent vxbSpiSpecGet_desc vxbDevMethodFind vxbDevUnitGet snprintf vxbFlashChipAdd semDelete vxbResourceFree free vxbDevSoftcGet semTake bcopy semGive sysClkRateGet taskDelay vxbDevProbe_desc vxbDevAttach_desc
	DECLARES 
	USES 
}
Module vxbMySpiFlash.o {
	OBJECT += libmy_qspi_flash_layer.a::vxbMySpiFlash.o
}
Library libmy_qspi_flash_layer.a {
	MODULES libmy_qspi_flash_layer.a::vxbMySpiFlash.o
}
Symbol vxbMySpiFlashProbe {
}
Symbol .TOC. {
}
Symbol vxbSpiFlashMatch {
}
Symbol vxbFdtDevMatch {
}
Symbol gDevProbeResult {
}
Symbol myDrvCheck {
}
Symbol printf {
}
Symbol gDevAttachResult {
}
Symbol gDevIdentify {
}
Symbol gDevJedec {
}
Symbol gDevDynamic {
}
Symbol spiFlashDynamicIdentify {
}
Symbol vxbDevIvarsGet {
}
Symbol vxFdtPropGet {
}
Symbol vxFdt32ToCpu {
}
Symbol spiFlashRead {
}
Symbol bzero {
}
Symbol vxbSpiDevXfer {
}
Symbol spiFlashCfiDataItemGet {
}
Symbol spiFlashCfiDataGet {
}
Symbol memset {
}
Symbol memcpy {
}
Symbol spiFlashDbgMask {
}
Symbol _func_kprintf {
}
Symbol spiFlashCfiIdentify {
}
Symbol spiFlashJedecIdentify {
}
Symbol spiFlashList {
}
Symbol strncpy {
}
Symbol spiFlashWrite {
}
Symbol spiFlashReadSR {
}
Symbol spiFlashWaitReady {
}
Symbol vxbUsDelay {
}
Symbol spiFlashWriteEn {
}
Symbol spiFlashWriteReg {
}
Symbol spiFlash4BEn {
}
Symbol strcmp {
}
Symbol spiFlashIdentify {
}
Symbol vxbMySpiFlashAttach {
}
Symbol vxbFdtDevGet {
}
Symbol calloc {
}
Symbol vxbDevSoftcSet {
}
Symbol vxbResourceAlloc {
}
Symbol semMCreate {
}
Symbol vxbDevParent {
}
Symbol vxbSpiSpecGet_desc {
}
Symbol vxbDevMethodFind {
}
Symbol vxbSpiFlashEnable {
}
Symbol vxbSpiFlashReset {
}
Symbol vxbSpiFlashRead {
}
Symbol vxbSpiFlashWrite {
}
Symbol vxbSpiFlashErase {
}
Symbol vxbDevUnitGet {
}
Symbol snprintf {
}
Symbol vxbFlashChipAdd {
}
Symbol semDelete {
}
Symbol vxbResourceFree {
}
Symbol free {
}
Symbol spiFlashDataRead {
}
Symbol vxbDevSoftcGet {
}
Symbol semTake {
}
Symbol bcopy {
}
Symbol semGive {
}
Symbol spiFlashWrite1Byte {
}
Symbol spiFlashSstDataWrite {
}
Symbol spiFlashReadFSR {
}
Symbol spiFlashStatusCheck {
}
Symbol spiFlashDataWrite {
}
Symbol spiFlashChipErase {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol spiFlashSectorErase {
}
Symbol spiFlashReadReg {
}
Symbol vxbMySpiFlash_Test {
}
Symbol vxbSpiFlashMethodList {
}
Symbol vxbDevProbe_desc {
}
Symbol vxbDevAttach_desc {
}
Symbol vxbMySpiFlashDrv {
}
Symbol __dataset__driver_vxbMySpiFlashDrv {
}
ObjectFile libmy_qspi_flash_layer.a::vxbMySpiFlash.o {
	NAME Object file vxbMySpiFlash.o from archive libmy_qspi_flash_layer.a
	EXPORTS vxbMySpiFlashProbe vxbSpiFlashMatch gDevProbeResult myDrvCheck gDevAttachResult gDevIdentify gDevJedec gDevDynamic spiFlashDynamicIdentify spiFlashRead spiFlashCfiDataItemGet spiFlashCfiDataGet spiFlashDbgMask spiFlashCfiIdentify spiFlashJedecIdentify spiFlashList spiFlashWrite spiFlashReadSR spiFlashWaitReady spiFlashWriteEn spiFlashWriteReg spiFlash4BEn spiFlashIdentify vxbMySpiFlashAttach vxbSpiFlashEnable vxbSpiFlashReset vxbSpiFlashRead vxbSpiFlashWrite vxbSpiFlashErase spiFlashDataRead spiFlashWrite1Byte spiFlashSstDataWrite spiFlashReadFSR spiFlashStatusCheck spiFlashDataWrite spiFlashChipErase spiFlashSectorErase spiFlashReadReg vxbMySpiFlash_Test vxbSpiFlashMethodList vxbMySpiFlashDrv __dataset__driver_vxbMySpiFlashDrv
	IMPORTS .TOC. vxbFdtDevMatch printf vxbDevIvarsGet vxFdtPropGet vxFdt32ToCpu bzero vxbSpiDevXfer memset memcpy _func_kprintf strncpy vxbUsDelay strcmp vxbFdtDevGet calloc vxbDevSoftcSet vxbResourceAlloc semMCreate vxbDevParent vxbSpiSpecGet_desc vxbDevMethodFind vxbDevUnitGet snprintf vxbFlashChipAdd semDelete vxbResourceFree free vxbDevSoftcGet semTake bcopy semGive sysClkRateGet taskDelay vxbDevProbe_desc vxbDevAttach_desc
	DECLARES 
	USES 
}
Module vxbMySpiFlash.o {
	OBJECT += libmy_qspi_flash_layer.a::vxbMySpiFlash.o
}
Library libmy_qspi_flash_layer.a {
	MODULES libmy_qspi_flash_layer.a::vxbMySpiFlash.o
}
