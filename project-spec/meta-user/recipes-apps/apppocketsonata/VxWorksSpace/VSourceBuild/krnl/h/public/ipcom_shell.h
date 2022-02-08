/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_SHELL_H
#define IPCOM_SHELL_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Interpeak Shell handling.
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"

/* Shell commands maximum name, usage and description strings */
#define IPCOM_SHELL_MAX_CMD_NAME_LENGTH             32
#define IPCOM_SHELL_MAX_CMD_USAGE_LENGTH            64
#define IPCOM_SHELL_MAX_CMD_DESCRIPTION_LENGTH      32


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include "ipcom_type.h"
#include "ipcom_cstyle.h"
#include "ipcom_tags.h"
#include "ipcom_inet.h"
#include "ipcom_list.h"
#include "ipcom_sock.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* File pointer and descriptor values when using IPCOM shell */
#define IP_FILE_STDIN    (IP_FILE *)0x0000fff1
#define IP_FILE_STDOUT   (IP_FILE *)0x0000fff2
#define IP_FILE_STDERR   (IP_FILE *)0x0000fff3

#define IP_FD_STDIN      (Ip_fd)0x0000fff1
#define IP_FD_STDOUT     (Ip_fd)0x0000fff2
#define IP_FD_STDERR     (Ip_fd)0x0000fff3


/* Shell command return codes (also called exit codes) */
#define IPCOM_SHELL_SUCCESS      0           /* successfully completed */
#define IPCOM_SHELL_ERR          1           /* execution of the command failed */
#define IPCOM_SHELL_ERR_USAGE    2           /* invalid or insufficient argument(s) */
#define IPCOM_SHELL_ERR_APP(e)   (10 + (e))  /* application specific error codes */
#define IPCOM_SHELL_ERR_SIG(s)   (128 + (s)) /* killed by signal 's' */

/* Shell parameter names, used when starting a shell */
#define IPCOM_SHELL_CTX_USER_NAME   1
#define IPCOM_SHELL_CTX_LOCAL_ADDR  2
#define IPCOM_SHELL_CTX_PEER_ADDR   3
#define IPCOM_SHELL_CTX_INVOKER     4
#define IPCOM_SHELL_CTX_FD          5

    /* Defined values for IPCOM_SHELL_CTX_INVOKER */
#define IPCOM_SHELL_CTX_INVOKER_TELNET  1
#define IPCOM_SHELL_CTX_INVOKER_SSH     2

#define IPCOM_SHELL_CTX_IPSSH_BASE  100

    /* Use this macro as start value for privately defined shell parameters */
#define IPCOM_SHELL_CTX_PRIVATE_BASE  1000

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         Ipcom_shell_cmd
 *===========================================================================
 */
typedef int (* Ipcom_shell_cmd_type) (int argc, char ** argv);

typedef struct Ipcom_shell_cmd_struct
{
  Ipcom_list             cmd_list;      /* list of shell commands */
  char                   name[IPCOM_SHELL_MAX_CMD_NAME_LENGTH];
  char                   usage[IPCOM_SHELL_MAX_CMD_USAGE_LENGTH];
  char                   description[IPCOM_SHELL_MAX_CMD_DESCRIPTION_LENGTH];
  Ipcom_shell_cmd_type   hook;
  Ip_s32                 priority;
  Ip_u32                 stack_size;
}
Ipcom_shell_cmd;


/*
 *===========================================================================
 *                         Ipcom_getline
 *===========================================================================
 */
typedef struct Ipcom_getline_struct
{
    Ipcom_list history_list;
    int history_len;
    int row_len;
    char *clipboard;
}
Ipcom_getline;


/*
 *===========================================================================
 *                         Ipcom_shell_ctx
 *===========================================================================
 */
typedef struct Ipcom_shell_ctx_struct
{
    int len;
    int max_size;
    Ip_u8* buf;
} Ipcom_shell_ctx;

typedef Ip_err (*Ipcom_start_shell_ptr)(Ip_fd *stdio_sock, const Ipcom_shell_ctx* sh_ctx);

/*
 ****************************************************************************
 * 6                    STANDARD FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipcom_set_start_shell_ptr
 *===========================================================================
 * Description: Sets the function pointer invoked when a shell shall be started.
 * Parameters:
 * Returns:
 *
 */
IP_GLOBAL void ipcom_set_start_shell_ptr(Ipcom_start_shell_ptr shell_start_ptr);


/*
 *===========================================================================
 *                    ipcom_get_start_shell_ptr
 *===========================================================================
 * Description: Returns the function pointer invoked when a shell shall be
 *              started.
 * Parameters:
 * Returns:
 *
 */
IP_GLOBAL Ipcom_start_shell_ptr ipcom_get_start_shell_ptr(void);

/*
 *===========================================================================
 *                    ipcom_start_shell
 *===========================================================================
 * Description: Starts a shell process and sets up a TCP connection. The
 *              TCP connection is used to convey stdin and stdout data. The
 *              underlaying shell process is terminated by closing the socket.
 *              If the shell terminates (e.g. if the user gives the command
 *              'exit') the TCP connection will be closed and the shell will
 *              terminate.
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipcom_start_shell(Ip_fd *stdio_sock, const Ipcom_shell_ctx* sh_ctx);


/*
 *===========================================================================
 *                    ipcom_start_shell_ipcom/native
 *===========================================================================
 * Description: Starts a shell process (ipcom/native shell) and sets up a
 *              TCP connection. The TCP connection is used to convey stdin
 *              and stdout data. The underlaying shell process is terminated
 *              by closing the socket. If the shell terminates (e.g. if the
 *              user gives the command 'exit') the TCP connection will be
 *              closed and the shell will terminate.
 * Parameters:
 * Returns:
 *
 */
#if IPCOM_USE_SHELL == IPCOM_SHELL_IPCOM
IP_PUBLIC Ip_err
ipcom_start_shell_ipcom(Ip_fd *stdio_sock, const Ipcom_shell_ctx* sh_ctx);
#endif
#if IPCOM_USE_SHELL == IPCOM_SHELL_NATIVE
IP_PUBLIC Ip_err
ipcom_start_shell_native(Ip_fd *stdio_sock, const Ipcom_shell_ctx* sh_ctx);
#endif

/*
 *===========================================================================
 *                    ipcom_start_shell_cmd
 *===========================================================================
 * Description: Starts a shell command process and sets up a TCP connection.
 *              The TCP connection is used to convey stdin and stdout data
 *              between the shell command process and the shell itself.
 * Parameters:
 *
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipcom_shell_run_extcmd(int argc, char **argv, Ip_fd *stdio_sock, Ip_pid_t ppid, Ip_u32 seqno, Ip_pid_t *cmd_pid, int *proc_index);


/*
 *===========================================================================
 *                    ipcom_shell_add_cmd
 *===========================================================================
 * Description:     Add a command to the list of available ipcom_shell commands
 * Parameters:      name : command's name
 *                  usage : usage string
 *                  description : description of command
 *                  hook : function to that executes the command
 *                  priority : na
 *                  stack_size : the stack to be used by the process that
 *                               executes the hook.
 *
 * Returns:         IPCOM_SUCCESS : ok
 *                  IPCOM_ERR_DUPLICATE : command already exists
 *                  IPCOM_ERR_NO_MEMORY : out of memory
 *
 *
 */
#if (defined(IPCOM_SHELL_C) || IPCOM_USE_SHELL >= IPCOM_SHELL_IPCOM \
  || (defined(IP_PORT_VXWORKS) && IPCOM_USE_SHELL == IPCOM_SHELL_NATIVE)) && \
     (!defined(PRJ_BUILD) || (IP_PORT_VXWORKS >= 65 && defined(INCLUDE_IPCOM_SHELL_CMD))) && \
     (!defined(IP_PORT_VXWORKS) || !defined(IPLITE) || defined(INCLUDE_IPCOM_SHELL_CMD))
IP_PUBLIC Ip_err
ipcom_shell_add_cmd(const char *name, const char *usage,
                    const char *description, Ipcom_shell_cmd_type hook,
                    Ip_s32 priority, Ip_s32 stack_size);
#else
#define ipcom_shell_add_cmd(n,u,d,h,p,s)  0
#endif

#define IPCOM_SHELL_PRIO_SAME   -1


/*
 *===========================================================================
 *                    ipcom_shell_remove_cmd
 *===========================================================================
 * Description:     Remove a command from the list of available ipcom_shell commands
 * Parameters:      name : the command to remove
 * Returns:         IPCOM_SUCCESS : ok
 *                  IPCOM_ERR_NOT_FOUND : the command does not exist
 *
 */
#if (defined(IPCOM_SHELL_C) || IPCOM_USE_SHELL >= IPCOM_SHELL_IPCOM \
  || (defined(IP_PORT_VXWORKS) && IPCOM_USE_SHELL == IPCOM_SHELL_NATIVE)) && \
     (!defined(PRJ_BUILD) || (IP_PORT_VXWORKS >= 65 && defined(INCLUDE_IPCOM_SHELL_CMD)))
IP_PUBLIC Ip_err
ipcom_shell_remove_cmd(const char *name, Ipcom_shell_cmd_type hook);
#else
#define ipcom_shell_remove_cmd(n,h)  0
#endif


/*
 *===========================================================================
 *                    ipcom_shell_find_cmd
 *===========================================================================
 * Description:     Search for  a command in the list of available ipcom_shell
 *                  commands
 * Parameters:      name : the command to search for
 * Returns:         pointer to the command or IP_NULL if not found
 *
 */
IP_PUBLIC Ipcom_shell_cmd *
ipcom_shell_find_cmd(const char *name);


/*
 *===========================================================================
 *                         SHELL file system calls
 *===========================================================================
 */

/* ipcom_shellio.c */
IP_PUBLIC Ip_ssize_t ipcom_shell_write(Ip_fd fd, IP_CONST void *buf, Ip_size_t count);
IP_PUBLIC Ip_size_t  ipcom_shell_fwrite(IP_CONST void *ptr, Ip_size_t size, Ip_size_t nitems, IP_FILE *stream);
IP_PUBLIC Ip_size_t  ipcom_shell_fread(void *ptr, Ip_size_t size, Ip_size_t nitems, IP_FILE *stream);

/* ipcom_exit.c */
IP_PUBLIC void ipcom_shell_exit(int status);


/*
 *===========================================================================
 *                         GETLINE
 *===========================================================================
 */

/* ipcom_getline.c */
IP_PUBLIC Ipcom_getline *ipcom_getline_init(int history_len);
IP_PUBLIC void ipcom_getline_exit(Ipcom_getline *gl);
IP_PUBLIC int ipcom_getline(Ip_fd fd, char *buf, int buflen, Ip_bool echo, Ipcom_getline *gl, int promptlen);

/*
 *===========================================================================
 *                         ipcom_cmd_shellcmds.c
 *===========================================================================
 * Minimalistic shell commands.
 */

/* With file system */
IP_PUBLIC int ipcom_cmd_pwd(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_ls(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_rm(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_rmdir(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_mkdir(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_cd(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_cp(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_cat(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_mv(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_uuencode(int argc, char **argv);

/* With IPCOM_USE_TIME */
IP_PUBLIC int ipcom_cmd_date(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_time(int argc, char **argv);

/* With IPCOM_USE_ENV */
IP_PUBLIC int ipcom_cmd_setenv(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_getenv(int argc, char **argv);

/* With IPCOM_VR_MAX > 1 */
IP_PUBLIC int ipcom_cmd_chvr(int argc, char **argv);

/* With IPCOM_USE_ALIAS */
IP_PUBLIC int ipcom_shellalias_alias(int argc, char **argv);
IP_PUBLIC int ipcom_shellalias_unalias(int argc, char **argv);
IP_PUBLIC int ipcom_shellalias_expand(int *argc, char ***argv);

/* Shell param functions */
IP_PUBLIC Ipcom_shell_ctx* ipcom_shell_ctx_new(Ip_size_t size);
IP_PUBLIC void ipcom_shell_ctx_free(Ipcom_shell_ctx* ctx);
IP_PUBLIC char* ipcom_shell_ctx_get_user(Ipcom_shell_ctx* ctx);
IP_PUBLIC Ip_err ipcom_shell_ctx_add_user(Ipcom_shell_ctx* ctx, const char* user);
IP_PUBLIC union Ip_sockaddr_union* ipcom_shell_ctx_get_clt_addr(Ipcom_shell_ctx* ctx);
IP_PUBLIC Ip_err ipcom_shell_ctx_add_local_addr(Ipcom_shell_ctx* ctx, const union Ip_sockaddr_union* addr);
IP_PUBLIC union Ip_sockaddr_union* ipcom_shell_ctx_get_peer_addr(Ipcom_shell_ctx* ctx);
IP_PUBLIC Ip_err ipcom_shell_ctx_add_peer_addr(Ipcom_shell_ctx* ctx, const union Ip_sockaddr_union* addr);
IP_PUBLIC Ip_err ipcom_shell_ctx_get_int(Ipcom_shell_ctx* param, int param_id, int* value);
IP_PUBLIC Ip_err ipcom_shell_ctx_add_int(Ipcom_shell_ctx* param, int param_id, int value);
IP_PUBLIC Ip_err ipcom_shell_ctx_get(Ipcom_shell_ctx* ctx, int param_id, Ip_u8** ret, int* len);
IP_PUBLIC Ip_err ipcom_shell_ctx_add(Ipcom_shell_ctx* ctx, int param_id, Ip_u8* value, int len);


#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

