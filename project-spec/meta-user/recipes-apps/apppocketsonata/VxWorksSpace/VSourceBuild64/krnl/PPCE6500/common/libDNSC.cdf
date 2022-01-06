Symbol .TOC. {
}
Symbol ipcom_sysvar_get {
}
Symbol strlen {
}
Symbol strcpy {
}
Symbol free {
}
Symbol ipdnsc_hostent_create {
}
Symbol ipdnsc_hostent_insert_addr {
}
Symbol ipdnsc_hostent_insert_alias {
}
Symbol ipdnsc_hostent_insert_name {
}
Symbol ipdnsc_hostent_free {
}
Symbol ipdnsc_create_query {
}
Symbol ipdnsc_send_wait {
}
Symbol ipcom_socket_usr {
}
Symbol memset {
}
Symbol ipcom_bind_usr {
}
Symbol memcpy {
}
Symbol ipcom_sendto_usr {
}
Symbol ipdnsc_in6addr_any {
}
Symbol malloc {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_recvfrom_usr {
}
Symbol ipcom_socketclose_usr {
}
Symbol ipdnsc {
}
Symbol time {
}
Symbol ipdnsc_hostent_copy {
}
Symbol memcmp {
}
Symbol ipcom_strcasecmp {
}
Symbol ipcom_inet_pton {
}
Symbol ipcom_mutex_lock {
}
Symbol ipcom_mutex_unlock {
}
Symbol ipdnsc_get_time {
}
Symbol ipdnsc_get_ipv6_addrconfig {
}
Symbol strchr {
}
Symbol isdigit {
}
Symbol atoi {
}
Symbol ipcom_if_nametoindex {
}
Symbol ipdnsc_default {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol ipdnsc_resolve_name {
}
Symbol ipdnsc_resolve_addr {
}
Symbol ipdnsc_cache_flush {
}
Symbol ipdnsc_create {
}
Symbol ipdnsc_start {
}
Symbol ipcom_mutex_create {
}
Symbol ipcom_mutex_delete {
}
Symbol ipcom_dns_init_ok {
}
Symbol ipcom_dns {
}
Symbol ipdnsc_getipnodebyname {
}
Symbol ipdnsc_getipnodebyaddr {
}
Symbol ipdnsc_freehostent {
}
Symbol ipdnsc_version {
}
Symbol realloc {
}
Symbol ipdnsc_get_soa {
}
Symbol ipdnsc_satisfy {
}
Symbol ipdnsc_get_ns {
}
Symbol ipdnsc_get_glue {
}
Symbol ipdnsc_free_nsrrset {
}
Symbol ipcom_inet_ntop {
}
Symbol ip_in6addr_any {
}
Symbol ipdnsc_do_update {
}
Symbol printf {
}
Symbol ipdnsc_samename {
}
Symbol strdup {
}
Symbol ipdnsc_mkupdate {
}
Symbol ipdnsc_send_update_signed {
}
Symbol ipdnsc_send_update {
}
Symbol ipdnsc_update_rmsg {
}
Symbol ipdnsc_cmd_nslookup {
}
Symbol ipcom_getopt_clear {
}
Symbol ipcom_getopt_data {
}
Symbol ipcom_getopt {
}
Symbol isspace {
}
Symbol isxdigit {
}
Symbol strtol {
}
Symbol sprintf {
}
Symbol ipcom_strncasecmp {
}
Symbol ipcom_ntohs {
}
Symbol isupper {
}
Symbol tolower {
}
Symbol ipcom_htons {
}
Symbol secHashMd5TemplateGet {
}
Symbol secHashInit {
}
Symbol secHashUpdate {
}
Symbol secHashCleanup {
}
Symbol secHashFinal {
}
ObjectFile libDNSC.a::ipdnsc.o {
	NAME Object file ipdnsc.o from archive libDNSC.a
	EXPORTS ipdnsc_create_query ipdnsc_send_wait ipdnsc_in6addr_any ipdnsc_get_time ipdnsc_get_ipv6_addrconfig ipdnsc_default ipdnsc_resolve_name ipdnsc_resolve_addr ipdnsc_cache_flush ipdnsc_create ipdnsc_start ipdnsc_version
	IMPORTS .TOC. ipcom_sysvar_get strlen strcpy free ipdnsc_hostent_create ipdnsc_hostent_insert_addr ipdnsc_hostent_insert_alias ipdnsc_hostent_insert_name ipdnsc_hostent_free ipcom_socket_usr memset ipcom_bind_usr memcpy ipcom_sendto_usr malloc ipcom_socketselect_usr ipcom_recvfrom_usr ipcom_socketclose_usr time ipdnsc_hostent_copy memcmp ipcom_strcasecmp ipcom_inet_pton ipcom_mutex_lock ipcom_mutex_unlock strchr isdigit atoi ipcom_if_nametoindex ipcom_sysvar_get_as_int ipcom_mutex_create ipcom_mutex_delete ipcom_dns_init_ok ipcom_dns ipdnsc_getipnodebyname ipdnsc_getipnodebyaddr ipdnsc_freehostent
	DECLARES ipdnsc
	USES 
}
Module ipdnsc.o {
	OBJECT += libDNSC.a::ipdnsc.o
}
ObjectFile libDNSC.a::ipdnsc_api.o {
	NAME Object file ipdnsc_api.o from archive libDNSC.a
	EXPORTS ipdnsc_hostent_insert_name ipdnsc_hostent_insert_alias ipdnsc_hostent_insert_addr ipdnsc_hostent_create ipdnsc_hostent_free ipdnsc_hostent_copy ipdnsc_freehostent ipdnsc_getipnodebyname ipdnsc_getipnodebyaddr ipdnsc_do_update ipdnsc_update_rmsg
	IMPORTS .TOC. strlen free malloc strcpy realloc memcpy memset ipcom_strcasecmp ipdnsc_get_soa ipdnsc_satisfy ipdnsc_get_ns ipdnsc_get_glue ipdnsc_free_nsrrset ipcom_inet_pton ipcom_inet_ntop ipdnsc ipdnsc_default ipdnsc_resolve_name ipdnsc_resolve_addr ip_in6addr_any memcmp printf ipdnsc_samename strdup ipdnsc_mkupdate ipdnsc_send_update_signed ipdnsc_send_update
	DECLARES 
	USES 
}
Module ipdnsc_api.o {
	OBJECT += libDNSC.a::ipdnsc_api.o
}
ObjectFile libDNSC.a::ipdnsc_cmd_nslookup.o {
	NAME Object file ipdnsc_cmd_nslookup.o from archive libDNSC.a
	EXPORTS ipdnsc_cmd_nslookup
	IMPORTS .TOC. printf ipdnsc_default memset ipcom_getopt_clear ipcom_getopt_data ipcom_getopt ipdnsc_cache_flush atoi ipcom_inet_pton ipdnsc_get_ipv6_addrconfig ipdnsc_resolve_addr ipcom_inet_ntop ipdnsc_resolve_name ipdnsc_hostent_free
	DECLARES 
	USES 
}
Module ipdnsc_cmd_nslookup.o {
	OBJECT += libDNSC.a::ipdnsc_cmd_nslookup.o
}
ObjectFile libDNSC.a::ipdnsc_update.o {
	NAME Object file ipdnsc_update.o from archive libDNSC.a
	EXPORTS ipdnsc_samename ipdnsc_free_nsrrset ipdnsc_mkupdate ipdnsc_get_soa ipdnsc_get_ns ipdnsc_get_glue ipdnsc_satisfy ipdnsc_send_update ipdnsc_send_update_signed
	IMPORTS .TOC. strlen strcpy isspace strchr isdigit isxdigit strtol sprintf ipcom_strncasecmp ipcom_ntohs isupper tolower memcpy malloc ipdnsc_create_query ipdnsc_send_wait free ipcom_strcasecmp memset ipcom_sysvar_get_as_int strdup ipdnsc_get_time ipcom_htons secHashMd5TemplateGet secHashInit secHashUpdate secHashCleanup secHashFinal memcmp printf ipcom_inet_pton ipdnsc_default ipdnsc_update_rmsg
	DECLARES 
	USES 
}
Module ipdnsc_update.o {
	OBJECT += libDNSC.a::ipdnsc_update.o
}
Library libDNSC.a {
	MODULES libDNSC.a::ipdnsc.o libDNSC.a::ipdnsc_api.o libDNSC.a::ipdnsc_cmd_nslookup.o libDNSC.a::ipdnsc_update.o
}
Symbol .TOC. {
}
Symbol ipcom_sysvar_get {
}
Symbol strlen {
}
Symbol strcpy {
}
Symbol free {
}
Symbol ipdnsc_hostent_create {
}
Symbol ipdnsc_hostent_insert_addr {
}
Symbol ipdnsc_hostent_insert_alias {
}
Symbol ipdnsc_hostent_insert_name {
}
Symbol ipdnsc_hostent_free {
}
Symbol ipdnsc_create_query {
}
Symbol ipdnsc_send_wait {
}
Symbol ipcom_socket_usr {
}
Symbol memset {
}
Symbol ipcom_bind_usr {
}
Symbol memcpy {
}
Symbol ipcom_sendto_usr {
}
Symbol ipdnsc_in6addr_any {
}
Symbol malloc {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_recvfrom_usr {
}
Symbol ipcom_socketclose_usr {
}
Symbol ipdnsc {
}
Symbol time {
}
Symbol ipdnsc_hostent_copy {
}
Symbol memcmp {
}
Symbol ipcom_strcasecmp {
}
Symbol ipcom_inet_pton {
}
Symbol ipcom_mutex_lock {
}
Symbol ipcom_mutex_unlock {
}
Symbol ipdnsc_get_time {
}
Symbol ipdnsc_get_ipv6_addrconfig {
}
Symbol strchr {
}
Symbol isdigit {
}
Symbol atoi {
}
Symbol ipcom_if_nametoindex {
}
Symbol ipdnsc_default {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol ipdnsc_resolve_name {
}
Symbol ipdnsc_resolve_addr {
}
Symbol ipdnsc_cache_flush {
}
Symbol ipdnsc_create {
}
Symbol ipdnsc_start {
}
Symbol ipcom_mutex_create {
}
Symbol ipcom_mutex_delete {
}
Symbol ipcom_dns_init_ok {
}
Symbol ipcom_dns {
}
Symbol ipdnsc_getipnodebyname {
}
Symbol ipdnsc_getipnodebyaddr {
}
Symbol ipdnsc_freehostent {
}
Symbol ipdnsc_version {
}
Symbol realloc {
}
Symbol ipdnsc_get_soa {
}
Symbol ipdnsc_satisfy {
}
Symbol ipdnsc_get_ns {
}
Symbol ipdnsc_get_glue {
}
Symbol ipdnsc_free_nsrrset {
}
Symbol ipcom_inet_ntop {
}
Symbol ip_in6addr_any {
}
Symbol ipdnsc_do_update {
}
Symbol printf {
}
Symbol ipdnsc_samename {
}
Symbol strdup {
}
Symbol ipdnsc_mkupdate {
}
Symbol ipdnsc_send_update_signed {
}
Symbol ipdnsc_send_update {
}
Symbol ipdnsc_update_rmsg {
}
Symbol ipdnsc_cmd_nslookup {
}
Symbol ipcom_getopt_clear {
}
Symbol ipcom_getopt_data {
}
Symbol ipcom_getopt {
}
Symbol isspace {
}
Symbol isxdigit {
}
Symbol strtol {
}
Symbol sprintf {
}
Symbol ipcom_strncasecmp {
}
Symbol ipcom_ntohs {
}
Symbol isupper {
}
Symbol tolower {
}
Symbol ipcom_htons {
}
Symbol secHashMd5TemplateGet {
}
Symbol secHashInit {
}
Symbol secHashUpdate {
}
Symbol secHashCleanup {
}
Symbol secHashFinal {
}
ObjectFile libDNSC.a::ipdnsc.o {
	NAME Object file ipdnsc.o from archive libDNSC.a
	EXPORTS ipdnsc_create_query ipdnsc_send_wait ipdnsc_in6addr_any ipdnsc_get_time ipdnsc_get_ipv6_addrconfig ipdnsc_default ipdnsc_resolve_name ipdnsc_resolve_addr ipdnsc_cache_flush ipdnsc_create ipdnsc_start ipdnsc_version
	IMPORTS .TOC. ipcom_sysvar_get strlen strcpy free ipdnsc_hostent_create ipdnsc_hostent_insert_addr ipdnsc_hostent_insert_alias ipdnsc_hostent_insert_name ipdnsc_hostent_free ipcom_socket_usr memset ipcom_bind_usr memcpy ipcom_sendto_usr malloc ipcom_socketselect_usr ipcom_recvfrom_usr ipcom_socketclose_usr time ipdnsc_hostent_copy memcmp ipcom_strcasecmp ipcom_inet_pton ipcom_mutex_lock ipcom_mutex_unlock strchr isdigit atoi ipcom_if_nametoindex ipcom_sysvar_get_as_int ipcom_mutex_create ipcom_mutex_delete ipcom_dns_init_ok ipcom_dns ipdnsc_getipnodebyname ipdnsc_getipnodebyaddr ipdnsc_freehostent
	DECLARES ipdnsc
	USES 
}
Module ipdnsc.o {
	OBJECT += libDNSC.a::ipdnsc.o
}
ObjectFile libDNSC.a::ipdnsc_api.o {
	NAME Object file ipdnsc_api.o from archive libDNSC.a
	EXPORTS ipdnsc_hostent_insert_name ipdnsc_hostent_insert_alias ipdnsc_hostent_insert_addr ipdnsc_hostent_create ipdnsc_hostent_free ipdnsc_hostent_copy ipdnsc_freehostent ipdnsc_getipnodebyname ipdnsc_getipnodebyaddr ipdnsc_do_update ipdnsc_update_rmsg
	IMPORTS .TOC. strlen free malloc strcpy realloc memcpy memset ipcom_strcasecmp ipdnsc_get_soa ipdnsc_satisfy ipdnsc_get_ns ipdnsc_get_glue ipdnsc_free_nsrrset ipcom_inet_pton ipcom_inet_ntop ipdnsc ipdnsc_default ipdnsc_resolve_name ipdnsc_resolve_addr ip_in6addr_any memcmp printf ipdnsc_samename strdup ipdnsc_mkupdate ipdnsc_send_update_signed ipdnsc_send_update
	DECLARES 
	USES 
}
Module ipdnsc_api.o {
	OBJECT += libDNSC.a::ipdnsc_api.o
}
ObjectFile libDNSC.a::ipdnsc_cmd_nslookup.o {
	NAME Object file ipdnsc_cmd_nslookup.o from archive libDNSC.a
	EXPORTS ipdnsc_cmd_nslookup
	IMPORTS .TOC. printf ipdnsc_default memset ipcom_getopt_clear ipcom_getopt_data ipcom_getopt ipdnsc_cache_flush atoi ipcom_inet_pton ipdnsc_get_ipv6_addrconfig ipdnsc_resolve_addr ipcom_inet_ntop ipdnsc_resolve_name ipdnsc_hostent_free
	DECLARES 
	USES 
}
Module ipdnsc_cmd_nslookup.o {
	OBJECT += libDNSC.a::ipdnsc_cmd_nslookup.o
}
ObjectFile libDNSC.a::ipdnsc_update.o {
	NAME Object file ipdnsc_update.o from archive libDNSC.a
	EXPORTS ipdnsc_samename ipdnsc_free_nsrrset ipdnsc_mkupdate ipdnsc_get_soa ipdnsc_get_ns ipdnsc_get_glue ipdnsc_satisfy ipdnsc_send_update ipdnsc_send_update_signed
	IMPORTS .TOC. strlen strcpy isspace strchr isdigit isxdigit strtol sprintf ipcom_strncasecmp ipcom_ntohs isupper tolower memcpy malloc ipdnsc_create_query ipdnsc_send_wait free ipcom_strcasecmp memset ipcom_sysvar_get_as_int strdup ipdnsc_get_time ipcom_htons secHashMd5TemplateGet secHashInit secHashUpdate secHashCleanup secHashFinal memcmp printf ipcom_inet_pton ipdnsc_default ipdnsc_update_rmsg
	DECLARES 
	USES 
}
Module ipdnsc_update.o {
	OBJECT += libDNSC.a::ipdnsc_update.o
}
Library libDNSC.a {
	MODULES libDNSC.a::ipdnsc.o libDNSC.a::ipdnsc_api.o libDNSC.a::ipdnsc_cmd_nslookup.o libDNSC.a::ipdnsc_update.o
}
Symbol .TOC. {
}
Symbol ipcom_sysvar_get {
}
Symbol strlen {
}
Symbol strcpy {
}
Symbol free {
}
Symbol ipdnsc_hostent_create {
}
Symbol ipdnsc_hostent_insert_addr {
}
Symbol ipdnsc_hostent_insert_alias {
}
Symbol ipdnsc_hostent_insert_name {
}
Symbol ipdnsc_hostent_free {
}
Symbol ipdnsc_create_query {
}
Symbol ipdnsc_send_wait {
}
Symbol ipcom_socket_usr {
}
Symbol memset {
}
Symbol ipcom_bind_usr {
}
Symbol memcpy {
}
Symbol ipcom_sendto_usr {
}
Symbol ipdnsc_in6addr_any {
}
Symbol malloc {
}
Symbol ipcom_socketselect_usr {
}
Symbol ipcom_recvfrom_usr {
}
Symbol ipcom_socketclose_usr {
}
Symbol ipdnsc {
}
Symbol time {
}
Symbol ipdnsc_hostent_copy {
}
Symbol memcmp {
}
Symbol ipcom_strcasecmp {
}
Symbol ipcom_inet_pton {
}
Symbol ipcom_mutex_lock {
}
Symbol ipcom_mutex_unlock {
}
Symbol ipdnsc_get_time {
}
Symbol ipdnsc_get_ipv6_addrconfig {
}
Symbol strchr {
}
Symbol isdigit {
}
Symbol atoi {
}
Symbol ipcom_if_nametoindex {
}
Symbol ipdnsc_default {
}
Symbol ipcom_sysvar_get_as_int {
}
Symbol ipdnsc_resolve_name {
}
Symbol ipdnsc_resolve_addr {
}
Symbol ipdnsc_cache_flush {
}
Symbol ipdnsc_create {
}
Symbol ipdnsc_start {
}
Symbol ipcom_mutex_create {
}
Symbol ipcom_mutex_delete {
}
Symbol ipcom_dns_init_ok {
}
Symbol ipcom_dns {
}
Symbol ipdnsc_getipnodebyname {
}
Symbol ipdnsc_getipnodebyaddr {
}
Symbol ipdnsc_freehostent {
}
Symbol ipdnsc_version {
}
Symbol realloc {
}
Symbol ipdnsc_get_soa {
}
Symbol ipdnsc_satisfy {
}
Symbol ipdnsc_get_ns {
}
Symbol ipdnsc_get_glue {
}
Symbol ipdnsc_free_nsrrset {
}
Symbol ipcom_inet_ntop {
}
Symbol ip_in6addr_any {
}
Symbol ipdnsc_do_update {
}
Symbol printf {
}
Symbol ipdnsc_samename {
}
Symbol strdup {
}
Symbol ipdnsc_mkupdate {
}
Symbol ipdnsc_send_update_signed {
}
Symbol ipdnsc_send_update {
}
Symbol ipdnsc_update_rmsg {
}
Symbol ipdnsc_cmd_nslookup {
}
Symbol ipcom_getopt_clear {
}
Symbol ipcom_getopt_data {
}
Symbol ipcom_getopt {
}
Symbol isspace {
}
Symbol isxdigit {
}
Symbol strtol {
}
Symbol sprintf {
}
Symbol ipcom_strncasecmp {
}
Symbol ipcom_ntohs {
}
Symbol isupper {
}
Symbol tolower {
}
Symbol ipcom_htons {
}
Symbol secHashMd5TemplateGet {
}
Symbol secHashInit {
}
Symbol secHashUpdate {
}
Symbol secHashCleanup {
}
Symbol secHashFinal {
}
ObjectFile libDNSC.a::ipdnsc.o {
	NAME Object file ipdnsc.o from archive libDNSC.a
	EXPORTS ipdnsc_create_query ipdnsc_send_wait ipdnsc_in6addr_any ipdnsc_get_time ipdnsc_get_ipv6_addrconfig ipdnsc_default ipdnsc_resolve_name ipdnsc_resolve_addr ipdnsc_cache_flush ipdnsc_create ipdnsc_start ipdnsc_version
	IMPORTS .TOC. ipcom_sysvar_get strlen strcpy free ipdnsc_hostent_create ipdnsc_hostent_insert_addr ipdnsc_hostent_insert_alias ipdnsc_hostent_insert_name ipdnsc_hostent_free ipcom_socket_usr memset ipcom_bind_usr memcpy ipcom_sendto_usr malloc ipcom_socketselect_usr ipcom_recvfrom_usr ipcom_socketclose_usr time ipdnsc_hostent_copy memcmp ipcom_strcasecmp ipcom_inet_pton ipcom_mutex_lock ipcom_mutex_unlock strchr isdigit atoi ipcom_if_nametoindex ipcom_sysvar_get_as_int ipcom_mutex_create ipcom_mutex_delete ipcom_dns_init_ok ipcom_dns ipdnsc_getipnodebyname ipdnsc_getipnodebyaddr ipdnsc_freehostent
	DECLARES ipdnsc
	USES 
}
Module ipdnsc.o {
	OBJECT += libDNSC.a::ipdnsc.o
}
ObjectFile libDNSC.a::ipdnsc_api.o {
	NAME Object file ipdnsc_api.o from archive libDNSC.a
	EXPORTS ipdnsc_hostent_insert_name ipdnsc_hostent_insert_alias ipdnsc_hostent_insert_addr ipdnsc_hostent_create ipdnsc_hostent_free ipdnsc_hostent_copy ipdnsc_freehostent ipdnsc_getipnodebyname ipdnsc_getipnodebyaddr ipdnsc_do_update ipdnsc_update_rmsg
	IMPORTS .TOC. strlen free malloc strcpy realloc memcpy memset ipcom_strcasecmp ipdnsc_get_soa ipdnsc_satisfy ipdnsc_get_ns ipdnsc_get_glue ipdnsc_free_nsrrset ipcom_inet_pton ipcom_inet_ntop ipdnsc ipdnsc_default ipdnsc_resolve_name ipdnsc_resolve_addr ip_in6addr_any memcmp printf ipdnsc_samename strdup ipdnsc_mkupdate ipdnsc_send_update_signed ipdnsc_send_update
	DECLARES 
	USES 
}
Module ipdnsc_api.o {
	OBJECT += libDNSC.a::ipdnsc_api.o
}
ObjectFile libDNSC.a::ipdnsc_cmd_nslookup.o {
	NAME Object file ipdnsc_cmd_nslookup.o from archive libDNSC.a
	EXPORTS ipdnsc_cmd_nslookup
	IMPORTS .TOC. printf ipdnsc_default memset ipcom_getopt_clear ipcom_getopt_data ipcom_getopt ipdnsc_cache_flush atoi ipcom_inet_pton ipdnsc_get_ipv6_addrconfig ipdnsc_resolve_addr ipcom_inet_ntop ipdnsc_resolve_name ipdnsc_hostent_free
	DECLARES 
	USES 
}
Module ipdnsc_cmd_nslookup.o {
	OBJECT += libDNSC.a::ipdnsc_cmd_nslookup.o
}
ObjectFile libDNSC.a::ipdnsc_update.o {
	NAME Object file ipdnsc_update.o from archive libDNSC.a
	EXPORTS ipdnsc_samename ipdnsc_free_nsrrset ipdnsc_mkupdate ipdnsc_get_soa ipdnsc_get_ns ipdnsc_get_glue ipdnsc_satisfy ipdnsc_send_update ipdnsc_send_update_signed
	IMPORTS .TOC. strlen strcpy isspace strchr isdigit isxdigit strtol sprintf ipcom_strncasecmp ipcom_ntohs isupper tolower memcpy malloc ipdnsc_create_query ipdnsc_send_wait free ipcom_strcasecmp memset ipcom_sysvar_get_as_int strdup ipdnsc_get_time ipcom_htons secHashMd5TemplateGet secHashInit secHashUpdate secHashCleanup secHashFinal memcmp printf ipcom_inet_pton ipdnsc_default ipdnsc_update_rmsg
	DECLARES 
	USES 
}
Module ipdnsc_update.o {
	OBJECT += libDNSC.a::ipdnsc_update.o
}
Library libDNSC.a {
	MODULES libDNSC.a::ipdnsc.o libDNSC.a::ipdnsc_api.o libDNSC.a::ipdnsc_cmd_nslookup.o libDNSC.a::ipdnsc_update.o
}
