Symbol .TOC. {
}
Symbol ipsntp {
}
Symbol ipcom_tmo_cancel {
}
Symbol ipcom_tmo_request {
}
Symbol ipsntp_clock_gettime {
}
Symbol ipsntp_clock_settime {
}
Symbol ipsntp_client_fraction_to_nsec {
}
Symbol ipsntp_server_nsec_to_fraction {
}
Symbol memset {
}
Symbol ipcom_sendto_usr {
}
Symbol memcpy {
}
Symbol ipcom_setsockopt_usr {
}
Symbol ipcom_syslog {
}
Symbol ipcom_if_indextoname {
}
Symbol strncpy {
}
Symbol ipcom_socketioctl_usr {
}
Symbol ipcom_errno_get {
}
Symbol printf {
}
Symbol ipcom_sendmsg_usr {
}
Symbol memcmp {
}
Symbol ip_in6addr_any {
}
Symbol malloc {
}
Symbol free {
}
Symbol ipcom_recvmsg_usr {
}
Symbol ipcom_socket_usr {
}
Symbol ipcom_socketclose_usr {
}
Symbol strcmp {
}
Symbol ipcom_if_nametoindex {
}
Symbol ipcom_sysvar_get {
}
Symbol strlen {
}
Symbol ipcom_inet_pton {
}
Symbol ipcom_bind_usr {
}
Symbol strchr {
}
Symbol isdigit {
}
Symbol atoi {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol ipsntp_check_leap_second {
}
Symbol ipsntp_add_leapsecond {
}
Symbol ipsntp_leapsecond_timer_settime {
}
Symbol ipcom_fopen {
}
Symbol fgets {
}
Symbol strncmp {
}
Symbol strrchr {
}
Symbol strtok_r {
}
Symbol strtoul {
}
Symbol ipcom_fclose {
}
Symbol ipcom_ipd_init {
}
Symbol ipsntp_leapsecond_timer_init {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_ipd_input {
}
Symbol ipsntp_leapsecond_timer_destroy {
}
Symbol ipcom_ipd_exit {
}
Symbol ipcom_proc_init {
}
Symbol ipcom_proc_exit {
}
Symbol ipsntp_register_server_time_hook {
}
Symbol ipsntp_set_reference {
}
Symbol ipsntp_set_precision {
}
Symbol ipsntp_wait_time_ex {
}
Symbol ipsntp_wait_time {
}
Symbol ipsntp_query_time_ex {
}
Symbol ipcom_getaddrinfo {
}
Symbol ipcom_freeaddrinfo {
}
Symbol ipsntp_query_time {
}
Symbol ipsntp_create {
}
Symbol ipsntp_start {
}
Symbol ipcom_proc_attr_init {
}
Symbol ipcom_priority_map {
}
Symbol ipcom_proc_acreate_v1 {
}
Symbol ipsntp_version {
}
Symbol ipsntp_cmd_sntp {
}
Symbol ipcom_getopt_clear {
}
Symbol ipcom_getopt_data {
}
Symbol ipcom_getopt {
}
Symbol strcpy {
}
Symbol ctime {
}
Symbol clock_gettime {
}
Symbol clock_settime {
}
Symbol timer_create {
}
Symbol timer_connect {
}
Symbol timer_delete {
}
Symbol timer_settime {
}
ObjectFile libSNTP.a::ipsntp.o {
	NAME Object file ipsntp.o from archive libSNTP.a
	EXPORTS ipsntp_client_fraction_to_nsec ipsntp_server_nsec_to_fraction ipsntp_check_leap_second ipsntp_add_leapsecond ipsntp_register_server_time_hook ipsntp_set_reference ipsntp_set_precision ipsntp_wait_time_ex ipsntp_wait_time ipsntp_query_time_ex ipsntp_query_time ipsntp_create ipsntp_start ipsntp_version
	IMPORTS .TOC. ipcom_tmo_cancel ipcom_tmo_request ipsntp_clock_gettime ipsntp_clock_settime memset ipcom_sendto_usr memcpy ipcom_setsockopt_usr ipcom_syslog ipcom_if_indextoname strncpy ipcom_socketioctl_usr ipcom_errno_get printf ipcom_sendmsg_usr memcmp ip_in6addr_any malloc free ipcom_recvmsg_usr ipcom_socket_usr ipcom_socketclose_usr strcmp ipcom_if_nametoindex ipcom_sysvar_get strlen ipcom_inet_pton ipcom_bind_usr strchr isdigit atoi ipcom_sysvar_get_as_int ipsntp_leapsecond_timer_settime ipcom_fopen fgets strncmp strrchr strtok_r strtoul ipcom_fclose ipcom_ipd_init ipsntp_leapsecond_timer_init ipcom_socketselect_usr ipcom_ipd_input ipsntp_leapsecond_timer_destroy ipcom_ipd_exit ipcom_proc_init ipcom_proc_exit ipcom_getaddrinfo ipcom_freeaddrinfo ipcom_proc_attr_init ipcom_priority_map ipcom_proc_acreate_v1
	DECLARES ipsntp
	USES 
}
Module ipsntp.o {
	OBJECT += libSNTP.a::ipsntp.o
}
ObjectFile libSNTP.a::ipsntp_cmd_sntp.o {
	NAME Object file ipsntp_cmd_sntp.o from archive libSNTP.a
	EXPORTS ipsntp_cmd_sntp
	IMPORTS .TOC. printf ipcom_getopt_clear ipcom_getopt_data ipcom_getopt ipsntp_version strlen strcpy atoi ipsntp_wait_time ipsntp_query_time ctime ipsntp_clock_settime
	DECLARES 
	USES 
}
Module ipsntp_cmd_sntp.o {
	OBJECT += libSNTP.a::ipsntp_cmd_sntp.o
}
ObjectFile libSNTP.a::ipsntp_time.o {
	NAME Object file ipsntp_time.o from archive libSNTP.a
	EXPORTS ipsntp_clock_gettime ipsntp_clock_settime ipsntp_leapsecond_timer_init ipsntp_leapsecond_timer_destroy ipsntp_leapsecond_timer_settime
	IMPORTS .TOC. clock_gettime clock_settime timer_create ipsntp_check_leap_second timer_connect timer_delete ipsntp_add_leapsecond timer_settime
	DECLARES 
	USES 
}
Module ipsntp_time.o {
	OBJECT += libSNTP.a::ipsntp_time.o
}
Library libSNTP.a {
	MODULES libSNTP.a::ipsntp.o libSNTP.a::ipsntp_cmd_sntp.o libSNTP.a::ipsntp_time.o
}
Symbol .TOC. {
}
Symbol ipsntp {
}
Symbol ipcom_tmo_cancel {
}
Symbol ipcom_tmo_request {
}
Symbol ipsntp_clock_gettime {
}
Symbol ipsntp_clock_settime {
}
Symbol ipsntp_client_fraction_to_nsec {
}
Symbol ipsntp_server_nsec_to_fraction {
}
Symbol memset {
}
Symbol ipcom_sendto_usr {
}
Symbol memcpy {
}
Symbol ipcom_setsockopt_usr {
}
Symbol ipcom_syslog {
}
Symbol ipcom_if_indextoname {
}
Symbol strncpy {
}
Symbol ipcom_socketioctl_usr {
}
Symbol ipcom_errno_get {
}
Symbol printf {
}
Symbol ipcom_sendmsg_usr {
}
Symbol memcmp {
}
Symbol ip_in6addr_any {
}
Symbol malloc {
}
Symbol free {
}
Symbol ipcom_recvmsg_usr {
}
Symbol ipcom_socket_usr {
}
Symbol ipcom_socketclose_usr {
}
Symbol strcmp {
}
Symbol ipcom_if_nametoindex {
}
Symbol ipcom_sysvar_get {
}
Symbol strlen {
}
Symbol ipcom_inet_pton {
}
Symbol ipcom_bind_usr {
}
Symbol strchr {
}
Symbol isdigit {
}
Symbol atoi {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol ipsntp_check_leap_second {
}
Symbol ipsntp_add_leapsecond {
}
Symbol ipsntp_leapsecond_timer_settime {
}
Symbol ipcom_fopen {
}
Symbol fgets {
}
Symbol strncmp {
}
Symbol strrchr {
}
Symbol strtok_r {
}
Symbol strtoul {
}
Symbol ipcom_fclose {
}
Symbol ipcom_ipd_init {
}
Symbol ipsntp_leapsecond_timer_init {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_ipd_input {
}
Symbol ipsntp_leapsecond_timer_destroy {
}
Symbol ipcom_ipd_exit {
}
Symbol ipcom_proc_init {
}
Symbol ipcom_proc_exit {
}
Symbol ipsntp_register_server_time_hook {
}
Symbol ipsntp_set_reference {
}
Symbol ipsntp_set_precision {
}
Symbol ipsntp_wait_time_ex {
}
Symbol ipsntp_wait_time {
}
Symbol ipsntp_query_time_ex {
}
Symbol ipcom_getaddrinfo {
}
Symbol ipcom_freeaddrinfo {
}
Symbol ipsntp_query_time {
}
Symbol ipsntp_create {
}
Symbol ipsntp_start {
}
Symbol ipcom_proc_attr_init {
}
Symbol ipcom_priority_map {
}
Symbol ipcom_proc_acreate_v1 {
}
Symbol ipsntp_version {
}
Symbol ipsntp_cmd_sntp {
}
Symbol ipcom_getopt_clear {
}
Symbol ipcom_getopt_data {
}
Symbol ipcom_getopt {
}
Symbol strcpy {
}
Symbol ctime {
}
Symbol clock_gettime {
}
Symbol clock_settime {
}
Symbol timer_create {
}
Symbol timer_connect {
}
Symbol timer_delete {
}
Symbol timer_settime {
}
ObjectFile libSNTP.a::ipsntp.o {
	NAME Object file ipsntp.o from archive libSNTP.a
	EXPORTS ipsntp_client_fraction_to_nsec ipsntp_server_nsec_to_fraction ipsntp_check_leap_second ipsntp_add_leapsecond ipsntp_register_server_time_hook ipsntp_set_reference ipsntp_set_precision ipsntp_wait_time_ex ipsntp_wait_time ipsntp_query_time_ex ipsntp_query_time ipsntp_create ipsntp_start ipsntp_version
	IMPORTS .TOC. ipcom_tmo_cancel ipcom_tmo_request ipsntp_clock_gettime ipsntp_clock_settime memset ipcom_sendto_usr memcpy ipcom_setsockopt_usr ipcom_syslog ipcom_if_indextoname strncpy ipcom_socketioctl_usr ipcom_errno_get printf ipcom_sendmsg_usr memcmp ip_in6addr_any malloc free ipcom_recvmsg_usr ipcom_socket_usr ipcom_socketclose_usr strcmp ipcom_if_nametoindex ipcom_sysvar_get strlen ipcom_inet_pton ipcom_bind_usr strchr isdigit atoi ipcom_sysvar_get_as_int ipsntp_leapsecond_timer_settime ipcom_fopen fgets strncmp strrchr strtok_r strtoul ipcom_fclose ipcom_ipd_init ipsntp_leapsecond_timer_init ipcom_socketselect_usr ipcom_ipd_input ipsntp_leapsecond_timer_destroy ipcom_ipd_exit ipcom_proc_init ipcom_proc_exit ipcom_getaddrinfo ipcom_freeaddrinfo ipcom_proc_attr_init ipcom_priority_map ipcom_proc_acreate_v1
	DECLARES ipsntp
	USES 
}
Module ipsntp.o {
	OBJECT += libSNTP.a::ipsntp.o
}
ObjectFile libSNTP.a::ipsntp_cmd_sntp.o {
	NAME Object file ipsntp_cmd_sntp.o from archive libSNTP.a
	EXPORTS ipsntp_cmd_sntp
	IMPORTS .TOC. printf ipcom_getopt_clear ipcom_getopt_data ipcom_getopt ipsntp_version strlen strcpy atoi ipsntp_wait_time ipsntp_query_time ctime ipsntp_clock_settime
	DECLARES 
	USES 
}
Module ipsntp_cmd_sntp.o {
	OBJECT += libSNTP.a::ipsntp_cmd_sntp.o
}
ObjectFile libSNTP.a::ipsntp_time.o {
	NAME Object file ipsntp_time.o from archive libSNTP.a
	EXPORTS ipsntp_clock_gettime ipsntp_clock_settime ipsntp_leapsecond_timer_init ipsntp_leapsecond_timer_destroy ipsntp_leapsecond_timer_settime
	IMPORTS .TOC. clock_gettime clock_settime timer_create ipsntp_check_leap_second timer_connect timer_delete ipsntp_add_leapsecond timer_settime
	DECLARES 
	USES 
}
Module ipsntp_time.o {
	OBJECT += libSNTP.a::ipsntp_time.o
}
Library libSNTP.a {
	MODULES libSNTP.a::ipsntp.o libSNTP.a::ipsntp_cmd_sntp.o libSNTP.a::ipsntp_time.o
}
Symbol .TOC. {
}
Symbol ipsntp {
}
Symbol ipcom_tmo_cancel {
}
Symbol ipcom_tmo_request {
}
Symbol ipsntp_clock_gettime {
}
Symbol ipsntp_clock_settime {
}
Symbol ipsntp_client_fraction_to_nsec {
}
Symbol ipsntp_server_nsec_to_fraction {
}
Symbol memset {
}
Symbol ipcom_sendto_usr {
}
Symbol memcpy {
}
Symbol ipcom_setsockopt_usr {
}
Symbol ipcom_syslog {
}
Symbol ipcom_if_indextoname {
}
Symbol strncpy {
}
Symbol ipcom_socketioctl_usr {
}
Symbol ipcom_errno_get {
}
Symbol printf {
}
Symbol ipcom_sendmsg_usr {
}
Symbol memcmp {
}
Symbol ip_in6addr_any {
}
Symbol malloc {
}
Symbol free {
}
Symbol ipcom_recvmsg_usr {
}
Symbol ipcom_socket_usr {
}
Symbol ipcom_socketclose_usr {
}
Symbol strcmp {
}
Symbol ipcom_if_nametoindex {
}
Symbol ipcom_sysvar_get {
}
Symbol strlen {
}
Symbol ipcom_inet_pton {
}
Symbol ipcom_bind_usr {
}
Symbol strchr {
}
Symbol isdigit {
}
Symbol atoi {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol ipsntp_check_leap_second {
}
Symbol ipsntp_add_leapsecond {
}
Symbol ipsntp_leapsecond_timer_settime {
}
Symbol ipcom_fopen {
}
Symbol fgets {
}
Symbol strncmp {
}
Symbol strrchr {
}
Symbol strtok_r {
}
Symbol strtoul {
}
Symbol ipcom_fclose {
}
Symbol ipcom_ipd_init {
}
Symbol ipsntp_leapsecond_timer_init {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_ipd_input {
}
Symbol ipsntp_leapsecond_timer_destroy {
}
Symbol ipcom_ipd_exit {
}
Symbol ipcom_proc_init {
}
Symbol ipcom_proc_exit {
}
Symbol ipsntp_register_server_time_hook {
}
Symbol ipsntp_set_reference {
}
Symbol ipsntp_set_precision {
}
Symbol ipsntp_wait_time_ex {
}
Symbol ipsntp_wait_time {
}
Symbol ipsntp_query_time_ex {
}
Symbol ipcom_getaddrinfo {
}
Symbol ipcom_freeaddrinfo {
}
Symbol ipsntp_query_time {
}
Symbol ipsntp_create {
}
Symbol ipsntp_start {
}
Symbol ipcom_proc_attr_init {
}
Symbol ipcom_priority_map {
}
Symbol ipcom_proc_acreate_v1 {
}
Symbol ipsntp_version {
}
Symbol ipsntp_cmd_sntp {
}
Symbol ipcom_getopt_clear {
}
Symbol ipcom_getopt_data {
}
Symbol ipcom_getopt {
}
Symbol strcpy {
}
Symbol ctime {
}
Symbol clock_gettime {
}
Symbol clock_settime {
}
Symbol timer_create {
}
Symbol timer_connect {
}
Symbol timer_delete {
}
Symbol timer_settime {
}
ObjectFile libSNTP.a::ipsntp.o {
	NAME Object file ipsntp.o from archive libSNTP.a
	EXPORTS ipsntp_client_fraction_to_nsec ipsntp_server_nsec_to_fraction ipsntp_check_leap_second ipsntp_add_leapsecond ipsntp_register_server_time_hook ipsntp_set_reference ipsntp_set_precision ipsntp_wait_time_ex ipsntp_wait_time ipsntp_query_time_ex ipsntp_query_time ipsntp_create ipsntp_start ipsntp_version
	IMPORTS .TOC. ipcom_tmo_cancel ipcom_tmo_request ipsntp_clock_gettime ipsntp_clock_settime memset ipcom_sendto_usr memcpy ipcom_setsockopt_usr ipcom_syslog ipcom_if_indextoname strncpy ipcom_socketioctl_usr ipcom_errno_get printf ipcom_sendmsg_usr memcmp ip_in6addr_any malloc free ipcom_recvmsg_usr ipcom_socket_usr ipcom_socketclose_usr strcmp ipcom_if_nametoindex ipcom_sysvar_get strlen ipcom_inet_pton ipcom_bind_usr strchr isdigit atoi ipcom_sysvar_get_as_int ipsntp_leapsecond_timer_settime ipcom_fopen fgets strncmp strrchr strtok_r strtoul ipcom_fclose ipcom_ipd_init ipsntp_leapsecond_timer_init ipcom_socketselect_usr ipcom_ipd_input ipsntp_leapsecond_timer_destroy ipcom_ipd_exit ipcom_proc_init ipcom_proc_exit ipcom_getaddrinfo ipcom_freeaddrinfo ipcom_proc_attr_init ipcom_priority_map ipcom_proc_acreate_v1
	DECLARES ipsntp
	USES 
}
Module ipsntp.o {
	OBJECT += libSNTP.a::ipsntp.o
}
ObjectFile libSNTP.a::ipsntp_cmd_sntp.o {
	NAME Object file ipsntp_cmd_sntp.o from archive libSNTP.a
	EXPORTS ipsntp_cmd_sntp
	IMPORTS .TOC. printf ipcom_getopt_clear ipcom_getopt_data ipcom_getopt ipsntp_version strlen strcpy atoi ipsntp_wait_time ipsntp_query_time ctime ipsntp_clock_settime
	DECLARES 
	USES 
}
Module ipsntp_cmd_sntp.o {
	OBJECT += libSNTP.a::ipsntp_cmd_sntp.o
}
ObjectFile libSNTP.a::ipsntp_time.o {
	NAME Object file ipsntp_time.o from archive libSNTP.a
	EXPORTS ipsntp_clock_gettime ipsntp_clock_settime ipsntp_leapsecond_timer_init ipsntp_leapsecond_timer_destroy ipsntp_leapsecond_timer_settime
	IMPORTS .TOC. clock_gettime clock_settime timer_create ipsntp_check_leap_second timer_connect timer_delete ipsntp_add_leapsecond timer_settime
	DECLARES 
	USES 
}
Module ipsntp_time.o {
	OBJECT += libSNTP.a::ipsntp_time.o
}
Library libSNTP.a {
	MODULES libSNTP.a::ipsntp.o libSNTP.a::ipsntp_cmd_sntp.o libSNTP.a::ipsntp_time.o
}
