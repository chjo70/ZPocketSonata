Symbol authnone_create {
}
Symbol .TOC. {
}
Symbol taskIdSelf {
}
Symbol _null_auth {
}
Symbol xdrmem_create {
}
Symbol xdr_opaque_auth {
}
Symbol perror {
}
Symbol authunix_create {
}
Symbol memSysPartId {
}
Symbol memPartAlloc {
}
Symbol xdr_authunix_parms {
}
Symbol abort {
}
Symbol memPartFree {
}
Symbol printErr {
}
Symbol bcopy {
}
Symbol xdr_u_long {
}
Symbol xdr_string {
}
Symbol xdr_int {
}
Symbol xdr_array {
}
Symbol clnt_genericInclude {
}
Symbol clnt_create {
}
Symbol hostGetByName {
}
Symbol inet_addr {
}
Symbol bzero {
}
Symbol strcmp {
}
Symbol clntudp_create {
}
Symbol clnttcp_create {
}
Symbol clnt_sperrno {
}
Symbol clnt_sperror {
}
Symbol sprintf {
}
Symbol strlen {
}
Symbol strcpy {
}
Symbol clnt_perror {
}
Symbol clnt_perrno {
}
Symbol clnt_spcreateerror {
}
Symbol strcat {
}
Symbol clnt_pcreateerror {
}
Symbol clnt_rawInclude {
}
Symbol clntraw_create {
}
Symbol xdr_callhdr {
}
Symbol svc_getreq {
}
Symbol xdr_replymsg {
}
Symbol _seterr_reply {
}
Symbol clnt_simpleInclude {
}
Symbol callrpc {
}
Symbol close {
}
Symbol strncpy {
}
Symbol pmap_getport {
}
Symbol socket {
}
Symbol connect {
}
Symbol rpcErrnoGet {
}
Symbol tickGet {
}
Symbol xdrrec_create {
}
Symbol xdrrec_endofrecord {
}
Symbol xdr_void {
}
Symbol xdrrec_skiprecord {
}
Symbol select {
}
Symbol read {
}
Symbol write {
}
Symbol clntudp_bufcreate {
}
Symbol setsockopt {
}
Symbol bindresvport {
}
Symbol ioctl {
}
Symbol sysClkRateGet {
}
Symbol sendto {
}
Symbol taskDelay {
}
Symbol recvfrom {
}
Symbol clntudp_freeres {
}
Symbol get_myaddress {
}
Symbol taskSuspend {
}
Symbol pmap_set {
}
Symbol xdr_pmap {
}
Symbol xdr_bool {
}
Symbol pmap_unset {
}
Symbol pmapUnset {
}
Symbol pmaplist {
}
Symbol free {
}
Symbol pmap_getmapsInclude {
}
Symbol pmap_getmaps {
}
Symbol xdr_pmaplist {
}
Symbol xdr_u_short {
}
Symbol xdr_reference {
}
Symbol pmap_rmtcall {
}
Symbol xdr_rmtcall_args {
}
Symbol xdr_rmtcallres {
}
Symbol inet_netof {
}
Symbol inet_makeaddr_b {
}
Symbol clnt_broadcast {
}
Symbol authunix_create_default {
}
Symbol malloc {
}
Symbol panic {
}
Symbol xdr_callmsg {
}
Symbol portmapd {
}
Symbol rpcTaskInit {
}
Symbol memset {
}
Symbol bind {
}
Symbol svcudp_create {
}
Symbol svctcp_create {
}
Symbol reg_service {
}
Symbol svc_register {
}
Symbol svc_run {
}
Symbol svc_sendreply {
}
Symbol reg_service_internal {
}
Symbol xdr_long {
}
Symbol svcerr_decode {
}
Symbol svcerr_noproc {
}
Symbol xdr_bytes {
}
Symbol xdr_opaque {
}
Symbol xdr_enum {
}
Symbol xdr_u_int {
}
Symbol xdr_des_block {
}
Symbol xdr_deskey {
}
Symbol xdr_accepted_reply {
}
Symbol xdr_rejected_reply {
}
Symbol xdr_union {
}
Symbol accepted {
}
Symbol rejected {
}
Symbol xprt_register {
}
Symbol xprt_unregister {
}
Symbol svc_find {
}
Symbol svc_unregister {
}
Symbol svc_unregisterall {
}
Symbol svcerr_systemerr {
}
Symbol svcerr_auth {
}
Symbol svcerr_weakauth {
}
Symbol svcerr_noprog {
}
Symbol svcerr_progvers {
}
Symbol svc_getreqset {
}
Symbol _authenticate {
}
Symbol _svcauth_null {
}
Symbol _svcauth_unix {
}
Symbol _svcauth_short {
}
Symbol printf {
}
Symbol svc_rawInclude {
}
Symbol svcraw_create {
}
Symbol svc_simpleInclude {
}
Symbol registerrpc {
}
Symbol getsockname {
}
Symbol listen {
}
Symbol svcfd_create {
}
Symbol accept {
}
Symbol memcpy {
}
Symbol errnoGet {
}
Symbol xdrrec_eof {
}
Symbol svcudp_bufcreate {
}
Symbol semTake {
}
Symbol bcmp {
}
Symbol semGive {
}
Symbol semDelete {
}
Symbol svcudp_enablecache {
}
Symbol cacheSemOptions {
}
Symbol semMCreate {
}
Symbol cache_fillparams {
}
Symbol xdr_free {
}
Symbol xdr_u_longlong_t {
}
Symbol xdr_longlong_t {
}
Symbol xdr_short {
}
Symbol xdr_char {
}
Symbol xdr_u_char {
}
Symbol _func_printErr {
}
Symbol xdr_netobj {
}
Symbol xdr_wrapstring {
}
Symbol xdr_vector {
}
Symbol xdr_floatInclude {
}
Symbol xdr_float {
}
Symbol xdr_double {
}
Symbol bcopyWords {
}
Symbol bcopyLongs {
}
Symbol lseek {
}
Symbol xdr_pointer {
}
Symbol rpcInit {
}
Symbol portmapdId {
}
Symbol portmapdPriority {
}
Symbol portmapdOptions {
}
Symbol portmapdStackSize {
}
Symbol taskSpawn {
}
Symbol taskDeleteHookAdd {
}
Symbol rpcClntErrnoSet {
}
Symbol errnoSet {
}
ObjectFile librpc.a::auth_none.o {
	NAME Object file auth_none.o from archive librpc.a
	EXPORTS authnone_create
	IMPORTS .TOC. taskIdSelf _null_auth xdrmem_create xdr_opaque_auth
	DECLARES 
	USES 
}
Module auth_none.o {
	OBJECT += librpc.a::auth_none.o
}
ObjectFile librpc.a::auth_unix.o {
	NAME Object file auth_unix.o from archive librpc.a
	EXPORTS authunix_create
	IMPORTS .TOC. xdrmem_create xdr_opaque_auth perror memSysPartId memPartAlloc _null_auth xdr_authunix_parms abort memPartFree printErr bcopy
	DECLARES 
	USES 
}
Module auth_unix.o {
	OBJECT += librpc.a::auth_unix.o
}
ObjectFile librpc.a::authunix_pro.o {
	NAME Object file authunix_pro.o from archive librpc.a
	EXPORTS xdr_authunix_parms
	IMPORTS .TOC. xdr_u_long xdr_string xdr_int xdr_array
	DECLARES 
	USES 
}
Module authunix_pro.o {
	OBJECT += librpc.a::authunix_pro.o
}
ObjectFile librpc.a::clnt_generic.o {
	NAME Object file clnt_generic.o from archive librpc.a
	EXPORTS clnt_genericInclude clnt_create
	IMPORTS .TOC. hostGetByName inet_addr bzero strcmp clntudp_create clnttcp_create taskIdSelf
	DECLARES 
	USES 
}
Module clnt_generic.o {
	OBJECT += librpc.a::clnt_generic.o
}
ObjectFile librpc.a::clnt_perror.o {
	NAME Object file clnt_perror.o from archive librpc.a
	EXPORTS clnt_sperrno clnt_sperror clnt_perror clnt_perrno clnt_spcreateerror clnt_pcreateerror
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc sprintf strlen strcpy printErr strcat
	DECLARES 
	USES 
}
Module clnt_perror.o {
	OBJECT += librpc.a::clnt_perror.o
}
ObjectFile librpc.a::clnt_raw.o {
	NAME Object file clnt_raw.o from archive librpc.a
	EXPORTS clnt_rawInclude clntraw_create
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc printErr bzero memPartFree xdrmem_create xdr_callhdr perror authnone_create svc_getreq _null_auth xdr_replymsg _seterr_reply xdr_opaque_auth
	DECLARES 
	USES 
}
Module clnt_raw.o {
	OBJECT += librpc.a::clnt_raw.o
}
ObjectFile librpc.a::clnt_simple.o {
	NAME Object file clnt_simple.o from archive librpc.a
	EXPORTS clnt_simpleInclude callrpc
	IMPORTS .TOC. taskIdSelf strcmp close hostGetByName clntudp_create strncpy
	DECLARES 
	USES 
}
Module clnt_simple.o {
	OBJECT += librpc.a::clnt_simple.o
}
ObjectFile librpc.a::clnt_tcp.o {
	NAME Object file clnt_tcp.o from archive librpc.a
	EXPORTS clnttcp_create
	IMPORTS .TOC. memSysPartId taskIdSelf memPartAlloc printErr pmap_getport memPartFree socket connect close rpcErrnoGet tickGet xdrmem_create xdr_callhdr xdrrec_create authnone_create xdrrec_endofrecord _null_auth xdr_void xdrrec_skiprecord xdr_replymsg _seterr_reply xdr_opaque_auth bzero select read write
	DECLARES 
	USES 
}
Module clnt_tcp.o {
	OBJECT += librpc.a::clnt_tcp.o
}
ObjectFile librpc.a::clnt_udp.o {
	NAME Object file clnt_udp.o from archive librpc.a
	EXPORTS clntudp_bufcreate clntudp_create clntudp_freeres
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc printErr pmap_getport tickGet xdrmem_create xdr_callhdr socket rpcErrnoGet setsockopt close bindresvport ioctl authnone_create memPartFree sysClkRateGet sendto taskDelay _null_auth bzero select recvfrom xdr_replymsg _seterr_reply xdr_opaque_auth
	DECLARES 
	USES 
}
Module clnt_udp.o {
	OBJECT += librpc.a::clnt_udp.o
}
ObjectFile librpc.a::get_myaddr.o {
	NAME Object file get_myaddr.o from archive librpc.a
	EXPORTS get_myaddress
	IMPORTS .TOC. socket perror taskSuspend ioctl bcopy close
	DECLARES 
	USES 
}
Module get_myaddr.o {
	OBJECT += librpc.a::get_myaddr.o
}
ObjectFile librpc.a::pmap_clnt.o {
	NAME Object file pmap_clnt.o from archive librpc.a
	EXPORTS pmap_set pmap_unset pmapUnset
	IMPORTS .TOC. get_myaddress clntudp_bufcreate xdr_pmap xdr_bool clnt_perror pmaplist free
	DECLARES 
	USES 
}
Module pmap_clnt.o {
	OBJECT += librpc.a::pmap_clnt.o
}
ObjectFile librpc.a::pmap_getmaps.o {
	NAME Object file pmap_getmaps.o from archive librpc.a
	EXPORTS pmap_getmapsInclude pmap_getmaps
	IMPORTS .TOC. clnttcp_create xdr_void xdr_pmaplist clnt_perror
	DECLARES 
	USES 
}
Module pmap_getmaps.o {
	OBJECT += librpc.a::pmap_getmaps.o
}
ObjectFile librpc.a::pmap_getport.o {
	NAME Object file pmap_getport.o from archive librpc.a
	EXPORTS pmap_getport
	IMPORTS .TOC. clntudp_bufcreate xdr_pmap xdr_u_short taskIdSelf
	DECLARES 
	USES 
}
Module pmap_getport.o {
	OBJECT += librpc.a::pmap_getport.o
}
ObjectFile librpc.a::pmap_prot.o {
	NAME Object file pmap_prot.o from archive librpc.a
	EXPORTS xdr_pmap
	IMPORTS .TOC. xdr_u_long
	DECLARES 
	USES 
}
Module pmap_prot.o {
	OBJECT += librpc.a::pmap_prot.o
}
ObjectFile librpc.a::pmap_prot2.o {
	NAME Object file pmap_prot2.o from archive librpc.a
	EXPORTS xdr_pmaplist
	IMPORTS .TOC. xdr_bool xdr_pmap xdr_reference
	DECLARES 
	USES 
}
Module pmap_prot2.o {
	OBJECT += librpc.a::pmap_prot2.o
}
ObjectFile librpc.a::pmap_rmt.o {
	NAME Object file pmap_rmt.o from archive librpc.a
	EXPORTS pmap_rmtcall xdr_rmtcall_args xdr_rmtcallres clnt_broadcast
	IMPORTS .TOC. clntudp_create xdr_u_long xdr_reference ioctl perror bcopy inet_netof inet_makeaddr_b authunix_create_default taskIdSelf memSysPartId memPartAlloc malloc panic socket setsockopt bzero tickGet xdrmem_create xdr_callmsg sendto _null_auth select rpcErrnoGet recvfrom xdr_replymsg xdr_void close free memPartFree
	DECLARES 
	USES 
}
Module pmap_rmt.o {
	OBJECT += librpc.a::pmap_rmt.o
}
ObjectFile librpc.a::portmap.o {
	NAME Object file portmap.o from archive librpc.a
	EXPORTS portmapd reg_service reg_service_internal
	IMPORTS .TOC. rpcTaskInit memset socket perror bind taskSuspend svcudp_create printErr svctcp_create svc_register svc_run abort malloc get_myaddress clntudp_create authunix_create svc_sendreply free xdr_void xdr_pmap memSysPartId memPartAlloc memPartFree xdr_long svcerr_decode xdr_pmaplist svcerr_noproc xdr_bytes xdr_u_long xdr_opaque
	DECLARES pmaplist
	USES 
}
Module portmap.o {
	OBJECT += librpc.a::portmap.o
}
ObjectFile librpc.a::rpc_callmsg.o {
	NAME Object file rpc_callmsg.o from archive librpc.a
	EXPORTS xdr_callmsg
	IMPORTS .TOC. bcopy memSysPartId memPartAlloc xdr_opaque xdr_enum xdr_u_int xdr_u_long xdr_opaque_auth
	DECLARES 
	USES 
}
Module rpc_callmsg.o {
	OBJECT += librpc.a::rpc_callmsg.o
}
ObjectFile librpc.a::rpc_common.o {
	NAME Object file rpc_common.o from archive librpc.a
	EXPORTS 
	IMPORTS 
	DECLARES _null_auth
	USES 
}
Module rpc_common.o {
	OBJECT += librpc.a::rpc_common.o
}
ObjectFile librpc.a::rpc_prot.o {
	NAME Object file rpc_prot.o from archive librpc.a
	EXPORTS xdr_opaque_auth xdr_des_block xdr_deskey xdr_accepted_reply xdr_rejected_reply xdr_replymsg xdr_callhdr accepted rejected _seterr_reply
	IMPORTS .TOC. xdr_enum xdr_bytes xdr_opaque xdr_u_long xdr_union
	DECLARES 
	USES 
}
Module rpc_prot.o {
	OBJECT += librpc.a::rpc_prot.o
}
ObjectFile librpc.a::svc.o {
	NAME Object file svc.o from archive librpc.a
	EXPORTS xprt_register xprt_unregister svc_find svc_register svc_unregister svc_unregisterall svc_sendreply svcerr_noproc svcerr_decode svcerr_systemerr svcerr_auth svcerr_weakauth svcerr_noprog svcerr_progvers svc_getreqset svc_getreq svc_run
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc pmap_set memPartFree pmap_unset pmapUnset panic bzero _authenticate select rpcErrnoGet perror
	DECLARES 
	USES 
}
Module svc.o {
	OBJECT += librpc.a::svc.o
}
ObjectFile librpc.a::svc_auth.o {
	NAME Object file svc_auth.o from archive librpc.a
	EXPORTS _authenticate _svcauth_null
	IMPORTS .TOC. _null_auth _svcauth_unix _svcauth_short
	DECLARES 
	USES 
}
Module svc_auth.o {
	OBJECT += librpc.a::svc_auth.o
}
ObjectFile librpc.a::svc_auth_uni.o {
	NAME Object file svc_auth_uni.o from archive librpc.a
	EXPORTS _svcauth_unix _svcauth_short
	IMPORTS .TOC. xdrmem_create bcopy printf xdr_authunix_parms
	DECLARES 
	USES 
}
Module svc_auth_uni.o {
	OBJECT += librpc.a::svc_auth_uni.o
}
ObjectFile librpc.a::svc_raw.o {
	NAME Object file svc_raw.o from archive librpc.a
	EXPORTS svc_rawInclude svcraw_create
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc printErr bzero memPartFree xdrmem_create xdr_callmsg xdr_replymsg
	DECLARES 
	USES 
}
Module svc_raw.o {
	OBJECT += librpc.a::svc_raw.o
}
ObjectFile librpc.a::svc_simple.o {
	NAME Object file svc_simple.o from archive librpc.a
	EXPORTS svc_simpleInclude registerrpc
	IMPORTS .TOC. taskIdSelf printErr svcudp_create pmap_unset svc_register memSysPartId memPartAlloc panic xdr_void svc_sendreply memPartFree taskSuspend bzero svcerr_decode
	DECLARES 
	USES 
}
Module svc_simple.o {
	OBJECT += librpc.a::svc_simple.o
}
ObjectFile librpc.a::svc_tcp.o {
	NAME Object file svc_tcp.o from archive librpc.a
	EXPORTS svctcp_create svcfd_create
	IMPORTS .TOC. socket perror bzero bindresvport bind getsockname listen close memSysPartId memPartAlloc memPartFree printErr _null_auth xprt_register xdrrec_create accept rpcErrnoGet xprt_unregister taskIdSelf memcpy select errnoGet read write xdrrec_eof xdrrec_skiprecord xdr_callmsg xdr_replymsg xdrrec_endofrecord abort
	DECLARES 
	USES 
}
Module svc_tcp.o {
	OBJECT += librpc.a::svc_tcp.o
}
ObjectFile librpc.a::svc_udp.o {
	NAME Object file svc_udp.o from archive librpc.a
	EXPORTS svcudp_bufcreate svcudp_create svcudp_enablecache cacheSemOptions cache_fillparams
	IMPORTS .TOC. socket perror bzero bindresvport bind getsockname close memSysPartId memPartAlloc printErr memPartFree xdrmem_create xprt_register free bcopy semTake bcmp semGive recvfrom rpcErrnoGet xdr_callmsg sendto xdr_replymsg xprt_unregister semDelete semMCreate
	DECLARES 
	USES 
}
Module svc_udp.o {
	OBJECT += librpc.a::svc_udp.o
}
ObjectFile librpc.a::xdr.o {
	NAME Object file xdr.o from archive librpc.a
	EXPORTS xdr_free xdr_void xdr_long xdr_int xdr_u_long xdr_u_int xdr_u_longlong_t xdr_longlong_t xdr_short xdr_u_short xdr_char xdr_u_char xdr_bool xdr_enum xdr_opaque xdr_bytes xdr_netobj xdr_union xdr_string xdr_wrapstring
	IMPORTS .TOC. memSysPartId memPartAlloc _func_printErr memPartFree strlen
	DECLARES 
	USES 
}
Module xdr.o {
	OBJECT += librpc.a::xdr.o
}
ObjectFile librpc.a::xdr_array.o {
	NAME Object file xdr_array.o from archive librpc.a
	EXPORTS xdr_array xdr_vector
	IMPORTS .TOC. xdr_u_int _func_printErr memSysPartId memPartAlloc bzero memPartFree
	DECLARES 
	USES 
}
Module xdr_array.o {
	OBJECT += librpc.a::xdr_array.o
}
ObjectFile librpc.a::xdr_float.o {
	NAME Object file xdr_float.o from archive librpc.a
	EXPORTS xdr_floatInclude xdr_float xdr_double
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module xdr_float.o {
	OBJECT += librpc.a::xdr_float.o
}
ObjectFile librpc.a::xdr_mem.o {
	NAME Object file xdr_mem.o from archive librpc.a
	EXPORTS xdrmem_create
	IMPORTS .TOC. bcopy bcopyWords bcopyLongs
	DECLARES 
	USES 
}
Module xdr_mem.o {
	OBJECT += librpc.a::xdr_mem.o
}
ObjectFile librpc.a::xdr_rec.o {
	NAME Object file xdr_rec.o from archive librpc.a
	EXPORTS xdrrec_create xdrrec_skiprecord xdrrec_eof xdrrec_endofrecord
	IMPORTS .TOC. memSysPartId memPartAlloc memPartFree printErr bcopy lseek
	DECLARES 
	USES 
}
Module xdr_rec.o {
	OBJECT += librpc.a::xdr_rec.o
}
ObjectFile librpc.a::xdr_ref.o {
	NAME Object file xdr_ref.o from archive librpc.a
	EXPORTS xdr_reference xdr_pointer
	IMPORTS .TOC. memSysPartId memPartAlloc printErr bzero memPartFree xdr_bool
	DECLARES 
	USES 
}
Module xdr_ref.o {
	OBJECT += librpc.a::xdr_ref.o
}
ObjectFile librpc.a::rpcLib.o {
	NAME Object file rpcLib.o from archive librpc.a
	EXPORTS rpcInit portmapdPriority portmapdOptions portmapdStackSize rpcTaskInit rpcClntErrnoSet rpcErrnoGet
	IMPORTS .TOC. portmapd taskSpawn clnt_genericInclude clnt_rawInclude clnt_simpleInclude pmap_getmapsInclude svc_rawInclude svc_simpleInclude xdr_floatInclude taskDeleteHookAdd taskIdSelf memSysPartId memPartAlloc bzero close svc_unregisterall memPartFree errnoSet errnoGet
	DECLARES portmapdId
	USES 
}
Module rpcLib.o {
	OBJECT += librpc.a::rpcLib.o
}
Library librpc.a {
	MODULES librpc.a::auth_none.o librpc.a::auth_unix.o librpc.a::authunix_pro.o librpc.a::clnt_generic.o librpc.a::clnt_perror.o librpc.a::clnt_raw.o librpc.a::clnt_simple.o librpc.a::clnt_tcp.o librpc.a::clnt_udp.o librpc.a::get_myaddr.o librpc.a::pmap_clnt.o librpc.a::pmap_getmaps.o librpc.a::pmap_getport.o librpc.a::pmap_prot.o librpc.a::pmap_prot2.o librpc.a::pmap_rmt.o librpc.a::portmap.o librpc.a::rpc_callmsg.o librpc.a::rpc_common.o librpc.a::rpc_prot.o librpc.a::svc.o librpc.a::svc_auth.o librpc.a::svc_auth_uni.o librpc.a::svc_raw.o librpc.a::svc_simple.o librpc.a::svc_tcp.o librpc.a::svc_udp.o librpc.a::xdr.o librpc.a::xdr_array.o librpc.a::xdr_float.o librpc.a::xdr_mem.o librpc.a::xdr_rec.o librpc.a::xdr_ref.o librpc.a::rpcLib.o
}
Symbol authnone_create {
}
Symbol .TOC. {
}
Symbol taskIdSelf {
}
Symbol _null_auth {
}
Symbol xdrmem_create {
}
Symbol xdr_opaque_auth {
}
Symbol perror {
}
Symbol authunix_create {
}
Symbol memSysPartId {
}
Symbol memPartAlloc {
}
Symbol xdr_authunix_parms {
}
Symbol abort {
}
Symbol memPartFree {
}
Symbol printErr {
}
Symbol bcopy {
}
Symbol xdr_u_long {
}
Symbol xdr_string {
}
Symbol xdr_int {
}
Symbol xdr_array {
}
Symbol clnt_genericInclude {
}
Symbol clnt_create {
}
Symbol hostGetByName {
}
Symbol inet_addr {
}
Symbol bzero {
}
Symbol strcmp {
}
Symbol clntudp_create {
}
Symbol clnttcp_create {
}
Symbol clnt_sperrno {
}
Symbol clnt_sperror {
}
Symbol sprintf {
}
Symbol strlen {
}
Symbol strcpy {
}
Symbol clnt_perror {
}
Symbol clnt_perrno {
}
Symbol clnt_spcreateerror {
}
Symbol strcat {
}
Symbol clnt_pcreateerror {
}
Symbol clnt_rawInclude {
}
Symbol clntraw_create {
}
Symbol xdr_callhdr {
}
Symbol svc_getreq {
}
Symbol xdr_replymsg {
}
Symbol _seterr_reply {
}
Symbol clnt_simpleInclude {
}
Symbol callrpc {
}
Symbol close {
}
Symbol strncpy {
}
Symbol pmap_getport {
}
Symbol socket {
}
Symbol connect {
}
Symbol rpcErrnoGet {
}
Symbol tickGet {
}
Symbol xdrrec_create {
}
Symbol xdrrec_endofrecord {
}
Symbol xdr_void {
}
Symbol xdrrec_skiprecord {
}
Symbol select {
}
Symbol read {
}
Symbol write {
}
Symbol clntudp_bufcreate {
}
Symbol setsockopt {
}
Symbol bindresvport {
}
Symbol ioctl {
}
Symbol sysClkRateGet {
}
Symbol sendto {
}
Symbol taskDelay {
}
Symbol recvfrom {
}
Symbol clntudp_freeres {
}
Symbol get_myaddress {
}
Symbol taskSuspend {
}
Symbol pmap_set {
}
Symbol xdr_pmap {
}
Symbol xdr_bool {
}
Symbol pmap_unset {
}
Symbol pmapUnset {
}
Symbol pmaplist {
}
Symbol free {
}
Symbol pmap_getmapsInclude {
}
Symbol pmap_getmaps {
}
Symbol xdr_pmaplist {
}
Symbol xdr_u_short {
}
Symbol xdr_reference {
}
Symbol pmap_rmtcall {
}
Symbol xdr_rmtcall_args {
}
Symbol xdr_rmtcallres {
}
Symbol inet_netof {
}
Symbol inet_makeaddr_b {
}
Symbol clnt_broadcast {
}
Symbol authunix_create_default {
}
Symbol malloc {
}
Symbol panic {
}
Symbol xdr_callmsg {
}
Symbol portmapd {
}
Symbol rpcTaskInit {
}
Symbol memset {
}
Symbol bind {
}
Symbol svcudp_create {
}
Symbol svctcp_create {
}
Symbol reg_service {
}
Symbol svc_register {
}
Symbol svc_run {
}
Symbol svc_sendreply {
}
Symbol reg_service_internal {
}
Symbol xdr_long {
}
Symbol svcerr_decode {
}
Symbol svcerr_noproc {
}
Symbol xdr_bytes {
}
Symbol xdr_opaque {
}
Symbol xdr_enum {
}
Symbol xdr_u_int {
}
Symbol xdr_des_block {
}
Symbol xdr_deskey {
}
Symbol xdr_accepted_reply {
}
Symbol xdr_rejected_reply {
}
Symbol xdr_union {
}
Symbol accepted {
}
Symbol rejected {
}
Symbol xprt_register {
}
Symbol xprt_unregister {
}
Symbol svc_find {
}
Symbol svc_unregister {
}
Symbol svc_unregisterall {
}
Symbol svcerr_systemerr {
}
Symbol svcerr_auth {
}
Symbol svcerr_weakauth {
}
Symbol svcerr_noprog {
}
Symbol svcerr_progvers {
}
Symbol svc_getreqset {
}
Symbol _authenticate {
}
Symbol _svcauth_null {
}
Symbol _svcauth_unix {
}
Symbol _svcauth_short {
}
Symbol printf {
}
Symbol svc_rawInclude {
}
Symbol svcraw_create {
}
Symbol svc_simpleInclude {
}
Symbol registerrpc {
}
Symbol getsockname {
}
Symbol listen {
}
Symbol svcfd_create {
}
Symbol accept {
}
Symbol memcpy {
}
Symbol errnoGet {
}
Symbol xdrrec_eof {
}
Symbol svcudp_bufcreate {
}
Symbol semTake {
}
Symbol bcmp {
}
Symbol semGive {
}
Symbol semDelete {
}
Symbol svcudp_enablecache {
}
Symbol cacheSemOptions {
}
Symbol semMCreate {
}
Symbol cache_fillparams {
}
Symbol xdr_free {
}
Symbol xdr_u_longlong_t {
}
Symbol xdr_longlong_t {
}
Symbol xdr_short {
}
Symbol xdr_char {
}
Symbol xdr_u_char {
}
Symbol _func_printErr {
}
Symbol xdr_netobj {
}
Symbol xdr_wrapstring {
}
Symbol xdr_vector {
}
Symbol xdr_floatInclude {
}
Symbol xdr_float {
}
Symbol xdr_double {
}
Symbol bcopyWords {
}
Symbol bcopyLongs {
}
Symbol lseek {
}
Symbol xdr_pointer {
}
Symbol rpcInit {
}
Symbol portmapdId {
}
Symbol portmapdPriority {
}
Symbol portmapdOptions {
}
Symbol portmapdStackSize {
}
Symbol taskSpawn {
}
Symbol taskDeleteHookAdd {
}
Symbol rpcClntErrnoSet {
}
Symbol errnoSet {
}
ObjectFile librpc.a::auth_none.o {
	NAME Object file auth_none.o from archive librpc.a
	EXPORTS authnone_create
	IMPORTS .TOC. taskIdSelf _null_auth xdrmem_create xdr_opaque_auth
	DECLARES 
	USES 
}
Module auth_none.o {
	OBJECT += librpc.a::auth_none.o
}
ObjectFile librpc.a::auth_unix.o {
	NAME Object file auth_unix.o from archive librpc.a
	EXPORTS authunix_create
	IMPORTS .TOC. xdrmem_create xdr_opaque_auth perror memSysPartId memPartAlloc _null_auth xdr_authunix_parms abort memPartFree printErr bcopy
	DECLARES 
	USES 
}
Module auth_unix.o {
	OBJECT += librpc.a::auth_unix.o
}
ObjectFile librpc.a::authunix_pro.o {
	NAME Object file authunix_pro.o from archive librpc.a
	EXPORTS xdr_authunix_parms
	IMPORTS .TOC. xdr_u_long xdr_string xdr_int xdr_array
	DECLARES 
	USES 
}
Module authunix_pro.o {
	OBJECT += librpc.a::authunix_pro.o
}
ObjectFile librpc.a::clnt_generic.o {
	NAME Object file clnt_generic.o from archive librpc.a
	EXPORTS clnt_genericInclude clnt_create
	IMPORTS .TOC. hostGetByName inet_addr bzero strcmp clntudp_create clnttcp_create taskIdSelf
	DECLARES 
	USES 
}
Module clnt_generic.o {
	OBJECT += librpc.a::clnt_generic.o
}
ObjectFile librpc.a::clnt_perror.o {
	NAME Object file clnt_perror.o from archive librpc.a
	EXPORTS clnt_sperrno clnt_sperror clnt_perror clnt_perrno clnt_spcreateerror clnt_pcreateerror
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc sprintf strlen strcpy printErr strcat
	DECLARES 
	USES 
}
Module clnt_perror.o {
	OBJECT += librpc.a::clnt_perror.o
}
ObjectFile librpc.a::clnt_raw.o {
	NAME Object file clnt_raw.o from archive librpc.a
	EXPORTS clnt_rawInclude clntraw_create
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc printErr bzero memPartFree xdrmem_create xdr_callhdr perror authnone_create svc_getreq _null_auth xdr_replymsg _seterr_reply xdr_opaque_auth
	DECLARES 
	USES 
}
Module clnt_raw.o {
	OBJECT += librpc.a::clnt_raw.o
}
ObjectFile librpc.a::clnt_simple.o {
	NAME Object file clnt_simple.o from archive librpc.a
	EXPORTS clnt_simpleInclude callrpc
	IMPORTS .TOC. taskIdSelf strcmp close hostGetByName clntudp_create strncpy
	DECLARES 
	USES 
}
Module clnt_simple.o {
	OBJECT += librpc.a::clnt_simple.o
}
ObjectFile librpc.a::clnt_tcp.o {
	NAME Object file clnt_tcp.o from archive librpc.a
	EXPORTS clnttcp_create
	IMPORTS .TOC. memSysPartId taskIdSelf memPartAlloc printErr pmap_getport memPartFree socket connect close rpcErrnoGet tickGet xdrmem_create xdr_callhdr xdrrec_create authnone_create xdrrec_endofrecord _null_auth xdr_void xdrrec_skiprecord xdr_replymsg _seterr_reply xdr_opaque_auth bzero select read write
	DECLARES 
	USES 
}
Module clnt_tcp.o {
	OBJECT += librpc.a::clnt_tcp.o
}
ObjectFile librpc.a::clnt_udp.o {
	NAME Object file clnt_udp.o from archive librpc.a
	EXPORTS clntudp_bufcreate clntudp_create clntudp_freeres
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc printErr pmap_getport tickGet xdrmem_create xdr_callhdr socket rpcErrnoGet setsockopt close bindresvport ioctl authnone_create memPartFree sysClkRateGet sendto taskDelay _null_auth bzero select recvfrom xdr_replymsg _seterr_reply xdr_opaque_auth
	DECLARES 
	USES 
}
Module clnt_udp.o {
	OBJECT += librpc.a::clnt_udp.o
}
ObjectFile librpc.a::get_myaddr.o {
	NAME Object file get_myaddr.o from archive librpc.a
	EXPORTS get_myaddress
	IMPORTS .TOC. socket perror taskSuspend ioctl bcopy close
	DECLARES 
	USES 
}
Module get_myaddr.o {
	OBJECT += librpc.a::get_myaddr.o
}
ObjectFile librpc.a::pmap_clnt.o {
	NAME Object file pmap_clnt.o from archive librpc.a
	EXPORTS pmap_set pmap_unset pmapUnset
	IMPORTS .TOC. get_myaddress clntudp_bufcreate xdr_pmap xdr_bool clnt_perror pmaplist free
	DECLARES 
	USES 
}
Module pmap_clnt.o {
	OBJECT += librpc.a::pmap_clnt.o
}
ObjectFile librpc.a::pmap_getmaps.o {
	NAME Object file pmap_getmaps.o from archive librpc.a
	EXPORTS pmap_getmapsInclude pmap_getmaps
	IMPORTS .TOC. clnttcp_create xdr_void xdr_pmaplist clnt_perror
	DECLARES 
	USES 
}
Module pmap_getmaps.o {
	OBJECT += librpc.a::pmap_getmaps.o
}
ObjectFile librpc.a::pmap_getport.o {
	NAME Object file pmap_getport.o from archive librpc.a
	EXPORTS pmap_getport
	IMPORTS .TOC. clntudp_bufcreate xdr_pmap xdr_u_short taskIdSelf
	DECLARES 
	USES 
}
Module pmap_getport.o {
	OBJECT += librpc.a::pmap_getport.o
}
ObjectFile librpc.a::pmap_prot.o {
	NAME Object file pmap_prot.o from archive librpc.a
	EXPORTS xdr_pmap
	IMPORTS .TOC. xdr_u_long
	DECLARES 
	USES 
}
Module pmap_prot.o {
	OBJECT += librpc.a::pmap_prot.o
}
ObjectFile librpc.a::pmap_prot2.o {
	NAME Object file pmap_prot2.o from archive librpc.a
	EXPORTS xdr_pmaplist
	IMPORTS .TOC. xdr_bool xdr_pmap xdr_reference
	DECLARES 
	USES 
}
Module pmap_prot2.o {
	OBJECT += librpc.a::pmap_prot2.o
}
ObjectFile librpc.a::pmap_rmt.o {
	NAME Object file pmap_rmt.o from archive librpc.a
	EXPORTS pmap_rmtcall xdr_rmtcall_args xdr_rmtcallres clnt_broadcast
	IMPORTS .TOC. clntudp_create xdr_u_long xdr_reference ioctl perror bcopy inet_netof inet_makeaddr_b authunix_create_default taskIdSelf memSysPartId memPartAlloc malloc panic socket setsockopt bzero tickGet xdrmem_create xdr_callmsg sendto _null_auth select rpcErrnoGet recvfrom xdr_replymsg xdr_void close free memPartFree
	DECLARES 
	USES 
}
Module pmap_rmt.o {
	OBJECT += librpc.a::pmap_rmt.o
}
ObjectFile librpc.a::portmap.o {
	NAME Object file portmap.o from archive librpc.a
	EXPORTS portmapd reg_service reg_service_internal
	IMPORTS .TOC. rpcTaskInit memset socket perror bind taskSuspend svcudp_create printErr svctcp_create svc_register svc_run abort malloc get_myaddress clntudp_create authunix_create svc_sendreply free xdr_void xdr_pmap memSysPartId memPartAlloc memPartFree xdr_long svcerr_decode xdr_pmaplist svcerr_noproc xdr_bytes xdr_u_long xdr_opaque
	DECLARES pmaplist
	USES 
}
Module portmap.o {
	OBJECT += librpc.a::portmap.o
}
ObjectFile librpc.a::rpc_callmsg.o {
	NAME Object file rpc_callmsg.o from archive librpc.a
	EXPORTS xdr_callmsg
	IMPORTS .TOC. bcopy memSysPartId memPartAlloc xdr_opaque xdr_enum xdr_u_int xdr_u_long xdr_opaque_auth
	DECLARES 
	USES 
}
Module rpc_callmsg.o {
	OBJECT += librpc.a::rpc_callmsg.o
}
ObjectFile librpc.a::rpc_common.o {
	NAME Object file rpc_common.o from archive librpc.a
	EXPORTS 
	IMPORTS 
	DECLARES _null_auth
	USES 
}
Module rpc_common.o {
	OBJECT += librpc.a::rpc_common.o
}
ObjectFile librpc.a::rpc_prot.o {
	NAME Object file rpc_prot.o from archive librpc.a
	EXPORTS xdr_opaque_auth xdr_des_block xdr_deskey xdr_accepted_reply xdr_rejected_reply xdr_replymsg xdr_callhdr accepted rejected _seterr_reply
	IMPORTS .TOC. xdr_enum xdr_bytes xdr_opaque xdr_u_long xdr_union
	DECLARES 
	USES 
}
Module rpc_prot.o {
	OBJECT += librpc.a::rpc_prot.o
}
ObjectFile librpc.a::svc.o {
	NAME Object file svc.o from archive librpc.a
	EXPORTS xprt_register xprt_unregister svc_find svc_register svc_unregister svc_unregisterall svc_sendreply svcerr_noproc svcerr_decode svcerr_systemerr svcerr_auth svcerr_weakauth svcerr_noprog svcerr_progvers svc_getreqset svc_getreq svc_run
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc pmap_set memPartFree pmap_unset pmapUnset panic bzero _authenticate select rpcErrnoGet perror
	DECLARES 
	USES 
}
Module svc.o {
	OBJECT += librpc.a::svc.o
}
ObjectFile librpc.a::svc_auth.o {
	NAME Object file svc_auth.o from archive librpc.a
	EXPORTS _authenticate _svcauth_null
	IMPORTS .TOC. _null_auth _svcauth_unix _svcauth_short
	DECLARES 
	USES 
}
Module svc_auth.o {
	OBJECT += librpc.a::svc_auth.o
}
ObjectFile librpc.a::svc_auth_uni.o {
	NAME Object file svc_auth_uni.o from archive librpc.a
	EXPORTS _svcauth_unix _svcauth_short
	IMPORTS .TOC. xdrmem_create bcopy printf xdr_authunix_parms
	DECLARES 
	USES 
}
Module svc_auth_uni.o {
	OBJECT += librpc.a::svc_auth_uni.o
}
ObjectFile librpc.a::svc_raw.o {
	NAME Object file svc_raw.o from archive librpc.a
	EXPORTS svc_rawInclude svcraw_create
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc printErr bzero memPartFree xdrmem_create xdr_callmsg xdr_replymsg
	DECLARES 
	USES 
}
Module svc_raw.o {
	OBJECT += librpc.a::svc_raw.o
}
ObjectFile librpc.a::svc_simple.o {
	NAME Object file svc_simple.o from archive librpc.a
	EXPORTS svc_simpleInclude registerrpc
	IMPORTS .TOC. taskIdSelf printErr svcudp_create pmap_unset svc_register memSysPartId memPartAlloc panic xdr_void svc_sendreply memPartFree taskSuspend bzero svcerr_decode
	DECLARES 
	USES 
}
Module svc_simple.o {
	OBJECT += librpc.a::svc_simple.o
}
ObjectFile librpc.a::svc_tcp.o {
	NAME Object file svc_tcp.o from archive librpc.a
	EXPORTS svctcp_create svcfd_create
	IMPORTS .TOC. socket perror bzero bindresvport bind getsockname listen close memSysPartId memPartAlloc memPartFree printErr _null_auth xprt_register xdrrec_create accept rpcErrnoGet xprt_unregister taskIdSelf memcpy select errnoGet read write xdrrec_eof xdrrec_skiprecord xdr_callmsg xdr_replymsg xdrrec_endofrecord abort
	DECLARES 
	USES 
}
Module svc_tcp.o {
	OBJECT += librpc.a::svc_tcp.o
}
ObjectFile librpc.a::svc_udp.o {
	NAME Object file svc_udp.o from archive librpc.a
	EXPORTS svcudp_bufcreate svcudp_create svcudp_enablecache cacheSemOptions cache_fillparams
	IMPORTS .TOC. socket perror bzero bindresvport bind getsockname close memSysPartId memPartAlloc printErr memPartFree xdrmem_create xprt_register free bcopy semTake bcmp semGive recvfrom rpcErrnoGet xdr_callmsg sendto xdr_replymsg xprt_unregister semDelete semMCreate
	DECLARES 
	USES 
}
Module svc_udp.o {
	OBJECT += librpc.a::svc_udp.o
}
ObjectFile librpc.a::xdr.o {
	NAME Object file xdr.o from archive librpc.a
	EXPORTS xdr_free xdr_void xdr_long xdr_int xdr_u_long xdr_u_int xdr_u_longlong_t xdr_longlong_t xdr_short xdr_u_short xdr_char xdr_u_char xdr_bool xdr_enum xdr_opaque xdr_bytes xdr_netobj xdr_union xdr_string xdr_wrapstring
	IMPORTS .TOC. memSysPartId memPartAlloc _func_printErr memPartFree strlen
	DECLARES 
	USES 
}
Module xdr.o {
	OBJECT += librpc.a::xdr.o
}
ObjectFile librpc.a::xdr_array.o {
	NAME Object file xdr_array.o from archive librpc.a
	EXPORTS xdr_array xdr_vector
	IMPORTS .TOC. xdr_u_int _func_printErr memSysPartId memPartAlloc bzero memPartFree
	DECLARES 
	USES 
}
Module xdr_array.o {
	OBJECT += librpc.a::xdr_array.o
}
ObjectFile librpc.a::xdr_float.o {
	NAME Object file xdr_float.o from archive librpc.a
	EXPORTS xdr_floatInclude xdr_float xdr_double
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module xdr_float.o {
	OBJECT += librpc.a::xdr_float.o
}
ObjectFile librpc.a::xdr_mem.o {
	NAME Object file xdr_mem.o from archive librpc.a
	EXPORTS xdrmem_create
	IMPORTS .TOC. bcopy bcopyWords bcopyLongs
	DECLARES 
	USES 
}
Module xdr_mem.o {
	OBJECT += librpc.a::xdr_mem.o
}
ObjectFile librpc.a::xdr_rec.o {
	NAME Object file xdr_rec.o from archive librpc.a
	EXPORTS xdrrec_create xdrrec_skiprecord xdrrec_eof xdrrec_endofrecord
	IMPORTS .TOC. memSysPartId memPartAlloc memPartFree printErr bcopy lseek
	DECLARES 
	USES 
}
Module xdr_rec.o {
	OBJECT += librpc.a::xdr_rec.o
}
ObjectFile librpc.a::xdr_ref.o {
	NAME Object file xdr_ref.o from archive librpc.a
	EXPORTS xdr_reference xdr_pointer
	IMPORTS .TOC. memSysPartId memPartAlloc printErr bzero memPartFree xdr_bool
	DECLARES 
	USES 
}
Module xdr_ref.o {
	OBJECT += librpc.a::xdr_ref.o
}
ObjectFile librpc.a::rpcLib.o {
	NAME Object file rpcLib.o from archive librpc.a
	EXPORTS rpcInit portmapdPriority portmapdOptions portmapdStackSize rpcTaskInit rpcClntErrnoSet rpcErrnoGet
	IMPORTS .TOC. portmapd taskSpawn clnt_genericInclude clnt_rawInclude clnt_simpleInclude pmap_getmapsInclude svc_rawInclude svc_simpleInclude xdr_floatInclude taskDeleteHookAdd taskIdSelf memSysPartId memPartAlloc bzero close svc_unregisterall memPartFree errnoSet errnoGet
	DECLARES portmapdId
	USES 
}
Module rpcLib.o {
	OBJECT += librpc.a::rpcLib.o
}
Library librpc.a {
	MODULES librpc.a::auth_none.o librpc.a::auth_unix.o librpc.a::authunix_pro.o librpc.a::clnt_generic.o librpc.a::clnt_perror.o librpc.a::clnt_raw.o librpc.a::clnt_simple.o librpc.a::clnt_tcp.o librpc.a::clnt_udp.o librpc.a::get_myaddr.o librpc.a::pmap_clnt.o librpc.a::pmap_getmaps.o librpc.a::pmap_getport.o librpc.a::pmap_prot.o librpc.a::pmap_prot2.o librpc.a::pmap_rmt.o librpc.a::portmap.o librpc.a::rpc_callmsg.o librpc.a::rpc_common.o librpc.a::rpc_prot.o librpc.a::svc.o librpc.a::svc_auth.o librpc.a::svc_auth_uni.o librpc.a::svc_raw.o librpc.a::svc_simple.o librpc.a::svc_tcp.o librpc.a::svc_udp.o librpc.a::xdr.o librpc.a::xdr_array.o librpc.a::xdr_float.o librpc.a::xdr_mem.o librpc.a::xdr_rec.o librpc.a::xdr_ref.o librpc.a::rpcLib.o
}
Symbol authnone_create {
}
Symbol .TOC. {
}
Symbol taskIdSelf {
}
Symbol _null_auth {
}
Symbol xdrmem_create {
}
Symbol xdr_opaque_auth {
}
Symbol perror {
}
Symbol authunix_create {
}
Symbol memSysPartId {
}
Symbol memPartAlloc {
}
Symbol xdr_authunix_parms {
}
Symbol abort {
}
Symbol memPartFree {
}
Symbol printErr {
}
Symbol bcopy {
}
Symbol xdr_u_long {
}
Symbol xdr_string {
}
Symbol xdr_int {
}
Symbol xdr_array {
}
Symbol clnt_genericInclude {
}
Symbol clnt_create {
}
Symbol hostGetByName {
}
Symbol inet_addr {
}
Symbol bzero {
}
Symbol strcmp {
}
Symbol clntudp_create {
}
Symbol clnttcp_create {
}
Symbol clnt_sperrno {
}
Symbol clnt_sperror {
}
Symbol sprintf {
}
Symbol strlen {
}
Symbol strcpy {
}
Symbol clnt_perror {
}
Symbol clnt_perrno {
}
Symbol clnt_spcreateerror {
}
Symbol strcat {
}
Symbol clnt_pcreateerror {
}
Symbol clnt_rawInclude {
}
Symbol clntraw_create {
}
Symbol xdr_callhdr {
}
Symbol svc_getreq {
}
Symbol xdr_replymsg {
}
Symbol _seterr_reply {
}
Symbol clnt_simpleInclude {
}
Symbol callrpc {
}
Symbol close {
}
Symbol strncpy {
}
Symbol pmap_getport {
}
Symbol socket {
}
Symbol connect {
}
Symbol rpcErrnoGet {
}
Symbol tickGet {
}
Symbol xdrrec_create {
}
Symbol xdrrec_endofrecord {
}
Symbol xdr_void {
}
Symbol xdrrec_skiprecord {
}
Symbol select {
}
Symbol read {
}
Symbol write {
}
Symbol clntudp_bufcreate {
}
Symbol setsockopt {
}
Symbol bindresvport {
}
Symbol ioctl {
}
Symbol sysClkRateGet {
}
Symbol sendto {
}
Symbol taskDelay {
}
Symbol recvfrom {
}
Symbol clntudp_freeres {
}
Symbol get_myaddress {
}
Symbol taskSuspend {
}
Symbol pmap_set {
}
Symbol xdr_pmap {
}
Symbol xdr_bool {
}
Symbol pmap_unset {
}
Symbol pmapUnset {
}
Symbol pmaplist {
}
Symbol free {
}
Symbol pmap_getmapsInclude {
}
Symbol pmap_getmaps {
}
Symbol xdr_pmaplist {
}
Symbol xdr_u_short {
}
Symbol xdr_reference {
}
Symbol pmap_rmtcall {
}
Symbol xdr_rmtcall_args {
}
Symbol xdr_rmtcallres {
}
Symbol inet_netof {
}
Symbol inet_makeaddr_b {
}
Symbol clnt_broadcast {
}
Symbol authunix_create_default {
}
Symbol malloc {
}
Symbol panic {
}
Symbol xdr_callmsg {
}
Symbol portmapd {
}
Symbol rpcTaskInit {
}
Symbol memset {
}
Symbol bind {
}
Symbol svcudp_create {
}
Symbol svctcp_create {
}
Symbol reg_service {
}
Symbol svc_register {
}
Symbol svc_run {
}
Symbol svc_sendreply {
}
Symbol reg_service_internal {
}
Symbol xdr_long {
}
Symbol svcerr_decode {
}
Symbol svcerr_noproc {
}
Symbol xdr_bytes {
}
Symbol xdr_opaque {
}
Symbol xdr_enum {
}
Symbol xdr_u_int {
}
Symbol xdr_des_block {
}
Symbol xdr_deskey {
}
Symbol xdr_accepted_reply {
}
Symbol xdr_rejected_reply {
}
Symbol xdr_union {
}
Symbol accepted {
}
Symbol rejected {
}
Symbol xprt_register {
}
Symbol xprt_unregister {
}
Symbol svc_find {
}
Symbol svc_unregister {
}
Symbol svc_unregisterall {
}
Symbol svcerr_systemerr {
}
Symbol svcerr_auth {
}
Symbol svcerr_weakauth {
}
Symbol svcerr_noprog {
}
Symbol svcerr_progvers {
}
Symbol svc_getreqset {
}
Symbol _authenticate {
}
Symbol _svcauth_null {
}
Symbol _svcauth_unix {
}
Symbol _svcauth_short {
}
Symbol printf {
}
Symbol svc_rawInclude {
}
Symbol svcraw_create {
}
Symbol svc_simpleInclude {
}
Symbol registerrpc {
}
Symbol getsockname {
}
Symbol listen {
}
Symbol svcfd_create {
}
Symbol accept {
}
Symbol memcpy {
}
Symbol errnoGet {
}
Symbol xdrrec_eof {
}
Symbol svcudp_bufcreate {
}
Symbol semTake {
}
Symbol bcmp {
}
Symbol semGive {
}
Symbol semDelete {
}
Symbol svcudp_enablecache {
}
Symbol cacheSemOptions {
}
Symbol semMCreate {
}
Symbol cache_fillparams {
}
Symbol xdr_free {
}
Symbol xdr_u_longlong_t {
}
Symbol xdr_longlong_t {
}
Symbol xdr_short {
}
Symbol xdr_char {
}
Symbol xdr_u_char {
}
Symbol _func_printErr {
}
Symbol xdr_netobj {
}
Symbol xdr_wrapstring {
}
Symbol xdr_vector {
}
Symbol xdr_floatInclude {
}
Symbol xdr_float {
}
Symbol xdr_double {
}
Symbol bcopyWords {
}
Symbol bcopyLongs {
}
Symbol lseek {
}
Symbol xdr_pointer {
}
Symbol rpcInit {
}
Symbol portmapdId {
}
Symbol portmapdPriority {
}
Symbol portmapdOptions {
}
Symbol portmapdStackSize {
}
Symbol taskSpawn {
}
Symbol taskDeleteHookAdd {
}
Symbol rpcClntErrnoSet {
}
Symbol errnoSet {
}
ObjectFile librpc.a::auth_none.o {
	NAME Object file auth_none.o from archive librpc.a
	EXPORTS authnone_create
	IMPORTS .TOC. taskIdSelf _null_auth xdrmem_create xdr_opaque_auth
	DECLARES 
	USES 
}
Module auth_none.o {
	OBJECT += librpc.a::auth_none.o
}
ObjectFile librpc.a::auth_unix.o {
	NAME Object file auth_unix.o from archive librpc.a
	EXPORTS authunix_create
	IMPORTS .TOC. xdrmem_create xdr_opaque_auth perror memSysPartId memPartAlloc _null_auth xdr_authunix_parms abort memPartFree printErr bcopy
	DECLARES 
	USES 
}
Module auth_unix.o {
	OBJECT += librpc.a::auth_unix.o
}
ObjectFile librpc.a::authunix_pro.o {
	NAME Object file authunix_pro.o from archive librpc.a
	EXPORTS xdr_authunix_parms
	IMPORTS .TOC. xdr_u_long xdr_string xdr_int xdr_array
	DECLARES 
	USES 
}
Module authunix_pro.o {
	OBJECT += librpc.a::authunix_pro.o
}
ObjectFile librpc.a::clnt_generic.o {
	NAME Object file clnt_generic.o from archive librpc.a
	EXPORTS clnt_genericInclude clnt_create
	IMPORTS .TOC. hostGetByName inet_addr bzero strcmp clntudp_create clnttcp_create taskIdSelf
	DECLARES 
	USES 
}
Module clnt_generic.o {
	OBJECT += librpc.a::clnt_generic.o
}
ObjectFile librpc.a::clnt_perror.o {
	NAME Object file clnt_perror.o from archive librpc.a
	EXPORTS clnt_sperrno clnt_sperror clnt_perror clnt_perrno clnt_spcreateerror clnt_pcreateerror
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc sprintf strlen strcpy printErr strcat
	DECLARES 
	USES 
}
Module clnt_perror.o {
	OBJECT += librpc.a::clnt_perror.o
}
ObjectFile librpc.a::clnt_raw.o {
	NAME Object file clnt_raw.o from archive librpc.a
	EXPORTS clnt_rawInclude clntraw_create
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc printErr bzero memPartFree xdrmem_create xdr_callhdr perror authnone_create svc_getreq _null_auth xdr_replymsg _seterr_reply xdr_opaque_auth
	DECLARES 
	USES 
}
Module clnt_raw.o {
	OBJECT += librpc.a::clnt_raw.o
}
ObjectFile librpc.a::clnt_simple.o {
	NAME Object file clnt_simple.o from archive librpc.a
	EXPORTS clnt_simpleInclude callrpc
	IMPORTS .TOC. taskIdSelf strcmp close hostGetByName clntudp_create strncpy
	DECLARES 
	USES 
}
Module clnt_simple.o {
	OBJECT += librpc.a::clnt_simple.o
}
ObjectFile librpc.a::clnt_tcp.o {
	NAME Object file clnt_tcp.o from archive librpc.a
	EXPORTS clnttcp_create
	IMPORTS .TOC. memSysPartId taskIdSelf memPartAlloc printErr pmap_getport memPartFree socket connect close rpcErrnoGet tickGet xdrmem_create xdr_callhdr xdrrec_create authnone_create xdrrec_endofrecord _null_auth xdr_void xdrrec_skiprecord xdr_replymsg _seterr_reply xdr_opaque_auth bzero select read write
	DECLARES 
	USES 
}
Module clnt_tcp.o {
	OBJECT += librpc.a::clnt_tcp.o
}
ObjectFile librpc.a::clnt_udp.o {
	NAME Object file clnt_udp.o from archive librpc.a
	EXPORTS clntudp_bufcreate clntudp_create clntudp_freeres
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc printErr pmap_getport tickGet xdrmem_create xdr_callhdr socket rpcErrnoGet setsockopt close bindresvport ioctl authnone_create memPartFree sysClkRateGet sendto taskDelay _null_auth bzero select recvfrom xdr_replymsg _seterr_reply xdr_opaque_auth
	DECLARES 
	USES 
}
Module clnt_udp.o {
	OBJECT += librpc.a::clnt_udp.o
}
ObjectFile librpc.a::get_myaddr.o {
	NAME Object file get_myaddr.o from archive librpc.a
	EXPORTS get_myaddress
	IMPORTS .TOC. socket perror taskSuspend ioctl bcopy close
	DECLARES 
	USES 
}
Module get_myaddr.o {
	OBJECT += librpc.a::get_myaddr.o
}
ObjectFile librpc.a::pmap_clnt.o {
	NAME Object file pmap_clnt.o from archive librpc.a
	EXPORTS pmap_set pmap_unset pmapUnset
	IMPORTS .TOC. get_myaddress clntudp_bufcreate xdr_pmap xdr_bool clnt_perror pmaplist free
	DECLARES 
	USES 
}
Module pmap_clnt.o {
	OBJECT += librpc.a::pmap_clnt.o
}
ObjectFile librpc.a::pmap_getmaps.o {
	NAME Object file pmap_getmaps.o from archive librpc.a
	EXPORTS pmap_getmapsInclude pmap_getmaps
	IMPORTS .TOC. clnttcp_create xdr_void xdr_pmaplist clnt_perror
	DECLARES 
	USES 
}
Module pmap_getmaps.o {
	OBJECT += librpc.a::pmap_getmaps.o
}
ObjectFile librpc.a::pmap_getport.o {
	NAME Object file pmap_getport.o from archive librpc.a
	EXPORTS pmap_getport
	IMPORTS .TOC. clntudp_bufcreate xdr_pmap xdr_u_short taskIdSelf
	DECLARES 
	USES 
}
Module pmap_getport.o {
	OBJECT += librpc.a::pmap_getport.o
}
ObjectFile librpc.a::pmap_prot.o {
	NAME Object file pmap_prot.o from archive librpc.a
	EXPORTS xdr_pmap
	IMPORTS .TOC. xdr_u_long
	DECLARES 
	USES 
}
Module pmap_prot.o {
	OBJECT += librpc.a::pmap_prot.o
}
ObjectFile librpc.a::pmap_prot2.o {
	NAME Object file pmap_prot2.o from archive librpc.a
	EXPORTS xdr_pmaplist
	IMPORTS .TOC. xdr_bool xdr_pmap xdr_reference
	DECLARES 
	USES 
}
Module pmap_prot2.o {
	OBJECT += librpc.a::pmap_prot2.o
}
ObjectFile librpc.a::pmap_rmt.o {
	NAME Object file pmap_rmt.o from archive librpc.a
	EXPORTS pmap_rmtcall xdr_rmtcall_args xdr_rmtcallres clnt_broadcast
	IMPORTS .TOC. clntudp_create xdr_u_long xdr_reference ioctl perror bcopy inet_netof inet_makeaddr_b authunix_create_default taskIdSelf memSysPartId memPartAlloc malloc panic socket setsockopt bzero tickGet xdrmem_create xdr_callmsg sendto _null_auth select rpcErrnoGet recvfrom xdr_replymsg xdr_void close free memPartFree
	DECLARES 
	USES 
}
Module pmap_rmt.o {
	OBJECT += librpc.a::pmap_rmt.o
}
ObjectFile librpc.a::portmap.o {
	NAME Object file portmap.o from archive librpc.a
	EXPORTS portmapd reg_service reg_service_internal
	IMPORTS .TOC. rpcTaskInit memset socket perror bind taskSuspend svcudp_create printErr svctcp_create svc_register svc_run abort malloc get_myaddress clntudp_create authunix_create svc_sendreply free xdr_void xdr_pmap memSysPartId memPartAlloc memPartFree xdr_long svcerr_decode xdr_pmaplist svcerr_noproc xdr_bytes xdr_u_long xdr_opaque
	DECLARES pmaplist
	USES 
}
Module portmap.o {
	OBJECT += librpc.a::portmap.o
}
ObjectFile librpc.a::rpc_callmsg.o {
	NAME Object file rpc_callmsg.o from archive librpc.a
	EXPORTS xdr_callmsg
	IMPORTS .TOC. bcopy memSysPartId memPartAlloc xdr_opaque xdr_enum xdr_u_int xdr_u_long xdr_opaque_auth
	DECLARES 
	USES 
}
Module rpc_callmsg.o {
	OBJECT += librpc.a::rpc_callmsg.o
}
ObjectFile librpc.a::rpc_common.o {
	NAME Object file rpc_common.o from archive librpc.a
	EXPORTS 
	IMPORTS 
	DECLARES _null_auth
	USES 
}
Module rpc_common.o {
	OBJECT += librpc.a::rpc_common.o
}
ObjectFile librpc.a::rpc_prot.o {
	NAME Object file rpc_prot.o from archive librpc.a
	EXPORTS xdr_opaque_auth xdr_des_block xdr_deskey xdr_accepted_reply xdr_rejected_reply xdr_replymsg xdr_callhdr accepted rejected _seterr_reply
	IMPORTS .TOC. xdr_enum xdr_bytes xdr_opaque xdr_u_long xdr_union
	DECLARES 
	USES 
}
Module rpc_prot.o {
	OBJECT += librpc.a::rpc_prot.o
}
ObjectFile librpc.a::svc.o {
	NAME Object file svc.o from archive librpc.a
	EXPORTS xprt_register xprt_unregister svc_find svc_register svc_unregister svc_unregisterall svc_sendreply svcerr_noproc svcerr_decode svcerr_systemerr svcerr_auth svcerr_weakauth svcerr_noprog svcerr_progvers svc_getreqset svc_getreq svc_run
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc pmap_set memPartFree pmap_unset pmapUnset panic bzero _authenticate select rpcErrnoGet perror
	DECLARES 
	USES 
}
Module svc.o {
	OBJECT += librpc.a::svc.o
}
ObjectFile librpc.a::svc_auth.o {
	NAME Object file svc_auth.o from archive librpc.a
	EXPORTS _authenticate _svcauth_null
	IMPORTS .TOC. _null_auth _svcauth_unix _svcauth_short
	DECLARES 
	USES 
}
Module svc_auth.o {
	OBJECT += librpc.a::svc_auth.o
}
ObjectFile librpc.a::svc_auth_uni.o {
	NAME Object file svc_auth_uni.o from archive librpc.a
	EXPORTS _svcauth_unix _svcauth_short
	IMPORTS .TOC. xdrmem_create bcopy printf xdr_authunix_parms
	DECLARES 
	USES 
}
Module svc_auth_uni.o {
	OBJECT += librpc.a::svc_auth_uni.o
}
ObjectFile librpc.a::svc_raw.o {
	NAME Object file svc_raw.o from archive librpc.a
	EXPORTS svc_rawInclude svcraw_create
	IMPORTS .TOC. taskIdSelf memSysPartId memPartAlloc printErr bzero memPartFree xdrmem_create xdr_callmsg xdr_replymsg
	DECLARES 
	USES 
}
Module svc_raw.o {
	OBJECT += librpc.a::svc_raw.o
}
ObjectFile librpc.a::svc_simple.o {
	NAME Object file svc_simple.o from archive librpc.a
	EXPORTS svc_simpleInclude registerrpc
	IMPORTS .TOC. taskIdSelf printErr svcudp_create pmap_unset svc_register memSysPartId memPartAlloc panic xdr_void svc_sendreply memPartFree taskSuspend bzero svcerr_decode
	DECLARES 
	USES 
}
Module svc_simple.o {
	OBJECT += librpc.a::svc_simple.o
}
ObjectFile librpc.a::svc_tcp.o {
	NAME Object file svc_tcp.o from archive librpc.a
	EXPORTS svctcp_create svcfd_create
	IMPORTS .TOC. socket perror bzero bindresvport bind getsockname listen close memSysPartId memPartAlloc memPartFree printErr _null_auth xprt_register xdrrec_create accept rpcErrnoGet xprt_unregister taskIdSelf memcpy select errnoGet read write xdrrec_eof xdrrec_skiprecord xdr_callmsg xdr_replymsg xdrrec_endofrecord abort
	DECLARES 
	USES 
}
Module svc_tcp.o {
	OBJECT += librpc.a::svc_tcp.o
}
ObjectFile librpc.a::svc_udp.o {
	NAME Object file svc_udp.o from archive librpc.a
	EXPORTS svcudp_bufcreate svcudp_create svcudp_enablecache cacheSemOptions cache_fillparams
	IMPORTS .TOC. socket perror bzero bindresvport bind getsockname close memSysPartId memPartAlloc printErr memPartFree xdrmem_create xprt_register free bcopy semTake bcmp semGive recvfrom rpcErrnoGet xdr_callmsg sendto xdr_replymsg xprt_unregister semDelete semMCreate
	DECLARES 
	USES 
}
Module svc_udp.o {
	OBJECT += librpc.a::svc_udp.o
}
ObjectFile librpc.a::xdr.o {
	NAME Object file xdr.o from archive librpc.a
	EXPORTS xdr_free xdr_void xdr_long xdr_int xdr_u_long xdr_u_int xdr_u_longlong_t xdr_longlong_t xdr_short xdr_u_short xdr_char xdr_u_char xdr_bool xdr_enum xdr_opaque xdr_bytes xdr_netobj xdr_union xdr_string xdr_wrapstring
	IMPORTS .TOC. memSysPartId memPartAlloc _func_printErr memPartFree strlen
	DECLARES 
	USES 
}
Module xdr.o {
	OBJECT += librpc.a::xdr.o
}
ObjectFile librpc.a::xdr_array.o {
	NAME Object file xdr_array.o from archive librpc.a
	EXPORTS xdr_array xdr_vector
	IMPORTS .TOC. xdr_u_int _func_printErr memSysPartId memPartAlloc bzero memPartFree
	DECLARES 
	USES 
}
Module xdr_array.o {
	OBJECT += librpc.a::xdr_array.o
}
ObjectFile librpc.a::xdr_float.o {
	NAME Object file xdr_float.o from archive librpc.a
	EXPORTS xdr_floatInclude xdr_float xdr_double
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module xdr_float.o {
	OBJECT += librpc.a::xdr_float.o
}
ObjectFile librpc.a::xdr_mem.o {
	NAME Object file xdr_mem.o from archive librpc.a
	EXPORTS xdrmem_create
	IMPORTS .TOC. bcopy bcopyWords bcopyLongs
	DECLARES 
	USES 
}
Module xdr_mem.o {
	OBJECT += librpc.a::xdr_mem.o
}
ObjectFile librpc.a::xdr_rec.o {
	NAME Object file xdr_rec.o from archive librpc.a
	EXPORTS xdrrec_create xdrrec_skiprecord xdrrec_eof xdrrec_endofrecord
	IMPORTS .TOC. memSysPartId memPartAlloc memPartFree printErr bcopy lseek
	DECLARES 
	USES 
}
Module xdr_rec.o {
	OBJECT += librpc.a::xdr_rec.o
}
ObjectFile librpc.a::xdr_ref.o {
	NAME Object file xdr_ref.o from archive librpc.a
	EXPORTS xdr_reference xdr_pointer
	IMPORTS .TOC. memSysPartId memPartAlloc printErr bzero memPartFree xdr_bool
	DECLARES 
	USES 
}
Module xdr_ref.o {
	OBJECT += librpc.a::xdr_ref.o
}
ObjectFile librpc.a::rpcLib.o {
	NAME Object file rpcLib.o from archive librpc.a
	EXPORTS rpcInit portmapdPriority portmapdOptions portmapdStackSize rpcTaskInit rpcClntErrnoSet rpcErrnoGet
	IMPORTS .TOC. portmapd taskSpawn clnt_genericInclude clnt_rawInclude clnt_simpleInclude pmap_getmapsInclude svc_rawInclude svc_simpleInclude xdr_floatInclude taskDeleteHookAdd taskIdSelf memSysPartId memPartAlloc bzero close svc_unregisterall memPartFree errnoSet errnoGet
	DECLARES portmapdId
	USES 
}
Module rpcLib.o {
	OBJECT += librpc.a::rpcLib.o
}
Library librpc.a {
	MODULES librpc.a::auth_none.o librpc.a::auth_unix.o librpc.a::authunix_pro.o librpc.a::clnt_generic.o librpc.a::clnt_perror.o librpc.a::clnt_raw.o librpc.a::clnt_simple.o librpc.a::clnt_tcp.o librpc.a::clnt_udp.o librpc.a::get_myaddr.o librpc.a::pmap_clnt.o librpc.a::pmap_getmaps.o librpc.a::pmap_getport.o librpc.a::pmap_prot.o librpc.a::pmap_prot2.o librpc.a::pmap_rmt.o librpc.a::portmap.o librpc.a::rpc_callmsg.o librpc.a::rpc_common.o librpc.a::rpc_prot.o librpc.a::svc.o librpc.a::svc_auth.o librpc.a::svc_auth_uni.o librpc.a::svc_raw.o librpc.a::svc_simple.o librpc.a::svc_tcp.o librpc.a::svc_udp.o librpc.a::xdr.o librpc.a::xdr_array.o librpc.a::xdr_float.o librpc.a::xdr_mem.o librpc.a::xdr_rec.o librpc.a::xdr_ref.o librpc.a::rpcLib.o
}
