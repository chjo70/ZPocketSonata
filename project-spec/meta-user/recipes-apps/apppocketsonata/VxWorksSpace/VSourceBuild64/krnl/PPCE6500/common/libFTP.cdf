Symbol .TOC. {
}
Symbol ipcom_inet_ntop {
}
Symbol strcpy {
}
Symbol memset {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_socketwrite_usr {
}
Symbol ipcom_errno_get {
}
Symbol strerror {
}
Symbol ipcom_syslog {
}
Symbol ipcom_socketread_usr {
}
Symbol strspn {
}
Symbol strtol {
}
Symbol vsnprintf {
}
Symbol strcat {
}
Symbol ipcom_strncasecmp {
}
Symbol strchr {
}
Symbol strcspn {
}
Symbol ipcom_socketclose_usr {
}
Symbol memcpy {
}
Symbol ipcom_socket_usr {
}
Symbol ipcom_random {
}
Symbol ipcom_bind_usr {
}
Symbol ipcom_getsockname_usr {
}
Symbol ipcom_connect_usr {
}
Symbol ipcom_listen_usr {
}
Symbol ipcom_accept_usr {
}
Symbol memcmp {
}
Symbol ipcom_filewrite {
}
Symbol ipftpc_exit {
}
Symbol ipcom_mutex_lock {
}
Symbol ipcom_mutex_unlock {
}
Symbol ipcom_mutex_delete {
}
Symbol ipftpc_open {
}
Symbol malloc {
}
Symbol ipcom_sysvar_get {
}
Symbol ipcom_inet_pton {
}
Symbol free {
}
Symbol ipftpc_close {
}
Symbol ipftpc_getattr {
}
Symbol ipftpc_setattr {
}
Symbol ipftpc_cmd {
}
Symbol ipftpc_login {
}
Symbol ipftpc_list {
}
Symbol ipftpc_get {
}
Symbol ipcom_unlink {
}
Symbol ipcom_fileopen {
}
Symbol ipcom_fstat {
}
Symbol ipcom_fileclose {
}
Symbol ipftpc_put {
}
Symbol ipcom_fileread {
}
Symbol ipftpc_lastreply {
}
Symbol ipftpc_strclass {
}
Symbol ipftpc_strerror {
}
Symbol ipftpc_create {
}
Symbol ipcom_mutex_create {
}
Symbol ipftpc_start {
}
Symbol ipftpc_version {
}
Symbol printf {
}
Symbol strlen {
}
Symbol strncmp {
}
Symbol ipcom_getcwd {
}
Symbol ipcom_chdir {
}
Symbol ipcom_getsockaddrbyaddr {
}
Symbol ipcom_getaddrinfo {
}
Symbol ipcom_freeaddrinfo {
}
Symbol strdup {
}
Symbol ipcom_stdout {
}
Symbol ipcom_fflush {
}
Symbol ipcom_getline {
}
Symbol memset_s {
}
Symbol ipftpc_cmd_main {
}
Symbol ipcom_getline_init {
}
Symbol ipcom_getopt_clear_r {
}
Symbol ipcom_getopt_r {
}
Symbol ipcom_getline_exit {
}
Symbol strcmp {
}
Symbol opendir {
}
Symbol closedir {
}
Symbol pathCat {
}
Symbol pathCondense {
}
Symbol iosDevFind {
}
Symbol atoi {
}
Symbol ipcom_stat {
}
Symbol time {
}
Symbol localtime_r {
}
Symbol strftime {
}
Symbol ipcom_setsockopt_usr {
}
Symbol strstr {
}
Symbol ipcom_strcasecmp {
}
Symbol ipcom_opendir {
}
Symbol ipcom_readdir {
}
Symbol ipcom_closedir {
}
Symbol ipcom_mkdir {
}
Symbol toupper {
}
Symbol strrchr {
}
Symbol snprintf {
}
Symbol ipftps_authenticate {
}
Symbol ipcom_sleep {
}
Symbol ipcom_rmdir {
}
Symbol ipcom_access {
}
Symbol ipcom_rename {
}
Symbol systemSecurityIsEnabled {
}
Symbol ipftps_get_activesession {
}
Symbol ipftps_session {
}
Symbol ipcom_proc_init {
}
Symbol ipcom_ipc_open {
}
Symbol ipcom_ipc_malloc {
}
Symbol ipcom_ipc_send {
}
Symbol ipcom_ipc_free {
}
Symbol ipcom_ipc_receive {
}
Symbol ipcom_ipc_close {
}
Symbol ipcom_auth_logout {
}
Symbol ipcom_ipc_isopen {
}
Symbol ipcom_proc_exit {
}
Symbol ipftps_main {
}
Symbol ipcom_once {
}
Symbol ipcom_ipc_install {
}
Symbol ipcom_ipd_init {
}
Symbol ipcom_proc_attr_init {
}
Symbol ipcom_priority_map {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol ipcom_ipd_input {
}
Symbol sprintf {
}
Symbol ipcom_proc_acreate_v1 {
}
Symbol ipcom_ipd_exit {
}
Symbol ipcom_ipc_uninstall {
}
Symbol ipftps_create {
}
Symbol ipftps_start {
}
Symbol ipftps_version {
}
ObjectFile libFTP.a::ipftpc.o {
	NAME Object file ipftpc.o from archive libFTP.a
	EXPORTS ipftpc_exit ipftpc_open ipftpc_close ipftpc_getattr ipftpc_setattr ipftpc_cmd ipftpc_login ipftpc_list ipftpc_get ipftpc_put ipftpc_lastreply ipftpc_strclass ipftpc_strerror ipftpc_create ipftpc_start ipftpc_version
	IMPORTS .TOC. ipcom_inet_ntop strcpy memset ipcom_socketselect_usr ipcom_socketwrite_usr ipcom_errno_get strerror ipcom_syslog ipcom_socketread_usr strspn strtol vsnprintf strcat ipcom_strncasecmp strchr strcspn ipcom_socketclose_usr memcpy ipcom_socket_usr ipcom_random ipcom_bind_usr ipcom_getsockname_usr ipcom_connect_usr ipcom_listen_usr ipcom_accept_usr memcmp ipcom_filewrite ipcom_mutex_lock ipcom_mutex_unlock ipcom_mutex_delete malloc ipcom_sysvar_get ipcom_inet_pton free ipcom_unlink ipcom_fileopen ipcom_fstat ipcom_fileclose ipcom_fileread ipcom_mutex_create
	DECLARES 
	USES 
}
Module ipftpc.o {
	OBJECT += libFTP.a::ipftpc.o
}
ObjectFile libFTP.a::ipftpc_cmd_ftp.o {
	NAME Object file ipftpc_cmd_ftp.o from archive libFTP.a
	EXPORTS ipftpc_cmd_main
	IMPORTS .TOC. printf strtol ipftpc_lastreply ipftpc_strerror ipftpc_strclass ipftpc_close free ipftpc_setattr ipftpc_put ipftpc_cmd ipftpc_list ipftpc_get strlen strncmp malloc ipcom_getcwd ipcom_chdir memset ipcom_getsockaddrbyaddr ipcom_getaddrinfo memcpy ipcom_freeaddrinfo ipftpc_open strdup ipcom_stdout ipcom_fflush ipcom_getline ipftpc_login memset_s strspn strcspn ipcom_getline_init ipcom_getopt_clear_r ipcom_getopt_r ipcom_getline_exit
	DECLARES 
	USES 
}
Module ipftpc_cmd_ftp.o {
	OBJECT += libFTP.a::ipftpc_cmd_ftp.o
}
ObjectFile libFTP.a::ipftps.o {
	NAME Object file ipftps.o from archive libFTP.a
	EXPORTS ipftps_get_activesession ipftps_session ipftps_main ipftps_create ipftps_start ipftps_version
	IMPORTS .TOC. ipcom_mutex_create memcpy ipcom_filewrite ipcom_socketwrite_usr strcspn strspn strcmp strlen strchr opendir closedir malloc pathCat strcpy pathCondense strcat iosDevFind free ipcom_syslog ipcom_errno_get ipcom_sysvar_get atoi strdup strerror vsnprintf ipcom_stat memset time localtime_r strftime ipcom_socketclose_usr ipcom_inet_ntop ipcom_socketselect_usr ipcom_accept_usr memcmp ipcom_socket_usr ipcom_setsockopt_usr ipcom_random ipcom_bind_usr ipcom_listen_usr ipcom_getsockname_usr ipcom_connect_usr ipcom_socketread_usr strstr ipcom_unlink ipcom_fileopen ipcom_fstat ipcom_fileclose strtol ipcom_inet_pton ipcom_strcasecmp strncmp ipcom_opendir ipcom_mutex_lock ipcom_readdir ipcom_closedir ipcom_mutex_unlock ipcom_mkdir toupper strrchr snprintf ipftps_authenticate ipcom_sleep memset_s ipcom_fileread ipcom_rmdir ipcom_access ipcom_rename systemSecurityIsEnabled ipcom_strncasecmp ipcom_proc_init ipcom_ipc_open ipcom_ipc_malloc ipcom_ipc_send ipcom_ipc_free ipcom_ipc_receive ipcom_ipc_close ipcom_auth_logout ipcom_ipc_isopen ipcom_proc_exit ipcom_once ipcom_ipc_install ipcom_ipd_init ipcom_proc_attr_init ipcom_priority_map ipcom_sysvar_get_as_int ipcom_ipd_input sprintf ipcom_proc_acreate_v1 ipcom_ipd_exit ipcom_ipc_uninstall
	DECLARES 
	USES 
}
Module ipftps.o {
	OBJECT += libFTP.a::ipftps.o
}
ObjectFile libFTP.a::ipftps_tls.o {
	NAME Object file ipftps_tls.o from archive libFTP.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module ipftps_tls.o {
	OBJECT += libFTP.a::ipftps_tls.o
}
Library libFTP.a {
	MODULES libFTP.a::ipftpc.o libFTP.a::ipftpc_cmd_ftp.o libFTP.a::ipftps.o libFTP.a::ipftps_tls.o
}
Symbol .TOC. {
}
Symbol ipcom_inet_ntop {
}
Symbol strcpy {
}
Symbol memset {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_socketwrite_usr {
}
Symbol ipcom_errno_get {
}
Symbol strerror {
}
Symbol ipcom_syslog {
}
Symbol ipcom_socketread_usr {
}
Symbol strspn {
}
Symbol strtol {
}
Symbol vsnprintf {
}
Symbol strcat {
}
Symbol ipcom_strncasecmp {
}
Symbol strchr {
}
Symbol strcspn {
}
Symbol ipcom_socketclose_usr {
}
Symbol memcpy {
}
Symbol ipcom_socket_usr {
}
Symbol ipcom_random {
}
Symbol ipcom_bind_usr {
}
Symbol ipcom_getsockname_usr {
}
Symbol ipcom_connect_usr {
}
Symbol ipcom_listen_usr {
}
Symbol ipcom_accept_usr {
}
Symbol memcmp {
}
Symbol ipcom_filewrite {
}
Symbol ipftpc_exit {
}
Symbol ipcom_mutex_lock {
}
Symbol ipcom_mutex_unlock {
}
Symbol ipcom_mutex_delete {
}
Symbol ipftpc_open {
}
Symbol malloc {
}
Symbol ipcom_sysvar_get {
}
Symbol ipcom_inet_pton {
}
Symbol free {
}
Symbol ipftpc_close {
}
Symbol ipftpc_getattr {
}
Symbol ipftpc_setattr {
}
Symbol ipftpc_cmd {
}
Symbol ipftpc_login {
}
Symbol ipftpc_list {
}
Symbol ipftpc_get {
}
Symbol ipcom_unlink {
}
Symbol ipcom_fileopen {
}
Symbol ipcom_fstat {
}
Symbol ipcom_fileclose {
}
Symbol ipftpc_put {
}
Symbol ipcom_fileread {
}
Symbol ipftpc_lastreply {
}
Symbol ipftpc_strclass {
}
Symbol ipftpc_strerror {
}
Symbol ipftpc_create {
}
Symbol ipcom_mutex_create {
}
Symbol ipftpc_start {
}
Symbol ipftpc_version {
}
Symbol printf {
}
Symbol strlen {
}
Symbol strncmp {
}
Symbol ipcom_getcwd {
}
Symbol ipcom_chdir {
}
Symbol ipcom_getsockaddrbyaddr {
}
Symbol ipcom_getaddrinfo {
}
Symbol ipcom_freeaddrinfo {
}
Symbol strdup {
}
Symbol ipcom_stdout {
}
Symbol ipcom_fflush {
}
Symbol ipcom_getline {
}
Symbol memset_s {
}
Symbol ipftpc_cmd_main {
}
Symbol ipcom_getline_init {
}
Symbol ipcom_getopt_clear_r {
}
Symbol ipcom_getopt_r {
}
Symbol ipcom_getline_exit {
}
Symbol strcmp {
}
Symbol opendir {
}
Symbol closedir {
}
Symbol pathCat {
}
Symbol pathCondense {
}
Symbol iosDevFind {
}
Symbol atoi {
}
Symbol ipcom_stat {
}
Symbol time {
}
Symbol localtime_r {
}
Symbol strftime {
}
Symbol ipcom_setsockopt_usr {
}
Symbol strstr {
}
Symbol ipcom_strcasecmp {
}
Symbol ipcom_opendir {
}
Symbol ipcom_readdir {
}
Symbol ipcom_closedir {
}
Symbol ipcom_mkdir {
}
Symbol toupper {
}
Symbol strrchr {
}
Symbol snprintf {
}
Symbol ipftps_authenticate {
}
Symbol ipcom_sleep {
}
Symbol ipcom_rmdir {
}
Symbol ipcom_access {
}
Symbol ipcom_rename {
}
Symbol systemSecurityIsEnabled {
}
Symbol ipftps_get_activesession {
}
Symbol ipftps_session {
}
Symbol ipcom_proc_init {
}
Symbol ipcom_ipc_open {
}
Symbol ipcom_ipc_malloc {
}
Symbol ipcom_ipc_send {
}
Symbol ipcom_ipc_free {
}
Symbol ipcom_ipc_receive {
}
Symbol ipcom_ipc_close {
}
Symbol ipcom_auth_logout {
}
Symbol ipcom_ipc_isopen {
}
Symbol ipcom_proc_exit {
}
Symbol ipftps_main {
}
Symbol ipcom_once {
}
Symbol ipcom_ipc_install {
}
Symbol ipcom_ipd_init {
}
Symbol ipcom_proc_attr_init {
}
Symbol ipcom_priority_map {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol ipcom_ipd_input {
}
Symbol sprintf {
}
Symbol ipcom_proc_acreate_v1 {
}
Symbol ipcom_ipd_exit {
}
Symbol ipcom_ipc_uninstall {
}
Symbol ipftps_create {
}
Symbol ipftps_start {
}
Symbol ipftps_version {
}
ObjectFile libFTP.a::ipftpc.o {
	NAME Object file ipftpc.o from archive libFTP.a
	EXPORTS ipftpc_exit ipftpc_open ipftpc_close ipftpc_getattr ipftpc_setattr ipftpc_cmd ipftpc_login ipftpc_list ipftpc_get ipftpc_put ipftpc_lastreply ipftpc_strclass ipftpc_strerror ipftpc_create ipftpc_start ipftpc_version
	IMPORTS .TOC. ipcom_inet_ntop strcpy memset ipcom_socketselect_usr ipcom_socketwrite_usr ipcom_errno_get strerror ipcom_syslog ipcom_socketread_usr strspn strtol vsnprintf strcat ipcom_strncasecmp strchr strcspn ipcom_socketclose_usr memcpy ipcom_socket_usr ipcom_random ipcom_bind_usr ipcom_getsockname_usr ipcom_connect_usr ipcom_listen_usr ipcom_accept_usr memcmp ipcom_filewrite ipcom_mutex_lock ipcom_mutex_unlock ipcom_mutex_delete malloc ipcom_sysvar_get ipcom_inet_pton free ipcom_unlink ipcom_fileopen ipcom_fstat ipcom_fileclose ipcom_fileread ipcom_mutex_create
	DECLARES 
	USES 
}
Module ipftpc.o {
	OBJECT += libFTP.a::ipftpc.o
}
ObjectFile libFTP.a::ipftpc_cmd_ftp.o {
	NAME Object file ipftpc_cmd_ftp.o from archive libFTP.a
	EXPORTS ipftpc_cmd_main
	IMPORTS .TOC. printf strtol ipftpc_lastreply ipftpc_strerror ipftpc_strclass ipftpc_close free ipftpc_setattr ipftpc_put ipftpc_cmd ipftpc_list ipftpc_get strlen strncmp malloc ipcom_getcwd ipcom_chdir memset ipcom_getsockaddrbyaddr ipcom_getaddrinfo memcpy ipcom_freeaddrinfo ipftpc_open strdup ipcom_stdout ipcom_fflush ipcom_getline ipftpc_login memset_s strspn strcspn ipcom_getline_init ipcom_getopt_clear_r ipcom_getopt_r ipcom_getline_exit
	DECLARES 
	USES 
}
Module ipftpc_cmd_ftp.o {
	OBJECT += libFTP.a::ipftpc_cmd_ftp.o
}
ObjectFile libFTP.a::ipftps.o {
	NAME Object file ipftps.o from archive libFTP.a
	EXPORTS ipftps_get_activesession ipftps_session ipftps_main ipftps_create ipftps_start ipftps_version
	IMPORTS .TOC. ipcom_mutex_create memcpy ipcom_filewrite ipcom_socketwrite_usr strcspn strspn strcmp strlen strchr opendir closedir malloc pathCat strcpy pathCondense strcat iosDevFind free ipcom_syslog ipcom_errno_get ipcom_sysvar_get atoi strdup strerror vsnprintf ipcom_stat memset time localtime_r strftime ipcom_socketclose_usr ipcom_inet_ntop ipcom_socketselect_usr ipcom_accept_usr memcmp ipcom_socket_usr ipcom_setsockopt_usr ipcom_random ipcom_bind_usr ipcom_listen_usr ipcom_getsockname_usr ipcom_connect_usr ipcom_socketread_usr strstr ipcom_unlink ipcom_fileopen ipcom_fstat ipcom_fileclose strtol ipcom_inet_pton ipcom_strcasecmp strncmp ipcom_opendir ipcom_mutex_lock ipcom_readdir ipcom_closedir ipcom_mutex_unlock ipcom_mkdir toupper strrchr snprintf ipftps_authenticate ipcom_sleep memset_s ipcom_fileread ipcom_rmdir ipcom_access ipcom_rename systemSecurityIsEnabled ipcom_strncasecmp ipcom_proc_init ipcom_ipc_open ipcom_ipc_malloc ipcom_ipc_send ipcom_ipc_free ipcom_ipc_receive ipcom_ipc_close ipcom_auth_logout ipcom_ipc_isopen ipcom_proc_exit ipcom_once ipcom_ipc_install ipcom_ipd_init ipcom_proc_attr_init ipcom_priority_map ipcom_sysvar_get_as_int ipcom_ipd_input sprintf ipcom_proc_acreate_v1 ipcom_ipd_exit ipcom_ipc_uninstall
	DECLARES 
	USES 
}
Module ipftps.o {
	OBJECT += libFTP.a::ipftps.o
}
ObjectFile libFTP.a::ipftps_tls.o {
	NAME Object file ipftps_tls.o from archive libFTP.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module ipftps_tls.o {
	OBJECT += libFTP.a::ipftps_tls.o
}
Library libFTP.a {
	MODULES libFTP.a::ipftpc.o libFTP.a::ipftpc_cmd_ftp.o libFTP.a::ipftps.o libFTP.a::ipftps_tls.o
}
Symbol .TOC. {
}
Symbol ipcom_inet_ntop {
}
Symbol strcpy {
}
Symbol memset {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_socketwrite_usr {
}
Symbol ipcom_errno_get {
}
Symbol strerror {
}
Symbol ipcom_syslog {
}
Symbol ipcom_socketread_usr {
}
Symbol strspn {
}
Symbol strtol {
}
Symbol vsnprintf {
}
Symbol strcat {
}
Symbol ipcom_strncasecmp {
}
Symbol strchr {
}
Symbol strcspn {
}
Symbol ipcom_socketclose_usr {
}
Symbol memcpy {
}
Symbol ipcom_socket_usr {
}
Symbol ipcom_random {
}
Symbol ipcom_bind_usr {
}
Symbol ipcom_getsockname_usr {
}
Symbol ipcom_connect_usr {
}
Symbol ipcom_listen_usr {
}
Symbol ipcom_accept_usr {
}
Symbol memcmp {
}
Symbol ipcom_filewrite {
}
Symbol ipftpc_exit {
}
Symbol ipcom_mutex_lock {
}
Symbol ipcom_mutex_unlock {
}
Symbol ipcom_mutex_delete {
}
Symbol ipftpc_open {
}
Symbol malloc {
}
Symbol ipcom_sysvar_get {
}
Symbol ipcom_inet_pton {
}
Symbol free {
}
Symbol ipftpc_close {
}
Symbol ipftpc_getattr {
}
Symbol ipftpc_setattr {
}
Symbol ipftpc_cmd {
}
Symbol ipftpc_login {
}
Symbol ipftpc_list {
}
Symbol ipftpc_get {
}
Symbol ipcom_unlink {
}
Symbol ipcom_fileopen {
}
Symbol ipcom_fstat {
}
Symbol ipcom_fileclose {
}
Symbol ipftpc_put {
}
Symbol ipcom_fileread {
}
Symbol ipftpc_lastreply {
}
Symbol ipftpc_strclass {
}
Symbol ipftpc_strerror {
}
Symbol ipftpc_create {
}
Symbol ipcom_mutex_create {
}
Symbol ipftpc_start {
}
Symbol ipftpc_version {
}
Symbol printf {
}
Symbol strlen {
}
Symbol strncmp {
}
Symbol ipcom_getcwd {
}
Symbol ipcom_chdir {
}
Symbol ipcom_getsockaddrbyaddr {
}
Symbol ipcom_getaddrinfo {
}
Symbol ipcom_freeaddrinfo {
}
Symbol strdup {
}
Symbol ipcom_stdout {
}
Symbol ipcom_fflush {
}
Symbol ipcom_getline {
}
Symbol memset_s {
}
Symbol ipftpc_cmd_main {
}
Symbol ipcom_getline_init {
}
Symbol ipcom_getopt_clear_r {
}
Symbol ipcom_getopt_r {
}
Symbol ipcom_getline_exit {
}
Symbol strcmp {
}
Symbol opendir {
}
Symbol closedir {
}
Symbol pathCat {
}
Symbol pathCondense {
}
Symbol iosDevFind {
}
Symbol atoi {
}
Symbol ipcom_stat {
}
Symbol time {
}
Symbol localtime_r {
}
Symbol strftime {
}
Symbol ipcom_setsockopt_usr {
}
Symbol strstr {
}
Symbol ipcom_strcasecmp {
}
Symbol ipcom_opendir {
}
Symbol ipcom_readdir {
}
Symbol ipcom_closedir {
}
Symbol ipcom_mkdir {
}
Symbol toupper {
}
Symbol strrchr {
}
Symbol snprintf {
}
Symbol ipftps_authenticate {
}
Symbol ipcom_sleep {
}
Symbol ipcom_rmdir {
}
Symbol ipcom_access {
}
Symbol ipcom_rename {
}
Symbol systemSecurityIsEnabled {
}
Symbol ipftps_get_activesession {
}
Symbol ipftps_session {
}
Symbol ipcom_proc_init {
}
Symbol ipcom_ipc_open {
}
Symbol ipcom_ipc_malloc {
}
Symbol ipcom_ipc_send {
}
Symbol ipcom_ipc_free {
}
Symbol ipcom_ipc_receive {
}
Symbol ipcom_ipc_close {
}
Symbol ipcom_auth_logout {
}
Symbol ipcom_ipc_isopen {
}
Symbol ipcom_proc_exit {
}
Symbol ipftps_main {
}
Symbol ipcom_once {
}
Symbol ipcom_ipc_install {
}
Symbol ipcom_ipd_init {
}
Symbol ipcom_proc_attr_init {
}
Symbol ipcom_priority_map {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol ipcom_ipd_input {
}
Symbol sprintf {
}
Symbol ipcom_proc_acreate_v1 {
}
Symbol ipcom_ipd_exit {
}
Symbol ipcom_ipc_uninstall {
}
Symbol ipftps_create {
}
Symbol ipftps_start {
}
Symbol ipftps_version {
}
ObjectFile libFTP.a::ipftpc.o {
	NAME Object file ipftpc.o from archive libFTP.a
	EXPORTS ipftpc_exit ipftpc_open ipftpc_close ipftpc_getattr ipftpc_setattr ipftpc_cmd ipftpc_login ipftpc_list ipftpc_get ipftpc_put ipftpc_lastreply ipftpc_strclass ipftpc_strerror ipftpc_create ipftpc_start ipftpc_version
	IMPORTS .TOC. ipcom_inet_ntop strcpy memset ipcom_socketselect_usr ipcom_socketwrite_usr ipcom_errno_get strerror ipcom_syslog ipcom_socketread_usr strspn strtol vsnprintf strcat ipcom_strncasecmp strchr strcspn ipcom_socketclose_usr memcpy ipcom_socket_usr ipcom_random ipcom_bind_usr ipcom_getsockname_usr ipcom_connect_usr ipcom_listen_usr ipcom_accept_usr memcmp ipcom_filewrite ipcom_mutex_lock ipcom_mutex_unlock ipcom_mutex_delete malloc ipcom_sysvar_get ipcom_inet_pton free ipcom_unlink ipcom_fileopen ipcom_fstat ipcom_fileclose ipcom_fileread ipcom_mutex_create
	DECLARES 
	USES 
}
Module ipftpc.o {
	OBJECT += libFTP.a::ipftpc.o
}
ObjectFile libFTP.a::ipftpc_cmd_ftp.o {
	NAME Object file ipftpc_cmd_ftp.o from archive libFTP.a
	EXPORTS ipftpc_cmd_main
	IMPORTS .TOC. printf strtol ipftpc_lastreply ipftpc_strerror ipftpc_strclass ipftpc_close free ipftpc_setattr ipftpc_put ipftpc_cmd ipftpc_list ipftpc_get strlen strncmp malloc ipcom_getcwd ipcom_chdir memset ipcom_getsockaddrbyaddr ipcom_getaddrinfo memcpy ipcom_freeaddrinfo ipftpc_open strdup ipcom_stdout ipcom_fflush ipcom_getline ipftpc_login memset_s strspn strcspn ipcom_getline_init ipcom_getopt_clear_r ipcom_getopt_r ipcom_getline_exit
	DECLARES 
	USES 
}
Module ipftpc_cmd_ftp.o {
	OBJECT += libFTP.a::ipftpc_cmd_ftp.o
}
ObjectFile libFTP.a::ipftps.o {
	NAME Object file ipftps.o from archive libFTP.a
	EXPORTS ipftps_get_activesession ipftps_session ipftps_main ipftps_create ipftps_start ipftps_version
	IMPORTS .TOC. ipcom_mutex_create memcpy ipcom_filewrite ipcom_socketwrite_usr strcspn strspn strcmp strlen strchr opendir closedir malloc pathCat strcpy pathCondense strcat iosDevFind free ipcom_syslog ipcom_errno_get ipcom_sysvar_get atoi strdup strerror vsnprintf ipcom_stat memset time localtime_r strftime ipcom_socketclose_usr ipcom_inet_ntop ipcom_socketselect_usr ipcom_accept_usr memcmp ipcom_socket_usr ipcom_setsockopt_usr ipcom_random ipcom_bind_usr ipcom_listen_usr ipcom_getsockname_usr ipcom_connect_usr ipcom_socketread_usr strstr ipcom_unlink ipcom_fileopen ipcom_fstat ipcom_fileclose strtol ipcom_inet_pton ipcom_strcasecmp strncmp ipcom_opendir ipcom_mutex_lock ipcom_readdir ipcom_closedir ipcom_mutex_unlock ipcom_mkdir toupper strrchr snprintf ipftps_authenticate ipcom_sleep memset_s ipcom_fileread ipcom_rmdir ipcom_access ipcom_rename systemSecurityIsEnabled ipcom_strncasecmp ipcom_proc_init ipcom_ipc_open ipcom_ipc_malloc ipcom_ipc_send ipcom_ipc_free ipcom_ipc_receive ipcom_ipc_close ipcom_auth_logout ipcom_ipc_isopen ipcom_proc_exit ipcom_once ipcom_ipc_install ipcom_ipd_init ipcom_proc_attr_init ipcom_priority_map ipcom_sysvar_get_as_int ipcom_ipd_input sprintf ipcom_proc_acreate_v1 ipcom_ipd_exit ipcom_ipc_uninstall
	DECLARES 
	USES 
}
Module ipftps.o {
	OBJECT += libFTP.a::ipftps.o
}
ObjectFile libFTP.a::ipftps_tls.o {
	NAME Object file ipftps_tls.o from archive libFTP.a
	EXPORTS 
	IMPORTS 
	DECLARES 
	USES 
}
Module ipftps_tls.o {
	OBJECT += libFTP.a::ipftps_tls.o
}
Library libFTP.a {
	MODULES libFTP.a::ipftpc.o libFTP.a::ipftpc_cmd_ftp.o libFTP.a::ipftps.o libFTP.a::ipftps_tls.o
}
