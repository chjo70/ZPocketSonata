Symbol .TOC. {
}
Symbol ipcom_fopen {
}
Symbol ipcom_syslog {
}
Symbol ipcom_socket_usr {
}
Symbol iptftp_bind_zero {
}
Symbol iptftp_send_loop {
}
Symbol iptftp_send_err {
}
Symbol ipcom_fclose {
}
Symbol ipcom_socketclose_usr {
}
Symbol iptftp_receive_loop {
}
Symbol iptftp_client_get {
}
Symbol malloc {
}
Symbol memset {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol ipcom_getaddrinfo {
}
Symbol memcpy {
}
Symbol strlen {
}
Symbol strcpy {
}
Symbol iptftp_strip_path {
}
Symbol ipcom_times {
}
Symbol printf {
}
Symbol ipcom_freeaddrinfo {
}
Symbol free {
}
Symbol iptftp_client_put {
}
Symbol iptftpc_create {
}
Symbol iptftpc_start {
}
Symbol iptftpc_version {
}
Symbol iptftp_cmd_tftp {
}
Symbol ipcom_getopt_clear_r {
}
Symbol ipcom_getopt_r {
}
Symbol atoi {
}
Symbol strcmp {
}
Symbol ipcom_errno_set {
}
Symbol ipcom_fread {
}
Symbol ipcom_feof {
}
Symbol ipcom_fwrite {
}
Symbol strrchr {
}
Symbol iptftp_sendto {
}
Symbol ipcom_if_indextoname {
}
Symbol ipcom_getifaddrs {
}
Symbol ipcom_freeifaddrs {
}
Symbol ipcom_sendmsg_usr {
}
Symbol ipcom_sendto_usr {
}
Symbol ipcom_errno_get {
}
Symbol iptftp_recvfrom {
}
Symbol ipcom_recvmsg_usr {
}
Symbol time {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_setsockopt_usr {
}
Symbol ipcom_bind_usr {
}
Symbol ipcom_sysvar_get {
}
Symbol ipcom_strcasecmp {
}
Symbol ipcom_proc_init {
}
Symbol ipcom_ipc_open {
}
Symbol ipcom_ipc_malloc {
}
Symbol ipcom_ipc_send {
}
Symbol ipcom_ipc_receive {
}
Symbol ipcom_ipc_close {
}
Symbol ipcom_ipc_free {
}
Symbol ipcom_proc_exit {
}
Symbol ipcom_proc_attr_init {
}
Symbol ipcom_priority_map {
}
Symbol ipcom_proc_acreate_v1 {
}
Symbol ipcom_stat {
}
Symbol ipcom_mkdir {
}
Symbol strerror {
}
Symbol ipcom_ipc_install {
}
Symbol ipcom_ipd_init {
}
Symbol ipcom_ipd_input {
}
Symbol ipcom_ipd_exit {
}
Symbol ipcom_ipc_uninstall {
}
Symbol iptftps_create {
}
Symbol iptftps_start {
}
Symbol iptftps_version {
}
ObjectFile libTFTP.a::iptftpc.o {
	NAME Object file iptftpc.o from archive libTFTP.a
	EXPORTS iptftp_client_get iptftp_client_put iptftpc_create iptftpc_start iptftpc_version
	IMPORTS .TOC. ipcom_fopen ipcom_syslog ipcom_socket_usr iptftp_bind_zero iptftp_send_loop iptftp_send_err ipcom_fclose ipcom_socketclose_usr iptftp_receive_loop malloc memset ipcom_sysvar_get_as_int ipcom_getaddrinfo memcpy strlen strcpy iptftp_strip_path ipcom_times printf ipcom_freeaddrinfo free
	DECLARES 
	USES 
}
Module iptftpc.o {
	OBJECT += libTFTP.a::iptftpc.o
}
ObjectFile libTFTP.a::iptftpc_cmd_tftp.o {
	NAME Object file iptftpc_cmd_tftp.o from archive libTFTP.a
	EXPORTS iptftp_cmd_tftp
	IMPORTS .TOC. ipcom_getopt_clear_r ipcom_getopt_r printf atoi strcmp iptftp_client_get iptftp_client_put
	DECLARES 
	USES 
}
Module iptftpc_cmd_tftp.o {
	OBJECT += libTFTP.a::iptftpc_cmd_tftp.o
}
ObjectFile libTFTP.a::iptftp_common.o {
	NAME Object file iptftp_common.o from archive libTFTP.a
	EXPORTS iptftp_strip_path iptftp_sendto iptftp_send_err iptftp_recvfrom iptftp_send_loop iptftp_receive_loop iptftp_bind_zero
	IMPORTS .TOC. ipcom_errno_set strlen strcpy ipcom_fread ipcom_feof ipcom_fwrite strrchr memset memcpy ipcom_if_indextoname ipcom_getifaddrs strcmp ipcom_freeifaddrs ipcom_sendmsg_usr ipcom_sendto_usr ipcom_errno_get ipcom_syslog malloc free ipcom_recvmsg_usr ipcom_sysvar_get_as_int time ipcom_socketselect_usr printf ipcom_setsockopt_usr ipcom_bind_usr
	DECLARES 
	USES 
}
Module iptftp_common.o {
	OBJECT += libTFTP.a::iptftp_common.o
}
ObjectFile libTFTP.a::iptftps.o {
	NAME Object file iptftps.o from archive libTFTP.a
	EXPORTS iptftps_create iptftps_start iptftps_version
	IMPORTS .TOC. ipcom_socket_usr ipcom_syslog iptftp_bind_zero ipcom_fopen iptftp_send_loop iptftp_send_err ipcom_fclose ipcom_socketclose_usr ipcom_sysvar_get ipcom_strcasecmp free iptftp_receive_loop ipcom_proc_init ipcom_ipc_open ipcom_ipc_malloc ipcom_ipc_send ipcom_ipc_receive ipcom_ipc_close ipcom_ipc_free ipcom_proc_exit ipcom_proc_attr_init ipcom_priority_map ipcom_sysvar_get_as_int ipcom_proc_acreate_v1 memcpy ipcom_recvmsg_usr strlen strcpy ipcom_stat ipcom_mkdir ipcom_errno_get strerror malloc memset ipcom_ipc_install ipcom_setsockopt_usr ipcom_bind_usr ipcom_ipd_init ipcom_socketselect_usr ipcom_ipd_input ipcom_ipd_exit ipcom_ipc_uninstall
	DECLARES 
	USES 
}
Module iptftps.o {
	OBJECT += libTFTP.a::iptftps.o
}
Library libTFTP.a {
	MODULES libTFTP.a::iptftpc.o libTFTP.a::iptftpc_cmd_tftp.o libTFTP.a::iptftp_common.o libTFTP.a::iptftps.o
}
