Symbol buf_panic {
}
Symbol .TOC. {
}
Symbol printf {
}
Symbol vprintf {
}
Symbol _sigCtxSave {
}
Symbol edrErrorInjectStub {
}
Symbol edrKernelFatalPolicyHandler {
}
Symbol buf_initmountpoint {
}
Symbol buf_deletebuffers {
}
Symbol brelvp {
}
Symbol semDelete {
}
Symbol free {
}
Symbol buf_makebuffers {
}
Symbol __errno {
}
Symbol semMCreate {
}
Symbol semCCreate {
}
Symbol malloc {
}
Symbol semBCreate {
}
Symbol buf_startwrite {
}
Symbol vreassignbuf {
}
Symbol vn_incr_numoutput {
}
Symbol buf_biodone {
}
Symbol bawrite {
}
Symbol semGive {
}
Symbol buf_getblk {
}
Symbol semTake {
}
Symbol semExchange {
}
Symbol bgetvp {
}
Symbol buf_rebusy {
}
Symbol brelse {
}
Symbol taskIdSelf {
}
Symbol vxAtomicGet {
}
Symbol buf_moveblk {
}
Symbol buf_swapdata {
}
Symbol buf_doread {
}
Symbol buf_wait {
}
Symbol bread {
}
Symbol breadn {
}
Symbol bdwrite {
}
Symbol bdirty {
}
Symbol bwrite {
}
Symbol buf_done {
}
Symbol vn_decr_numoutput {
}
Symbol buf_invalid {
}
Symbol mountBufFree {
}
Symbol bio_free {
}
Symbol fsmUnmountHookRun {
}
Symbol vrele {
}
Symbol vn_deletefiletable {
}
Symbol vn_deletevnodes {
}
Symbol mountDelete {
}
Symbol iosDevSuspend {
}
Symbol iosDevDelete {
}
Symbol mountCreate {
}
Symbol vnodeAffDriverNumber {
}
Symbol vnodeAffLibInit {
}
Symbol memset {
}
Symbol vn_makevnodes {
}
Symbol vn_makefiletable {
}
Symbol mountBufAlloc {
}
Symbol xbdBlockSize {
}
Symbol bio_alloc {
}
Symbol mountEject {
}
Symbol mountInsDev {
}
Symbol iosLock {
}
Symbol iosDevReplaceExt {
}
Symbol iosDevDelCallback {
}
Symbol iosUnlock {
}
Symbol aff_panic {
}
Symbol taskSuspend {
}
Symbol vn_getfp {
}
Symbol vn_relfp {
}
Symbol lookup {
}
Symbol vref {
}
Symbol vput {
}
Symbol namei {
}
Symbol strlen {
}
Symbol strncpy {
}
Symbol memmove {
}
Symbol vnReLookup {
}
Symbol vnCheckPath {
}
Symbol vnLockVnodes {
}
Symbol vn_open {
}
Symbol vattr_null {
}
Symbol vn_close {
}
Symbol vn_mkdir {
}
Symbol vncio_open {
}
Symbol xbdIoctl {
}
Symbol errnoSet {
}
Symbol pathCondense {
}
Symbol vncio_create {
}
Symbol vn_remove {
}
Symbol vn_link {
}
Symbol vncio_delete {
}
Symbol vncio_read {
}
Symbol vncio_write {
}
Symbol vncio_close {
}
Symbol vncio_readdir {
}
Symbol vncio_rename {
}
Symbol vn_getlock {
}
Symbol vn_setlock {
}
Symbol vncio_fsname_to_id {
}
Symbol vnc_ftype_map {
}
Symbol strcmp {
}
Symbol vncio_ioctl {
}
Symbol bzero {
}
Symbol time {
}
Symbol iosDrvInstall {
}
Symbol vop_error_rename {
}
Symbol lfGetNewLock {
}
Symbol lfFreeLock {
}
Symbol lfDetectDeadlock {
}
Symbol maxlockdepth {
}
Symbol lockf_debug {
}
Symbol vn_panic {
}
Symbol memcpy {
}
Symbol _func_pthread_testandset_canceltype {
}
Symbol lf_advlock {
}
Symbol vn_initialize_syncerd {
}
Symbol vn_syncer_taskid {
}
Symbol vn_syncer_mutex {
}
Symbol syncer_semaphore {
}
Symbol syncer_workitem_pending {
}
Symbol syncer_delayno {
}
Symbol vnSyncerTaskPriority {
}
Symbol vnSyncerTaskOptions {
}
Symbol vnSyncerTaskStacksize {
}
Symbol vn_sync_task {
}
Symbol taskSpawn {
}
Symbol vn_syncer_add_to_worklist {
}
Symbol sysClkRateGet {
}
Symbol tickGet {
}
Symbol taskDelay {
}
Symbol vxAtomicInc {
}
Symbol vxAtomicDec {
}
Symbol vpurgebufs {
}
Symbol vn_vfree {
}
Symbol vprint {
}
Symbol vnode_types {
}
Symbol strncat {
}
Symbol vn_unhold {
}
Symbol getnewvnode {
}
Symbol vgetino {
}
Symbol vflushbuf {
}
Symbol vinvalbuf {
}
Symbol vaccess {
}
Symbol enosys {
}
Symbol vopErrorENOTDIR {
}
Symbol vopErrorEISDIR {
}
ObjectFile libfsVfs.a::bufSubr.o {
	NAME Object file bufSubr.o from archive libfsVfs.a
	EXPORTS buf_panic buf_initmountpoint buf_deletebuffers buf_makebuffers buf_startwrite buf_biodone bawrite buf_getblk buf_rebusy brelse buf_moveblk buf_swapdata buf_doread buf_wait bread breadn bdwrite bdirty bwrite buf_done buf_invalid
	IMPORTS .TOC. printf vprintf _sigCtxSave edrErrorInjectStub edrKernelFatalPolicyHandler brelvp semDelete free __errno semMCreate semCCreate malloc semBCreate vreassignbuf vn_incr_numoutput semGive semTake semExchange bgetvp taskIdSelf vxAtomicGet vn_decr_numoutput
	DECLARES 
	USES 
}
Module bufSubr.o {
	OBJECT += libfsVfs.a::bufSubr.o
}
ObjectFile libfsVfs.a::mountSubr.o {
	NAME Object file mountSubr.o from archive libfsVfs.a
	EXPORTS mountBufFree mountDelete mountCreate mountBufAlloc mountEject mountInsDev
	IMPORTS .TOC. buf_deletebuffers free bio_free fsmUnmountHookRun vrele vn_deletefiletable vn_deletevnodes semDelete iosDevSuspend iosDevDelete __errno vnodeAffDriverNumber vnodeAffLibInit malloc memset semMCreate vn_makevnodes vn_makefiletable semGive xbdBlockSize bio_alloc buf_initmountpoint buf_makebuffers iosLock iosDevReplaceExt iosDevDelCallback iosUnlock
	DECLARES 
	USES 
}
Module mountSubr.o {
	OBJECT += libfsVfs.a::mountSubr.o
}
ObjectFile libfsVfs.a::vnodeAff.o {
	NAME Object file vnodeAff.o from archive libfsVfs.a
	EXPORTS aff_panic vn_makefiletable vn_deletefiletable vn_getfp vn_relfp lookup namei vnReLookup vnCheckPath vnLockVnodes vn_open vn_close vn_mkdir vncio_open vncio_create vn_remove vn_link vncio_delete vncio_read vncio_write vncio_close vncio_readdir vncio_rename vn_getlock vn_setlock vncio_fsname_to_id vnc_ftype_map vncio_ioctl vnodeAffLibInit vnodeAffDriverNumber vop_error_rename
	IMPORTS .TOC. printf vprintf taskSuspend __errno semMCreate malloc semDelete free semTake semGive vref vrele vput strlen strncpy memmove vattr_null xbdIoctl errnoSet pathCondense strcmp mountDelete bzero memset time iosDrvInstall
	DECLARES 
	USES 
}
Module vnodeAff.o {
	OBJECT += libfsVfs.a::vnodeAff.o
}
ObjectFile libfsVfs.a::vnodeLockf.o {
	NAME Object file vnodeLockf.o from archive libfsVfs.a
	EXPORTS lfGetNewLock lfFreeLock lfDetectDeadlock maxlockdepth lockf_debug lf_advlock
	IMPORTS .TOC. malloc semBCreate free semDelete printf vn_panic memcpy semGive _func_pthread_testandset_canceltype semTake taskIdSelf
	DECLARES 
	USES 
}
Module vnodeLockf.o {
	OBJECT += libfsVfs.a::vnodeLockf.o
}
ObjectFile libfsVfs.a::vnodeSubr.o {
	NAME Object file vnodeSubr.o from archive libfsVfs.a
	EXPORTS vn_panic vn_deletevnodes vn_initialize_syncerd vn_syncer_taskid vnSyncerTaskPriority vnSyncerTaskOptions vnSyncerTaskStacksize vn_sync_task vn_makevnodes vn_syncer_add_to_worklist vattr_null bgetvp brelvp vreassignbuf vn_incr_numoutput vn_decr_numoutput vpurgebufs vn_vfree vput vprint vnode_types vn_unhold getnewvnode vgetino vref vrele vflushbuf vinvalbuf vaccess enosys vopErrorENOTDIR vopErrorEISDIR
	IMPORTS .TOC. printf vprintf _sigCtxSave edrErrorInjectStub edrKernelFatalPolicyHandler semDelete free __errno semMCreate semBCreate taskSpawn semCCreate malloc bzero semTake semGive sysClkRateGet tickGet taskDelay vxAtomicInc vxAtomicDec buf_rebusy brelse vxAtomicGet strncat bwrite bawrite
	DECLARES vn_syncer_mutex syncer_semaphore syncer_workitem_pending syncer_delayno
	USES 
}
Module vnodeSubr.o {
	OBJECT += libfsVfs.a::vnodeSubr.o
}
Library libfsVfs.a {
	MODULES libfsVfs.a::bufSubr.o libfsVfs.a::mountSubr.o libfsVfs.a::vnodeAff.o libfsVfs.a::vnodeLockf.o libfsVfs.a::vnodeSubr.o
}
Symbol buf_panic {
}
Symbol .TOC. {
}
Symbol printf {
}
Symbol vprintf {
}
Symbol _sigCtxSave {
}
Symbol edrErrorInjectStub {
}
Symbol edrKernelFatalPolicyHandler {
}
Symbol buf_initmountpoint {
}
Symbol buf_deletebuffers {
}
Symbol brelvp {
}
Symbol semDelete {
}
Symbol free {
}
Symbol buf_makebuffers {
}
Symbol __errno {
}
Symbol semMCreate {
}
Symbol semCCreate {
}
Symbol malloc {
}
Symbol semBCreate {
}
Symbol buf_startwrite {
}
Symbol vreassignbuf {
}
Symbol vn_incr_numoutput {
}
Symbol buf_biodone {
}
Symbol bawrite {
}
Symbol semGive {
}
Symbol buf_getblk {
}
Symbol semTake {
}
Symbol semExchange {
}
Symbol bgetvp {
}
Symbol buf_rebusy {
}
Symbol brelse {
}
Symbol taskIdSelf {
}
Symbol vxAtomicGet {
}
Symbol buf_moveblk {
}
Symbol buf_swapdata {
}
Symbol buf_doread {
}
Symbol buf_wait {
}
Symbol bread {
}
Symbol breadn {
}
Symbol bdwrite {
}
Symbol bdirty {
}
Symbol bwrite {
}
Symbol buf_done {
}
Symbol vn_decr_numoutput {
}
Symbol buf_invalid {
}
Symbol mountBufFree {
}
Symbol bio_free {
}
Symbol fsmUnmountHookRun {
}
Symbol vrele {
}
Symbol vn_deletefiletable {
}
Symbol vn_deletevnodes {
}
Symbol mountDelete {
}
Symbol iosDevSuspend {
}
Symbol iosDevDelete {
}
Symbol mountCreate {
}
Symbol vnodeAffDriverNumber {
}
Symbol vnodeAffLibInit {
}
Symbol memset {
}
Symbol vn_makevnodes {
}
Symbol vn_makefiletable {
}
Symbol mountBufAlloc {
}
Symbol xbdBlockSize {
}
Symbol bio_alloc {
}
Symbol mountEject {
}
Symbol mountInsDev {
}
Symbol iosLock {
}
Symbol iosDevReplaceExt {
}
Symbol iosDevDelCallback {
}
Symbol iosUnlock {
}
Symbol aff_panic {
}
Symbol taskSuspend {
}
Symbol vn_getfp {
}
Symbol vn_relfp {
}
Symbol lookup {
}
Symbol vref {
}
Symbol vput {
}
Symbol namei {
}
Symbol strlen {
}
Symbol strncpy {
}
Symbol memmove {
}
Symbol vnReLookup {
}
Symbol vnCheckPath {
}
Symbol vnLockVnodes {
}
Symbol vn_open {
}
Symbol vattr_null {
}
Symbol vn_close {
}
Symbol vn_mkdir {
}
Symbol vncio_open {
}
Symbol xbdIoctl {
}
Symbol errnoSet {
}
Symbol pathCondense {
}
Symbol vncio_create {
}
Symbol vn_remove {
}
Symbol vn_link {
}
Symbol vncio_delete {
}
Symbol vncio_read {
}
Symbol vncio_write {
}
Symbol vncio_close {
}
Symbol vncio_readdir {
}
Symbol vncio_rename {
}
Symbol vn_getlock {
}
Symbol vn_setlock {
}
Symbol vncio_fsname_to_id {
}
Symbol vnc_ftype_map {
}
Symbol strcmp {
}
Symbol vncio_ioctl {
}
Symbol bzero {
}
Symbol time {
}
Symbol iosDrvInstall {
}
Symbol vop_error_rename {
}
Symbol lfGetNewLock {
}
Symbol lfFreeLock {
}
Symbol lfDetectDeadlock {
}
Symbol maxlockdepth {
}
Symbol lockf_debug {
}
Symbol vn_panic {
}
Symbol memcpy {
}
Symbol _func_pthread_testandset_canceltype {
}
Symbol lf_advlock {
}
Symbol vn_initialize_syncerd {
}
Symbol vn_syncer_taskid {
}
Symbol vn_syncer_mutex {
}
Symbol syncer_semaphore {
}
Symbol syncer_workitem_pending {
}
Symbol syncer_delayno {
}
Symbol vnSyncerTaskPriority {
}
Symbol vnSyncerTaskOptions {
}
Symbol vnSyncerTaskStacksize {
}
Symbol vn_sync_task {
}
Symbol taskSpawn {
}
Symbol vn_syncer_add_to_worklist {
}
Symbol sysClkRateGet {
}
Symbol tickGet {
}
Symbol taskDelay {
}
Symbol vxAtomicInc {
}
Symbol vxAtomicDec {
}
Symbol vpurgebufs {
}
Symbol vn_vfree {
}
Symbol vprint {
}
Symbol vnode_types {
}
Symbol strncat {
}
Symbol vn_unhold {
}
Symbol getnewvnode {
}
Symbol vgetino {
}
Symbol vflushbuf {
}
Symbol vinvalbuf {
}
Symbol vaccess {
}
Symbol enosys {
}
Symbol vopErrorENOTDIR {
}
Symbol vopErrorEISDIR {
}
ObjectFile libfsVfs.a::bufSubr.o {
	NAME Object file bufSubr.o from archive libfsVfs.a
	EXPORTS buf_panic buf_initmountpoint buf_deletebuffers buf_makebuffers buf_startwrite buf_biodone bawrite buf_getblk buf_rebusy brelse buf_moveblk buf_swapdata buf_doread buf_wait bread breadn bdwrite bdirty bwrite buf_done buf_invalid
	IMPORTS .TOC. printf vprintf _sigCtxSave edrErrorInjectStub edrKernelFatalPolicyHandler brelvp semDelete free __errno semMCreate semCCreate malloc semBCreate vreassignbuf vn_incr_numoutput semGive semTake semExchange bgetvp taskIdSelf vxAtomicGet vn_decr_numoutput
	DECLARES 
	USES 
}
Module bufSubr.o {
	OBJECT += libfsVfs.a::bufSubr.o
}
ObjectFile libfsVfs.a::mountSubr.o {
	NAME Object file mountSubr.o from archive libfsVfs.a
	EXPORTS mountBufFree mountDelete mountCreate mountBufAlloc mountEject mountInsDev
	IMPORTS .TOC. buf_deletebuffers free bio_free fsmUnmountHookRun vrele vn_deletefiletable vn_deletevnodes semDelete iosDevSuspend iosDevDelete __errno vnodeAffDriverNumber vnodeAffLibInit malloc memset semMCreate vn_makevnodes vn_makefiletable semGive xbdBlockSize bio_alloc buf_initmountpoint buf_makebuffers iosLock iosDevReplaceExt iosDevDelCallback iosUnlock
	DECLARES 
	USES 
}
Module mountSubr.o {
	OBJECT += libfsVfs.a::mountSubr.o
}
ObjectFile libfsVfs.a::vnodeAff.o {
	NAME Object file vnodeAff.o from archive libfsVfs.a
	EXPORTS aff_panic vn_makefiletable vn_deletefiletable vn_getfp vn_relfp lookup namei vnReLookup vnCheckPath vnLockVnodes vn_open vn_close vn_mkdir vncio_open vncio_create vn_remove vn_link vncio_delete vncio_read vncio_write vncio_close vncio_readdir vncio_rename vn_getlock vn_setlock vncio_fsname_to_id vnc_ftype_map vncio_ioctl vnodeAffLibInit vnodeAffDriverNumber vop_error_rename
	IMPORTS .TOC. printf vprintf taskSuspend __errno semMCreate malloc semDelete free semTake semGive vref vrele vput strlen strncpy memmove vattr_null xbdIoctl errnoSet pathCondense strcmp mountDelete bzero memset time iosDrvInstall
	DECLARES 
	USES 
}
Module vnodeAff.o {
	OBJECT += libfsVfs.a::vnodeAff.o
}
ObjectFile libfsVfs.a::vnodeLockf.o {
	NAME Object file vnodeLockf.o from archive libfsVfs.a
	EXPORTS lfGetNewLock lfFreeLock lfDetectDeadlock maxlockdepth lockf_debug lf_advlock
	IMPORTS .TOC. malloc semBCreate free semDelete printf vn_panic memcpy semGive _func_pthread_testandset_canceltype semTake taskIdSelf
	DECLARES 
	USES 
}
Module vnodeLockf.o {
	OBJECT += libfsVfs.a::vnodeLockf.o
}
ObjectFile libfsVfs.a::vnodeSubr.o {
	NAME Object file vnodeSubr.o from archive libfsVfs.a
	EXPORTS vn_panic vn_deletevnodes vn_initialize_syncerd vn_syncer_taskid vnSyncerTaskPriority vnSyncerTaskOptions vnSyncerTaskStacksize vn_sync_task vn_makevnodes vn_syncer_add_to_worklist vattr_null bgetvp brelvp vreassignbuf vn_incr_numoutput vn_decr_numoutput vpurgebufs vn_vfree vput vprint vnode_types vn_unhold getnewvnode vgetino vref vrele vflushbuf vinvalbuf vaccess enosys vopErrorENOTDIR vopErrorEISDIR
	IMPORTS .TOC. printf vprintf _sigCtxSave edrErrorInjectStub edrKernelFatalPolicyHandler semDelete free __errno semMCreate semBCreate taskSpawn semCCreate malloc bzero semTake semGive sysClkRateGet tickGet taskDelay vxAtomicInc vxAtomicDec buf_rebusy brelse vxAtomicGet strncat bwrite bawrite
	DECLARES vn_syncer_mutex syncer_semaphore syncer_workitem_pending syncer_delayno
	USES 
}
Module vnodeSubr.o {
	OBJECT += libfsVfs.a::vnodeSubr.o
}
Library libfsVfs.a {
	MODULES libfsVfs.a::bufSubr.o libfsVfs.a::mountSubr.o libfsVfs.a::vnodeAff.o libfsVfs.a::vnodeLockf.o libfsVfs.a::vnodeSubr.o
}
Symbol buf_panic {
}
Symbol .TOC. {
}
Symbol printf {
}
Symbol vprintf {
}
Symbol _sigCtxSave {
}
Symbol edrErrorInjectStub {
}
Symbol edrKernelFatalPolicyHandler {
}
Symbol buf_initmountpoint {
}
Symbol buf_deletebuffers {
}
Symbol brelvp {
}
Symbol semDelete {
}
Symbol free {
}
Symbol buf_makebuffers {
}
Symbol __errno {
}
Symbol semMCreate {
}
Symbol semCCreate {
}
Symbol malloc {
}
Symbol semBCreate {
}
Symbol buf_startwrite {
}
Symbol vreassignbuf {
}
Symbol vn_incr_numoutput {
}
Symbol buf_biodone {
}
Symbol bawrite {
}
Symbol semGive {
}
Symbol buf_getblk {
}
Symbol semTake {
}
Symbol semExchange {
}
Symbol bgetvp {
}
Symbol buf_rebusy {
}
Symbol brelse {
}
Symbol taskIdSelf {
}
Symbol vxAtomicGet {
}
Symbol buf_moveblk {
}
Symbol buf_swapdata {
}
Symbol buf_doread {
}
Symbol buf_wait {
}
Symbol bread {
}
Symbol breadn {
}
Symbol bdwrite {
}
Symbol bdirty {
}
Symbol bwrite {
}
Symbol buf_done {
}
Symbol vn_decr_numoutput {
}
Symbol buf_invalid {
}
Symbol mountBufFree {
}
Symbol bio_free {
}
Symbol fsmUnmountHookRun {
}
Symbol vrele {
}
Symbol vn_deletefiletable {
}
Symbol vn_deletevnodes {
}
Symbol mountDelete {
}
Symbol iosDevSuspend {
}
Symbol iosDevDelete {
}
Symbol mountCreate {
}
Symbol vnodeAffDriverNumber {
}
Symbol vnodeAffLibInit {
}
Symbol memset {
}
Symbol vn_makevnodes {
}
Symbol vn_makefiletable {
}
Symbol mountBufAlloc {
}
Symbol xbdBlockSize {
}
Symbol bio_alloc {
}
Symbol mountEject {
}
Symbol mountInsDev {
}
Symbol iosLock {
}
Symbol iosDevReplaceExt {
}
Symbol iosDevDelCallback {
}
Symbol iosUnlock {
}
Symbol aff_panic {
}
Symbol taskSuspend {
}
Symbol vn_getfp {
}
Symbol vn_relfp {
}
Symbol lookup {
}
Symbol vref {
}
Symbol vput {
}
Symbol namei {
}
Symbol strlen {
}
Symbol strncpy {
}
Symbol memmove {
}
Symbol vnReLookup {
}
Symbol vnCheckPath {
}
Symbol vnLockVnodes {
}
Symbol vn_open {
}
Symbol vattr_null {
}
Symbol vn_close {
}
Symbol vn_mkdir {
}
Symbol vncio_open {
}
Symbol xbdIoctl {
}
Symbol errnoSet {
}
Symbol pathCondense {
}
Symbol vncio_create {
}
Symbol vn_remove {
}
Symbol vn_link {
}
Symbol vncio_delete {
}
Symbol vncio_read {
}
Symbol vncio_write {
}
Symbol vncio_close {
}
Symbol vncio_readdir {
}
Symbol vncio_rename {
}
Symbol vn_getlock {
}
Symbol vn_setlock {
}
Symbol vncio_fsname_to_id {
}
Symbol vnc_ftype_map {
}
Symbol strcmp {
}
Symbol vncio_ioctl {
}
Symbol bzero {
}
Symbol time {
}
Symbol iosDrvInstall {
}
Symbol vop_error_rename {
}
Symbol lfGetNewLock {
}
Symbol lfFreeLock {
}
Symbol lfDetectDeadlock {
}
Symbol maxlockdepth {
}
Symbol lockf_debug {
}
Symbol vn_panic {
}
Symbol memcpy {
}
Symbol _func_pthread_testandset_canceltype {
}
Symbol lf_advlock {
}
Symbol vn_initialize_syncerd {
}
Symbol vn_syncer_taskid {
}
Symbol vn_syncer_mutex {
}
Symbol syncer_semaphore {
}
Symbol syncer_workitem_pending {
}
Symbol syncer_delayno {
}
Symbol vnSyncerTaskPriority {
}
Symbol vnSyncerTaskOptions {
}
Symbol vnSyncerTaskStacksize {
}
Symbol vn_sync_task {
}
Symbol taskSpawn {
}
Symbol vn_syncer_add_to_worklist {
}
Symbol sysClkRateGet {
}
Symbol tickGet {
}
Symbol taskDelay {
}
Symbol vxAtomicInc {
}
Symbol vxAtomicDec {
}
Symbol vpurgebufs {
}
Symbol vn_vfree {
}
Symbol vprint {
}
Symbol vnode_types {
}
Symbol strncat {
}
Symbol vn_unhold {
}
Symbol getnewvnode {
}
Symbol vgetino {
}
Symbol vflushbuf {
}
Symbol vinvalbuf {
}
Symbol vaccess {
}
Symbol enosys {
}
Symbol vopErrorENOTDIR {
}
Symbol vopErrorEISDIR {
}
ObjectFile libfsVfs.a::bufSubr.o {
	NAME Object file bufSubr.o from archive libfsVfs.a
	EXPORTS buf_panic buf_initmountpoint buf_deletebuffers buf_makebuffers buf_startwrite buf_biodone bawrite buf_getblk buf_rebusy brelse buf_moveblk buf_swapdata buf_doread buf_wait bread breadn bdwrite bdirty bwrite buf_done buf_invalid
	IMPORTS .TOC. printf vprintf _sigCtxSave edrErrorInjectStub edrKernelFatalPolicyHandler brelvp semDelete free __errno semMCreate semCCreate malloc semBCreate vreassignbuf vn_incr_numoutput semGive semTake semExchange bgetvp taskIdSelf vxAtomicGet vn_decr_numoutput
	DECLARES 
	USES 
}
Module bufSubr.o {
	OBJECT += libfsVfs.a::bufSubr.o
}
ObjectFile libfsVfs.a::mountSubr.o {
	NAME Object file mountSubr.o from archive libfsVfs.a
	EXPORTS mountBufFree mountDelete mountCreate mountBufAlloc mountEject mountInsDev
	IMPORTS .TOC. buf_deletebuffers free bio_free fsmUnmountHookRun vrele vn_deletefiletable vn_deletevnodes semDelete iosDevSuspend iosDevDelete __errno vnodeAffDriverNumber vnodeAffLibInit malloc memset semMCreate vn_makevnodes vn_makefiletable semGive xbdBlockSize bio_alloc buf_initmountpoint buf_makebuffers iosLock iosDevReplaceExt iosDevDelCallback iosUnlock
	DECLARES 
	USES 
}
Module mountSubr.o {
	OBJECT += libfsVfs.a::mountSubr.o
}
ObjectFile libfsVfs.a::vnodeAff.o {
	NAME Object file vnodeAff.o from archive libfsVfs.a
	EXPORTS aff_panic vn_makefiletable vn_deletefiletable vn_getfp vn_relfp lookup namei vnReLookup vnCheckPath vnLockVnodes vn_open vn_close vn_mkdir vncio_open vncio_create vn_remove vn_link vncio_delete vncio_read vncio_write vncio_close vncio_readdir vncio_rename vn_getlock vn_setlock vncio_fsname_to_id vnc_ftype_map vncio_ioctl vnodeAffLibInit vnodeAffDriverNumber vop_error_rename
	IMPORTS .TOC. printf vprintf taskSuspend __errno semMCreate malloc semDelete free semTake semGive vref vrele vput strlen strncpy memmove vattr_null xbdIoctl errnoSet pathCondense strcmp mountDelete bzero memset time iosDrvInstall
	DECLARES 
	USES 
}
Module vnodeAff.o {
	OBJECT += libfsVfs.a::vnodeAff.o
}
ObjectFile libfsVfs.a::vnodeLockf.o {
	NAME Object file vnodeLockf.o from archive libfsVfs.a
	EXPORTS lfGetNewLock lfFreeLock lfDetectDeadlock maxlockdepth lockf_debug lf_advlock
	IMPORTS .TOC. malloc semBCreate free semDelete printf vn_panic memcpy semGive _func_pthread_testandset_canceltype semTake taskIdSelf
	DECLARES 
	USES 
}
Module vnodeLockf.o {
	OBJECT += libfsVfs.a::vnodeLockf.o
}
ObjectFile libfsVfs.a::vnodeSubr.o {
	NAME Object file vnodeSubr.o from archive libfsVfs.a
	EXPORTS vn_panic vn_deletevnodes vn_initialize_syncerd vn_syncer_taskid vnSyncerTaskPriority vnSyncerTaskOptions vnSyncerTaskStacksize vn_sync_task vn_makevnodes vn_syncer_add_to_worklist vattr_null bgetvp brelvp vreassignbuf vn_incr_numoutput vn_decr_numoutput vpurgebufs vn_vfree vput vprint vnode_types vn_unhold getnewvnode vgetino vref vrele vflushbuf vinvalbuf vaccess enosys vopErrorENOTDIR vopErrorEISDIR
	IMPORTS .TOC. printf vprintf _sigCtxSave edrErrorInjectStub edrKernelFatalPolicyHandler semDelete free __errno semMCreate semBCreate taskSpawn semCCreate malloc bzero semTake semGive sysClkRateGet tickGet taskDelay vxAtomicInc vxAtomicDec buf_rebusy brelse vxAtomicGet strncat bwrite bawrite
	DECLARES vn_syncer_mutex syncer_semaphore syncer_workitem_pending syncer_delayno
	USES 
}
Module vnodeSubr.o {
	OBJECT += libfsVfs.a::vnodeSubr.o
}
Library libfsVfs.a {
	MODULES libfsVfs.a::bufSubr.o libfsVfs.a::mountSubr.o libfsVfs.a::vnodeAff.o libfsVfs.a::vnodeLockf.o libfsVfs.a::vnodeSubr.o
}
