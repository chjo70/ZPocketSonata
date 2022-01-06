Symbol .TOC. {
}
Symbol strlen {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol memset {
}
Symbol strncpy {
}
Symbol ipcom_if_nametoindex {
}
Symbol ipcom_sysctl {
}
Symbol malloc {
}
Symbol ipcom_syslog {
}
Symbol ipcom_errno_get {
}
Symbol ipdhcpc {
}
Symbol ipnet_cmd_init_addrs {
}
Symbol ipcom_socketioctl_usr {
}
Symbol free {
}
Symbol ipcom_mutex_create {
}
Symbol ipcom_sleep {
}
Symbol time {
}
Symbol ipcom_socket_usr {
}
Symbol ipcom_bind_usr {
}
Symbol ipcom_getsockopt_usr {
}
Symbol ipcom_setsockopt_usr {
}
Symbol ipcom_mutex_lock {
}
Symbol ipcom_socketclose_usr {
}
Symbol ipcom_mutex_unlock {
}
Symbol ipcom_mutex_delete {
}
Symbol ipdhcpc_cmd_dhcpc {
}
Symbol ipcom_shell_remove_cmd {
}
Symbol ipcom_random {
}
Symbol memcpy {
}
Symbol ipcom_in_checksum {
}
Symbol ipcom_sendto_usr {
}
Symbol ipcom_sendmsg_usr {
}
Symbol ipcom_millisleep {
}
Symbol ipcom_if_indextoname {
}
Symbol ipcom_tmo_cancel {
}
Symbol ipcom_tmo_request {
}
Symbol ipcom_tmo_get {
}
Symbol strerror {
}
Symbol ipdhcpc_option_limit_get_next {
}
Symbol ipdhcpc_option_callback {
}
Symbol ipcom_inet_ntop {
}
Symbol ipcom_sysvar_set {
}
Symbol ipdhcpc_iflease {
}
Symbol memcmp {
}
Symbol strtok_r {
}
Symbol isxdigit {
}
Symbol strtol {
}
Symbol ipdhcpc_ifopen {
}
Symbol snprintf {
}
Symbol ipcom_sysvar_get {
}
Symbol ipcom_strcasecmp {
}
Symbol strcmp {
}
Symbol sprintf {
}
Symbol ipcom_sysvar_get_descriptive_int0 {
}
Symbol ipdhcpc_handle_free {
}
Symbol ipdhcpc_ifclose {
}
Symbol ipdhcpc_option_add {
}
Symbol ipdhcpc_handle_malloc {
}
Symbol ipcom_inet_pton {
}
Symbol strchr {
}
Symbol atoi {
}
Symbol sscanf {
}
Symbol ipdhcpc_ifrequest {
}
Symbol ipdhcpc_reply_cb {
}
Symbol ipdhcpc_if_isopen {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_ipd_input {
}
Symbol ipcom_recv_usr {
}
Symbol ipcom_recvfrom_usr {
}
Symbol ipcom_if_nameindex {
}
Symbol ipcom_if_freenameindex {
}
Symbol ipcom_proc_init {
}
Symbol ipcom_ipd_init {
}
Symbol ipcom_ipd_exit {
}
Symbol ipcom_proc_exit {
}
Symbol ipdhcpc_reply_callback {
}
Symbol ipdhcpc_ifunlease {
}
Symbol ipdhcpc_option_sprintf {
}
Symbol ipdhcpc_option_find {
}
Symbol ipdhcpc_option_get_first {
}
Symbol ipdhcpc_create {
}
Symbol ipdhcpc_start {
}
Symbol ipcom_proc_attr_init {
}
Symbol ipcom_priority_map {
}
Symbol ipcom_proc_acreate_v1 {
}
Symbol ipcom_shell_add_cmd {
}
Symbol ipdhcpc_renew_get {
}
Symbol ipdhcpc_inform_get {
}
Symbol ipdhcpc_version {
}
Symbol vsnprintf {
}
Symbol printf {
}
Symbol ipcom_inet_ntoa {
}
ObjectFile libDHCPC.a::ipdhcpc.o {
	NAME Object file ipdhcpc.o from archive libDHCPC.a
	EXPORTS ipdhcpc_option_limit_get_next ipdhcpc_iflease ipdhcpc_ifopen ipdhcpc_handle_free ipdhcpc_ifclose ipdhcpc_option_add ipdhcpc_handle_malloc ipdhcpc_ifrequest ipdhcpc_reply_cb ipdhcpc_if_isopen ipdhcpc_ifunlease ipdhcpc_option_sprintf ipdhcpc_option_find ipdhcpc_option_get_first ipdhcpc_create ipdhcpc_start ipdhcpc_renew_get ipdhcpc_inform_get ipdhcpc_version
	IMPORTS .TOC. strlen ipcom_sysvar_get_as_int memset strncpy ipcom_if_nametoindex ipcom_sysctl malloc ipcom_syslog ipcom_errno_get ipnet_cmd_init_addrs ipcom_socketioctl_usr free ipcom_mutex_create ipcom_sleep time ipcom_socket_usr ipcom_bind_usr ipcom_getsockopt_usr ipcom_setsockopt_usr ipcom_mutex_lock ipcom_socketclose_usr ipcom_mutex_unlock ipcom_mutex_delete ipdhcpc_cmd_dhcpc ipcom_shell_remove_cmd ipcom_random memcpy ipcom_in_checksum ipcom_sendto_usr ipcom_sendmsg_usr ipcom_millisleep ipcom_if_indextoname ipcom_tmo_cancel ipcom_tmo_request ipcom_tmo_get strerror ipdhcpc_option_callback ipcom_inet_ntop ipcom_sysvar_set memcmp strtok_r isxdigit strtol snprintf ipcom_sysvar_get ipcom_strcasecmp strcmp sprintf ipcom_sysvar_get_descriptive_int0 ipcom_inet_pton strchr atoi sscanf ipcom_socketselect_usr ipcom_ipd_input ipcom_recv_usr ipcom_recvfrom_usr ipcom_if_nameindex ipcom_if_freenameindex ipcom_proc_init ipcom_ipd_init ipcom_ipd_exit ipcom_proc_exit ipdhcpc_reply_callback ipcom_proc_attr_init ipcom_priority_map ipcom_proc_acreate_v1 ipcom_shell_add_cmd
	DECLARES ipdhcpc
	USES 
}
Module ipdhcpc.o {
	OBJECT += libDHCPC.a::ipdhcpc.o
}
ObjectFile libDHCPC.a::ipdhcpc_cmd_dhcpc.o {
	NAME Object file ipdhcpc_cmd_dhcpc.o from archive libDHCPC.a
	EXPORTS ipdhcpc_cmd_dhcpc
	IMPORTS .TOC. malloc vsnprintf printf free ipdhcpc_renew_get ipdhcpc_inform_get strcmp ipdhcpc ipcom_mutex_lock ipcom_mutex_unlock ipcom_inet_ntoa
	DECLARES 
	USES 
}
Module ipdhcpc_cmd_dhcpc.o {
	OBJECT += libDHCPC.a::ipdhcpc_cmd_dhcpc.o
}
Library libDHCPC.a {
	MODULES libDHCPC.a::ipdhcpc.o libDHCPC.a::ipdhcpc_cmd_dhcpc.o
}
