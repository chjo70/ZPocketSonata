Symbol .TOC. {
}
Symbol spinLockIsrTake {
}
Symbol spinLockIsrGive {
}
Symbol printf {
}
Symbol getoptInit {
}
Symbol getopt_r {
}
Symbol vxmux_slab_memory_pool_list {
}
Symbol vxmux_memory_pool_garbage_collect {
}
Symbol vxAtomicGet {
}
Symbol vxmux_slab_get_size {
}
Symbol vxmux_cmd_slab_init {
}
Symbol shellCmdTopicAdd {
}
Symbol shellCmdAdd {
}
Symbol l2configInit {
}
Symbol semMCreate {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol muxDevAcquire {
}
Symbol muxL2Ioctl {
}
Symbol muxDevRelease {
}
Symbol muxL2VlanShow {
}
Symbol muxL2Show {
}
Symbol bzero {
}
Symbol strcmp {
}
Symbol l2config {
}
Symbol semTake {
}
Symbol strlen {
}
Symbol malloc {
}
Symbol strcpy {
}
Symbol getOptServ {
}
Symbol free {
}
Symbol semGive {
}
Symbol bcopy {
}
Symbol endFindByName {
}
Symbol strtoul {
}
Symbol atoi {
}
Symbol muxL2LibInit {
}
Symbol errnoSet {
}
Symbol spinLockIsrInit {
}
Symbol _func_mux_l2 {
}
Symbol muxL2EndTake {
}
Symbol muxL2EndGive {
}
Symbol muxL2PortDetach {
}
Symbol muxL2PortDetachRtn {
}
Symbol muxError {
}
Symbol memSysPartId {
}
Symbol memPartAlignedAlloc {
}
Symbol memalign {
}
Symbol endEtherAddressForm {
}
Symbol end8023AddressForm {
}
Symbol muxL2PortAttach {
}
Symbol muxL2PortAltAttach {
}
Symbol m_prepend {
}
Symbol netMblkOffsetToBufCopy {
}
Symbol muxL2VlanDebug {
}
Symbol muxL2DefaultConfigParams {
}
Symbol end2LibInit {
}
Symbol mux2Receive {
}
Symbol muxEndStyles {
}
Symbol end2EtherHdrParse {
}
Symbol end2EtherIIFormLinkHdr {
}
Symbol ipcom_pkt_free {
}
Symbol end2BufferPoolConfig {
}
Symbol ipcom_conf_pkt_pool_buffer_alignment {
}
Symbol ipcom_conf_pkt_pool_buffer_extra_space {
}
Symbol _end2_linkBufPool {
}
Symbol vxmux_mux_mblk_init {
}
Symbol muxMblkToIpcomPktRx {
}
Symbol muxIpcomPktFreeMblk {
}
Symbol ipcom_pkt_stack_malloc {
}
Symbol muxMblkToIpcomPktMallocDrops {
}
Symbol vxAtomicInc {
}
Symbol netMblkClChainFree {
}
Symbol muxRestoreMblkFromIpcomPkt {
}
Symbol ipcom_pkt_stack_free {
}
Symbol muxMblkToIpcomPktTx {
}
Symbol vxmux_null_pool {
}
Symbol ipcom_atomic_get {
}
Symbol ipcom_pkt_malloc {
}
Symbol ipnet_vlan_set_tag {
}
Symbol muxIpcomPktToMblkTx {
}
Symbol ipcom_pkt_get_info_safe {
}
Symbol muxRestoreIpcomPktFromMblkTx {
}
Symbol netMblkClFree {
}
Symbol muxMblkToIpcomPktTxChainDrops {
}
Symbol muxOverEnd2Init {
}
Symbol muxBindStyles {
}
Symbol netMblkToBufCopy {
}
Symbol ipcom_pkt_create {
}
Symbol mux2LibInit {
}
Symbol mux2Bind {
}
Symbol muxBindCommon {
}
Symbol mux2Send {
}
Symbol mux2PollSend {
}
Symbol mux2PollReceive {
}
Symbol mux2OverEndInit {
}
Symbol ipcom_stack_index {
}
Symbol errnoGet {
}
Symbol mux2OverEndOutputFilterChainDrops {
}
Symbol muxTkOverEnd2Init {
}
Symbol memset {
}
Symbol _vxmux_pNullPoolFuncTbl {
}
Symbol netPoolCreate {
}
Symbol ipcom_port {
}
Symbol vxmux_null_buf_init {
}
Symbol ipcom_null_pool_create {
}
Symbol vxAtomicAdd {
}
Symbol vxAtomicSub {
}
Symbol logMsg {
}
Symbol taskSuspend {
}
Symbol vxAtomicCas {
}
Symbol vxmux_slab_init {
}
Symbol vxmux_memory_pool_new {
}
Symbol calloc {
}
Symbol vxAtomicSet {
}
Symbol vxmux_slab_cache_new {
}
Symbol vxmux_slab_add {
}
Symbol vxmux_slab_alloc_try {
}
Symbol vxmux_slab_alloc_from {
}
Symbol vxmux_slab_free {
}
Symbol vxmux_slab_get_objects_per_slab {
}
ObjectFile libCOREIP.a::vxmux_checksum.o {
	NAME Object file vxmux_checksum.o from archive libCOREIP.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module vxmux_checksum.o {
	OBJECT += libCOREIP.a::vxmux_checksum.o
}
ObjectFile libCOREIP.a::vxmux_cmd_vxslab.o {
	NAME Object file vxmux_cmd_vxslab.o from archive libCOREIP.a
	EXPORTS vxmux_cmd_slab_init
	IMPORTS .TOC. spinLockIsrTake spinLockIsrGive printf getoptInit getopt_r vxmux_slab_memory_pool_list vxmux_memory_pool_garbage_collect vxAtomicGet vxmux_slab_get_size shellCmdTopicAdd shellCmdAdd
	DECLARES 
	USES 
}
Module vxmux_cmd_vxslab.o {
	OBJECT += libCOREIP.a::vxmux_cmd_vxslab.o
}
ObjectFile libCOREIP.a::l2config.o {
	NAME Object file l2config.o from archive libCOREIP.a
	EXPORTS l2configInit l2config
	IMPORTS .TOC. semMCreate __stderr fprintf printf muxDevAcquire muxL2Ioctl muxDevRelease muxL2VlanShow muxL2Show bzero strcmp semTake strlen malloc strcpy getOptServ getoptInit getopt_r free semGive bcopy endFindByName strtoul atoi
	DECLARES 
	USES 
}
Module l2config.o {
	OBJECT += libCOREIP.a::l2config.o
}
ObjectFile libCOREIP.a::muxL2Lib.o {
	NAME Object file muxL2Lib.o from archive libCOREIP.a
	EXPORTS muxL2LibInit muxL2EndTake muxL2EndGive muxL2Ioctl muxL2PortDetach muxL2PortAttach muxL2PortAltAttach muxL2Show muxL2VlanShow muxL2VlanDebug
	IMPORTS .TOC. errnoSet spinLockIsrInit semMCreate malloc bzero _func_mux_l2 muxL2PortDetachRtn free muxDevAcquire muxDevRelease muxError memSysPartId memPartAlignedAlloc memalign spinLockIsrTake bcopy spinLockIsrGive endEtherAddressForm end8023AddressForm semTake semGive endFindByName printf m_prepend netMblkOffsetToBufCopy
	DECLARES muxL2DefaultConfigParams
	USES 
}
Module muxL2Lib.o {
	OBJECT += libCOREIP.a::muxL2Lib.o
}
ObjectFile libCOREIP.a::vxmux_end2.o {
	NAME Object file vxmux_end2.o from archive libCOREIP.a
	EXPORTS end2LibInit mux2Receive end2EtherHdrParse end2EtherIIFormLinkHdr end2BufferPoolConfig
	IMPORTS .TOC. muxEndStyles ipcom_pkt_free ipcom_conf_pkt_pool_buffer_alignment ipcom_conf_pkt_pool_buffer_extra_space
	DECLARES _end2_linkBufPool
	USES 
}
Module vxmux_end2.o {
	OBJECT += libCOREIP.a::vxmux_end2.o
}
ObjectFile libCOREIP.a::vxmux_mux_mblk.o {
	NAME Object file vxmux_mux_mblk.o from archive libCOREIP.a
	EXPORTS vxmux_mux_mblk_init muxMblkToIpcomPktRx muxIpcomPktFreeMblk muxRestoreMblkFromIpcomPkt muxMblkToIpcomPktTx muxIpcomPktToMblkTx muxRestoreIpcomPktFromMblkTx
	IMPORTS .TOC. ipcom_pkt_free ipcom_pkt_stack_malloc vxAtomicInc netMblkClChainFree ipcom_pkt_stack_free vxmux_null_pool ipcom_atomic_get ipcom_pkt_malloc ipnet_vlan_set_tag ipcom_pkt_get_info_safe netMblkClFree
	DECLARES muxMblkToIpcomPktMallocDrops muxMblkToIpcomPktTxChainDrops
	USES 
}
Module vxmux_mux_mblk.o {
	OBJECT += libCOREIP.a::vxmux_mux_mblk.o
}
ObjectFile libCOREIP.a::vxmux_mux_over_end2.o {
	NAME Object file vxmux_mux_over_end2.o from archive libCOREIP.a
	EXPORTS muxOverEnd2Init
	IMPORTS .TOC. muxEndStyles muxBindStyles muxIpcomPktToMblkTx ipcom_pkt_free ipcom_pkt_get_info_safe muxMblkToIpcomPktTx netMblkToBufCopy ipcom_pkt_create
	DECLARES 
	USES 
}
Module vxmux_mux_over_end2.o {
	OBJECT += libCOREIP.a::vxmux_mux_over_end2.o
}
ObjectFile libCOREIP.a::vxmux_mux2.o {
	NAME Object file vxmux_mux2.o from archive libCOREIP.a
	EXPORTS mux2LibInit mux2Bind mux2Send mux2PollSend mux2PollReceive
	IMPORTS .TOC. muxBindStyles muxBindCommon
	DECLARES 
	USES 
}
Module vxmux_mux2.o {
	OBJECT += libCOREIP.a::vxmux_mux2.o
}
ObjectFile libCOREIP.a::vxmux_mux2_over_end.o {
	NAME Object file vxmux_mux2_over_end.o from archive libCOREIP.a
	EXPORTS mux2OverEndInit
	IMPORTS .TOC. muxEndStyles muxBindStyles muxMblkToIpcomPktTx ipcom_pkt_free ipcom_stack_index muxMblkToIpcomPktRx ipnet_vlan_set_tag muxRestoreMblkFromIpcomPkt muxIpcomPktToMblkTx errnoGet muxRestoreIpcomPktFromMblkTx
	DECLARES mux2OverEndOutputFilterChainDrops
	USES 
}
Module vxmux_mux2_over_end.o {
	OBJECT += libCOREIP.a::vxmux_mux2_over_end.o
}
ObjectFile libCOREIP.a::vxmux_muxtk_over_end2.o {
	NAME Object file vxmux_muxtk_over_end2.o from archive libCOREIP.a
	EXPORTS muxTkOverEnd2Init
	IMPORTS .TOC. muxEndStyles muxBindStyles muxIpcomPktToMblkTx ipcom_pkt_free ipcom_pkt_get_info_safe muxMblkToIpcomPktTx netMblkClFree netMblkToBufCopy ipcom_pkt_create
	DECLARES 
	USES 
}
Module vxmux_muxtk_over_end2.o {
	OBJECT += libCOREIP.a::vxmux_muxtk_over_end2.o
}
ObjectFile libCOREIP.a::vxmux_null_buf.o {
	NAME Object file vxmux_null_buf.o from archive libCOREIP.a
	EXPORTS _vxmux_pNullPoolFuncTbl vxmux_null_buf_init
	IMPORTS .TOC. spinLockIsrInit errnoSet bzero malloc spinLockIsrTake spinLockIsrGive memalign memset strcpy netPoolCreate ipcom_port free ipcom_null_pool_create
	DECLARES vxmux_null_pool
	USES 
}
Module vxmux_null_buf.o {
	OBJECT += libCOREIP.a::vxmux_null_buf.o
}
ObjectFile libCOREIP.a::vxmux_pkt_pool_min.o {
	NAME Object file vxmux_pkt_pool_min.o from archive libCOREIP.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module vxmux_pkt_pool_min.o {
	OBJECT += libCOREIP.a::vxmux_pkt_pool_min.o
}
ObjectFile libCOREIP.a::vxmux_slab.o {
	NAME Object file vxmux_slab.o from archive libCOREIP.a
	EXPORTS vxmux_slab_get_size vxmux_memory_pool_garbage_collect vxmux_slab_init vxmux_memory_pool_new vxmux_slab_cache_new vxmux_slab_add vxmux_slab_alloc_try vxmux_slab_alloc_from vxmux_slab_free vxmux_slab_get_objects_per_slab
	IMPORTS .TOC. free vxAtomicAdd vxAtomicSub malloc logMsg taskSuspend vxAtomicGet vxAtomicCas bzero spinLockIsrTake spinLockIsrGive strlen calloc strcpy vxAtomicSet memset
	DECLARES vxmux_slab_memory_pool_list
	USES 
}
Module vxmux_slab.o {
	OBJECT += libCOREIP.a::vxmux_slab.o
}
Library libCOREIP.a {
	MODULES libCOREIP.a::vxmux_checksum.o libCOREIP.a::vxmux_cmd_vxslab.o libCOREIP.a::l2config.o libCOREIP.a::muxL2Lib.o libCOREIP.a::vxmux_end2.o libCOREIP.a::vxmux_mux_mblk.o libCOREIP.a::vxmux_mux_over_end2.o libCOREIP.a::vxmux_mux2.o libCOREIP.a::vxmux_mux2_over_end.o libCOREIP.a::vxmux_muxtk_over_end2.o libCOREIP.a::vxmux_null_buf.o libCOREIP.a::vxmux_pkt_pool_min.o libCOREIP.a::vxmux_slab.o
}
Symbol .TOC. {
}
Symbol spinLockIsrTake {
}
Symbol spinLockIsrGive {
}
Symbol printf {
}
Symbol getoptInit {
}
Symbol getopt_r {
}
Symbol vxmux_slab_memory_pool_list {
}
Symbol vxmux_memory_pool_garbage_collect {
}
Symbol vxAtomicGet {
}
Symbol vxmux_slab_get_size {
}
Symbol vxmux_cmd_slab_init {
}
Symbol shellCmdTopicAdd {
}
Symbol shellCmdAdd {
}
Symbol l2configInit {
}
Symbol semMCreate {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol muxDevAcquire {
}
Symbol muxL2Ioctl {
}
Symbol muxDevRelease {
}
Symbol muxL2VlanShow {
}
Symbol muxL2Show {
}
Symbol bzero {
}
Symbol strcmp {
}
Symbol l2config {
}
Symbol semTake {
}
Symbol strlen {
}
Symbol malloc {
}
Symbol strcpy {
}
Symbol getOptServ {
}
Symbol free {
}
Symbol semGive {
}
Symbol bcopy {
}
Symbol endFindByName {
}
Symbol strtoul {
}
Symbol atoi {
}
Symbol muxL2LibInit {
}
Symbol errnoSet {
}
Symbol spinLockIsrInit {
}
Symbol _func_mux_l2 {
}
Symbol muxL2EndTake {
}
Symbol muxL2EndGive {
}
Symbol muxL2PortDetach {
}
Symbol muxL2PortDetachRtn {
}
Symbol muxError {
}
Symbol memSysPartId {
}
Symbol memPartAlignedAlloc {
}
Symbol memalign {
}
Symbol endEtherAddressForm {
}
Symbol end8023AddressForm {
}
Symbol muxL2PortAttach {
}
Symbol muxL2PortAltAttach {
}
Symbol m_prepend {
}
Symbol netMblkOffsetToBufCopy {
}
Symbol muxL2VlanDebug {
}
Symbol muxL2DefaultConfigParams {
}
Symbol end2LibInit {
}
Symbol mux2Receive {
}
Symbol muxEndStyles {
}
Symbol end2EtherHdrParse {
}
Symbol end2EtherIIFormLinkHdr {
}
Symbol ipcom_pkt_free {
}
Symbol end2BufferPoolConfig {
}
Symbol ipcom_conf_pkt_pool_buffer_alignment {
}
Symbol ipcom_conf_pkt_pool_buffer_extra_space {
}
Symbol _end2_linkBufPool {
}
Symbol vxmux_mux_mblk_init {
}
Symbol muxMblkToIpcomPktRx {
}
Symbol muxIpcomPktFreeMblk {
}
Symbol ipcom_pkt_stack_malloc {
}
Symbol muxMblkToIpcomPktMallocDrops {
}
Symbol vxAtomicInc {
}
Symbol netMblkClChainFree {
}
Symbol muxRestoreMblkFromIpcomPkt {
}
Symbol ipcom_pkt_stack_free {
}
Symbol muxMblkToIpcomPktTx {
}
Symbol vxmux_null_pool {
}
Symbol ipcom_atomic_get {
}
Symbol ipcom_pkt_malloc {
}
Symbol ipnet_vlan_set_tag {
}
Symbol muxIpcomPktToMblkTx {
}
Symbol ipcom_pkt_get_info_safe {
}
Symbol muxRestoreIpcomPktFromMblkTx {
}
Symbol netMblkClFree {
}
Symbol muxMblkToIpcomPktTxChainDrops {
}
Symbol muxOverEnd2Init {
}
Symbol muxBindStyles {
}
Symbol netMblkToBufCopy {
}
Symbol ipcom_pkt_create {
}
Symbol mux2LibInit {
}
Symbol mux2Bind {
}
Symbol muxBindCommon {
}
Symbol mux2Send {
}
Symbol mux2PollSend {
}
Symbol mux2PollReceive {
}
Symbol mux2OverEndInit {
}
Symbol ipcom_stack_index {
}
Symbol errnoGet {
}
Symbol mux2OverEndOutputFilterChainDrops {
}
Symbol muxTkOverEnd2Init {
}
Symbol memset {
}
Symbol _vxmux_pNullPoolFuncTbl {
}
Symbol netPoolCreate {
}
Symbol ipcom_port {
}
Symbol vxmux_null_buf_init {
}
Symbol ipcom_null_pool_create {
}
Symbol vxAtomicAdd {
}
Symbol vxAtomicSub {
}
Symbol logMsg {
}
Symbol taskSuspend {
}
Symbol vxAtomicCas {
}
Symbol vxmux_slab_init {
}
Symbol vxmux_memory_pool_new {
}
Symbol calloc {
}
Symbol vxAtomicSet {
}
Symbol vxmux_slab_cache_new {
}
Symbol vxmux_slab_add {
}
Symbol vxmux_slab_alloc_try {
}
Symbol vxmux_slab_alloc_from {
}
Symbol vxmux_slab_free {
}
Symbol vxmux_slab_get_objects_per_slab {
}
ObjectFile libCOREIP.a::vxmux_checksum.o {
	NAME Object file vxmux_checksum.o from archive libCOREIP.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module vxmux_checksum.o {
	OBJECT += libCOREIP.a::vxmux_checksum.o
}
ObjectFile libCOREIP.a::vxmux_cmd_vxslab.o {
	NAME Object file vxmux_cmd_vxslab.o from archive libCOREIP.a
	EXPORTS vxmux_cmd_slab_init
	IMPORTS .TOC. spinLockIsrTake spinLockIsrGive printf getoptInit getopt_r vxmux_slab_memory_pool_list vxmux_memory_pool_garbage_collect vxAtomicGet vxmux_slab_get_size shellCmdTopicAdd shellCmdAdd
	DECLARES 
	USES 
}
Module vxmux_cmd_vxslab.o {
	OBJECT += libCOREIP.a::vxmux_cmd_vxslab.o
}
ObjectFile libCOREIP.a::l2config.o {
	NAME Object file l2config.o from archive libCOREIP.a
	EXPORTS l2configInit l2config
	IMPORTS .TOC. semMCreate __stderr fprintf printf muxDevAcquire muxL2Ioctl muxDevRelease muxL2VlanShow muxL2Show bzero strcmp semTake strlen malloc strcpy getOptServ getoptInit getopt_r free semGive bcopy endFindByName strtoul atoi
	DECLARES 
	USES 
}
Module l2config.o {
	OBJECT += libCOREIP.a::l2config.o
}
ObjectFile libCOREIP.a::muxL2Lib.o {
	NAME Object file muxL2Lib.o from archive libCOREIP.a
	EXPORTS muxL2LibInit muxL2EndTake muxL2EndGive muxL2Ioctl muxL2PortDetach muxL2PortAttach muxL2PortAltAttach muxL2Show muxL2VlanShow muxL2VlanDebug
	IMPORTS .TOC. errnoSet spinLockIsrInit semMCreate malloc bzero _func_mux_l2 muxL2PortDetachRtn free muxDevAcquire muxDevRelease muxError memSysPartId memPartAlignedAlloc memalign spinLockIsrTake bcopy spinLockIsrGive endEtherAddressForm end8023AddressForm semTake semGive endFindByName printf m_prepend netMblkOffsetToBufCopy
	DECLARES muxL2DefaultConfigParams
	USES 
}
Module muxL2Lib.o {
	OBJECT += libCOREIP.a::muxL2Lib.o
}
ObjectFile libCOREIP.a::vxmux_end2.o {
	NAME Object file vxmux_end2.o from archive libCOREIP.a
	EXPORTS end2LibInit mux2Receive end2EtherHdrParse end2EtherIIFormLinkHdr end2BufferPoolConfig
	IMPORTS .TOC. muxEndStyles ipcom_pkt_free ipcom_conf_pkt_pool_buffer_alignment ipcom_conf_pkt_pool_buffer_extra_space
	DECLARES _end2_linkBufPool
	USES 
}
Module vxmux_end2.o {
	OBJECT += libCOREIP.a::vxmux_end2.o
}
ObjectFile libCOREIP.a::vxmux_mux_mblk.o {
	NAME Object file vxmux_mux_mblk.o from archive libCOREIP.a
	EXPORTS vxmux_mux_mblk_init muxMblkToIpcomPktRx muxIpcomPktFreeMblk muxRestoreMblkFromIpcomPkt muxMblkToIpcomPktTx muxIpcomPktToMblkTx muxRestoreIpcomPktFromMblkTx
	IMPORTS .TOC. ipcom_pkt_free ipcom_pkt_stack_malloc vxAtomicInc netMblkClChainFree ipcom_pkt_stack_free vxmux_null_pool ipcom_atomic_get ipcom_pkt_malloc ipnet_vlan_set_tag ipcom_pkt_get_info_safe netMblkClFree
	DECLARES muxMblkToIpcomPktMallocDrops muxMblkToIpcomPktTxChainDrops
	USES 
}
Module vxmux_mux_mblk.o {
	OBJECT += libCOREIP.a::vxmux_mux_mblk.o
}
ObjectFile libCOREIP.a::vxmux_mux_over_end2.o {
	NAME Object file vxmux_mux_over_end2.o from archive libCOREIP.a
	EXPORTS muxOverEnd2Init
	IMPORTS .TOC. muxEndStyles muxBindStyles muxIpcomPktToMblkTx ipcom_pkt_free ipcom_pkt_get_info_safe muxMblkToIpcomPktTx netMblkToBufCopy ipcom_pkt_create
	DECLARES 
	USES 
}
Module vxmux_mux_over_end2.o {
	OBJECT += libCOREIP.a::vxmux_mux_over_end2.o
}
ObjectFile libCOREIP.a::vxmux_mux2.o {
	NAME Object file vxmux_mux2.o from archive libCOREIP.a
	EXPORTS mux2LibInit mux2Bind mux2Send mux2PollSend mux2PollReceive
	IMPORTS .TOC. muxBindStyles muxBindCommon
	DECLARES 
	USES 
}
Module vxmux_mux2.o {
	OBJECT += libCOREIP.a::vxmux_mux2.o
}
ObjectFile libCOREIP.a::vxmux_mux2_over_end.o {
	NAME Object file vxmux_mux2_over_end.o from archive libCOREIP.a
	EXPORTS mux2OverEndInit
	IMPORTS .TOC. muxEndStyles muxBindStyles muxMblkToIpcomPktTx ipcom_pkt_free ipcom_stack_index muxMblkToIpcomPktRx ipnet_vlan_set_tag muxRestoreMblkFromIpcomPkt muxIpcomPktToMblkTx errnoGet muxRestoreIpcomPktFromMblkTx
	DECLARES mux2OverEndOutputFilterChainDrops
	USES 
}
Module vxmux_mux2_over_end.o {
	OBJECT += libCOREIP.a::vxmux_mux2_over_end.o
}
ObjectFile libCOREIP.a::vxmux_muxtk_over_end2.o {
	NAME Object file vxmux_muxtk_over_end2.o from archive libCOREIP.a
	EXPORTS muxTkOverEnd2Init
	IMPORTS .TOC. muxEndStyles muxBindStyles muxIpcomPktToMblkTx ipcom_pkt_free ipcom_pkt_get_info_safe muxMblkToIpcomPktTx netMblkClFree netMblkToBufCopy ipcom_pkt_create
	DECLARES 
	USES 
}
Module vxmux_muxtk_over_end2.o {
	OBJECT += libCOREIP.a::vxmux_muxtk_over_end2.o
}
ObjectFile libCOREIP.a::vxmux_null_buf.o {
	NAME Object file vxmux_null_buf.o from archive libCOREIP.a
	EXPORTS _vxmux_pNullPoolFuncTbl vxmux_null_buf_init
	IMPORTS .TOC. spinLockIsrInit errnoSet bzero malloc spinLockIsrTake spinLockIsrGive memalign memset strcpy netPoolCreate ipcom_port free ipcom_null_pool_create
	DECLARES vxmux_null_pool
	USES 
}
Module vxmux_null_buf.o {
	OBJECT += libCOREIP.a::vxmux_null_buf.o
}
ObjectFile libCOREIP.a::vxmux_pkt_pool_min.o {
	NAME Object file vxmux_pkt_pool_min.o from archive libCOREIP.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module vxmux_pkt_pool_min.o {
	OBJECT += libCOREIP.a::vxmux_pkt_pool_min.o
}
ObjectFile libCOREIP.a::vxmux_slab.o {
	NAME Object file vxmux_slab.o from archive libCOREIP.a
	EXPORTS vxmux_slab_get_size vxmux_memory_pool_garbage_collect vxmux_slab_init vxmux_memory_pool_new vxmux_slab_cache_new vxmux_slab_add vxmux_slab_alloc_try vxmux_slab_alloc_from vxmux_slab_free vxmux_slab_get_objects_per_slab
	IMPORTS .TOC. free vxAtomicAdd vxAtomicSub malloc logMsg taskSuspend vxAtomicGet vxAtomicCas bzero spinLockIsrTake spinLockIsrGive strlen calloc strcpy vxAtomicSet memset
	DECLARES vxmux_slab_memory_pool_list
	USES 
}
Module vxmux_slab.o {
	OBJECT += libCOREIP.a::vxmux_slab.o
}
Library libCOREIP.a {
	MODULES libCOREIP.a::vxmux_checksum.o libCOREIP.a::vxmux_cmd_vxslab.o libCOREIP.a::l2config.o libCOREIP.a::muxL2Lib.o libCOREIP.a::vxmux_end2.o libCOREIP.a::vxmux_mux_mblk.o libCOREIP.a::vxmux_mux_over_end2.o libCOREIP.a::vxmux_mux2.o libCOREIP.a::vxmux_mux2_over_end.o libCOREIP.a::vxmux_muxtk_over_end2.o libCOREIP.a::vxmux_null_buf.o libCOREIP.a::vxmux_pkt_pool_min.o libCOREIP.a::vxmux_slab.o
}
Symbol .TOC. {
}
Symbol spinLockIsrTake {
}
Symbol spinLockIsrGive {
}
Symbol printf {
}
Symbol getoptInit {
}
Symbol getopt_r {
}
Symbol vxmux_slab_memory_pool_list {
}
Symbol vxmux_memory_pool_garbage_collect {
}
Symbol vxAtomicGet {
}
Symbol vxmux_slab_get_size {
}
Symbol vxmux_cmd_slab_init {
}
Symbol shellCmdTopicAdd {
}
Symbol shellCmdAdd {
}
Symbol l2configInit {
}
Symbol semMCreate {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol muxDevAcquire {
}
Symbol muxL2Ioctl {
}
Symbol muxDevRelease {
}
Symbol muxL2VlanShow {
}
Symbol muxL2Show {
}
Symbol bzero {
}
Symbol strcmp {
}
Symbol l2config {
}
Symbol semTake {
}
Symbol strlen {
}
Symbol malloc {
}
Symbol strcpy {
}
Symbol getOptServ {
}
Symbol free {
}
Symbol semGive {
}
Symbol bcopy {
}
Symbol endFindByName {
}
Symbol strtoul {
}
Symbol atoi {
}
Symbol muxL2LibInit {
}
Symbol errnoSet {
}
Symbol spinLockIsrInit {
}
Symbol _func_mux_l2 {
}
Symbol muxL2EndTake {
}
Symbol muxL2EndGive {
}
Symbol muxL2PortDetach {
}
Symbol muxL2PortDetachRtn {
}
Symbol muxError {
}
Symbol memSysPartId {
}
Symbol memPartAlignedAlloc {
}
Symbol memalign {
}
Symbol endEtherAddressForm {
}
Symbol end8023AddressForm {
}
Symbol muxL2PortAttach {
}
Symbol muxL2PortAltAttach {
}
Symbol m_prepend {
}
Symbol netMblkOffsetToBufCopy {
}
Symbol muxL2VlanDebug {
}
Symbol muxL2DefaultConfigParams {
}
Symbol end2LibInit {
}
Symbol mux2Receive {
}
Symbol muxEndStyles {
}
Symbol end2EtherHdrParse {
}
Symbol end2EtherIIFormLinkHdr {
}
Symbol ipcom_pkt_free {
}
Symbol end2BufferPoolConfig {
}
Symbol ipcom_conf_pkt_pool_buffer_alignment {
}
Symbol ipcom_conf_pkt_pool_buffer_extra_space {
}
Symbol _end2_linkBufPool {
}
Symbol vxmux_mux_mblk_init {
}
Symbol muxMblkToIpcomPktRx {
}
Symbol muxIpcomPktFreeMblk {
}
Symbol ipcom_pkt_stack_malloc {
}
Symbol muxMblkToIpcomPktMallocDrops {
}
Symbol vxAtomicInc {
}
Symbol netMblkClChainFree {
}
Symbol muxRestoreMblkFromIpcomPkt {
}
Symbol ipcom_pkt_stack_free {
}
Symbol muxMblkToIpcomPktTx {
}
Symbol vxmux_null_pool {
}
Symbol ipcom_atomic_get {
}
Symbol ipcom_pkt_malloc {
}
Symbol ipnet_vlan_set_tag {
}
Symbol muxIpcomPktToMblkTx {
}
Symbol ipcom_pkt_get_info_safe {
}
Symbol muxRestoreIpcomPktFromMblkTx {
}
Symbol netMblkClFree {
}
Symbol muxMblkToIpcomPktTxChainDrops {
}
Symbol muxOverEnd2Init {
}
Symbol muxBindStyles {
}
Symbol netMblkToBufCopy {
}
Symbol ipcom_pkt_create {
}
Symbol mux2LibInit {
}
Symbol mux2Bind {
}
Symbol muxBindCommon {
}
Symbol mux2Send {
}
Symbol mux2PollSend {
}
Symbol mux2PollReceive {
}
Symbol mux2OverEndInit {
}
Symbol ipcom_stack_index {
}
Symbol errnoGet {
}
Symbol mux2OverEndOutputFilterChainDrops {
}
Symbol muxTkOverEnd2Init {
}
Symbol memset {
}
Symbol _vxmux_pNullPoolFuncTbl {
}
Symbol netPoolCreate {
}
Symbol ipcom_port {
}
Symbol vxmux_null_buf_init {
}
Symbol ipcom_null_pool_create {
}
Symbol vxAtomicAdd {
}
Symbol vxAtomicSub {
}
Symbol logMsg {
}
Symbol taskSuspend {
}
Symbol vxAtomicCas {
}
Symbol vxmux_slab_init {
}
Symbol vxmux_memory_pool_new {
}
Symbol calloc {
}
Symbol vxAtomicSet {
}
Symbol vxmux_slab_cache_new {
}
Symbol vxmux_slab_add {
}
Symbol vxmux_slab_alloc_try {
}
Symbol vxmux_slab_alloc_from {
}
Symbol vxmux_slab_free {
}
Symbol vxmux_slab_get_objects_per_slab {
}
ObjectFile libCOREIP.a::vxmux_checksum.o {
	NAME Object file vxmux_checksum.o from archive libCOREIP.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module vxmux_checksum.o {
	OBJECT += libCOREIP.a::vxmux_checksum.o
}
ObjectFile libCOREIP.a::vxmux_cmd_vxslab.o {
	NAME Object file vxmux_cmd_vxslab.o from archive libCOREIP.a
	EXPORTS vxmux_cmd_slab_init
	IMPORTS .TOC. spinLockIsrTake spinLockIsrGive printf getoptInit getopt_r vxmux_slab_memory_pool_list vxmux_memory_pool_garbage_collect vxAtomicGet vxmux_slab_get_size shellCmdTopicAdd shellCmdAdd
	DECLARES 
	USES 
}
Module vxmux_cmd_vxslab.o {
	OBJECT += libCOREIP.a::vxmux_cmd_vxslab.o
}
ObjectFile libCOREIP.a::l2config.o {
	NAME Object file l2config.o from archive libCOREIP.a
	EXPORTS l2configInit l2config
	IMPORTS .TOC. semMCreate __stderr fprintf printf muxDevAcquire muxL2Ioctl muxDevRelease muxL2VlanShow muxL2Show bzero strcmp semTake strlen malloc strcpy getOptServ getoptInit getopt_r free semGive bcopy endFindByName strtoul atoi
	DECLARES 
	USES 
}
Module l2config.o {
	OBJECT += libCOREIP.a::l2config.o
}
ObjectFile libCOREIP.a::muxL2Lib.o {
	NAME Object file muxL2Lib.o from archive libCOREIP.a
	EXPORTS muxL2LibInit muxL2EndTake muxL2EndGive muxL2Ioctl muxL2PortDetach muxL2PortAttach muxL2PortAltAttach muxL2Show muxL2VlanShow muxL2VlanDebug
	IMPORTS .TOC. errnoSet spinLockIsrInit semMCreate malloc bzero _func_mux_l2 muxL2PortDetachRtn free muxDevAcquire muxDevRelease muxError memSysPartId memPartAlignedAlloc memalign spinLockIsrTake bcopy spinLockIsrGive endEtherAddressForm end8023AddressForm semTake semGive endFindByName printf m_prepend netMblkOffsetToBufCopy
	DECLARES muxL2DefaultConfigParams
	USES 
}
Module muxL2Lib.o {
	OBJECT += libCOREIP.a::muxL2Lib.o
}
ObjectFile libCOREIP.a::vxmux_end2.o {
	NAME Object file vxmux_end2.o from archive libCOREIP.a
	EXPORTS end2LibInit mux2Receive end2EtherHdrParse end2EtherIIFormLinkHdr end2BufferPoolConfig
	IMPORTS .TOC. muxEndStyles ipcom_pkt_free ipcom_conf_pkt_pool_buffer_alignment ipcom_conf_pkt_pool_buffer_extra_space
	DECLARES _end2_linkBufPool
	USES 
}
Module vxmux_end2.o {
	OBJECT += libCOREIP.a::vxmux_end2.o
}
ObjectFile libCOREIP.a::vxmux_mux_mblk.o {
	NAME Object file vxmux_mux_mblk.o from archive libCOREIP.a
	EXPORTS vxmux_mux_mblk_init muxMblkToIpcomPktRx muxIpcomPktFreeMblk muxRestoreMblkFromIpcomPkt muxMblkToIpcomPktTx muxIpcomPktToMblkTx muxRestoreIpcomPktFromMblkTx
	IMPORTS .TOC. ipcom_pkt_free ipcom_pkt_stack_malloc vxAtomicInc netMblkClChainFree ipcom_pkt_stack_free vxmux_null_pool ipcom_atomic_get ipcom_pkt_malloc ipnet_vlan_set_tag ipcom_pkt_get_info_safe netMblkClFree
	DECLARES muxMblkToIpcomPktMallocDrops muxMblkToIpcomPktTxChainDrops
	USES 
}
Module vxmux_mux_mblk.o {
	OBJECT += libCOREIP.a::vxmux_mux_mblk.o
}
ObjectFile libCOREIP.a::vxmux_mux_over_end2.o {
	NAME Object file vxmux_mux_over_end2.o from archive libCOREIP.a
	EXPORTS muxOverEnd2Init
	IMPORTS .TOC. muxEndStyles muxBindStyles muxIpcomPktToMblkTx ipcom_pkt_free ipcom_pkt_get_info_safe muxMblkToIpcomPktTx netMblkToBufCopy ipcom_pkt_create
	DECLARES 
	USES 
}
Module vxmux_mux_over_end2.o {
	OBJECT += libCOREIP.a::vxmux_mux_over_end2.o
}
ObjectFile libCOREIP.a::vxmux_mux2.o {
	NAME Object file vxmux_mux2.o from archive libCOREIP.a
	EXPORTS mux2LibInit mux2Bind mux2Send mux2PollSend mux2PollReceive
	IMPORTS .TOC. muxBindStyles muxBindCommon
	DECLARES 
	USES 
}
Module vxmux_mux2.o {
	OBJECT += libCOREIP.a::vxmux_mux2.o
}
ObjectFile libCOREIP.a::vxmux_mux2_over_end.o {
	NAME Object file vxmux_mux2_over_end.o from archive libCOREIP.a
	EXPORTS mux2OverEndInit
	IMPORTS .TOC. muxEndStyles muxBindStyles muxMblkToIpcomPktTx ipcom_pkt_free ipcom_stack_index muxMblkToIpcomPktRx ipnet_vlan_set_tag muxRestoreMblkFromIpcomPkt muxIpcomPktToMblkTx errnoGet muxRestoreIpcomPktFromMblkTx
	DECLARES mux2OverEndOutputFilterChainDrops
	USES 
}
Module vxmux_mux2_over_end.o {
	OBJECT += libCOREIP.a::vxmux_mux2_over_end.o
}
ObjectFile libCOREIP.a::vxmux_muxtk_over_end2.o {
	NAME Object file vxmux_muxtk_over_end2.o from archive libCOREIP.a
	EXPORTS muxTkOverEnd2Init
	IMPORTS .TOC. muxEndStyles muxBindStyles muxIpcomPktToMblkTx ipcom_pkt_free ipcom_pkt_get_info_safe muxMblkToIpcomPktTx netMblkClFree netMblkToBufCopy ipcom_pkt_create
	DECLARES 
	USES 
}
Module vxmux_muxtk_over_end2.o {
	OBJECT += libCOREIP.a::vxmux_muxtk_over_end2.o
}
ObjectFile libCOREIP.a::vxmux_null_buf.o {
	NAME Object file vxmux_null_buf.o from archive libCOREIP.a
	EXPORTS _vxmux_pNullPoolFuncTbl vxmux_null_buf_init
	IMPORTS .TOC. spinLockIsrInit errnoSet bzero malloc spinLockIsrTake spinLockIsrGive memalign memset strcpy netPoolCreate ipcom_port free ipcom_null_pool_create
	DECLARES vxmux_null_pool
	USES 
}
Module vxmux_null_buf.o {
	OBJECT += libCOREIP.a::vxmux_null_buf.o
}
ObjectFile libCOREIP.a::vxmux_pkt_pool_min.o {
	NAME Object file vxmux_pkt_pool_min.o from archive libCOREIP.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module vxmux_pkt_pool_min.o {
	OBJECT += libCOREIP.a::vxmux_pkt_pool_min.o
}
ObjectFile libCOREIP.a::vxmux_slab.o {
	NAME Object file vxmux_slab.o from archive libCOREIP.a
	EXPORTS vxmux_slab_get_size vxmux_memory_pool_garbage_collect vxmux_slab_init vxmux_memory_pool_new vxmux_slab_cache_new vxmux_slab_add vxmux_slab_alloc_try vxmux_slab_alloc_from vxmux_slab_free vxmux_slab_get_objects_per_slab
	IMPORTS .TOC. free vxAtomicAdd vxAtomicSub malloc logMsg taskSuspend vxAtomicGet vxAtomicCas bzero spinLockIsrTake spinLockIsrGive strlen calloc strcpy vxAtomicSet memset
	DECLARES vxmux_slab_memory_pool_list
	USES 
}
Module vxmux_slab.o {
	OBJECT += libCOREIP.a::vxmux_slab.o
}
Library libCOREIP.a {
	MODULES libCOREIP.a::vxmux_checksum.o libCOREIP.a::vxmux_cmd_vxslab.o libCOREIP.a::l2config.o libCOREIP.a::muxL2Lib.o libCOREIP.a::vxmux_end2.o libCOREIP.a::vxmux_mux_mblk.o libCOREIP.a::vxmux_mux_over_end2.o libCOREIP.a::vxmux_mux2.o libCOREIP.a::vxmux_mux2_over_end.o libCOREIP.a::vxmux_muxtk_over_end2.o libCOREIP.a::vxmux_null_buf.o libCOREIP.a::vxmux_pkt_pool_min.o libCOREIP.a::vxmux_slab.o
}
