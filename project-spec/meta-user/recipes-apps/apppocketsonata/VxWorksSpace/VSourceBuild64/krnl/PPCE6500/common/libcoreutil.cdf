Symbol .TOC. {
}
Symbol avlUintInsert {
}
Symbol avlUintDelete {
}
Symbol avlUintSearch {
}
Symbol avlUintSuccessorGet {
}
Symbol avlUintPredecessorGet {
}
Symbol avlUintMinimumGet {
}
Symbol avlUintMaximumGet {
}
Symbol avlUintTreeWalk {
}
Symbol bcmp {
}
Symbol binvert {
}
Symbol bswap {
}
Symbol uswab {
}
Symbol bzero {
}
Symbol bfill {
}
Symbol index {
}
Symbol rindex {
}
Symbol strlen {
}
Symbol bitFirstGet {
}
Symbol ffsMsb {
}
Symbol dllInit {
}
Symbol dllTerminate {
}
Symbol dllInsert {
}
Symbol dllAdd {
}
Symbol dllRemove {
}
Symbol dllGet {
}
Symbol dllCount {
}
Symbol dllEach {
}
Symbol lstInit {
}
Symbol lstInsert {
}
Symbol lstAdd {
}
Symbol lstDelete {
}
Symbol lstCount {
}
Symbol lstFirst {
}
Symbol lstLast {
}
Symbol lstGet {
}
Symbol lstPrevious {
}
Symbol lstNext {
}
Symbol lstFind {
}
Symbol lstConcat {
}
Symbol lstExtract {
}
Symbol lstNth {
}
Symbol lstNStep {
}
Symbol abs {
}
Symbol lstFree2 {
}
Symbol lstFree {
}
Symbol free {
}
Symbol rngCreate {
}
Symbol malloc {
}
Symbol rngDelete {
}
Symbol rngFlush {
}
Symbol rngBufGet {
}
Symbol bcopy {
}
Symbol rngBufPut {
}
Symbol rngIsEmpty {
}
Symbol rngIsFull {
}
Symbol rngFreeBytes {
}
Symbol rngNBytes {
}
Symbol rngPutAhead {
}
Symbol rngMoveAhead {
}
Symbol sllInit {
}
Symbol sllTerminate {
}
Symbol sllCount {
}
Symbol sllGet {
}
Symbol sllPutAtHead {
}
Symbol sllPutAtTail {
}
Symbol sllRemove {
}
Symbol sllPrevious {
}
Symbol sllEach {
}
Symbol hookAddToTail {
}
Symbol taskIdSelf {
}
Symbol kernelLockTake {
}
Symbol windExit {
}
Symbol errnoSet {
}
Symbol hookAddToHead {
}
Symbol hookDelete {
}
Symbol hookFind {
}
Symbol hookTblInit {
}
Symbol qFifoClassId {
}
Symbol qFifoInit {
}
Symbol semMInitialize {
}
Symbol hookTblAddToTail {
}
Symbol intContext {
}
Symbol __errno {
}
Symbol semMTake {
}
Symbol semMGive {
}
Symbol vxAtomicCas {
}
Symbol windPendQPut {
}
Symbol hookTblAddToHead {
}
Symbol hookTblDelete {
}
Symbol hookTblUpdatersUnpend {
}
Symbol kernelLockTry {
}
Symbol windPendQFlush {
}
Symbol workQAdd1 {
}
Symbol hookTblFind {
}
Symbol vxAtomicOr {
}
Symbol vxAtomic32Inc {
}
Symbol vxAtomicAnd {
}
Symbol vxAtomic32Dec {
}
Symbol datasetIterate {
}
Symbol wrs_kernel_data_set_start {
}
Symbol wrs_kernel_data_set_end {
}
Symbol strncmp {
}
Symbol strendcpy {
}
Symbol skipPrefix {
}
Symbol getpagesize {
}
Symbol vmLibInfo {
}
Symbol applLoggerInit {
}
Symbol applUtilLogSem {
}
Symbol catInfo {
}
Symbol applUtilInstInit {
}
Symbol applLoggerStop {
}
Symbol logLevelChange {
}
Symbol logDecorationChange {
}
Symbol loggerInfoShow {
}
Symbol printf {
}
Symbol initApplLogger {
}
Symbol stopApplLogger {
}
Symbol changeLogLevel {
}
Symbol showLoggerInfo {
}
Symbol _applLog {
}
Symbol snprintf {
}
Symbol strerror_r {
}
Symbol semTake {
}
Symbol write {
}
Symbol vfdprintf {
}
Symbol semGive {
}
Symbol avlUint64Insert {
}
Symbol avlUint64Delete {
}
Symbol avlUint64Search {
}
Symbol avlUint64SuccessorGet {
}
Symbol avlUint64PredecessorGet {
}
Symbol avlUint64MinimumGet {
}
Symbol avlUint64MaximumGet {
}
Symbol avlUint64TreeWalk {
}
Symbol __ctype_toupper {
}
Symbol __ctype_tolower {
}
Symbol memmem {
}
Symbol memimem {
}
Symbol hookShow {
}
Symbol _func_symFindSymbol {
}
Symbol sysSymTbl {
}
Symbol _func_symNameGet {
}
Symbol _func_symValueGet {
}
Symbol cplusDemangle {
}
Symbol hookTblShow {
}
Symbol objRoutineNameGet {
}
Symbol getopt_r {
}
Symbol strchr {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol getopt {
}
Symbol opterr {
}
Symbol optind {
}
Symbol optopt {
}
Symbol optreset {
}
Symbol optarg {
}
Symbol getoptInit {
}
Symbol getOptServ {
}
Symbol strtok_r {
}
Symbol avlInsert {
}
Symbol avlDelete {
}
Symbol avlSearch {
}
Symbol avlSuccessorGet {
}
Symbol avlPredecessorGet {
}
Symbol avlMinimumGet {
}
Symbol avlMaximumGet {
}
Symbol avlTreeWalk {
}
Symbol avlInsertInform {
}
Symbol avlRemoveInsert {
}
Symbol dllCreate {
}
Symbol dllDelete {
}
Symbol hashTblInit {
}
Symbol handleInit {
}
Symbol hashTblCreate {
}
Symbol hashTblDestroy {
}
Symbol handleTerminate {
}
Symbol hashTblDelete {
}
Symbol hashTblTerminate {
}
Symbol hashTblPut {
}
Symbol hashTblFind {
}
Symbol hashTblRemove {
}
Symbol hashTblEach {
}
Symbol hashFuncIterScale {
}
Symbol hashFuncModulo {
}
Symbol hashFuncMultiply {
}
Symbol hashKeyCmp {
}
Symbol hashKeyStrCmp {
}
Symbol strcmp {
}
Symbol sllCreate {
}
Symbol sllDelete {
}
Symbol _procNumWasSet {
}
ObjectFile libcoreutil.a::avlUintLib.o {
	NAME Object file avlUintLib.o from archive libcoreutil.a
	EXPORTS avlUintInsert avlUintDelete avlUintSearch avlUintSuccessorGet avlUintPredecessorGet avlUintMinimumGet avlUintMaximumGet avlUintTreeWalk
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module avlUintLib.o {
	OBJECT += libcoreutil.a::avlUintLib.o
}
ObjectFile libcoreutil.a::bLib.o {
	NAME Object file bLib.o from archive libcoreutil.a
	EXPORTS bcmp binvert bswap uswab bzero index rindex
	IMPORTS .TOC. bfill strlen
	DECLARES 
	USES 
}
Module bLib.o {
	OBJECT += libcoreutil.a::bLib.o
}
ObjectFile libcoreutil.a::bmpLib.o {
	NAME Object file bmpLib.o from archive libcoreutil.a
	EXPORTS bitFirstGet
	IMPORTS .TOC. ffsMsb
	DECLARES 
	USES 
}
Module bmpLib.o {
	OBJECT += libcoreutil.a::bmpLib.o
}
ObjectFile libcoreutil.a::dllLib.o {
	NAME Object file dllLib.o from archive libcoreutil.a
	EXPORTS dllInit dllTerminate dllInsert dllAdd dllRemove dllGet dllCount dllEach
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module dllLib.o {
	OBJECT += libcoreutil.a::dllLib.o
}
ObjectFile libcoreutil.a::ffsLib.o {
	NAME Object file ffsLib.o from archive libcoreutil.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module ffsLib.o {
	OBJECT += libcoreutil.a::ffsLib.o
}
ObjectFile libcoreutil.a::lstLib.o {
	NAME Object file lstLib.o from archive libcoreutil.a
	EXPORTS lstInit lstInsert lstAdd lstDelete lstCount lstFirst lstLast lstGet lstPrevious lstNext lstFind lstConcat lstExtract lstNth lstNStep lstFree2 lstFree
	IMPORTS .TOC. abs free
	DECLARES 
	USES 
}
Module lstLib.o {
	OBJECT += libcoreutil.a::lstLib.o
}
ObjectFile libcoreutil.a::rngLib.o {
	NAME Object file rngLib.o from archive libcoreutil.a
	EXPORTS rngCreate rngDelete rngFlush rngBufGet rngBufPut rngIsEmpty rngIsFull rngFreeBytes rngNBytes rngPutAhead rngMoveAhead
	IMPORTS .TOC. malloc free bcopy
	DECLARES 
	USES 
}
Module rngLib.o {
	OBJECT += libcoreutil.a::rngLib.o
}
ObjectFile libcoreutil.a::sllLib.o {
	NAME Object file sllLib.o from archive libcoreutil.a
	EXPORTS sllInit sllTerminate sllCount sllGet sllPutAtHead sllPutAtTail sllRemove sllPrevious sllEach
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module sllLib.o {
	OBJECT += libcoreutil.a::sllLib.o
}
ObjectFile libcoreutil.a::hookLib.o {
	NAME Object file hookLib.o from archive libcoreutil.a
	EXPORTS hookAddToTail hookAddToHead hookDelete hookFind
	IMPORTS .TOC. taskIdSelf kernelLockTake windExit errnoSet
	DECLARES 
	USES 
}
Module hookLib.o {
	OBJECT += libcoreutil.a::hookLib.o
}
ObjectFile libcoreutil.a::hookTblLib.o {
	NAME Object file hookTblLib.o from archive libcoreutil.a
	EXPORTS hookTblInit hookTblAddToTail hookTblAddToHead hookTblDelete hookTblUpdatersUnpend hookTblFind
	IMPORTS .TOC. qFifoClassId qFifoInit semMInitialize intContext __errno taskIdSelf semMTake semMGive errnoSet vxAtomicCas kernelLockTake windPendQPut windExit kernelLockTry windPendQFlush workQAdd1 vxAtomicOr vxAtomic32Inc vxAtomicAnd vxAtomic32Dec
	DECLARES 
	USES 
}
Module hookTblLib.o {
	OBJECT += libcoreutil.a::hookTblLib.o
}
ObjectFile libcoreutil.a::dataset.o {
	NAME Object file dataset.o from archive libcoreutil.a
	EXPORTS datasetIterate
	IMPORTS .TOC. wrs_kernel_data_set_start wrs_kernel_data_set_end strncmp
	DECLARES 
	USES 
}
Module dataset.o {
	OBJECT += libcoreutil.a::dataset.o
}
ObjectFile libcoreutil.a::strendcpy.o {
	NAME Object file strendcpy.o from archive libcoreutil.a
	EXPORTS strendcpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strendcpy.o {
	OBJECT += libcoreutil.a::strendcpy.o
}
ObjectFile libcoreutil.a::skipPrefix.o {
	NAME Object file skipPrefix.o from archive libcoreutil.a
	EXPORTS skipPrefix
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module skipPrefix.o {
	OBJECT += libcoreutil.a::skipPrefix.o
}
ObjectFile libcoreutil.a::getpagesize.o {
	NAME Object file getpagesize.o from archive libcoreutil.a
	EXPORTS getpagesize
	IMPORTS .TOC. vmLibInfo
	DECLARES 
	USES 
}
Module getpagesize.o {
	OBJECT += libcoreutil.a::getpagesize.o
}
ObjectFile libcoreutil.a::applUtilLib.o {
	NAME Object file applUtilLib.o from archive libcoreutil.a
	EXPORTS applLoggerInit catInfo applUtilInstInit applLoggerStop logLevelChange logDecorationChange loggerInfoShow initApplLogger stopApplLogger changeLogLevel showLoggerInfo _applLog
	IMPORTS .TOC. __errno printf snprintf strerror_r strncmp semTake write vfdprintf semGive
	DECLARES applUtilLogSem
	USES 
}
Module applUtilLib.o {
	OBJECT += libcoreutil.a::applUtilLib.o
}
ObjectFile libcoreutil.a::avlUint64Lib.o {
	NAME Object file avlUint64Lib.o from archive libcoreutil.a
	EXPORTS avlUint64Insert avlUint64Delete avlUint64Search avlUint64SuccessorGet avlUint64PredecessorGet avlUint64MinimumGet avlUint64MaximumGet avlUint64TreeWalk
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module avlUint64Lib.o {
	OBJECT += libcoreutil.a::avlUint64Lib.o
}
ObjectFile libcoreutil.a::memmem.o {
	NAME Object file memmem.o from archive libcoreutil.a
	EXPORTS memmem memimem
	IMPORTS .TOC. __ctype_toupper __ctype_tolower
	DECLARES 
	USES 
}
Module memmem.o {
	OBJECT += libcoreutil.a::memmem.o
}
ObjectFile libcoreutil.a::hookShow.o {
	NAME Object file hookShow.o from archive libcoreutil.a
	EXPORTS hookShow
	IMPORTS .TOC. _func_symFindSymbol sysSymTbl _func_symNameGet _func_symValueGet cplusDemangle printf
	DECLARES 
	USES 
}
Module hookShow.o {
	OBJECT += libcoreutil.a::hookShow.o
}
ObjectFile libcoreutil.a::hookTblShow.o {
	NAME Object file hookTblShow.o from archive libcoreutil.a
	EXPORTS hookTblShow
	IMPORTS .TOC. vxAtomicOr vxAtomic32Inc objRoutineNameGet printf vxAtomicAnd vxAtomic32Dec vxAtomicCas hookTblUpdatersUnpend
	DECLARES 
	USES 
}
Module hookTblShow.o {
	OBJECT += libcoreutil.a::hookTblShow.o
}
ObjectFile libcoreutil.a::getopt.o {
	NAME Object file getopt.o from archive libcoreutil.a
	EXPORTS getopt_r getopt opterr optind getoptInit getOptServ
	IMPORTS .TOC. strchr __stderr fprintf strtok_r
	DECLARES optopt optreset optarg
	USES 
}
Module getopt.o {
	OBJECT += libcoreutil.a::getopt.o
}
ObjectFile libcoreutil.a::avlLib.o {
	NAME Object file avlLib.o from archive libcoreutil.a
	EXPORTS avlInsert avlDelete avlSearch avlSuccessorGet avlPredecessorGet avlMinimumGet avlMaximumGet avlTreeWalk avlInsertInform avlRemoveInsert
	IMPORTS .TOC. printf
	DECLARES 
	USES 
}
Module avlLib.o {
	OBJECT += libcoreutil.a::avlLib.o
}
ObjectFile libcoreutil.a::dllCreateLib.o {
	NAME Object file dllCreateLib.o from archive libcoreutil.a
	EXPORTS dllCreate dllDelete
	IMPORTS .TOC. malloc dllInit free
	DECLARES 
	USES 
}
Module dllCreateLib.o {
	OBJECT += libcoreutil.a::dllCreateLib.o
}
ObjectFile libcoreutil.a::hashLib.o {
	NAME Object file hashLib.o from archive libcoreutil.a
	EXPORTS hashTblInit hashTblCreate hashTblDestroy hashTblDelete hashTblTerminate hashTblPut hashTblFind hashTblRemove hashTblEach hashFuncIterScale hashFuncModulo hashFuncMultiply hashKeyCmp hashKeyStrCmp
	IMPORTS .TOC. sllInit handleInit malloc handleTerminate free sllPutAtHead sllPrevious sllRemove sllEach ffsMsb strcmp
	DECLARES 
	USES 
}
Module hashLib.o {
	OBJECT += libcoreutil.a::hashLib.o
}
ObjectFile libcoreutil.a::sllCreateLib.o {
	NAME Object file sllCreateLib.o from archive libcoreutil.a
	EXPORTS sllCreate sllDelete
	IMPORTS .TOC. malloc sllInit free
	DECLARES 
	USES 
}
Module sllCreateLib.o {
	OBJECT += libcoreutil.a::sllCreateLib.o
}
ObjectFile libcoreutil.a::procNumSetFuncBind.o {
	NAME Object file procNumSetFuncBind.o from archive libcoreutil.a
	EXPORTS _procNumWasSet
	IMPORTS 
	DECLARES 
	USES 
}
Module procNumSetFuncBind.o {
	OBJECT += libcoreutil.a::procNumSetFuncBind.o
}
Library libcoreutil.a {
	MODULES libcoreutil.a::avlUintLib.o libcoreutil.a::bLib.o libcoreutil.a::bmpLib.o libcoreutil.a::dllLib.o libcoreutil.a::ffsLib.o libcoreutil.a::lstLib.o libcoreutil.a::rngLib.o libcoreutil.a::sllLib.o libcoreutil.a::hookLib.o libcoreutil.a::hookTblLib.o libcoreutil.a::dataset.o libcoreutil.a::strendcpy.o libcoreutil.a::skipPrefix.o libcoreutil.a::getpagesize.o libcoreutil.a::applUtilLib.o libcoreutil.a::avlUint64Lib.o libcoreutil.a::memmem.o libcoreutil.a::hookShow.o libcoreutil.a::hookTblShow.o libcoreutil.a::getopt.o libcoreutil.a::avlLib.o libcoreutil.a::dllCreateLib.o libcoreutil.a::hashLib.o libcoreutil.a::sllCreateLib.o libcoreutil.a::procNumSetFuncBind.o
}
Symbol .TOC. {
}
Symbol avlUintInsert {
}
Symbol avlUintDelete {
}
Symbol avlUintSearch {
}
Symbol avlUintSuccessorGet {
}
Symbol avlUintPredecessorGet {
}
Symbol avlUintMinimumGet {
}
Symbol avlUintMaximumGet {
}
Symbol avlUintTreeWalk {
}
Symbol bcmp {
}
Symbol binvert {
}
Symbol bswap {
}
Symbol uswab {
}
Symbol bzero {
}
Symbol bfill {
}
Symbol index {
}
Symbol rindex {
}
Symbol strlen {
}
Symbol bitFirstGet {
}
Symbol ffsMsb {
}
Symbol dllInit {
}
Symbol dllTerminate {
}
Symbol dllInsert {
}
Symbol dllAdd {
}
Symbol dllRemove {
}
Symbol dllGet {
}
Symbol dllCount {
}
Symbol dllEach {
}
Symbol lstInit {
}
Symbol lstInsert {
}
Symbol lstAdd {
}
Symbol lstDelete {
}
Symbol lstCount {
}
Symbol lstFirst {
}
Symbol lstLast {
}
Symbol lstGet {
}
Symbol lstPrevious {
}
Symbol lstNext {
}
Symbol lstFind {
}
Symbol lstConcat {
}
Symbol lstExtract {
}
Symbol lstNth {
}
Symbol lstNStep {
}
Symbol abs {
}
Symbol lstFree2 {
}
Symbol lstFree {
}
Symbol free {
}
Symbol rngCreate {
}
Symbol malloc {
}
Symbol rngDelete {
}
Symbol rngFlush {
}
Symbol rngBufGet {
}
Symbol bcopy {
}
Symbol rngBufPut {
}
Symbol rngIsEmpty {
}
Symbol rngIsFull {
}
Symbol rngFreeBytes {
}
Symbol rngNBytes {
}
Symbol rngPutAhead {
}
Symbol rngMoveAhead {
}
Symbol sllInit {
}
Symbol sllTerminate {
}
Symbol sllCount {
}
Symbol sllGet {
}
Symbol sllPutAtHead {
}
Symbol sllPutAtTail {
}
Symbol sllRemove {
}
Symbol sllPrevious {
}
Symbol sllEach {
}
Symbol hookAddToTail {
}
Symbol taskIdSelf {
}
Symbol kernelLockTake {
}
Symbol windExit {
}
Symbol errnoSet {
}
Symbol hookAddToHead {
}
Symbol hookDelete {
}
Symbol hookFind {
}
Symbol hookTblInit {
}
Symbol qFifoClassId {
}
Symbol qFifoInit {
}
Symbol semMInitialize {
}
Symbol hookTblAddToTail {
}
Symbol intContext {
}
Symbol __errno {
}
Symbol semMTake {
}
Symbol semMGive {
}
Symbol vxAtomicCas {
}
Symbol windPendQPut {
}
Symbol hookTblAddToHead {
}
Symbol hookTblDelete {
}
Symbol hookTblUpdatersUnpend {
}
Symbol kernelLockTry {
}
Symbol windPendQFlush {
}
Symbol workQAdd1 {
}
Symbol hookTblFind {
}
Symbol vxAtomicOr {
}
Symbol vxAtomic32Inc {
}
Symbol vxAtomicAnd {
}
Symbol vxAtomic32Dec {
}
Symbol datasetIterate {
}
Symbol wrs_kernel_data_set_start {
}
Symbol wrs_kernel_data_set_end {
}
Symbol strncmp {
}
Symbol strendcpy {
}
Symbol skipPrefix {
}
Symbol getpagesize {
}
Symbol vmLibInfo {
}
Symbol applLoggerInit {
}
Symbol applUtilLogSem {
}
Symbol catInfo {
}
Symbol applUtilInstInit {
}
Symbol applLoggerStop {
}
Symbol logLevelChange {
}
Symbol logDecorationChange {
}
Symbol loggerInfoShow {
}
Symbol printf {
}
Symbol initApplLogger {
}
Symbol stopApplLogger {
}
Symbol changeLogLevel {
}
Symbol showLoggerInfo {
}
Symbol _applLog {
}
Symbol snprintf {
}
Symbol strerror_r {
}
Symbol semTake {
}
Symbol write {
}
Symbol vfdprintf {
}
Symbol semGive {
}
Symbol avlUint64Insert {
}
Symbol avlUint64Delete {
}
Symbol avlUint64Search {
}
Symbol avlUint64SuccessorGet {
}
Symbol avlUint64PredecessorGet {
}
Symbol avlUint64MinimumGet {
}
Symbol avlUint64MaximumGet {
}
Symbol avlUint64TreeWalk {
}
Symbol __ctype_toupper {
}
Symbol __ctype_tolower {
}
Symbol memmem {
}
Symbol memimem {
}
Symbol hookShow {
}
Symbol _func_symFindSymbol {
}
Symbol sysSymTbl {
}
Symbol _func_symNameGet {
}
Symbol _func_symValueGet {
}
Symbol cplusDemangle {
}
Symbol hookTblShow {
}
Symbol objRoutineNameGet {
}
Symbol getopt_r {
}
Symbol strchr {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol getopt {
}
Symbol opterr {
}
Symbol optind {
}
Symbol optopt {
}
Symbol optreset {
}
Symbol optarg {
}
Symbol getoptInit {
}
Symbol getOptServ {
}
Symbol strtok_r {
}
Symbol avlInsert {
}
Symbol avlDelete {
}
Symbol avlSearch {
}
Symbol avlSuccessorGet {
}
Symbol avlPredecessorGet {
}
Symbol avlMinimumGet {
}
Symbol avlMaximumGet {
}
Symbol avlTreeWalk {
}
Symbol avlInsertInform {
}
Symbol avlRemoveInsert {
}
Symbol dllCreate {
}
Symbol dllDelete {
}
Symbol hashTblInit {
}
Symbol handleInit {
}
Symbol hashTblCreate {
}
Symbol hashTblDestroy {
}
Symbol handleTerminate {
}
Symbol hashTblDelete {
}
Symbol hashTblTerminate {
}
Symbol hashTblPut {
}
Symbol hashTblFind {
}
Symbol hashTblRemove {
}
Symbol hashTblEach {
}
Symbol hashFuncIterScale {
}
Symbol hashFuncModulo {
}
Symbol hashFuncMultiply {
}
Symbol hashKeyCmp {
}
Symbol hashKeyStrCmp {
}
Symbol strcmp {
}
Symbol sllCreate {
}
Symbol sllDelete {
}
Symbol _procNumWasSet {
}
ObjectFile libcoreutil.a::avlUintLib.o {
	NAME Object file avlUintLib.o from archive libcoreutil.a
	EXPORTS avlUintInsert avlUintDelete avlUintSearch avlUintSuccessorGet avlUintPredecessorGet avlUintMinimumGet avlUintMaximumGet avlUintTreeWalk
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module avlUintLib.o {
	OBJECT += libcoreutil.a::avlUintLib.o
}
ObjectFile libcoreutil.a::bLib.o {
	NAME Object file bLib.o from archive libcoreutil.a
	EXPORTS bcmp binvert bswap uswab bzero index rindex
	IMPORTS .TOC. bfill strlen
	DECLARES 
	USES 
}
Module bLib.o {
	OBJECT += libcoreutil.a::bLib.o
}
ObjectFile libcoreutil.a::bmpLib.o {
	NAME Object file bmpLib.o from archive libcoreutil.a
	EXPORTS bitFirstGet
	IMPORTS .TOC. ffsMsb
	DECLARES 
	USES 
}
Module bmpLib.o {
	OBJECT += libcoreutil.a::bmpLib.o
}
ObjectFile libcoreutil.a::dllLib.o {
	NAME Object file dllLib.o from archive libcoreutil.a
	EXPORTS dllInit dllTerminate dllInsert dllAdd dllRemove dllGet dllCount dllEach
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module dllLib.o {
	OBJECT += libcoreutil.a::dllLib.o
}
ObjectFile libcoreutil.a::ffsLib.o {
	NAME Object file ffsLib.o from archive libcoreutil.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module ffsLib.o {
	OBJECT += libcoreutil.a::ffsLib.o
}
ObjectFile libcoreutil.a::lstLib.o {
	NAME Object file lstLib.o from archive libcoreutil.a
	EXPORTS lstInit lstInsert lstAdd lstDelete lstCount lstFirst lstLast lstGet lstPrevious lstNext lstFind lstConcat lstExtract lstNth lstNStep lstFree2 lstFree
	IMPORTS .TOC. abs free
	DECLARES 
	USES 
}
Module lstLib.o {
	OBJECT += libcoreutil.a::lstLib.o
}
ObjectFile libcoreutil.a::rngLib.o {
	NAME Object file rngLib.o from archive libcoreutil.a
	EXPORTS rngCreate rngDelete rngFlush rngBufGet rngBufPut rngIsEmpty rngIsFull rngFreeBytes rngNBytes rngPutAhead rngMoveAhead
	IMPORTS .TOC. malloc free bcopy
	DECLARES 
	USES 
}
Module rngLib.o {
	OBJECT += libcoreutil.a::rngLib.o
}
ObjectFile libcoreutil.a::sllLib.o {
	NAME Object file sllLib.o from archive libcoreutil.a
	EXPORTS sllInit sllTerminate sllCount sllGet sllPutAtHead sllPutAtTail sllRemove sllPrevious sllEach
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module sllLib.o {
	OBJECT += libcoreutil.a::sllLib.o
}
ObjectFile libcoreutil.a::hookLib.o {
	NAME Object file hookLib.o from archive libcoreutil.a
	EXPORTS hookAddToTail hookAddToHead hookDelete hookFind
	IMPORTS .TOC. taskIdSelf kernelLockTake windExit errnoSet
	DECLARES 
	USES 
}
Module hookLib.o {
	OBJECT += libcoreutil.a::hookLib.o
}
ObjectFile libcoreutil.a::hookTblLib.o {
	NAME Object file hookTblLib.o from archive libcoreutil.a
	EXPORTS hookTblInit hookTblAddToTail hookTblAddToHead hookTblDelete hookTblUpdatersUnpend hookTblFind
	IMPORTS .TOC. qFifoClassId qFifoInit semMInitialize intContext __errno taskIdSelf semMTake semMGive errnoSet vxAtomicCas kernelLockTake windPendQPut windExit kernelLockTry windPendQFlush workQAdd1 vxAtomicOr vxAtomic32Inc vxAtomicAnd vxAtomic32Dec
	DECLARES 
	USES 
}
Module hookTblLib.o {
	OBJECT += libcoreutil.a::hookTblLib.o
}
ObjectFile libcoreutil.a::dataset.o {
	NAME Object file dataset.o from archive libcoreutil.a
	EXPORTS datasetIterate
	IMPORTS .TOC. wrs_kernel_data_set_start wrs_kernel_data_set_end strncmp
	DECLARES 
	USES 
}
Module dataset.o {
	OBJECT += libcoreutil.a::dataset.o
}
ObjectFile libcoreutil.a::strendcpy.o {
	NAME Object file strendcpy.o from archive libcoreutil.a
	EXPORTS strendcpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strendcpy.o {
	OBJECT += libcoreutil.a::strendcpy.o
}
ObjectFile libcoreutil.a::skipPrefix.o {
	NAME Object file skipPrefix.o from archive libcoreutil.a
	EXPORTS skipPrefix
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module skipPrefix.o {
	OBJECT += libcoreutil.a::skipPrefix.o
}
ObjectFile libcoreutil.a::getpagesize.o {
	NAME Object file getpagesize.o from archive libcoreutil.a
	EXPORTS getpagesize
	IMPORTS .TOC. vmLibInfo
	DECLARES 
	USES 
}
Module getpagesize.o {
	OBJECT += libcoreutil.a::getpagesize.o
}
ObjectFile libcoreutil.a::applUtilLib.o {
	NAME Object file applUtilLib.o from archive libcoreutil.a
	EXPORTS applLoggerInit catInfo applUtilInstInit applLoggerStop logLevelChange logDecorationChange loggerInfoShow initApplLogger stopApplLogger changeLogLevel showLoggerInfo _applLog
	IMPORTS .TOC. __errno printf snprintf strerror_r strncmp semTake write vfdprintf semGive
	DECLARES applUtilLogSem
	USES 
}
Module applUtilLib.o {
	OBJECT += libcoreutil.a::applUtilLib.o
}
ObjectFile libcoreutil.a::avlUint64Lib.o {
	NAME Object file avlUint64Lib.o from archive libcoreutil.a
	EXPORTS avlUint64Insert avlUint64Delete avlUint64Search avlUint64SuccessorGet avlUint64PredecessorGet avlUint64MinimumGet avlUint64MaximumGet avlUint64TreeWalk
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module avlUint64Lib.o {
	OBJECT += libcoreutil.a::avlUint64Lib.o
}
ObjectFile libcoreutil.a::memmem.o {
	NAME Object file memmem.o from archive libcoreutil.a
	EXPORTS memmem memimem
	IMPORTS .TOC. __ctype_toupper __ctype_tolower
	DECLARES 
	USES 
}
Module memmem.o {
	OBJECT += libcoreutil.a::memmem.o
}
ObjectFile libcoreutil.a::hookShow.o {
	NAME Object file hookShow.o from archive libcoreutil.a
	EXPORTS hookShow
	IMPORTS .TOC. _func_symFindSymbol sysSymTbl _func_symNameGet _func_symValueGet cplusDemangle printf
	DECLARES 
	USES 
}
Module hookShow.o {
	OBJECT += libcoreutil.a::hookShow.o
}
ObjectFile libcoreutil.a::hookTblShow.o {
	NAME Object file hookTblShow.o from archive libcoreutil.a
	EXPORTS hookTblShow
	IMPORTS .TOC. vxAtomicOr vxAtomic32Inc objRoutineNameGet printf vxAtomicAnd vxAtomic32Dec vxAtomicCas hookTblUpdatersUnpend
	DECLARES 
	USES 
}
Module hookTblShow.o {
	OBJECT += libcoreutil.a::hookTblShow.o
}
ObjectFile libcoreutil.a::getopt.o {
	NAME Object file getopt.o from archive libcoreutil.a
	EXPORTS getopt_r getopt opterr optind getoptInit getOptServ
	IMPORTS .TOC. strchr __stderr fprintf strtok_r
	DECLARES optopt optreset optarg
	USES 
}
Module getopt.o {
	OBJECT += libcoreutil.a::getopt.o
}
ObjectFile libcoreutil.a::avlLib.o {
	NAME Object file avlLib.o from archive libcoreutil.a
	EXPORTS avlInsert avlDelete avlSearch avlSuccessorGet avlPredecessorGet avlMinimumGet avlMaximumGet avlTreeWalk avlInsertInform avlRemoveInsert
	IMPORTS .TOC. printf
	DECLARES 
	USES 
}
Module avlLib.o {
	OBJECT += libcoreutil.a::avlLib.o
}
ObjectFile libcoreutil.a::dllCreateLib.o {
	NAME Object file dllCreateLib.o from archive libcoreutil.a
	EXPORTS dllCreate dllDelete
	IMPORTS .TOC. malloc dllInit free
	DECLARES 
	USES 
}
Module dllCreateLib.o {
	OBJECT += libcoreutil.a::dllCreateLib.o
}
ObjectFile libcoreutil.a::hashLib.o {
	NAME Object file hashLib.o from archive libcoreutil.a
	EXPORTS hashTblInit hashTblCreate hashTblDestroy hashTblDelete hashTblTerminate hashTblPut hashTblFind hashTblRemove hashTblEach hashFuncIterScale hashFuncModulo hashFuncMultiply hashKeyCmp hashKeyStrCmp
	IMPORTS .TOC. sllInit handleInit malloc handleTerminate free sllPutAtHead sllPrevious sllRemove sllEach ffsMsb strcmp
	DECLARES 
	USES 
}
Module hashLib.o {
	OBJECT += libcoreutil.a::hashLib.o
}
ObjectFile libcoreutil.a::sllCreateLib.o {
	NAME Object file sllCreateLib.o from archive libcoreutil.a
	EXPORTS sllCreate sllDelete
	IMPORTS .TOC. malloc sllInit free
	DECLARES 
	USES 
}
Module sllCreateLib.o {
	OBJECT += libcoreutil.a::sllCreateLib.o
}
ObjectFile libcoreutil.a::procNumSetFuncBind.o {
	NAME Object file procNumSetFuncBind.o from archive libcoreutil.a
	EXPORTS _procNumWasSet
	IMPORTS 
	DECLARES 
	USES 
}
Module procNumSetFuncBind.o {
	OBJECT += libcoreutil.a::procNumSetFuncBind.o
}
Library libcoreutil.a {
	MODULES libcoreutil.a::avlUintLib.o libcoreutil.a::bLib.o libcoreutil.a::bmpLib.o libcoreutil.a::dllLib.o libcoreutil.a::ffsLib.o libcoreutil.a::lstLib.o libcoreutil.a::rngLib.o libcoreutil.a::sllLib.o libcoreutil.a::hookLib.o libcoreutil.a::hookTblLib.o libcoreutil.a::dataset.o libcoreutil.a::strendcpy.o libcoreutil.a::skipPrefix.o libcoreutil.a::getpagesize.o libcoreutil.a::applUtilLib.o libcoreutil.a::avlUint64Lib.o libcoreutil.a::memmem.o libcoreutil.a::hookShow.o libcoreutil.a::hookTblShow.o libcoreutil.a::getopt.o libcoreutil.a::avlLib.o libcoreutil.a::dllCreateLib.o libcoreutil.a::hashLib.o libcoreutil.a::sllCreateLib.o libcoreutil.a::procNumSetFuncBind.o
}
Symbol .TOC. {
}
Symbol avlUintInsert {
}
Symbol avlUintDelete {
}
Symbol avlUintSearch {
}
Symbol avlUintSuccessorGet {
}
Symbol avlUintPredecessorGet {
}
Symbol avlUintMinimumGet {
}
Symbol avlUintMaximumGet {
}
Symbol avlUintTreeWalk {
}
Symbol bcmp {
}
Symbol binvert {
}
Symbol bswap {
}
Symbol uswab {
}
Symbol bzero {
}
Symbol bfill {
}
Symbol index {
}
Symbol rindex {
}
Symbol strlen {
}
Symbol bitFirstGet {
}
Symbol ffsMsb {
}
Symbol dllInit {
}
Symbol dllTerminate {
}
Symbol dllInsert {
}
Symbol dllAdd {
}
Symbol dllRemove {
}
Symbol dllGet {
}
Symbol dllCount {
}
Symbol dllEach {
}
Symbol lstInit {
}
Symbol lstInsert {
}
Symbol lstAdd {
}
Symbol lstDelete {
}
Symbol lstCount {
}
Symbol lstFirst {
}
Symbol lstLast {
}
Symbol lstGet {
}
Symbol lstPrevious {
}
Symbol lstNext {
}
Symbol lstFind {
}
Symbol lstConcat {
}
Symbol lstExtract {
}
Symbol lstNth {
}
Symbol lstNStep {
}
Symbol abs {
}
Symbol lstFree2 {
}
Symbol lstFree {
}
Symbol free {
}
Symbol rngCreate {
}
Symbol malloc {
}
Symbol rngDelete {
}
Symbol rngFlush {
}
Symbol rngBufGet {
}
Symbol bcopy {
}
Symbol rngBufPut {
}
Symbol rngIsEmpty {
}
Symbol rngIsFull {
}
Symbol rngFreeBytes {
}
Symbol rngNBytes {
}
Symbol rngPutAhead {
}
Symbol rngMoveAhead {
}
Symbol sllInit {
}
Symbol sllTerminate {
}
Symbol sllCount {
}
Symbol sllGet {
}
Symbol sllPutAtHead {
}
Symbol sllPutAtTail {
}
Symbol sllRemove {
}
Symbol sllPrevious {
}
Symbol sllEach {
}
Symbol hookAddToTail {
}
Symbol taskIdSelf {
}
Symbol kernelLockTake {
}
Symbol windExit {
}
Symbol errnoSet {
}
Symbol hookAddToHead {
}
Symbol hookDelete {
}
Symbol hookFind {
}
Symbol hookTblInit {
}
Symbol qFifoClassId {
}
Symbol qFifoInit {
}
Symbol semMInitialize {
}
Symbol hookTblAddToTail {
}
Symbol intContext {
}
Symbol __errno {
}
Symbol semMTake {
}
Symbol semMGive {
}
Symbol vxAtomicCas {
}
Symbol windPendQPut {
}
Symbol hookTblAddToHead {
}
Symbol hookTblDelete {
}
Symbol hookTblUpdatersUnpend {
}
Symbol kernelLockTry {
}
Symbol windPendQFlush {
}
Symbol workQAdd1 {
}
Symbol hookTblFind {
}
Symbol vxAtomicOr {
}
Symbol vxAtomic32Inc {
}
Symbol vxAtomicAnd {
}
Symbol vxAtomic32Dec {
}
Symbol datasetIterate {
}
Symbol wrs_kernel_data_set_start {
}
Symbol wrs_kernel_data_set_end {
}
Symbol strncmp {
}
Symbol strendcpy {
}
Symbol skipPrefix {
}
Symbol getpagesize {
}
Symbol vmLibInfo {
}
Symbol applLoggerInit {
}
Symbol applUtilLogSem {
}
Symbol catInfo {
}
Symbol applUtilInstInit {
}
Symbol applLoggerStop {
}
Symbol logLevelChange {
}
Symbol logDecorationChange {
}
Symbol loggerInfoShow {
}
Symbol printf {
}
Symbol initApplLogger {
}
Symbol stopApplLogger {
}
Symbol changeLogLevel {
}
Symbol showLoggerInfo {
}
Symbol _applLog {
}
Symbol snprintf {
}
Symbol strerror_r {
}
Symbol semTake {
}
Symbol write {
}
Symbol vfdprintf {
}
Symbol semGive {
}
Symbol avlUint64Insert {
}
Symbol avlUint64Delete {
}
Symbol avlUint64Search {
}
Symbol avlUint64SuccessorGet {
}
Symbol avlUint64PredecessorGet {
}
Symbol avlUint64MinimumGet {
}
Symbol avlUint64MaximumGet {
}
Symbol avlUint64TreeWalk {
}
Symbol __ctype_toupper {
}
Symbol __ctype_tolower {
}
Symbol memmem {
}
Symbol memimem {
}
Symbol hookShow {
}
Symbol _func_symFindSymbol {
}
Symbol sysSymTbl {
}
Symbol _func_symNameGet {
}
Symbol _func_symValueGet {
}
Symbol cplusDemangle {
}
Symbol hookTblShow {
}
Symbol objRoutineNameGet {
}
Symbol getopt_r {
}
Symbol strchr {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol getopt {
}
Symbol opterr {
}
Symbol optind {
}
Symbol optopt {
}
Symbol optreset {
}
Symbol optarg {
}
Symbol getoptInit {
}
Symbol getOptServ {
}
Symbol strtok_r {
}
Symbol avlInsert {
}
Symbol avlDelete {
}
Symbol avlSearch {
}
Symbol avlSuccessorGet {
}
Symbol avlPredecessorGet {
}
Symbol avlMinimumGet {
}
Symbol avlMaximumGet {
}
Symbol avlTreeWalk {
}
Symbol avlInsertInform {
}
Symbol avlRemoveInsert {
}
Symbol dllCreate {
}
Symbol dllDelete {
}
Symbol hashTblInit {
}
Symbol handleInit {
}
Symbol hashTblCreate {
}
Symbol hashTblDestroy {
}
Symbol handleTerminate {
}
Symbol hashTblDelete {
}
Symbol hashTblTerminate {
}
Symbol hashTblPut {
}
Symbol hashTblFind {
}
Symbol hashTblRemove {
}
Symbol hashTblEach {
}
Symbol hashFuncIterScale {
}
Symbol hashFuncModulo {
}
Symbol hashFuncMultiply {
}
Symbol hashKeyCmp {
}
Symbol hashKeyStrCmp {
}
Symbol strcmp {
}
Symbol sllCreate {
}
Symbol sllDelete {
}
Symbol _procNumWasSet {
}
ObjectFile libcoreutil.a::avlUintLib.o {
	NAME Object file avlUintLib.o from archive libcoreutil.a
	EXPORTS avlUintInsert avlUintDelete avlUintSearch avlUintSuccessorGet avlUintPredecessorGet avlUintMinimumGet avlUintMaximumGet avlUintTreeWalk
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module avlUintLib.o {
	OBJECT += libcoreutil.a::avlUintLib.o
}
ObjectFile libcoreutil.a::bLib.o {
	NAME Object file bLib.o from archive libcoreutil.a
	EXPORTS bcmp binvert bswap uswab bzero index rindex
	IMPORTS .TOC. bfill strlen
	DECLARES 
	USES 
}
Module bLib.o {
	OBJECT += libcoreutil.a::bLib.o
}
ObjectFile libcoreutil.a::bmpLib.o {
	NAME Object file bmpLib.o from archive libcoreutil.a
	EXPORTS bitFirstGet
	IMPORTS .TOC. ffsMsb
	DECLARES 
	USES 
}
Module bmpLib.o {
	OBJECT += libcoreutil.a::bmpLib.o
}
ObjectFile libcoreutil.a::dllLib.o {
	NAME Object file dllLib.o from archive libcoreutil.a
	EXPORTS dllInit dllTerminate dllInsert dllAdd dllRemove dllGet dllCount dllEach
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module dllLib.o {
	OBJECT += libcoreutil.a::dllLib.o
}
ObjectFile libcoreutil.a::ffsLib.o {
	NAME Object file ffsLib.o from archive libcoreutil.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module ffsLib.o {
	OBJECT += libcoreutil.a::ffsLib.o
}
ObjectFile libcoreutil.a::lstLib.o {
	NAME Object file lstLib.o from archive libcoreutil.a
	EXPORTS lstInit lstInsert lstAdd lstDelete lstCount lstFirst lstLast lstGet lstPrevious lstNext lstFind lstConcat lstExtract lstNth lstNStep lstFree2 lstFree
	IMPORTS .TOC. abs free
	DECLARES 
	USES 
}
Module lstLib.o {
	OBJECT += libcoreutil.a::lstLib.o
}
ObjectFile libcoreutil.a::rngLib.o {
	NAME Object file rngLib.o from archive libcoreutil.a
	EXPORTS rngCreate rngDelete rngFlush rngBufGet rngBufPut rngIsEmpty rngIsFull rngFreeBytes rngNBytes rngPutAhead rngMoveAhead
	IMPORTS .TOC. malloc free bcopy
	DECLARES 
	USES 
}
Module rngLib.o {
	OBJECT += libcoreutil.a::rngLib.o
}
ObjectFile libcoreutil.a::sllLib.o {
	NAME Object file sllLib.o from archive libcoreutil.a
	EXPORTS sllInit sllTerminate sllCount sllGet sllPutAtHead sllPutAtTail sllRemove sllPrevious sllEach
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module sllLib.o {
	OBJECT += libcoreutil.a::sllLib.o
}
ObjectFile libcoreutil.a::hookLib.o {
	NAME Object file hookLib.o from archive libcoreutil.a
	EXPORTS hookAddToTail hookAddToHead hookDelete hookFind
	IMPORTS .TOC. taskIdSelf kernelLockTake windExit errnoSet
	DECLARES 
	USES 
}
Module hookLib.o {
	OBJECT += libcoreutil.a::hookLib.o
}
ObjectFile libcoreutil.a::hookTblLib.o {
	NAME Object file hookTblLib.o from archive libcoreutil.a
	EXPORTS hookTblInit hookTblAddToTail hookTblAddToHead hookTblDelete hookTblUpdatersUnpend hookTblFind
	IMPORTS .TOC. qFifoClassId qFifoInit semMInitialize intContext __errno taskIdSelf semMTake semMGive errnoSet vxAtomicCas kernelLockTake windPendQPut windExit kernelLockTry windPendQFlush workQAdd1 vxAtomicOr vxAtomic32Inc vxAtomicAnd vxAtomic32Dec
	DECLARES 
	USES 
}
Module hookTblLib.o {
	OBJECT += libcoreutil.a::hookTblLib.o
}
ObjectFile libcoreutil.a::dataset.o {
	NAME Object file dataset.o from archive libcoreutil.a
	EXPORTS datasetIterate
	IMPORTS .TOC. wrs_kernel_data_set_start wrs_kernel_data_set_end strncmp
	DECLARES 
	USES 
}
Module dataset.o {
	OBJECT += libcoreutil.a::dataset.o
}
ObjectFile libcoreutil.a::strendcpy.o {
	NAME Object file strendcpy.o from archive libcoreutil.a
	EXPORTS strendcpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strendcpy.o {
	OBJECT += libcoreutil.a::strendcpy.o
}
ObjectFile libcoreutil.a::skipPrefix.o {
	NAME Object file skipPrefix.o from archive libcoreutil.a
	EXPORTS skipPrefix
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module skipPrefix.o {
	OBJECT += libcoreutil.a::skipPrefix.o
}
ObjectFile libcoreutil.a::getpagesize.o {
	NAME Object file getpagesize.o from archive libcoreutil.a
	EXPORTS getpagesize
	IMPORTS .TOC. vmLibInfo
	DECLARES 
	USES 
}
Module getpagesize.o {
	OBJECT += libcoreutil.a::getpagesize.o
}
ObjectFile libcoreutil.a::applUtilLib.o {
	NAME Object file applUtilLib.o from archive libcoreutil.a
	EXPORTS applLoggerInit catInfo applUtilInstInit applLoggerStop logLevelChange logDecorationChange loggerInfoShow initApplLogger stopApplLogger changeLogLevel showLoggerInfo _applLog
	IMPORTS .TOC. __errno printf snprintf strerror_r strncmp semTake write vfdprintf semGive
	DECLARES applUtilLogSem
	USES 
}
Module applUtilLib.o {
	OBJECT += libcoreutil.a::applUtilLib.o
}
ObjectFile libcoreutil.a::avlUint64Lib.o {
	NAME Object file avlUint64Lib.o from archive libcoreutil.a
	EXPORTS avlUint64Insert avlUint64Delete avlUint64Search avlUint64SuccessorGet avlUint64PredecessorGet avlUint64MinimumGet avlUint64MaximumGet avlUint64TreeWalk
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module avlUint64Lib.o {
	OBJECT += libcoreutil.a::avlUint64Lib.o
}
ObjectFile libcoreutil.a::memmem.o {
	NAME Object file memmem.o from archive libcoreutil.a
	EXPORTS memmem memimem
	IMPORTS .TOC. __ctype_toupper __ctype_tolower
	DECLARES 
	USES 
}
Module memmem.o {
	OBJECT += libcoreutil.a::memmem.o
}
ObjectFile libcoreutil.a::hookShow.o {
	NAME Object file hookShow.o from archive libcoreutil.a
	EXPORTS hookShow
	IMPORTS .TOC. _func_symFindSymbol sysSymTbl _func_symNameGet _func_symValueGet cplusDemangle printf
	DECLARES 
	USES 
}
Module hookShow.o {
	OBJECT += libcoreutil.a::hookShow.o
}
ObjectFile libcoreutil.a::hookTblShow.o {
	NAME Object file hookTblShow.o from archive libcoreutil.a
	EXPORTS hookTblShow
	IMPORTS .TOC. vxAtomicOr vxAtomic32Inc objRoutineNameGet printf vxAtomicAnd vxAtomic32Dec vxAtomicCas hookTblUpdatersUnpend
	DECLARES 
	USES 
}
Module hookTblShow.o {
	OBJECT += libcoreutil.a::hookTblShow.o
}
ObjectFile libcoreutil.a::getopt.o {
	NAME Object file getopt.o from archive libcoreutil.a
	EXPORTS getopt_r getopt opterr optind getoptInit getOptServ
	IMPORTS .TOC. strchr __stderr fprintf strtok_r
	DECLARES optopt optreset optarg
	USES 
}
Module getopt.o {
	OBJECT += libcoreutil.a::getopt.o
}
ObjectFile libcoreutil.a::avlLib.o {
	NAME Object file avlLib.o from archive libcoreutil.a
	EXPORTS avlInsert avlDelete avlSearch avlSuccessorGet avlPredecessorGet avlMinimumGet avlMaximumGet avlTreeWalk avlInsertInform avlRemoveInsert
	IMPORTS .TOC. printf
	DECLARES 
	USES 
}
Module avlLib.o {
	OBJECT += libcoreutil.a::avlLib.o
}
ObjectFile libcoreutil.a::dllCreateLib.o {
	NAME Object file dllCreateLib.o from archive libcoreutil.a
	EXPORTS dllCreate dllDelete
	IMPORTS .TOC. malloc dllInit free
	DECLARES 
	USES 
}
Module dllCreateLib.o {
	OBJECT += libcoreutil.a::dllCreateLib.o
}
ObjectFile libcoreutil.a::hashLib.o {
	NAME Object file hashLib.o from archive libcoreutil.a
	EXPORTS hashTblInit hashTblCreate hashTblDestroy hashTblDelete hashTblTerminate hashTblPut hashTblFind hashTblRemove hashTblEach hashFuncIterScale hashFuncModulo hashFuncMultiply hashKeyCmp hashKeyStrCmp
	IMPORTS .TOC. sllInit handleInit malloc handleTerminate free sllPutAtHead sllPrevious sllRemove sllEach ffsMsb strcmp
	DECLARES 
	USES 
}
Module hashLib.o {
	OBJECT += libcoreutil.a::hashLib.o
}
ObjectFile libcoreutil.a::sllCreateLib.o {
	NAME Object file sllCreateLib.o from archive libcoreutil.a
	EXPORTS sllCreate sllDelete
	IMPORTS .TOC. malloc sllInit free
	DECLARES 
	USES 
}
Module sllCreateLib.o {
	OBJECT += libcoreutil.a::sllCreateLib.o
}
ObjectFile libcoreutil.a::procNumSetFuncBind.o {
	NAME Object file procNumSetFuncBind.o from archive libcoreutil.a
	EXPORTS _procNumWasSet
	IMPORTS 
	DECLARES 
	USES 
}
Module procNumSetFuncBind.o {
	OBJECT += libcoreutil.a::procNumSetFuncBind.o
}
Library libcoreutil.a {
	MODULES libcoreutil.a::avlUintLib.o libcoreutil.a::bLib.o libcoreutil.a::bmpLib.o libcoreutil.a::dllLib.o libcoreutil.a::ffsLib.o libcoreutil.a::lstLib.o libcoreutil.a::rngLib.o libcoreutil.a::sllLib.o libcoreutil.a::hookLib.o libcoreutil.a::hookTblLib.o libcoreutil.a::dataset.o libcoreutil.a::strendcpy.o libcoreutil.a::skipPrefix.o libcoreutil.a::getpagesize.o libcoreutil.a::applUtilLib.o libcoreutil.a::avlUint64Lib.o libcoreutil.a::memmem.o libcoreutil.a::hookShow.o libcoreutil.a::hookTblShow.o libcoreutil.a::getopt.o libcoreutil.a::avlLib.o libcoreutil.a::dllCreateLib.o libcoreutil.a::hashLib.o libcoreutil.a::sllCreateLib.o libcoreutil.a::procNumSetFuncBind.o
}
