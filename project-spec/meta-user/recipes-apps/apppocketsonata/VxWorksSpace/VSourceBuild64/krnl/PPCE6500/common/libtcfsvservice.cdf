Symbol init_upload_modes {
}
Symbol .TOC. {
}
Symbol loc_alloc {
}
Symbol write_json_config {
}
Symbol strlen {
}
Symbol memPartAlloc {
}
Symbol checksum {
}
Symbol read_json_config {
}
Symbol loc_free {
}
Symbol read_json_config_pm {
}
Symbol find_upload_mode {
}
Symbol strcmp {
}
Symbol last_upload_mode_id {
}
Symbol memset {
}
Symbol strncpy {
}
Symbol tcf_set_errno {
}
Symbol tcf_json_read_string {
}
Symbol tcf_json_test_char {
}
Symbol tcf_json_write_string {
}
Symbol write_stream {
}
Symbol wvEvtBufferFullNotify {
}
Symbol logging_overflow {
}
Symbol buffer_overflow_handler {
}
Symbol wvCurrentLogGet {
}
Symbol tcf_post_event {
}
Symbol _pmValidate {
}
Symbol _pmDefaultArena {
}
Symbol tcf_json_read_long {
}
Symbol wvEvtClassClear {
}
Symbol wvEvtClassSet {
}
Symbol enable_events {
}
Symbol tcf_json_read_boolean {
}
Symbol enable_stacktrace {
}
Symbol command_get_config {
}
Symbol write_stringz {
}
Symbol tcf_write_errno {
}
Symbol wvEvtClassGet {
}
Symbol tcf_json_write_long {
}
Symbol list_events {
}
Symbol is_stacktrace_enabled {
}
Symbol tcf_json_write_boolean {
}
Symbol write_stacktrace_config {
}
Symbol command_set_config {
}
Symbol command_store_config {
}
Symbol create_byte_array_output_stream {
}
Symbol read_stream {
}
Symbol get_byte_array_output_stream_data {
}
Symbol activate_logging {
}
Symbol create_byte_array_input_stream {
}
Symbol wvEvtLogStart {
}
Symbol ini_uploadmode_services {
}
Symbol new_deferred_upload {
}
Symbol new_continuous_upload {
}
Symbol new_postmortem_pm_upload {
}
Symbol _pmRegionAddr {
}
Symbol _pmFreeSpace {
}
Symbol _pmRegionOpen {
}
Symbol _pmRegionSize {
}
Symbol _pmRegionCreate {
}
Symbol _pmRegionClose {
}
Symbol wvCurrentLogListGet {
}
Symbol wvLogListDelete {
}
Symbol memPartDelete {
}
Symbol memPartCreate {
}
Symbol wvPartitionSet {
}
Symbol wvLogListCreate {
}
Symbol rBuffCreate {
}
Symbol wvLogCountGet {
}
Symbol wvMaximumLogs {
}
Symbol wvLogCreate {
}
Symbol rBuffLibInit {
}
Symbol tcf_json_read_uint64 {
}
Symbol tcf_json_write_uint64 {
}
Symbol tcf_json_read_struct {
}
Symbol _pmInit {
}
Symbol tcf_add_command_handler {
}
Symbol wvFileUploadPathClose {
}
Symbol wvFileUploadPathCreate {
}
Symbol wvUploadStart {
}
Symbol create_file_upload_session {
}
Symbol is_valid_wv_log {
}
Symbol pthread_create {
}
Symbol _wvTipcConfigure {
}
Symbol _wvTipcInit {
}
Symbol newTipcEvt {
}
Symbol virtual_stream_is_empty {
}
Symbol pthread_mutex_lock {
}
Symbol pthread_cond_signal {
}
Symbol pthread_mutex_unlock {
}
Symbol snprintf {
}
Symbol virtual_stream_create {
}
Symbol virtual_stream_add_data {
}
Symbol sync_event {
}
Symbol pthread_cond_wait {
}
Symbol virtual_stream_delete {
}
Symbol create_tcf_upload_session {
}
Symbol pthread_mutex_init {
}
Symbol check_error {
}
Symbol pthread_cond_init {
}
Symbol enable_usb_event {
}
Symbol wvUsbInst {
}
Symbol newUsbHostEvt {
}
Symbol _usb2WvFilter {
}
Symbol newUsbPeriEvt {
}
Symbol _usbPeriphWvFilter {
}
Symbol memSysPartId {
}
Symbol rBuffDestroy {
}
Symbol logging_started {
}
Symbol upload_done {
}
Symbol logging_stopped {
}
Symbol new_postmortem_upload {
}
Symbol pWvNetEvtMap {
}
Symbol _wvNetDConfigure {
}
Symbol newNetEvt {
}
Symbol wvObjInst {
}
Symbol _wvObjStacktrace {
}
Symbol write_objects {
}
Symbol tcf_json_read_array {
}
Symbol newRtpEvt {
}
Symbol objClassIdGet {
}
Symbol objVerify {
}
Symbol objNamePtrGet {
}
Symbol objEach {
}
Symbol wvLogFirstGet {
}
Symbol wvLogNextGet {
}
Symbol wvLogListValidate {
}
Symbol wvCurrentLogListSet {
}
Symbol wvLogDelete {
}
Symbol command_delete_logs {
}
Symbol command_list_logs {
}
Symbol command_start_logging {
}
Symbol command_attach_logging {
}
Symbol command_is_logging {
}
Symbol evtAction {
}
Symbol command_stop_logging {
}
Symbol wvEvtLogStop {
}
Symbol wvUploadStop {
}
Symbol ini_upload_services {
}
Symbol _wvCallStackSetLevel {
}
Symbol newSigEvt {
}
Symbol _sigEnabled {
}
Symbol wvSigInst {
}
Symbol newEvtEvt {
}
Symbol _evtEnabled {
}
Symbol wvEventInst {
}
Symbol newSalEvt {
}
Symbol _salEnabled {
}
Symbol wvSalInst {
}
Symbol newEDREvt {
}
Symbol _edrEnabled {
}
Symbol wvEdrInst {
}
Symbol newMscEvt {
}
Symbol _mscEnabled {
}
Symbol wvMemScopeInst {
}
Symbol newPmnEvt {
}
Symbol wvPowerInst {
}
Symbol register_events {
}
Symbol newTaskLibEvt {
}
Symbol newSempLibEvt {
}
Symbol newMsgQLibEvt {
}
Symbol newWdLibEvt {
}
Symbol newMemLibEvt {
}
Symbol newIoLibEvt {
}
Symbol newIsrLibEvt {
}
Symbol newSdLibEvt {
}
Symbol ini_sysviewer_service {
}
Symbol command_get_buf_stat {
}
Symbol tcf_json_write_int64 {
}
Symbol _func_symFind {
}
Symbol sysSymTbl {
}
Symbol is_symbol_api_enabled {
}
Symbol init_symbols {
}
Symbol _edrPmArena {
}
Symbol _wvCallStackSetEvent {
}
Symbol _wvCallStackDepthSet {
}
Symbol _wvTaskCallStackSet {
}
Symbol _wvTaskCallStackClear {
}
Symbol _wvCallStackFilterSet {
}
Symbol tcf_json_read_int64 {
}
ObjectFile libtcfsvservice.a::uploadmode.o {
	NAME Object file uploadmode.o from archive libtcfsvservice.a
	EXPORTS init_upload_modes write_json_config read_json_config read_json_config_pm find_upload_mode last_upload_mode_id buffer_overflow_handler command_get_config command_set_config command_store_config activate_logging ini_uploadmode_services
	IMPORTS .TOC. loc_alloc strlen memPartAlloc checksum loc_free strcmp memset strncpy tcf_set_errno tcf_json_read_string tcf_json_test_char tcf_json_write_string write_stream wvEvtBufferFullNotify logging_overflow wvCurrentLogGet tcf_post_event _pmValidate _pmDefaultArena tcf_json_read_long wvEvtClassClear wvEvtClassSet enable_events tcf_json_read_boolean enable_stacktrace write_stringz tcf_write_errno wvEvtClassGet tcf_json_write_long list_events is_stacktrace_enabled tcf_json_write_boolean write_stacktrace_config create_byte_array_output_stream read_stream get_byte_array_output_stream_data create_byte_array_input_stream wvEvtLogStart new_deferred_upload new_continuous_upload new_postmortem_pm_upload
	DECLARES 
	USES 
}
Module uploadmode.o {
	OBJECT += libtcfsvservice.a::uploadmode.o
}
ObjectFile libtcfsvservice.a::um_postmortem_pm.o {
	NAME Object file um_postmortem_pm.o from archive libtcfsvservice.a
	EXPORTS new_postmortem_pm_upload
	IMPORTS .TOC. _pmDefaultArena _pmRegionAddr _pmFreeSpace _pmRegionOpen _pmRegionSize _pmRegionCreate _pmRegionClose wvCurrentLogListGet wvLogListDelete memPartDelete memPartCreate write_json_config read_json_config_pm wvPartitionSet wvLogListCreate buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffLibInit tcf_set_errno strcmp tcf_json_read_long tcf_json_read_uint64 tcf_json_read_boolean tcf_json_write_string write_stream tcf_json_write_uint64 tcf_json_write_long tcf_json_write_boolean tcf_json_read_struct find_upload_mode write_stringz tcf_write_errno _pmInit tcf_json_test_char tcf_add_command_handler loc_alloc
	DECLARES 
	USES 
}
Module um_postmortem_pm.o {
	OBJECT += libtcfsvservice.a::um_postmortem_pm.o
}
ObjectFile libtcfsvservice.a::sv_upload_file.o {
	NAME Object file sv_upload_file.o from archive libtcfsvservice.a
	EXPORTS create_file_upload_session
	IMPORTS .TOC. wvFileUploadPathClose strcmp tcf_json_read_boolean tcf_json_read_string wvFileUploadPathCreate wvUploadStart loc_free loc_alloc tcf_json_read_struct is_valid_wv_log pthread_create
	DECLARES 
	USES 
}
Module sv_upload_file.o {
	OBJECT += libtcfsvservice.a::sv_upload_file.o
}
ObjectFile libtcfsvservice.a::tipc_events.o {
	NAME Object file tipc_events.o from archive libtcfsvservice.a
	EXPORTS newTipcEvt
	IMPORTS .TOC. _wvTipcConfigure _wvTipcInit write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_long strcmp tcf_json_read_boolean tcf_json_read_long tcf_json_read_struct loc_alloc
	DECLARES 
	USES 
}
Module tipc_events.o {
	OBJECT += libtcfsvservice.a::tipc_events.o
}
ObjectFile libtcfsvservice.a::sv_upload_tcf.o {
	NAME Object file sv_upload_tcf.o from archive libtcfsvservice.a
	EXPORTS create_tcf_upload_session
	IMPORTS .TOC. virtual_stream_is_empty pthread_mutex_lock pthread_cond_signal pthread_mutex_unlock memset snprintf virtual_stream_create virtual_stream_add_data sync_event pthread_cond_wait virtual_stream_delete loc_free strcmp tcf_json_read_boolean tcf_json_read_long tcf_json_read_struct is_valid_wv_log loc_alloc pthread_mutex_init check_error pthread_cond_init wvUploadStart
	DECLARES 
	USES 
}
Module sv_upload_tcf.o {
	OBJECT += libtcfsvservice.a::sv_upload_tcf.o
}
ObjectFile libtcfsvservice.a::usb_events.o {
	NAME Object file usb_events.o from archive libtcfsvservice.a
	EXPORTS enable_usb_event newUsbHostEvt newUsbPeriEvt
	IMPORTS .TOC. write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_uint64 strcmp tcf_json_read_boolean tcf_json_read_uint64 tcf_json_read_struct loc_alloc wvUsbInst _usb2WvFilter _usbPeriphWvFilter
	DECLARES 
	USES 
}
Module usb_events.o {
	OBJECT += libtcfsvservice.a::usb_events.o
}
ObjectFile libtcfsvservice.a::um_deferred.o {
	NAME Object file um_deferred.o from archive libtcfsvservice.a
	EXPORTS new_deferred_upload
	IMPORTS .TOC. memSysPartId buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffDestroy rBuffLibInit tcf_set_errno wvCurrentLogListGet wvLogListCreate strcmp tcf_json_read_long tcf_json_read_boolean write_stream tcf_json_write_string tcf_json_write_long tcf_json_write_boolean tcf_json_read_struct last_upload_mode_id wvLogListDelete wvPartitionSet wvCurrentLogGet loc_alloc
	DECLARES 
	USES 
}
Module um_deferred.o {
	OBJECT += libtcfsvservice.a::um_deferred.o
}
ObjectFile libtcfsvservice.a::logging_events.o {
	NAME Object file logging_events.o from archive libtcfsvservice.a
	EXPORTS logging_overflow logging_started upload_done logging_stopped
	IMPORTS .TOC. loc_alloc loc_free write_stringz tcf_json_write_uint64 write_stream
	DECLARES 
	USES 
}
Module logging_events.o {
	OBJECT += libtcfsvservice.a::logging_events.o
}
ObjectFile libtcfsvservice.a::um_postmortem.o {
	NAME Object file um_postmortem.o from archive libtcfsvservice.a
	EXPORTS new_postmortem_upload
	IMPORTS .TOC. memPartCreate wvPartitionSet wvCurrentLogListGet wvLogListCreate buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffLibInit tcf_set_errno strcmp tcf_json_read_uint64 tcf_json_read_boolean write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_uint64 tcf_json_read_struct wvLogListDelete memPartDelete loc_alloc
	DECLARES 
	USES 
}
Module um_postmortem.o {
	OBJECT += libtcfsvservice.a::um_postmortem.o
}
ObjectFile libtcfsvservice.a::net_events.o {
	NAME Object file net_events.o from archive libtcfsvservice.a
	EXPORTS newNetEvt
	IMPORTS .TOC. pWvNetEvtMap _wvNetDConfigure write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_long strcmp tcf_json_read_boolean tcf_json_read_long tcf_json_read_struct loc_alloc
	DECLARES 
	USES 
}
Module net_events.o {
	OBJECT += libtcfsvservice.a::net_events.o
}
ObjectFile libtcfsvservice.a::rtp_events.o {
	NAME Object file rtp_events.o from archive libtcfsvservice.a
	EXPORTS newRtpEvt
	IMPORTS .TOC. write_stream tcf_json_write_string wvObjInst tcf_json_write_boolean _wvObjStacktrace write_objects strcmp tcf_json_read_uint64 tcf_json_read_boolean tcf_json_read_struct tcf_json_read_array loc_alloc
	DECLARES 
	USES 
}
Module rtp_events.o {
	OBJECT += libtcfsvservice.a::rtp_events.o
}
ObjectFile libtcfsvservice.a::sv_objinfo.o {
	NAME Object file sv_objinfo.o from archive libtcfsvservice.a
	EXPORTS write_objects
	IMPORTS .TOC. objClassIdGet objVerify objNamePtrGet write_stream tcf_json_write_string tcf_json_write_uint64 objEach
	DECLARES 
	USES 
}
Module sv_objinfo.o {
	OBJECT += libtcfsvservice.a::sv_objinfo.o
}
ObjectFile libtcfsvservice.a::logging.o {
	NAME Object file logging.o from archive libtcfsvservice.a
	EXPORTS is_valid_wv_log command_delete_logs command_list_logs command_start_logging command_attach_logging command_is_logging command_stop_logging
	IMPORTS .TOC. write_stream tcf_json_write_string tcf_json_write_long tcf_json_write_uint64 wvLogCountGet wvLogFirstGet wvLogNextGet find_upload_mode wvLogListValidate wvCurrentLogListGet wvCurrentLogListSet strcmp tcf_json_read_long tcf_json_read_uint64 tcf_json_read_struct wvLogDelete wvLogListDelete tcf_json_read_array tcf_json_test_char write_stringz tcf_write_errno last_upload_mode_id wvEvtLogStart wvCurrentLogGet tcf_set_errno logging_started evtAction tcf_json_write_boolean wvEvtLogStop logging_stopped
	DECLARES 
	USES 
}
Module logging.o {
	OBJECT += libtcfsvservice.a::logging.o
}
ObjectFile libtcfsvservice.a::sv_upload.o {
	NAME Object file sv_upload.o from archive libtcfsvservice.a
	EXPORTS sync_event ini_upload_services
	IMPORTS .TOC. pthread_mutex_lock pthread_cond_signal pthread_mutex_unlock pthread_mutex_init check_error pthread_cond_init tcf_post_event pthread_cond_wait upload_done wvUploadStop loc_free tcf_json_read_string strcmp tcf_json_read_uint64 tcf_json_test_char tcf_json_read_array write_stringz tcf_write_errno tcf_json_write_uint64 write_stream pthread_create tcf_set_errno tcf_add_command_handler create_tcf_upload_session create_file_upload_session
	DECLARES 
	USES 
}
Module sv_upload.o {
	OBJECT += libtcfsvservice.a::sv_upload.o
}
ObjectFile libtcfsvservice.a::lib_events.o {
	NAME Object file lib_events.o from archive libtcfsvservice.a
	EXPORTS newSigEvt newEvtEvt newSalEvt newEDREvt newMscEvt newPmnEvt
	IMPORTS .TOC. _wvCallStackSetLevel write_stream tcf_json_write_string tcf_json_write_boolean strcmp tcf_json_read_boolean tcf_json_read_struct loc_alloc _sigEnabled wvSigInst _evtEnabled wvEventInst _salEnabled wvSalInst _edrEnabled wvEdrInst _mscEnabled wvMemScopeInst wvPowerInst
	DECLARES 
	USES 
}
Module lib_events.o {
	OBJECT += libtcfsvservice.a::lib_events.o
}
ObjectFile libtcfsvservice.a::sv_events.o {
	NAME Object file sv_events.o from archive libtcfsvservice.a
	EXPORTS register_events list_events enable_events
	IMPORTS .TOC. strcmp loc_alloc loc_free write_stream tcf_json_write_string tcf_json_write_boolean memset tcf_json_read_string tcf_json_read_array tcf_json_test_char enable_usb_event newTaskLibEvt newSempLibEvt newMsgQLibEvt newWdLibEvt newMemLibEvt newIoLibEvt newIsrLibEvt newSigEvt newEvtEvt newRtpEvt newSalEvt newEDREvt newSdLibEvt newUsbHostEvt newUsbPeriEvt newNetEvt newTipcEvt newMscEvt newPmnEvt
	DECLARES 
	USES 
}
Module sv_events.o {
	OBJECT += libtcfsvservice.a::sv_events.o
}
ObjectFile libtcfsvservice.a::um_continuous.o {
	NAME Object file um_continuous.o from archive libtcfsvservice.a
	EXPORTS new_continuous_upload
	IMPORTS .TOC. memSysPartId buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffLibInit tcf_set_errno wvCurrentLogListGet wvLogListCreate strcmp tcf_json_read_long write_stream tcf_json_write_string tcf_json_write_long tcf_json_read_struct last_upload_mode_id wvLogListDelete wvPartitionSet loc_alloc
	DECLARES 
	USES 
}
Module um_continuous.o {
	OBJECT += libtcfsvservice.a::um_continuous.o
}
ObjectFile libtcfsvservice.a::sysviewer.o {
	NAME Object file sysviewer.o from archive libtcfsvservice.a
	EXPORTS ini_sysviewer_service
	IMPORTS .TOC. tcf_json_test_char write_stringz tcf_write_errno write_stream tcf_json_write_string tcf_json_write_long register_events init_upload_modes tcf_add_command_handler command_list_logs command_delete_logs command_start_logging command_stop_logging command_attach_logging command_is_logging command_get_buf_stat command_get_config command_set_config command_store_config ini_uploadmode_services ini_upload_services activate_logging
	DECLARES 
	USES 
}
Module sysviewer.o {
	OBJECT += libtcfsvservice.a::sysviewer.o
}
ObjectFile libtcfsvservice.a::buf_stat.o {
	NAME Object file buf_stat.o from archive libtcfsvservice.a
	EXPORTS command_get_buf_stat
	IMPORTS .TOC. write_stream tcf_json_write_string tcf_json_write_uint64 tcf_json_write_int64 tcf_json_read_uint64 tcf_json_test_char is_valid_wv_log write_stringz tcf_write_errno
	DECLARES 
	USES 
}
Module buf_stat.o {
	OBJECT += libtcfsvservice.a::buf_stat.o
}
ObjectFile libtcfsvservice.a::sv_symbol.o {
	NAME Object file sv_symbol.o from archive libtcfsvservice.a
	EXPORTS is_symbol_api_enabled init_symbols _pmDefaultArena _pmRegionAddr _pmFreeSpace _pmRegionOpen _pmRegionSize _pmRegionCreate _pmRegionClose _pmValidate _pmInit _edrPmArena _wvNetDConfigure _wvCallStackSetLevel _wvCallStackSetEvent _wvCallStackDepthSet _wvTaskCallStackSet _wvTaskCallStackClear _wvCallStackFilterSet _wvObjStacktrace _wvTipcConfigure _wvTipcInit _sigEnabled _evtEnabled _salEnabled _edrEnabled _mscEnabled _usb2WvFilter _usbPeriphWvFilter
	IMPORTS .TOC. _func_symFind sysSymTbl
	DECLARES 
	USES 
}
Module sv_symbol.o {
	OBJECT += libtcfsvservice.a::sv_symbol.o
}
ObjectFile libtcfsvservice.a::wol_events.o {
	NAME Object file wol_events.o from archive libtcfsvservice.a
	EXPORTS newTaskLibEvt newSempLibEvt newMsgQLibEvt newWdLibEvt newMemLibEvt newIoLibEvt newIsrLibEvt newSdLibEvt
	IMPORTS .TOC. _wvObjStacktrace wvObjInst write_stream tcf_json_write_string tcf_json_write_boolean strcmp tcf_json_read_boolean tcf_json_read_struct loc_alloc
	DECLARES 
	USES 
}
Module wol_events.o {
	OBJECT += libtcfsvservice.a::wol_events.o
}
ObjectFile libtcfsvservice.a::stack_trace.o {
	NAME Object file stack_trace.o from archive libtcfsvservice.a
	EXPORTS is_stacktrace_enabled enable_stacktrace write_stacktrace_config
	IMPORTS .TOC. loc_alloc loc_free tcf_json_read_uint64 strcmp tcf_json_read_string tcf_json_read_int64 tcf_json_read_boolean tcf_json_read_array _wvCallStackDepthSet _wvCallStackSetLevel _wvCallStackSetEvent _wvTaskCallStackClear _wvCallStackFilterSet _wvTaskCallStackSet wvEvtClassGet tcf_json_read_struct tcf_json_test_char write_stream tcf_json_write_string tcf_json_write_int64 tcf_json_write_boolean tcf_json_write_uint64
	DECLARES 
	USES 
}
Module stack_trace.o {
	OBJECT += libtcfsvservice.a::stack_trace.o
}
Library libtcfsvservice.a {
	MODULES libtcfsvservice.a::uploadmode.o libtcfsvservice.a::um_postmortem_pm.o libtcfsvservice.a::sv_upload_file.o libtcfsvservice.a::tipc_events.o libtcfsvservice.a::sv_upload_tcf.o libtcfsvservice.a::usb_events.o libtcfsvservice.a::um_deferred.o libtcfsvservice.a::logging_events.o libtcfsvservice.a::um_postmortem.o libtcfsvservice.a::net_events.o libtcfsvservice.a::rtp_events.o libtcfsvservice.a::sv_objinfo.o libtcfsvservice.a::logging.o libtcfsvservice.a::sv_upload.o libtcfsvservice.a::lib_events.o libtcfsvservice.a::sv_events.o libtcfsvservice.a::um_continuous.o libtcfsvservice.a::sysviewer.o libtcfsvservice.a::buf_stat.o libtcfsvservice.a::sv_symbol.o libtcfsvservice.a::wol_events.o libtcfsvservice.a::stack_trace.o
}
Symbol init_upload_modes {
}
Symbol .TOC. {
}
Symbol loc_alloc {
}
Symbol write_json_config {
}
Symbol strlen {
}
Symbol memPartAlloc {
}
Symbol checksum {
}
Symbol read_json_config {
}
Symbol loc_free {
}
Symbol read_json_config_pm {
}
Symbol find_upload_mode {
}
Symbol strcmp {
}
Symbol last_upload_mode_id {
}
Symbol memset {
}
Symbol strncpy {
}
Symbol tcf_set_errno {
}
Symbol tcf_json_read_string {
}
Symbol tcf_json_test_char {
}
Symbol tcf_json_write_string {
}
Symbol write_stream {
}
Symbol wvEvtBufferFullNotify {
}
Symbol logging_overflow {
}
Symbol buffer_overflow_handler {
}
Symbol wvCurrentLogGet {
}
Symbol tcf_post_event {
}
Symbol _pmValidate {
}
Symbol _pmDefaultArena {
}
Symbol tcf_json_read_long {
}
Symbol wvEvtClassClear {
}
Symbol wvEvtClassSet {
}
Symbol enable_events {
}
Symbol tcf_json_read_boolean {
}
Symbol enable_stacktrace {
}
Symbol command_get_config {
}
Symbol write_stringz {
}
Symbol tcf_write_errno {
}
Symbol wvEvtClassGet {
}
Symbol tcf_json_write_long {
}
Symbol list_events {
}
Symbol is_stacktrace_enabled {
}
Symbol tcf_json_write_boolean {
}
Symbol write_stacktrace_config {
}
Symbol command_set_config {
}
Symbol command_store_config {
}
Symbol create_byte_array_output_stream {
}
Symbol read_stream {
}
Symbol get_byte_array_output_stream_data {
}
Symbol activate_logging {
}
Symbol create_byte_array_input_stream {
}
Symbol wvEvtLogStart {
}
Symbol ini_uploadmode_services {
}
Symbol new_deferred_upload {
}
Symbol new_continuous_upload {
}
Symbol new_postmortem_pm_upload {
}
Symbol _pmRegionAddr {
}
Symbol _pmFreeSpace {
}
Symbol _pmRegionOpen {
}
Symbol _pmRegionSize {
}
Symbol _pmRegionCreate {
}
Symbol _pmRegionClose {
}
Symbol wvCurrentLogListGet {
}
Symbol wvLogListDelete {
}
Symbol memPartDelete {
}
Symbol memPartCreate {
}
Symbol wvPartitionSet {
}
Symbol wvLogListCreate {
}
Symbol rBuffCreate {
}
Symbol wvLogCountGet {
}
Symbol wvMaximumLogs {
}
Symbol wvLogCreate {
}
Symbol rBuffLibInit {
}
Symbol tcf_json_read_uint64 {
}
Symbol tcf_json_write_uint64 {
}
Symbol tcf_json_read_struct {
}
Symbol _pmInit {
}
Symbol tcf_add_command_handler {
}
Symbol wvFileUploadPathClose {
}
Symbol wvFileUploadPathCreate {
}
Symbol wvUploadStart {
}
Symbol create_file_upload_session {
}
Symbol is_valid_wv_log {
}
Symbol pthread_create {
}
Symbol _wvTipcConfigure {
}
Symbol _wvTipcInit {
}
Symbol newTipcEvt {
}
Symbol virtual_stream_is_empty {
}
Symbol pthread_mutex_lock {
}
Symbol pthread_cond_signal {
}
Symbol pthread_mutex_unlock {
}
Symbol snprintf {
}
Symbol virtual_stream_create {
}
Symbol virtual_stream_add_data {
}
Symbol sync_event {
}
Symbol pthread_cond_wait {
}
Symbol virtual_stream_delete {
}
Symbol create_tcf_upload_session {
}
Symbol pthread_mutex_init {
}
Symbol check_error {
}
Symbol pthread_cond_init {
}
Symbol enable_usb_event {
}
Symbol wvUsbInst {
}
Symbol newUsbHostEvt {
}
Symbol _usb2WvFilter {
}
Symbol newUsbPeriEvt {
}
Symbol _usbPeriphWvFilter {
}
Symbol memSysPartId {
}
Symbol rBuffDestroy {
}
Symbol logging_started {
}
Symbol upload_done {
}
Symbol logging_stopped {
}
Symbol new_postmortem_upload {
}
Symbol pWvNetEvtMap {
}
Symbol _wvNetDConfigure {
}
Symbol newNetEvt {
}
Symbol wvObjInst {
}
Symbol _wvObjStacktrace {
}
Symbol write_objects {
}
Symbol tcf_json_read_array {
}
Symbol newRtpEvt {
}
Symbol objClassIdGet {
}
Symbol objVerify {
}
Symbol objNamePtrGet {
}
Symbol objEach {
}
Symbol wvLogFirstGet {
}
Symbol wvLogNextGet {
}
Symbol wvLogListValidate {
}
Symbol wvCurrentLogListSet {
}
Symbol wvLogDelete {
}
Symbol command_delete_logs {
}
Symbol command_list_logs {
}
Symbol command_start_logging {
}
Symbol command_attach_logging {
}
Symbol command_is_logging {
}
Symbol evtAction {
}
Symbol command_stop_logging {
}
Symbol wvEvtLogStop {
}
Symbol wvUploadStop {
}
Symbol ini_upload_services {
}
Symbol _wvCallStackSetLevel {
}
Symbol newSigEvt {
}
Symbol _sigEnabled {
}
Symbol wvSigInst {
}
Symbol newEvtEvt {
}
Symbol _evtEnabled {
}
Symbol wvEventInst {
}
Symbol newSalEvt {
}
Symbol _salEnabled {
}
Symbol wvSalInst {
}
Symbol newEDREvt {
}
Symbol _edrEnabled {
}
Symbol wvEdrInst {
}
Symbol newMscEvt {
}
Symbol _mscEnabled {
}
Symbol wvMemScopeInst {
}
Symbol newPmnEvt {
}
Symbol wvPowerInst {
}
Symbol register_events {
}
Symbol newTaskLibEvt {
}
Symbol newSempLibEvt {
}
Symbol newMsgQLibEvt {
}
Symbol newWdLibEvt {
}
Symbol newMemLibEvt {
}
Symbol newIoLibEvt {
}
Symbol newIsrLibEvt {
}
Symbol newSdLibEvt {
}
Symbol ini_sysviewer_service {
}
Symbol command_get_buf_stat {
}
Symbol tcf_json_write_int64 {
}
Symbol _func_symFind {
}
Symbol sysSymTbl {
}
Symbol is_symbol_api_enabled {
}
Symbol init_symbols {
}
Symbol _edrPmArena {
}
Symbol _wvCallStackSetEvent {
}
Symbol _wvCallStackDepthSet {
}
Symbol _wvTaskCallStackSet {
}
Symbol _wvTaskCallStackClear {
}
Symbol _wvCallStackFilterSet {
}
Symbol tcf_json_read_int64 {
}
ObjectFile libtcfsvservice.a::uploadmode.o {
	NAME Object file uploadmode.o from archive libtcfsvservice.a
	EXPORTS init_upload_modes write_json_config read_json_config read_json_config_pm find_upload_mode last_upload_mode_id buffer_overflow_handler command_get_config command_set_config command_store_config activate_logging ini_uploadmode_services
	IMPORTS .TOC. loc_alloc strlen memPartAlloc checksum loc_free strcmp memset strncpy tcf_set_errno tcf_json_read_string tcf_json_test_char tcf_json_write_string write_stream wvEvtBufferFullNotify logging_overflow wvCurrentLogGet tcf_post_event _pmValidate _pmDefaultArena tcf_json_read_long wvEvtClassClear wvEvtClassSet enable_events tcf_json_read_boolean enable_stacktrace write_stringz tcf_write_errno wvEvtClassGet tcf_json_write_long list_events is_stacktrace_enabled tcf_json_write_boolean write_stacktrace_config create_byte_array_output_stream read_stream get_byte_array_output_stream_data create_byte_array_input_stream wvEvtLogStart new_deferred_upload new_continuous_upload new_postmortem_pm_upload
	DECLARES 
	USES 
}
Module uploadmode.o {
	OBJECT += libtcfsvservice.a::uploadmode.o
}
ObjectFile libtcfsvservice.a::um_postmortem_pm.o {
	NAME Object file um_postmortem_pm.o from archive libtcfsvservice.a
	EXPORTS new_postmortem_pm_upload
	IMPORTS .TOC. _pmDefaultArena _pmRegionAddr _pmFreeSpace _pmRegionOpen _pmRegionSize _pmRegionCreate _pmRegionClose wvCurrentLogListGet wvLogListDelete memPartDelete memPartCreate write_json_config read_json_config_pm wvPartitionSet wvLogListCreate buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffLibInit tcf_set_errno strcmp tcf_json_read_long tcf_json_read_uint64 tcf_json_read_boolean tcf_json_write_string write_stream tcf_json_write_uint64 tcf_json_write_long tcf_json_write_boolean tcf_json_read_struct find_upload_mode write_stringz tcf_write_errno _pmInit tcf_json_test_char tcf_add_command_handler loc_alloc
	DECLARES 
	USES 
}
Module um_postmortem_pm.o {
	OBJECT += libtcfsvservice.a::um_postmortem_pm.o
}
ObjectFile libtcfsvservice.a::sv_upload_file.o {
	NAME Object file sv_upload_file.o from archive libtcfsvservice.a
	EXPORTS create_file_upload_session
	IMPORTS .TOC. wvFileUploadPathClose strcmp tcf_json_read_boolean tcf_json_read_string wvFileUploadPathCreate wvUploadStart loc_free loc_alloc tcf_json_read_struct is_valid_wv_log pthread_create
	DECLARES 
	USES 
}
Module sv_upload_file.o {
	OBJECT += libtcfsvservice.a::sv_upload_file.o
}
ObjectFile libtcfsvservice.a::tipc_events.o {
	NAME Object file tipc_events.o from archive libtcfsvservice.a
	EXPORTS newTipcEvt
	IMPORTS .TOC. _wvTipcConfigure _wvTipcInit write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_long strcmp tcf_json_read_boolean tcf_json_read_long tcf_json_read_struct loc_alloc
	DECLARES 
	USES 
}
Module tipc_events.o {
	OBJECT += libtcfsvservice.a::tipc_events.o
}
ObjectFile libtcfsvservice.a::sv_upload_tcf.o {
	NAME Object file sv_upload_tcf.o from archive libtcfsvservice.a
	EXPORTS create_tcf_upload_session
	IMPORTS .TOC. virtual_stream_is_empty pthread_mutex_lock pthread_cond_signal pthread_mutex_unlock memset snprintf virtual_stream_create virtual_stream_add_data sync_event pthread_cond_wait virtual_stream_delete loc_free strcmp tcf_json_read_boolean tcf_json_read_long tcf_json_read_struct is_valid_wv_log loc_alloc pthread_mutex_init check_error pthread_cond_init wvUploadStart
	DECLARES 
	USES 
}
Module sv_upload_tcf.o {
	OBJECT += libtcfsvservice.a::sv_upload_tcf.o
}
ObjectFile libtcfsvservice.a::usb_events.o {
	NAME Object file usb_events.o from archive libtcfsvservice.a
	EXPORTS enable_usb_event newUsbHostEvt newUsbPeriEvt
	IMPORTS .TOC. write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_uint64 strcmp tcf_json_read_boolean tcf_json_read_uint64 tcf_json_read_struct loc_alloc wvUsbInst _usb2WvFilter _usbPeriphWvFilter
	DECLARES 
	USES 
}
Module usb_events.o {
	OBJECT += libtcfsvservice.a::usb_events.o
}
ObjectFile libtcfsvservice.a::um_deferred.o {
	NAME Object file um_deferred.o from archive libtcfsvservice.a
	EXPORTS new_deferred_upload
	IMPORTS .TOC. memSysPartId buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffDestroy rBuffLibInit tcf_set_errno wvCurrentLogListGet wvLogListCreate strcmp tcf_json_read_long tcf_json_read_boolean write_stream tcf_json_write_string tcf_json_write_long tcf_json_write_boolean tcf_json_read_struct last_upload_mode_id wvLogListDelete wvPartitionSet wvCurrentLogGet loc_alloc
	DECLARES 
	USES 
}
Module um_deferred.o {
	OBJECT += libtcfsvservice.a::um_deferred.o
}
ObjectFile libtcfsvservice.a::logging_events.o {
	NAME Object file logging_events.o from archive libtcfsvservice.a
	EXPORTS logging_overflow logging_started upload_done logging_stopped
	IMPORTS .TOC. loc_alloc loc_free write_stringz tcf_json_write_uint64 write_stream
	DECLARES 
	USES 
}
Module logging_events.o {
	OBJECT += libtcfsvservice.a::logging_events.o
}
ObjectFile libtcfsvservice.a::um_postmortem.o {
	NAME Object file um_postmortem.o from archive libtcfsvservice.a
	EXPORTS new_postmortem_upload
	IMPORTS .TOC. memPartCreate wvPartitionSet wvCurrentLogListGet wvLogListCreate buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffLibInit tcf_set_errno strcmp tcf_json_read_uint64 tcf_json_read_boolean write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_uint64 tcf_json_read_struct wvLogListDelete memPartDelete loc_alloc
	DECLARES 
	USES 
}
Module um_postmortem.o {
	OBJECT += libtcfsvservice.a::um_postmortem.o
}
ObjectFile libtcfsvservice.a::net_events.o {
	NAME Object file net_events.o from archive libtcfsvservice.a
	EXPORTS newNetEvt
	IMPORTS .TOC. pWvNetEvtMap _wvNetDConfigure write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_long strcmp tcf_json_read_boolean tcf_json_read_long tcf_json_read_struct loc_alloc
	DECLARES 
	USES 
}
Module net_events.o {
	OBJECT += libtcfsvservice.a::net_events.o
}
ObjectFile libtcfsvservice.a::rtp_events.o {
	NAME Object file rtp_events.o from archive libtcfsvservice.a
	EXPORTS newRtpEvt
	IMPORTS .TOC. write_stream tcf_json_write_string wvObjInst tcf_json_write_boolean _wvObjStacktrace write_objects strcmp tcf_json_read_uint64 tcf_json_read_boolean tcf_json_read_struct tcf_json_read_array loc_alloc
	DECLARES 
	USES 
}
Module rtp_events.o {
	OBJECT += libtcfsvservice.a::rtp_events.o
}
ObjectFile libtcfsvservice.a::sv_objinfo.o {
	NAME Object file sv_objinfo.o from archive libtcfsvservice.a
	EXPORTS write_objects
	IMPORTS .TOC. objClassIdGet objVerify objNamePtrGet write_stream tcf_json_write_string tcf_json_write_uint64 objEach
	DECLARES 
	USES 
}
Module sv_objinfo.o {
	OBJECT += libtcfsvservice.a::sv_objinfo.o
}
ObjectFile libtcfsvservice.a::logging.o {
	NAME Object file logging.o from archive libtcfsvservice.a
	EXPORTS is_valid_wv_log command_delete_logs command_list_logs command_start_logging command_attach_logging command_is_logging command_stop_logging
	IMPORTS .TOC. write_stream tcf_json_write_string tcf_json_write_long tcf_json_write_uint64 wvLogCountGet wvLogFirstGet wvLogNextGet find_upload_mode wvLogListValidate wvCurrentLogListGet wvCurrentLogListSet strcmp tcf_json_read_long tcf_json_read_uint64 tcf_json_read_struct wvLogDelete wvLogListDelete tcf_json_read_array tcf_json_test_char write_stringz tcf_write_errno last_upload_mode_id wvEvtLogStart wvCurrentLogGet tcf_set_errno logging_started evtAction tcf_json_write_boolean wvEvtLogStop logging_stopped
	DECLARES 
	USES 
}
Module logging.o {
	OBJECT += libtcfsvservice.a::logging.o
}
ObjectFile libtcfsvservice.a::sv_upload.o {
	NAME Object file sv_upload.o from archive libtcfsvservice.a
	EXPORTS sync_event ini_upload_services
	IMPORTS .TOC. pthread_mutex_lock pthread_cond_signal pthread_mutex_unlock pthread_mutex_init check_error pthread_cond_init tcf_post_event pthread_cond_wait upload_done wvUploadStop loc_free tcf_json_read_string strcmp tcf_json_read_uint64 tcf_json_test_char tcf_json_read_array write_stringz tcf_write_errno tcf_json_write_uint64 write_stream pthread_create tcf_set_errno tcf_add_command_handler create_tcf_upload_session create_file_upload_session
	DECLARES 
	USES 
}
Module sv_upload.o {
	OBJECT += libtcfsvservice.a::sv_upload.o
}
ObjectFile libtcfsvservice.a::lib_events.o {
	NAME Object file lib_events.o from archive libtcfsvservice.a
	EXPORTS newSigEvt newEvtEvt newSalEvt newEDREvt newMscEvt newPmnEvt
	IMPORTS .TOC. _wvCallStackSetLevel write_stream tcf_json_write_string tcf_json_write_boolean strcmp tcf_json_read_boolean tcf_json_read_struct loc_alloc _sigEnabled wvSigInst _evtEnabled wvEventInst _salEnabled wvSalInst _edrEnabled wvEdrInst _mscEnabled wvMemScopeInst wvPowerInst
	DECLARES 
	USES 
}
Module lib_events.o {
	OBJECT += libtcfsvservice.a::lib_events.o
}
ObjectFile libtcfsvservice.a::sv_events.o {
	NAME Object file sv_events.o from archive libtcfsvservice.a
	EXPORTS register_events list_events enable_events
	IMPORTS .TOC. strcmp loc_alloc loc_free write_stream tcf_json_write_string tcf_json_write_boolean memset tcf_json_read_string tcf_json_read_array tcf_json_test_char enable_usb_event newTaskLibEvt newSempLibEvt newMsgQLibEvt newWdLibEvt newMemLibEvt newIoLibEvt newIsrLibEvt newSigEvt newEvtEvt newRtpEvt newSalEvt newEDREvt newSdLibEvt newUsbHostEvt newUsbPeriEvt newNetEvt newTipcEvt newMscEvt newPmnEvt
	DECLARES 
	USES 
}
Module sv_events.o {
	OBJECT += libtcfsvservice.a::sv_events.o
}
ObjectFile libtcfsvservice.a::um_continuous.o {
	NAME Object file um_continuous.o from archive libtcfsvservice.a
	EXPORTS new_continuous_upload
	IMPORTS .TOC. memSysPartId buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffLibInit tcf_set_errno wvCurrentLogListGet wvLogListCreate strcmp tcf_json_read_long write_stream tcf_json_write_string tcf_json_write_long tcf_json_read_struct last_upload_mode_id wvLogListDelete wvPartitionSet loc_alloc
	DECLARES 
	USES 
}
Module um_continuous.o {
	OBJECT += libtcfsvservice.a::um_continuous.o
}
ObjectFile libtcfsvservice.a::sysviewer.o {
	NAME Object file sysviewer.o from archive libtcfsvservice.a
	EXPORTS ini_sysviewer_service
	IMPORTS .TOC. tcf_json_test_char write_stringz tcf_write_errno write_stream tcf_json_write_string tcf_json_write_long register_events init_upload_modes tcf_add_command_handler command_list_logs command_delete_logs command_start_logging command_stop_logging command_attach_logging command_is_logging command_get_buf_stat command_get_config command_set_config command_store_config ini_uploadmode_services ini_upload_services activate_logging
	DECLARES 
	USES 
}
Module sysviewer.o {
	OBJECT += libtcfsvservice.a::sysviewer.o
}
ObjectFile libtcfsvservice.a::buf_stat.o {
	NAME Object file buf_stat.o from archive libtcfsvservice.a
	EXPORTS command_get_buf_stat
	IMPORTS .TOC. write_stream tcf_json_write_string tcf_json_write_uint64 tcf_json_write_int64 tcf_json_read_uint64 tcf_json_test_char is_valid_wv_log write_stringz tcf_write_errno
	DECLARES 
	USES 
}
Module buf_stat.o {
	OBJECT += libtcfsvservice.a::buf_stat.o
}
ObjectFile libtcfsvservice.a::sv_symbol.o {
	NAME Object file sv_symbol.o from archive libtcfsvservice.a
	EXPORTS is_symbol_api_enabled init_symbols _pmDefaultArena _pmRegionAddr _pmFreeSpace _pmRegionOpen _pmRegionSize _pmRegionCreate _pmRegionClose _pmValidate _pmInit _edrPmArena _wvNetDConfigure _wvCallStackSetLevel _wvCallStackSetEvent _wvCallStackDepthSet _wvTaskCallStackSet _wvTaskCallStackClear _wvCallStackFilterSet _wvObjStacktrace _wvTipcConfigure _wvTipcInit _sigEnabled _evtEnabled _salEnabled _edrEnabled _mscEnabled _usb2WvFilter _usbPeriphWvFilter
	IMPORTS .TOC. _func_symFind sysSymTbl
	DECLARES 
	USES 
}
Module sv_symbol.o {
	OBJECT += libtcfsvservice.a::sv_symbol.o
}
ObjectFile libtcfsvservice.a::wol_events.o {
	NAME Object file wol_events.o from archive libtcfsvservice.a
	EXPORTS newTaskLibEvt newSempLibEvt newMsgQLibEvt newWdLibEvt newMemLibEvt newIoLibEvt newIsrLibEvt newSdLibEvt
	IMPORTS .TOC. _wvObjStacktrace wvObjInst write_stream tcf_json_write_string tcf_json_write_boolean strcmp tcf_json_read_boolean tcf_json_read_struct loc_alloc
	DECLARES 
	USES 
}
Module wol_events.o {
	OBJECT += libtcfsvservice.a::wol_events.o
}
ObjectFile libtcfsvservice.a::stack_trace.o {
	NAME Object file stack_trace.o from archive libtcfsvservice.a
	EXPORTS is_stacktrace_enabled enable_stacktrace write_stacktrace_config
	IMPORTS .TOC. loc_alloc loc_free tcf_json_read_uint64 strcmp tcf_json_read_string tcf_json_read_int64 tcf_json_read_boolean tcf_json_read_array _wvCallStackDepthSet _wvCallStackSetLevel _wvCallStackSetEvent _wvTaskCallStackClear _wvCallStackFilterSet _wvTaskCallStackSet wvEvtClassGet tcf_json_read_struct tcf_json_test_char write_stream tcf_json_write_string tcf_json_write_int64 tcf_json_write_boolean tcf_json_write_uint64
	DECLARES 
	USES 
}
Module stack_trace.o {
	OBJECT += libtcfsvservice.a::stack_trace.o
}
Library libtcfsvservice.a {
	MODULES libtcfsvservice.a::uploadmode.o libtcfsvservice.a::um_postmortem_pm.o libtcfsvservice.a::sv_upload_file.o libtcfsvservice.a::tipc_events.o libtcfsvservice.a::sv_upload_tcf.o libtcfsvservice.a::usb_events.o libtcfsvservice.a::um_deferred.o libtcfsvservice.a::logging_events.o libtcfsvservice.a::um_postmortem.o libtcfsvservice.a::net_events.o libtcfsvservice.a::rtp_events.o libtcfsvservice.a::sv_objinfo.o libtcfsvservice.a::logging.o libtcfsvservice.a::sv_upload.o libtcfsvservice.a::lib_events.o libtcfsvservice.a::sv_events.o libtcfsvservice.a::um_continuous.o libtcfsvservice.a::sysviewer.o libtcfsvservice.a::buf_stat.o libtcfsvservice.a::sv_symbol.o libtcfsvservice.a::wol_events.o libtcfsvservice.a::stack_trace.o
}
Symbol init_upload_modes {
}
Symbol .TOC. {
}
Symbol loc_alloc {
}
Symbol write_json_config {
}
Symbol strlen {
}
Symbol memPartAlloc {
}
Symbol checksum {
}
Symbol read_json_config {
}
Symbol loc_free {
}
Symbol read_json_config_pm {
}
Symbol find_upload_mode {
}
Symbol strcmp {
}
Symbol last_upload_mode_id {
}
Symbol memset {
}
Symbol strncpy {
}
Symbol tcf_set_errno {
}
Symbol tcf_json_read_string {
}
Symbol tcf_json_test_char {
}
Symbol tcf_json_write_string {
}
Symbol write_stream {
}
Symbol wvEvtBufferFullNotify {
}
Symbol logging_overflow {
}
Symbol buffer_overflow_handler {
}
Symbol wvCurrentLogGet {
}
Symbol tcf_post_event {
}
Symbol _pmValidate {
}
Symbol _pmDefaultArena {
}
Symbol tcf_json_read_long {
}
Symbol wvEvtClassClear {
}
Symbol wvEvtClassSet {
}
Symbol enable_events {
}
Symbol tcf_json_read_boolean {
}
Symbol enable_stacktrace {
}
Symbol command_get_config {
}
Symbol write_stringz {
}
Symbol tcf_write_errno {
}
Symbol wvEvtClassGet {
}
Symbol tcf_json_write_long {
}
Symbol list_events {
}
Symbol is_stacktrace_enabled {
}
Symbol tcf_json_write_boolean {
}
Symbol write_stacktrace_config {
}
Symbol command_set_config {
}
Symbol command_store_config {
}
Symbol create_byte_array_output_stream {
}
Symbol read_stream {
}
Symbol get_byte_array_output_stream_data {
}
Symbol activate_logging {
}
Symbol create_byte_array_input_stream {
}
Symbol wvEvtLogStart {
}
Symbol ini_uploadmode_services {
}
Symbol new_deferred_upload {
}
Symbol new_continuous_upload {
}
Symbol new_postmortem_pm_upload {
}
Symbol _pmRegionAddr {
}
Symbol _pmFreeSpace {
}
Symbol _pmRegionOpen {
}
Symbol _pmRegionSize {
}
Symbol _pmRegionCreate {
}
Symbol _pmRegionClose {
}
Symbol wvCurrentLogListGet {
}
Symbol wvLogListDelete {
}
Symbol memPartDelete {
}
Symbol memPartCreate {
}
Symbol wvPartitionSet {
}
Symbol wvLogListCreate {
}
Symbol rBuffCreate {
}
Symbol wvLogCountGet {
}
Symbol wvMaximumLogs {
}
Symbol wvLogCreate {
}
Symbol rBuffLibInit {
}
Symbol tcf_json_read_uint64 {
}
Symbol tcf_json_write_uint64 {
}
Symbol tcf_json_read_struct {
}
Symbol _pmInit {
}
Symbol tcf_add_command_handler {
}
Symbol wvFileUploadPathClose {
}
Symbol wvFileUploadPathCreate {
}
Symbol wvUploadStart {
}
Symbol create_file_upload_session {
}
Symbol is_valid_wv_log {
}
Symbol pthread_create {
}
Symbol _wvTipcConfigure {
}
Symbol _wvTipcInit {
}
Symbol newTipcEvt {
}
Symbol virtual_stream_is_empty {
}
Symbol pthread_mutex_lock {
}
Symbol pthread_cond_signal {
}
Symbol pthread_mutex_unlock {
}
Symbol snprintf {
}
Symbol virtual_stream_create {
}
Symbol virtual_stream_add_data {
}
Symbol sync_event {
}
Symbol pthread_cond_wait {
}
Symbol virtual_stream_delete {
}
Symbol create_tcf_upload_session {
}
Symbol pthread_mutex_init {
}
Symbol check_error {
}
Symbol pthread_cond_init {
}
Symbol enable_usb_event {
}
Symbol wvUsbInst {
}
Symbol newUsbHostEvt {
}
Symbol _usb2WvFilter {
}
Symbol newUsbPeriEvt {
}
Symbol _usbPeriphWvFilter {
}
Symbol memSysPartId {
}
Symbol rBuffDestroy {
}
Symbol logging_started {
}
Symbol upload_done {
}
Symbol logging_stopped {
}
Symbol new_postmortem_upload {
}
Symbol pWvNetEvtMap {
}
Symbol _wvNetDConfigure {
}
Symbol newNetEvt {
}
Symbol wvObjInst {
}
Symbol _wvObjStacktrace {
}
Symbol write_objects {
}
Symbol tcf_json_read_array {
}
Symbol newRtpEvt {
}
Symbol objClassIdGet {
}
Symbol objVerify {
}
Symbol objNamePtrGet {
}
Symbol objEach {
}
Symbol wvLogFirstGet {
}
Symbol wvLogNextGet {
}
Symbol wvLogListValidate {
}
Symbol wvCurrentLogListSet {
}
Symbol wvLogDelete {
}
Symbol command_delete_logs {
}
Symbol command_list_logs {
}
Symbol command_start_logging {
}
Symbol command_attach_logging {
}
Symbol command_is_logging {
}
Symbol evtAction {
}
Symbol command_stop_logging {
}
Symbol wvEvtLogStop {
}
Symbol wvUploadStop {
}
Symbol ini_upload_services {
}
Symbol _wvCallStackSetLevel {
}
Symbol newSigEvt {
}
Symbol _sigEnabled {
}
Symbol wvSigInst {
}
Symbol newEvtEvt {
}
Symbol _evtEnabled {
}
Symbol wvEventInst {
}
Symbol newSalEvt {
}
Symbol _salEnabled {
}
Symbol wvSalInst {
}
Symbol newEDREvt {
}
Symbol _edrEnabled {
}
Symbol wvEdrInst {
}
Symbol newMscEvt {
}
Symbol _mscEnabled {
}
Symbol wvMemScopeInst {
}
Symbol newPmnEvt {
}
Symbol wvPowerInst {
}
Symbol register_events {
}
Symbol newTaskLibEvt {
}
Symbol newSempLibEvt {
}
Symbol newMsgQLibEvt {
}
Symbol newWdLibEvt {
}
Symbol newMemLibEvt {
}
Symbol newIoLibEvt {
}
Symbol newIsrLibEvt {
}
Symbol newSdLibEvt {
}
Symbol ini_sysviewer_service {
}
Symbol command_get_buf_stat {
}
Symbol tcf_json_write_int64 {
}
Symbol _func_symFind {
}
Symbol sysSymTbl {
}
Symbol is_symbol_api_enabled {
}
Symbol init_symbols {
}
Symbol _edrPmArena {
}
Symbol _wvCallStackSetEvent {
}
Symbol _wvCallStackDepthSet {
}
Symbol _wvTaskCallStackSet {
}
Symbol _wvTaskCallStackClear {
}
Symbol _wvCallStackFilterSet {
}
Symbol tcf_json_read_int64 {
}
ObjectFile libtcfsvservice.a::uploadmode.o {
	NAME Object file uploadmode.o from archive libtcfsvservice.a
	EXPORTS init_upload_modes write_json_config read_json_config read_json_config_pm find_upload_mode last_upload_mode_id buffer_overflow_handler command_get_config command_set_config command_store_config activate_logging ini_uploadmode_services
	IMPORTS .TOC. loc_alloc strlen memPartAlloc checksum loc_free strcmp memset strncpy tcf_set_errno tcf_json_read_string tcf_json_test_char tcf_json_write_string write_stream wvEvtBufferFullNotify logging_overflow wvCurrentLogGet tcf_post_event _pmValidate _pmDefaultArena tcf_json_read_long wvEvtClassClear wvEvtClassSet enable_events tcf_json_read_boolean enable_stacktrace write_stringz tcf_write_errno wvEvtClassGet tcf_json_write_long list_events is_stacktrace_enabled tcf_json_write_boolean write_stacktrace_config create_byte_array_output_stream read_stream get_byte_array_output_stream_data create_byte_array_input_stream wvEvtLogStart new_deferred_upload new_continuous_upload new_postmortem_pm_upload
	DECLARES 
	USES 
}
Module uploadmode.o {
	OBJECT += libtcfsvservice.a::uploadmode.o
}
ObjectFile libtcfsvservice.a::um_postmortem_pm.o {
	NAME Object file um_postmortem_pm.o from archive libtcfsvservice.a
	EXPORTS new_postmortem_pm_upload
	IMPORTS .TOC. _pmDefaultArena _pmRegionAddr _pmFreeSpace _pmRegionOpen _pmRegionSize _pmRegionCreate _pmRegionClose wvCurrentLogListGet wvLogListDelete memPartDelete memPartCreate write_json_config read_json_config_pm wvPartitionSet wvLogListCreate buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffLibInit tcf_set_errno strcmp tcf_json_read_long tcf_json_read_uint64 tcf_json_read_boolean tcf_json_write_string write_stream tcf_json_write_uint64 tcf_json_write_long tcf_json_write_boolean tcf_json_read_struct find_upload_mode write_stringz tcf_write_errno _pmInit tcf_json_test_char tcf_add_command_handler loc_alloc
	DECLARES 
	USES 
}
Module um_postmortem_pm.o {
	OBJECT += libtcfsvservice.a::um_postmortem_pm.o
}
ObjectFile libtcfsvservice.a::sv_upload_file.o {
	NAME Object file sv_upload_file.o from archive libtcfsvservice.a
	EXPORTS create_file_upload_session
	IMPORTS .TOC. wvFileUploadPathClose strcmp tcf_json_read_boolean tcf_json_read_string wvFileUploadPathCreate wvUploadStart loc_free loc_alloc tcf_json_read_struct is_valid_wv_log pthread_create
	DECLARES 
	USES 
}
Module sv_upload_file.o {
	OBJECT += libtcfsvservice.a::sv_upload_file.o
}
ObjectFile libtcfsvservice.a::tipc_events.o {
	NAME Object file tipc_events.o from archive libtcfsvservice.a
	EXPORTS newTipcEvt
	IMPORTS .TOC. _wvTipcConfigure _wvTipcInit write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_long strcmp tcf_json_read_boolean tcf_json_read_long tcf_json_read_struct loc_alloc
	DECLARES 
	USES 
}
Module tipc_events.o {
	OBJECT += libtcfsvservice.a::tipc_events.o
}
ObjectFile libtcfsvservice.a::sv_upload_tcf.o {
	NAME Object file sv_upload_tcf.o from archive libtcfsvservice.a
	EXPORTS create_tcf_upload_session
	IMPORTS .TOC. virtual_stream_is_empty pthread_mutex_lock pthread_cond_signal pthread_mutex_unlock memset snprintf virtual_stream_create virtual_stream_add_data sync_event pthread_cond_wait virtual_stream_delete loc_free strcmp tcf_json_read_boolean tcf_json_read_long tcf_json_read_struct is_valid_wv_log loc_alloc pthread_mutex_init check_error pthread_cond_init wvUploadStart
	DECLARES 
	USES 
}
Module sv_upload_tcf.o {
	OBJECT += libtcfsvservice.a::sv_upload_tcf.o
}
ObjectFile libtcfsvservice.a::usb_events.o {
	NAME Object file usb_events.o from archive libtcfsvservice.a
	EXPORTS enable_usb_event newUsbHostEvt newUsbPeriEvt
	IMPORTS .TOC. write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_uint64 strcmp tcf_json_read_boolean tcf_json_read_uint64 tcf_json_read_struct loc_alloc wvUsbInst _usb2WvFilter _usbPeriphWvFilter
	DECLARES 
	USES 
}
Module usb_events.o {
	OBJECT += libtcfsvservice.a::usb_events.o
}
ObjectFile libtcfsvservice.a::um_deferred.o {
	NAME Object file um_deferred.o from archive libtcfsvservice.a
	EXPORTS new_deferred_upload
	IMPORTS .TOC. memSysPartId buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffDestroy rBuffLibInit tcf_set_errno wvCurrentLogListGet wvLogListCreate strcmp tcf_json_read_long tcf_json_read_boolean write_stream tcf_json_write_string tcf_json_write_long tcf_json_write_boolean tcf_json_read_struct last_upload_mode_id wvLogListDelete wvPartitionSet wvCurrentLogGet loc_alloc
	DECLARES 
	USES 
}
Module um_deferred.o {
	OBJECT += libtcfsvservice.a::um_deferred.o
}
ObjectFile libtcfsvservice.a::logging_events.o {
	NAME Object file logging_events.o from archive libtcfsvservice.a
	EXPORTS logging_overflow logging_started upload_done logging_stopped
	IMPORTS .TOC. loc_alloc loc_free write_stringz tcf_json_write_uint64 write_stream
	DECLARES 
	USES 
}
Module logging_events.o {
	OBJECT += libtcfsvservice.a::logging_events.o
}
ObjectFile libtcfsvservice.a::um_postmortem.o {
	NAME Object file um_postmortem.o from archive libtcfsvservice.a
	EXPORTS new_postmortem_upload
	IMPORTS .TOC. memPartCreate wvPartitionSet wvCurrentLogListGet wvLogListCreate buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffLibInit tcf_set_errno strcmp tcf_json_read_uint64 tcf_json_read_boolean write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_uint64 tcf_json_read_struct wvLogListDelete memPartDelete loc_alloc
	DECLARES 
	USES 
}
Module um_postmortem.o {
	OBJECT += libtcfsvservice.a::um_postmortem.o
}
ObjectFile libtcfsvservice.a::net_events.o {
	NAME Object file net_events.o from archive libtcfsvservice.a
	EXPORTS newNetEvt
	IMPORTS .TOC. pWvNetEvtMap _wvNetDConfigure write_stream tcf_json_write_string tcf_json_write_boolean tcf_json_write_long strcmp tcf_json_read_boolean tcf_json_read_long tcf_json_read_struct loc_alloc
	DECLARES 
	USES 
}
Module net_events.o {
	OBJECT += libtcfsvservice.a::net_events.o
}
ObjectFile libtcfsvservice.a::rtp_events.o {
	NAME Object file rtp_events.o from archive libtcfsvservice.a
	EXPORTS newRtpEvt
	IMPORTS .TOC. write_stream tcf_json_write_string wvObjInst tcf_json_write_boolean _wvObjStacktrace write_objects strcmp tcf_json_read_uint64 tcf_json_read_boolean tcf_json_read_struct tcf_json_read_array loc_alloc
	DECLARES 
	USES 
}
Module rtp_events.o {
	OBJECT += libtcfsvservice.a::rtp_events.o
}
ObjectFile libtcfsvservice.a::sv_objinfo.o {
	NAME Object file sv_objinfo.o from archive libtcfsvservice.a
	EXPORTS write_objects
	IMPORTS .TOC. objClassIdGet objVerify objNamePtrGet write_stream tcf_json_write_string tcf_json_write_uint64 objEach
	DECLARES 
	USES 
}
Module sv_objinfo.o {
	OBJECT += libtcfsvservice.a::sv_objinfo.o
}
ObjectFile libtcfsvservice.a::logging.o {
	NAME Object file logging.o from archive libtcfsvservice.a
	EXPORTS is_valid_wv_log command_delete_logs command_list_logs command_start_logging command_attach_logging command_is_logging command_stop_logging
	IMPORTS .TOC. write_stream tcf_json_write_string tcf_json_write_long tcf_json_write_uint64 wvLogCountGet wvLogFirstGet wvLogNextGet find_upload_mode wvLogListValidate wvCurrentLogListGet wvCurrentLogListSet strcmp tcf_json_read_long tcf_json_read_uint64 tcf_json_read_struct wvLogDelete wvLogListDelete tcf_json_read_array tcf_json_test_char write_stringz tcf_write_errno last_upload_mode_id wvEvtLogStart wvCurrentLogGet tcf_set_errno logging_started evtAction tcf_json_write_boolean wvEvtLogStop logging_stopped
	DECLARES 
	USES 
}
Module logging.o {
	OBJECT += libtcfsvservice.a::logging.o
}
ObjectFile libtcfsvservice.a::sv_upload.o {
	NAME Object file sv_upload.o from archive libtcfsvservice.a
	EXPORTS sync_event ini_upload_services
	IMPORTS .TOC. pthread_mutex_lock pthread_cond_signal pthread_mutex_unlock pthread_mutex_init check_error pthread_cond_init tcf_post_event pthread_cond_wait upload_done wvUploadStop loc_free tcf_json_read_string strcmp tcf_json_read_uint64 tcf_json_test_char tcf_json_read_array write_stringz tcf_write_errno tcf_json_write_uint64 write_stream pthread_create tcf_set_errno tcf_add_command_handler create_tcf_upload_session create_file_upload_session
	DECLARES 
	USES 
}
Module sv_upload.o {
	OBJECT += libtcfsvservice.a::sv_upload.o
}
ObjectFile libtcfsvservice.a::lib_events.o {
	NAME Object file lib_events.o from archive libtcfsvservice.a
	EXPORTS newSigEvt newEvtEvt newSalEvt newEDREvt newMscEvt newPmnEvt
	IMPORTS .TOC. _wvCallStackSetLevel write_stream tcf_json_write_string tcf_json_write_boolean strcmp tcf_json_read_boolean tcf_json_read_struct loc_alloc _sigEnabled wvSigInst _evtEnabled wvEventInst _salEnabled wvSalInst _edrEnabled wvEdrInst _mscEnabled wvMemScopeInst wvPowerInst
	DECLARES 
	USES 
}
Module lib_events.o {
	OBJECT += libtcfsvservice.a::lib_events.o
}
ObjectFile libtcfsvservice.a::sv_events.o {
	NAME Object file sv_events.o from archive libtcfsvservice.a
	EXPORTS register_events list_events enable_events
	IMPORTS .TOC. strcmp loc_alloc loc_free write_stream tcf_json_write_string tcf_json_write_boolean memset tcf_json_read_string tcf_json_read_array tcf_json_test_char enable_usb_event newTaskLibEvt newSempLibEvt newMsgQLibEvt newWdLibEvt newMemLibEvt newIoLibEvt newIsrLibEvt newSigEvt newEvtEvt newRtpEvt newSalEvt newEDREvt newSdLibEvt newUsbHostEvt newUsbPeriEvt newNetEvt newTipcEvt newMscEvt newPmnEvt
	DECLARES 
	USES 
}
Module sv_events.o {
	OBJECT += libtcfsvservice.a::sv_events.o
}
ObjectFile libtcfsvservice.a::um_continuous.o {
	NAME Object file um_continuous.o from archive libtcfsvservice.a
	EXPORTS new_continuous_upload
	IMPORTS .TOC. memSysPartId buffer_overflow_handler rBuffCreate wvLogCountGet wvMaximumLogs wvLogCreate rBuffLibInit tcf_set_errno wvCurrentLogListGet wvLogListCreate strcmp tcf_json_read_long write_stream tcf_json_write_string tcf_json_write_long tcf_json_read_struct last_upload_mode_id wvLogListDelete wvPartitionSet loc_alloc
	DECLARES 
	USES 
}
Module um_continuous.o {
	OBJECT += libtcfsvservice.a::um_continuous.o
}
ObjectFile libtcfsvservice.a::sysviewer.o {
	NAME Object file sysviewer.o from archive libtcfsvservice.a
	EXPORTS ini_sysviewer_service
	IMPORTS .TOC. tcf_json_test_char write_stringz tcf_write_errno write_stream tcf_json_write_string tcf_json_write_long register_events init_upload_modes tcf_add_command_handler command_list_logs command_delete_logs command_start_logging command_stop_logging command_attach_logging command_is_logging command_get_buf_stat command_get_config command_set_config command_store_config ini_uploadmode_services ini_upload_services activate_logging
	DECLARES 
	USES 
}
Module sysviewer.o {
	OBJECT += libtcfsvservice.a::sysviewer.o
}
ObjectFile libtcfsvservice.a::buf_stat.o {
	NAME Object file buf_stat.o from archive libtcfsvservice.a
	EXPORTS command_get_buf_stat
	IMPORTS .TOC. write_stream tcf_json_write_string tcf_json_write_uint64 tcf_json_write_int64 tcf_json_read_uint64 tcf_json_test_char is_valid_wv_log write_stringz tcf_write_errno
	DECLARES 
	USES 
}
Module buf_stat.o {
	OBJECT += libtcfsvservice.a::buf_stat.o
}
ObjectFile libtcfsvservice.a::sv_symbol.o {
	NAME Object file sv_symbol.o from archive libtcfsvservice.a
	EXPORTS is_symbol_api_enabled init_symbols _pmDefaultArena _pmRegionAddr _pmFreeSpace _pmRegionOpen _pmRegionSize _pmRegionCreate _pmRegionClose _pmValidate _pmInit _edrPmArena _wvNetDConfigure _wvCallStackSetLevel _wvCallStackSetEvent _wvCallStackDepthSet _wvTaskCallStackSet _wvTaskCallStackClear _wvCallStackFilterSet _wvObjStacktrace _wvTipcConfigure _wvTipcInit _sigEnabled _evtEnabled _salEnabled _edrEnabled _mscEnabled _usb2WvFilter _usbPeriphWvFilter
	IMPORTS .TOC. _func_symFind sysSymTbl
	DECLARES 
	USES 
}
Module sv_symbol.o {
	OBJECT += libtcfsvservice.a::sv_symbol.o
}
ObjectFile libtcfsvservice.a::wol_events.o {
	NAME Object file wol_events.o from archive libtcfsvservice.a
	EXPORTS newTaskLibEvt newSempLibEvt newMsgQLibEvt newWdLibEvt newMemLibEvt newIoLibEvt newIsrLibEvt newSdLibEvt
	IMPORTS .TOC. _wvObjStacktrace wvObjInst write_stream tcf_json_write_string tcf_json_write_boolean strcmp tcf_json_read_boolean tcf_json_read_struct loc_alloc
	DECLARES 
	USES 
}
Module wol_events.o {
	OBJECT += libtcfsvservice.a::wol_events.o
}
ObjectFile libtcfsvservice.a::stack_trace.o {
	NAME Object file stack_trace.o from archive libtcfsvservice.a
	EXPORTS is_stacktrace_enabled enable_stacktrace write_stacktrace_config
	IMPORTS .TOC. loc_alloc loc_free tcf_json_read_uint64 strcmp tcf_json_read_string tcf_json_read_int64 tcf_json_read_boolean tcf_json_read_array _wvCallStackDepthSet _wvCallStackSetLevel _wvCallStackSetEvent _wvTaskCallStackClear _wvCallStackFilterSet _wvTaskCallStackSet wvEvtClassGet tcf_json_read_struct tcf_json_test_char write_stream tcf_json_write_string tcf_json_write_int64 tcf_json_write_boolean tcf_json_write_uint64
	DECLARES 
	USES 
}
Module stack_trace.o {
	OBJECT += libtcfsvservice.a::stack_trace.o
}
Library libtcfsvservice.a {
	MODULES libtcfsvservice.a::uploadmode.o libtcfsvservice.a::um_postmortem_pm.o libtcfsvservice.a::sv_upload_file.o libtcfsvservice.a::tipc_events.o libtcfsvservice.a::sv_upload_tcf.o libtcfsvservice.a::usb_events.o libtcfsvservice.a::um_deferred.o libtcfsvservice.a::logging_events.o libtcfsvservice.a::um_postmortem.o libtcfsvservice.a::net_events.o libtcfsvservice.a::rtp_events.o libtcfsvservice.a::sv_objinfo.o libtcfsvservice.a::logging.o libtcfsvservice.a::sv_upload.o libtcfsvservice.a::lib_events.o libtcfsvservice.a::sv_events.o libtcfsvservice.a::um_continuous.o libtcfsvservice.a::sysviewer.o libtcfsvservice.a::buf_stat.o libtcfsvservice.a::sv_symbol.o libtcfsvservice.a::wol_events.o libtcfsvservice.a::stack_trace.o
}
