Symbol .TOC. {
}
Symbol lstInit {
}
Symbol semMCreate {
}
Symbol fsimInit {
}
Symbol mtdDevCreate {
}
Symbol mtdDevDelete {
}
Symbol semTake {
}
Symbol lstFirst {
}
Symbol strcmp {
}
Symbol lstNext {
}
Symbol semGive {
}
Symbol fsimStart {
}
Symbol errnoSet {
}
Symbol open {
}
Symbol taskIdSelf {
}
Symbol printf {
}
Symbol lseek {
}
Symbol memset {
}
Symbol write {
}
Symbol close {
}
Symbol lstAdd {
}
Symbol ioctl {
}
Symbol fsimDevCreate {
}
Symbol fsimChipCreate {
}
Symbol malloc {
}
Symbol free {
}
Symbol fsimChipDelete {
}
Symbol fsimCreate {
}
Symbol strlen {
}
Symbol strcpy {
}
Symbol fsimRead {
}
Symbol fsimErase {
}
Symbol fsimWritePage {
}
Symbol fsimWritePages {
}
Symbol fsimWrite {
}
Symbol fsimReadPage {
}
Symbol fsimReadPages {
}
Symbol fsimIsBlankPage {
}
Symbol lstDelete {
}
Symbol fsimDevDelete {
}
Symbol fsimDelete {
}
Symbol read {
}
Symbol fsimMount {
}
Symbol fsimUnmount {
}
Symbol errnoGet {
}
Symbol fsimRun {
}
Symbol fsimStop {
}
Symbol fsimDevPageRW {
}
Symbol fsimDevPagesRW {
}
Symbol getChipBlkNo {
}
Symbol getChipPageNo {
}
Symbol fsimIoctl {
}
Symbol fsimShow {
}
Symbol fsimShowAll {
}
Symbol fsimPrintBuf {
}
Symbol memcpy {
}
Symbol fsimDump {
}
Symbol fsimDumpData {
}
Symbol fsimDumpOob {
}
Symbol fsimImageSave {
}
Symbol fsimImageCopy {
}
Symbol fsimDevStatChip {
}
Symbol fsimStatChip {
}
Symbol fsimStatBlk {
}
Symbol fsimStatPage {
}
Symbol reboot {
}
Symbol fsimMarkBad {
}
Symbol fsimUnmarkBad {
}
Symbol fsimIsBadBlock {
}
Symbol fsimInjectError {
}
Symbol fsimErrorGenerator {
}
Symbol fsimRemoveError {
}
Symbol fsimReboot {
}
Symbol taskIdVerify {
}
Symbol fsimInvalidateMap {
}
Symbol fsimIsPageMapped {
}
Symbol fsimUpdateMapStatus {
}
Symbol fsimFind {
}
Symbol fsimDbgTurn {
}
Symbol tickGet {
}
Symbol srand {
}
Symbol rand {
}
Symbol semDelete {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol fsimCrc32 {
}
Symbol mtdRegisterNotify {
}
Symbol calloc {
}
Symbol mtdUnRegisterNotify {
}
Symbol mtdFindAndNotify {
}
Symbol mtdNotify {
}
Symbol fsimTffsRegister {
}
Symbol noOfDrives {
}
Symbol flSocketOf {
}
Symbol needCheckRAM {
}
Symbol printErr {
}
Symbol strncpy {
}
Symbol fsimTffsList {
}
Symbol fsimNorIdentify {
}
Symbol flIdentifyRegister {
}
Symbol flInitSocket {
}
Symbol fsimTffsUnregister {
}
Symbol fsimTffsShow {
}
Symbol fsimTffsFind {
}
Symbol flSetWindowSize {
}
Symbol fsimTffsFormat {
}
Symbol tffsDevFormat {
}
Symbol fsimNorMap {
}
ObjectFile libbdmSim.a::fsimLib.o {
	NAME Object file fsimLib.o from archive libbdmSim.a
	EXPORTS fsimInit fsimStart fsimDevCreate fsimCreate fsimRead fsimErase fsimWritePage fsimWritePages fsimWrite fsimReadPage fsimReadPages fsimIsBlankPage fsimDevDelete fsimDelete fsimMount fsimUnmount fsimRun fsimStop fsimDevPageRW fsimDevPagesRW getChipBlkNo getChipPageNo fsimIoctl fsimShow fsimShowAll fsimPrintBuf fsimDump fsimDumpData fsimDumpOob fsimImageSave fsimImageCopy fsimDevStatChip fsimStatChip fsimStatBlk fsimStatPage fsimMarkBad fsimUnmarkBad fsimIsBadBlock fsimInjectError fsimErrorGenerator fsimRemoveError fsimReboot fsimInvalidateMap fsimIsPageMapped fsimUpdateMapStatus fsimFind fsimDbgTurn
	IMPORTS .TOC. lstInit semMCreate mtdDevCreate mtdDevDelete semTake lstFirst strcmp lstNext semGive errnoSet open taskIdSelf printf lseek memset write close lstAdd ioctl fsimChipCreate malloc free fsimChipDelete strlen strcpy lstDelete read errnoGet memcpy reboot taskIdVerify
	DECLARES 
	USES 
}
Module fsimLib.o {
	OBJECT += libbdmSim.a::fsimLib.o
}
ObjectFile libbdmSim.a::fsimChip.o {
	NAME Object file fsimChip.o from archive libbdmSim.a
	EXPORTS fsimChipCreate fsimChipDelete
	IMPORTS .TOC. lseek taskIdSelf write printf errnoSet ioctl semTake memset semGive errnoGet read tickGet srand rand open close malloc semMCreate memcpy semDelete free sysClkRateGet taskDelay
	DECLARES 
	USES 
}
Module fsimChip.o {
	OBJECT += libbdmSim.a::fsimChip.o
}
ObjectFile libbdmSim.a::fsimMtd.o {
	NAME Object file fsimMtd.o from archive libbdmSim.a
	EXPORTS fsimCrc32 mtdRegisterNotify mtdUnRegisterNotify mtdFindAndNotify mtdNotify mtdDevCreate mtdDevDelete
	IMPORTS .TOC. malloc printf memset free memcpy fsimInjectError taskIdSelf fsimIsBadBlock calloc strcmp
	DECLARES 
	USES 
}
Module fsimMtd.o {
	OBJECT += libbdmSim.a::fsimMtd.o
}
ObjectFile libbdmSim.a::fsimTffs.o {
	NAME Object file fsimTffs.o from archive libbdmSim.a
	EXPORTS fsimTffsRegister fsimNorIdentify fsimTffsUnregister fsimTffsShow fsimTffsFind fsimTffsFormat fsimNorMap
	IMPORTS .TOC. noOfDrives flSocketOf fsimFind printf memset needCheckRAM malloc printErr strncpy lstAdd flIdentifyRegister flInitSocket lstDelete free lstFirst lstNext flSetWindowSize tffsDevFormat fsimInvalidateMap fsimIsPageMapped fsimUpdateMapStatus
	DECLARES fsimTffsList
	USES 
}
Module fsimTffs.o {
	OBJECT += libbdmSim.a::fsimTffs.o
}
Library libbdmSim.a {
	MODULES libbdmSim.a::fsimLib.o libbdmSim.a::fsimChip.o libbdmSim.a::fsimMtd.o libbdmSim.a::fsimTffs.o
}
Symbol .TOC. {
}
Symbol lstInit {
}
Symbol semMCreate {
}
Symbol fsimInit {
}
Symbol mtdDevCreate {
}
Symbol mtdDevDelete {
}
Symbol semTake {
}
Symbol lstFirst {
}
Symbol strcmp {
}
Symbol lstNext {
}
Symbol semGive {
}
Symbol fsimStart {
}
Symbol errnoSet {
}
Symbol open {
}
Symbol taskIdSelf {
}
Symbol printf {
}
Symbol lseek {
}
Symbol memset {
}
Symbol write {
}
Symbol close {
}
Symbol lstAdd {
}
Symbol ioctl {
}
Symbol fsimDevCreate {
}
Symbol fsimChipCreate {
}
Symbol malloc {
}
Symbol free {
}
Symbol fsimChipDelete {
}
Symbol fsimCreate {
}
Symbol strlen {
}
Symbol strcpy {
}
Symbol fsimRead {
}
Symbol fsimErase {
}
Symbol fsimWritePage {
}
Symbol fsimWritePages {
}
Symbol fsimWrite {
}
Symbol fsimReadPage {
}
Symbol fsimReadPages {
}
Symbol fsimIsBlankPage {
}
Symbol lstDelete {
}
Symbol fsimDevDelete {
}
Symbol fsimDelete {
}
Symbol read {
}
Symbol fsimMount {
}
Symbol fsimUnmount {
}
Symbol errnoGet {
}
Symbol fsimRun {
}
Symbol fsimStop {
}
Symbol fsimDevPageRW {
}
Symbol fsimDevPagesRW {
}
Symbol getChipBlkNo {
}
Symbol getChipPageNo {
}
Symbol fsimIoctl {
}
Symbol fsimShow {
}
Symbol fsimShowAll {
}
Symbol fsimPrintBuf {
}
Symbol memcpy {
}
Symbol fsimDump {
}
Symbol fsimDumpData {
}
Symbol fsimDumpOob {
}
Symbol fsimImageSave {
}
Symbol fsimImageCopy {
}
Symbol fsimDevStatChip {
}
Symbol fsimStatChip {
}
Symbol fsimStatBlk {
}
Symbol fsimStatPage {
}
Symbol reboot {
}
Symbol fsimMarkBad {
}
Symbol fsimUnmarkBad {
}
Symbol fsimIsBadBlock {
}
Symbol fsimInjectError {
}
Symbol fsimErrorGenerator {
}
Symbol fsimRemoveError {
}
Symbol fsimReboot {
}
Symbol taskIdVerify {
}
Symbol fsimInvalidateMap {
}
Symbol fsimIsPageMapped {
}
Symbol fsimUpdateMapStatus {
}
Symbol fsimFind {
}
Symbol fsimDbgTurn {
}
Symbol tickGet {
}
Symbol srand {
}
Symbol rand {
}
Symbol semDelete {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol fsimCrc32 {
}
Symbol mtdRegisterNotify {
}
Symbol calloc {
}
Symbol mtdUnRegisterNotify {
}
Symbol mtdFindAndNotify {
}
Symbol mtdNotify {
}
Symbol fsimTffsRegister {
}
Symbol noOfDrives {
}
Symbol flSocketOf {
}
Symbol needCheckRAM {
}
Symbol printErr {
}
Symbol strncpy {
}
Symbol fsimTffsList {
}
Symbol fsimNorIdentify {
}
Symbol flIdentifyRegister {
}
Symbol flInitSocket {
}
Symbol fsimTffsUnregister {
}
Symbol fsimTffsShow {
}
Symbol fsimTffsFind {
}
Symbol flSetWindowSize {
}
Symbol fsimTffsFormat {
}
Symbol tffsDevFormat {
}
Symbol fsimNorMap {
}
ObjectFile libbdmSim.a::fsimLib.o {
	NAME Object file fsimLib.o from archive libbdmSim.a
	EXPORTS fsimInit fsimStart fsimDevCreate fsimCreate fsimRead fsimErase fsimWritePage fsimWritePages fsimWrite fsimReadPage fsimReadPages fsimIsBlankPage fsimDevDelete fsimDelete fsimMount fsimUnmount fsimRun fsimStop fsimDevPageRW fsimDevPagesRW getChipBlkNo getChipPageNo fsimIoctl fsimShow fsimShowAll fsimPrintBuf fsimDump fsimDumpData fsimDumpOob fsimImageSave fsimImageCopy fsimDevStatChip fsimStatChip fsimStatBlk fsimStatPage fsimMarkBad fsimUnmarkBad fsimIsBadBlock fsimInjectError fsimErrorGenerator fsimRemoveError fsimReboot fsimInvalidateMap fsimIsPageMapped fsimUpdateMapStatus fsimFind fsimDbgTurn
	IMPORTS .TOC. lstInit semMCreate mtdDevCreate mtdDevDelete semTake lstFirst strcmp lstNext semGive errnoSet open taskIdSelf printf lseek memset write close lstAdd ioctl fsimChipCreate malloc free fsimChipDelete strlen strcpy lstDelete read errnoGet memcpy reboot taskIdVerify
	DECLARES 
	USES 
}
Module fsimLib.o {
	OBJECT += libbdmSim.a::fsimLib.o
}
ObjectFile libbdmSim.a::fsimChip.o {
	NAME Object file fsimChip.o from archive libbdmSim.a
	EXPORTS fsimChipCreate fsimChipDelete
	IMPORTS .TOC. lseek taskIdSelf write printf errnoSet ioctl semTake memset semGive errnoGet read tickGet srand rand open close malloc semMCreate memcpy semDelete free sysClkRateGet taskDelay
	DECLARES 
	USES 
}
Module fsimChip.o {
	OBJECT += libbdmSim.a::fsimChip.o
}
ObjectFile libbdmSim.a::fsimMtd.o {
	NAME Object file fsimMtd.o from archive libbdmSim.a
	EXPORTS fsimCrc32 mtdRegisterNotify mtdUnRegisterNotify mtdFindAndNotify mtdNotify mtdDevCreate mtdDevDelete
	IMPORTS .TOC. malloc printf memset free memcpy fsimInjectError taskIdSelf fsimIsBadBlock calloc strcmp
	DECLARES 
	USES 
}
Module fsimMtd.o {
	OBJECT += libbdmSim.a::fsimMtd.o
}
ObjectFile libbdmSim.a::fsimTffs.o {
	NAME Object file fsimTffs.o from archive libbdmSim.a
	EXPORTS fsimTffsRegister fsimNorIdentify fsimTffsUnregister fsimTffsShow fsimTffsFind fsimTffsFormat fsimNorMap
	IMPORTS .TOC. noOfDrives flSocketOf fsimFind printf memset needCheckRAM malloc printErr strncpy lstAdd flIdentifyRegister flInitSocket lstDelete free lstFirst lstNext flSetWindowSize tffsDevFormat fsimInvalidateMap fsimIsPageMapped fsimUpdateMapStatus
	DECLARES fsimTffsList
	USES 
}
Module fsimTffs.o {
	OBJECT += libbdmSim.a::fsimTffs.o
}
Library libbdmSim.a {
	MODULES libbdmSim.a::fsimLib.o libbdmSim.a::fsimChip.o libbdmSim.a::fsimMtd.o libbdmSim.a::fsimTffs.o
}
Symbol .TOC. {
}
Symbol lstInit {
}
Symbol semMCreate {
}
Symbol fsimInit {
}
Symbol mtdDevCreate {
}
Symbol mtdDevDelete {
}
Symbol semTake {
}
Symbol lstFirst {
}
Symbol strcmp {
}
Symbol lstNext {
}
Symbol semGive {
}
Symbol fsimStart {
}
Symbol errnoSet {
}
Symbol open {
}
Symbol taskIdSelf {
}
Symbol printf {
}
Symbol lseek {
}
Symbol memset {
}
Symbol write {
}
Symbol close {
}
Symbol lstAdd {
}
Symbol ioctl {
}
Symbol fsimDevCreate {
}
Symbol fsimChipCreate {
}
Symbol malloc {
}
Symbol free {
}
Symbol fsimChipDelete {
}
Symbol fsimCreate {
}
Symbol strlen {
}
Symbol strcpy {
}
Symbol fsimRead {
}
Symbol fsimErase {
}
Symbol fsimWritePage {
}
Symbol fsimWritePages {
}
Symbol fsimWrite {
}
Symbol fsimReadPage {
}
Symbol fsimReadPages {
}
Symbol fsimIsBlankPage {
}
Symbol lstDelete {
}
Symbol fsimDevDelete {
}
Symbol fsimDelete {
}
Symbol read {
}
Symbol fsimMount {
}
Symbol fsimUnmount {
}
Symbol errnoGet {
}
Symbol fsimRun {
}
Symbol fsimStop {
}
Symbol fsimDevPageRW {
}
Symbol fsimDevPagesRW {
}
Symbol getChipBlkNo {
}
Symbol getChipPageNo {
}
Symbol fsimIoctl {
}
Symbol fsimShow {
}
Symbol fsimShowAll {
}
Symbol fsimPrintBuf {
}
Symbol memcpy {
}
Symbol fsimDump {
}
Symbol fsimDumpData {
}
Symbol fsimDumpOob {
}
Symbol fsimImageSave {
}
Symbol fsimImageCopy {
}
Symbol fsimDevStatChip {
}
Symbol fsimStatChip {
}
Symbol fsimStatBlk {
}
Symbol fsimStatPage {
}
Symbol reboot {
}
Symbol fsimMarkBad {
}
Symbol fsimUnmarkBad {
}
Symbol fsimIsBadBlock {
}
Symbol fsimInjectError {
}
Symbol fsimErrorGenerator {
}
Symbol fsimRemoveError {
}
Symbol fsimReboot {
}
Symbol taskIdVerify {
}
Symbol fsimInvalidateMap {
}
Symbol fsimIsPageMapped {
}
Symbol fsimUpdateMapStatus {
}
Symbol fsimFind {
}
Symbol fsimDbgTurn {
}
Symbol tickGet {
}
Symbol srand {
}
Symbol rand {
}
Symbol semDelete {
}
Symbol sysClkRateGet {
}
Symbol taskDelay {
}
Symbol fsimCrc32 {
}
Symbol mtdRegisterNotify {
}
Symbol calloc {
}
Symbol mtdUnRegisterNotify {
}
Symbol mtdFindAndNotify {
}
Symbol mtdNotify {
}
Symbol fsimTffsRegister {
}
Symbol noOfDrives {
}
Symbol flSocketOf {
}
Symbol needCheckRAM {
}
Symbol printErr {
}
Symbol strncpy {
}
Symbol fsimTffsList {
}
Symbol fsimNorIdentify {
}
Symbol flIdentifyRegister {
}
Symbol flInitSocket {
}
Symbol fsimTffsUnregister {
}
Symbol fsimTffsShow {
}
Symbol fsimTffsFind {
}
Symbol flSetWindowSize {
}
Symbol fsimTffsFormat {
}
Symbol tffsDevFormat {
}
Symbol fsimNorMap {
}
ObjectFile libbdmSim.a::fsimLib.o {
	NAME Object file fsimLib.o from archive libbdmSim.a
	EXPORTS fsimInit fsimStart fsimDevCreate fsimCreate fsimRead fsimErase fsimWritePage fsimWritePages fsimWrite fsimReadPage fsimReadPages fsimIsBlankPage fsimDevDelete fsimDelete fsimMount fsimUnmount fsimRun fsimStop fsimDevPageRW fsimDevPagesRW getChipBlkNo getChipPageNo fsimIoctl fsimShow fsimShowAll fsimPrintBuf fsimDump fsimDumpData fsimDumpOob fsimImageSave fsimImageCopy fsimDevStatChip fsimStatChip fsimStatBlk fsimStatPage fsimMarkBad fsimUnmarkBad fsimIsBadBlock fsimInjectError fsimErrorGenerator fsimRemoveError fsimReboot fsimInvalidateMap fsimIsPageMapped fsimUpdateMapStatus fsimFind fsimDbgTurn
	IMPORTS .TOC. lstInit semMCreate mtdDevCreate mtdDevDelete semTake lstFirst strcmp lstNext semGive errnoSet open taskIdSelf printf lseek memset write close lstAdd ioctl fsimChipCreate malloc free fsimChipDelete strlen strcpy lstDelete read errnoGet memcpy reboot taskIdVerify
	DECLARES 
	USES 
}
Module fsimLib.o {
	OBJECT += libbdmSim.a::fsimLib.o
}
ObjectFile libbdmSim.a::fsimChip.o {
	NAME Object file fsimChip.o from archive libbdmSim.a
	EXPORTS fsimChipCreate fsimChipDelete
	IMPORTS .TOC. lseek taskIdSelf write printf errnoSet ioctl semTake memset semGive errnoGet read tickGet srand rand open close malloc semMCreate memcpy semDelete free sysClkRateGet taskDelay
	DECLARES 
	USES 
}
Module fsimChip.o {
	OBJECT += libbdmSim.a::fsimChip.o
}
ObjectFile libbdmSim.a::fsimMtd.o {
	NAME Object file fsimMtd.o from archive libbdmSim.a
	EXPORTS fsimCrc32 mtdRegisterNotify mtdUnRegisterNotify mtdFindAndNotify mtdNotify mtdDevCreate mtdDevDelete
	IMPORTS .TOC. malloc printf memset free memcpy fsimInjectError taskIdSelf fsimIsBadBlock calloc strcmp
	DECLARES 
	USES 
}
Module fsimMtd.o {
	OBJECT += libbdmSim.a::fsimMtd.o
}
ObjectFile libbdmSim.a::fsimTffs.o {
	NAME Object file fsimTffs.o from archive libbdmSim.a
	EXPORTS fsimTffsRegister fsimNorIdentify fsimTffsUnregister fsimTffsShow fsimTffsFind fsimTffsFormat fsimNorMap
	IMPORTS .TOC. noOfDrives flSocketOf fsimFind printf memset needCheckRAM malloc printErr strncpy lstAdd flIdentifyRegister flInitSocket lstDelete free lstFirst lstNext flSetWindowSize tffsDevFormat fsimInvalidateMap fsimIsPageMapped fsimUpdateMapStatus
	DECLARES fsimTffsList
	USES 
}
Module fsimTffs.o {
	OBJECT += libbdmSim.a::fsimTffs.o
}
Library libbdmSim.a {
	MODULES libbdmSim.a::fsimLib.o libbdmSim.a::fsimChip.o libbdmSim.a::fsimMtd.o libbdmSim.a::fsimTffs.o
}
