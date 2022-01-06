/* ipcom_auth.h - IPCOM authentication library */

/*
 * Copyright (c) 2006-2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20apr16,rbo  Added ipcom_auth_ctx_login

*/

#ifndef IPCOM_AUTH_H
#define IPCOM_AUTH_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
DESCRIPTION
This library contains the API for IPCOM authentication.
INCLUDE FILES: ipcom_type.h, ipcom_err.h
*/

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_type.h>
#include <ipcom_err.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#if (!defined(IPCOM_KERNEL) && defined(IPCOM_USRLIB)) || defined(IPCOM_USE_REMOTE_AUTH)
#define ipcom_auth_useradd     ipcom_auth_useradd_usr
#define ipcom_auth_userdel     ipcom_auth_userdel_usr
#define ipcom_auth_userget     ipcom_auth_userget_usr
#define ipcom_auth_userlist    ipcom_auth_userlist_usr
#endif

#define IPCOM_AUTH_USERNAME_MAX    81  /* Max user name length. */
#define IPCOM_AUTH_PASSWORD_MAX   129  /* Max user password length. */
#define IPCOM_AUTH_SALT_LENGTH_MAX  8   /* 8 byte random value added to the password. */

#define IPCOM_AUTH_LOGIN_IF_UNDEF   0
#define IPCOM_AUTH_LOGIN_IF_TELNET  1
#define IPCOM_AUTH_LOGIN_IF_RLOGIN  2
#define IPCOM_AUTH_LOGIN_IF_SSH     3
#define IPCOM_AUTH_LOGIN_IF_FTP     4
#define IPCOM_AUTH_LOGIN_IF_CONSOLE 5
#define IPCOM_AUTH_LOGIN_IF_PPP     6

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         Ipcom_auth_userinfo
 *===========================================================================
 * User information filled in by the login functions, their callback or
 * retrieved by calling ipcom_auth_userget() or ipcom_auth_userlist().
 */
typedef struct Ipcom_auth_userinfo_struct
{
    char       username[IPCOM_AUTH_USERNAME_MAX];
    char       password[IPCOM_AUTH_PASSWORD_MAX];
    Ip_uid_t   userid;
    Ip_bool    pwdhash;
    char       salt[IPCOM_AUTH_SALT_LENGTH_MAX];
    int        salt_len;
#ifdef IPCOM_USE_AUTH_RADIUS
    Ip_u8     *radius_attributes;
    int        radius_attrlen;
#endif
}
Ipcom_auth_userinfo;


/*
 *===========================================================================
 *                         Ipcom_auth_login_hook
 *===========================================================================
 * Login function callback for non-blocking login (used by PPP/RADIUS)
 */
typedef void (* Ipcom_auth_login_hook) (Ip_err retval, Ipcom_auth_userinfo *userinfo,
                                        void *auth_login_cookie);

/*
 *===========================================================================
 *                         Ipcom_auth_chap
 *===========================================================================
 * Argument structure for ipcom_auth_chap_login().
 */
typedef struct Ipcom_auth_chap_struct
{
    const Ip_u8 *response;
    Ip_u8        ident;

    const Ip_u8 *challenge;
    int          challenge_size;
}
Ipcom_auth_chap;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/*******************************************************************************
*
* ipcom_auth_login - validate username and password
*
* DESCRIPTION
* This routine validates a username and password. The routine looks up the user
* and validates the password in the VxWorks user database.
*
* If a local user is not found and RADIUS client support is compiled in, the
* function will validate a user sending a RADIUS client access request packet to
* a RADIUS server.
*
* When RADIUS is used, the routine can operate in either blocking and non-
* blocking mode.  In non-blocking mode, the routine is run with an optional
* pointer to a user function and a cookie.  The user function is called when
* authentication is complete.
*
* In non-blocking mode, if the authentication cannot be immediately resolved,
* 'IPCOM_ERR_PENDING' is returned and the user routine is called when the
* authentication completes.
*
* Note that even in non-blocking mode, the routine may return success
* immediately if a local user exists with a valid password.
*
* Parameters:
* \is
* \i <username>
* Name of the user to validate.
* \i <password>
* User\'s password in cleartext or hashed format.
* \i <userinfo>
* Pointer to an 'Ipcom_auth_userinfo' structure, if user information such as
* user ID is desired. Can optionally be 'IP_NULL' if no additional information
* is desired.
* \i <auth_login_hook>
* When RADIUS is used, this routine can run in either blocking mode or non-
* blocking mode.  For blocking mode, set <auth_login_hook> to 'IP_NULL'.
* For non-blocking mode, use a pointer to an 'ipcom_auth_login_hook()' routine,
* which is called when the authentication is complete.
* \i <auth_login_cookie>
* User 32-bit cookie which is supplied in the <auth_login_hook> parameter
* \ie
*
* RETURNS
* \is
* \i 'IPCOM_SUCCESS'
* Valid user and password.
* \i 'IPCOM_ERR_AUTH_FAILED'
* Valid user, bad password.
* \i 'IPCOM_ERR_PENDING'
* Non-blocking login, the authentication reply is pending and the
* auth_login_hook() routine will be called when a result is available.
* \i 'IPCOM_ERR_AUTH_UNKNOWN'
* Unknown user (only returned without RADIUS support).
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipcom_auth_login
(
    const char *username,
    const char *password,
    Ipcom_auth_userinfo *userinfo,
    Ipcom_auth_login_hook auth_login_hook,
    void *auth_login_cookie
);


/*******************************************************************************
*
* ipcom_auth_ctx_login - validate username and password
*
* DESCRIPTION
* This routine validates a username and password. The routine looks up the user
* and validates the password in the VxWorks user database.
*
* If a local user is not found and RADIUS client support is compiled in, the
* function will validate a user sending a RADIUS client access request packet to
* a RADIUS server.
*
* When RADIUS is used, the routine can operate in either blocking and non-
* blocking mode.  In non-blocking mode, the routine is run with an optional
* pointer to a user function and a cookie.  The user function is called when
* authentication is complete.
*
* In non-blocking mode, if the authentication cannot be immediately resolved,
* 'IPCOM_ERR_PENDING' is returned and the user routine is called when the
* authentication completes.
*
* Note that even in non-blocking mode, the routine may return success
* immediately if a local user exists with a valid password.
*
* Parameters:
* \is
* \i <username>
* Name of the user to validate.
* \i <password>
* User\'s password in cleartext or hashed format.
* \i <userinfo>
* Pointer to an 'Ipcom_auth_userinfo' structure, if user information such as
* user ID is desired. Can optionally be 'IP_NULL' if no additional information
* is desired.
* \i <auth_login_hook>
* When RADIUS is used, this routine can run in either blocking mode or non-
* blocking mode.  For blocking mode, set <auth_login_hook> to 'IP_NULL'.
* For non-blocking mode, use a pointer to an 'ipcom_auth_login_hook()' routine,
* which is called when the authentication is complete.
* \i <auth_login_cookie>
* User 32-bit cookie which is supplied in the <auth_login_hook> parameter
* \i <login_interface>
* identifies what interface the request was recieved on, e.g. IPCOM_AUTH_LOGIN_IF_SSH
* \i <socket>
* The file descriptor for the connection the request was recieved on.
* \ie
*
* RETURNS
* \is
* \i 'IPCOM_SUCCESS'
* Valid user and password.
* \i 'IPCOM_ERR_AUTH_FAILED'
* Valid user, bad password.
* \i 'IPCOM_ERR_PENDING'
* Non-blocking login, the authentication reply is pending and the
* auth_login_hook() routine will be called when a result is available.
* \i 'IPCOM_ERR_AUTH_UNKNOWN'
* Unknown user (only returned without RADIUS support).
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipcom_auth_ctx_login
(
    const char *username,
    const char *password,
    Ipcom_auth_userinfo *userinfo,
    Ipcom_auth_login_hook auth_login_hook,
    void *auth_login_cookie,
    int login_interface,
    Ip_fd socket
);


/*******************************************************************************
*
* ipcom_auth_chap_login - validate username
*
* This routine validates username using <chap_response>, <ident>, and
* <challenge>. The routine looks up the user and validates the password using
* the MD5 Challenge-Handshake Authentication Protocol (CHAP) challenge/response
* syntax used in PPP. It is currently supported only in conjunction with the
* RADIUS protocol. In other words the local VxWorks user database is not used
* when this routine is invoked.
*
* If the RADIUS client support is compiled in, the function validates the user
* by sending a RADIUS client access request packet to a RADIUS server.
*
* When RADIUS is used, the routine can operate in either blocking and non-
* blocking mode.  In non-blocking mode, the routine is run with an optional
* pointer to a user function and a cookie.  The user function is called when
* authentication is complete.
*
* In non-blocking mode, if the authentication cannot be immediately resolved,
* 'IPCOM_ERR_PENDING' is returned and the user routine is called when the
* authentication completes.
*
* Note that even in non-blocking mode, the function may return success
* immediately, if a local user exists and the password check was valid.
*
* Parameters:
* \is
* \i <username>
* Name of the user to validate.
* \i <chap_response>
* CHAP response, 16 bytes long.
* \i <chap_ident>
* 8-bit CHAP identifier.
* \i <chap_challenge, chap_challenge_size>
* CHAP challenge data and length.
* \i <userinfo>
* Pointer to an 'ipcom_auth_userinfo structure', if user information such as the
* user ID is desired. Can optionally be 'IP_NULL', if no additional information
* is desired.
* \i <auth_login_hook>
* When RADIUS is used, this routine can run in either blocking mode or non-
* blocking mode.  For blocking mode, set <auth_login_hook> to 'IP_NULL'.
* For non-blocking mode, use a pointer to an 'ipcom_auth_login_hook()' routine,
* which is called when the authentication is complete.
* \i <auth_login_cookie>
* User 32-bit cookie which is supplied in the auth_login_hook().
* \ie
*
* RETURNS: 'IPCOM_SUCCESS', or one of the following errors:
* \is
* \i 'IPCOM_ERR_AUTH_FAILED'
* Valid user, bad password.
* \i 'IPCOM_ERR_PENDING'
* Non-blocking login, the authentication reply is pending and the
* auth_login_hook() will be called when a result is available.
* \i 'IPCOM_ERR_AUTH_UNKNOWN'
* Unknown user (only returned without RADIUS support).
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipcom_auth_chap_login
(
    const char *username,
    Ipcom_auth_chap *chap,
    Ipcom_auth_userinfo *userinfo,
    Ipcom_auth_login_hook auth_login_hook,
    void *auth_login_cookie
);

IP_PUBLIC Ip_err ipcom_auth_logout
(
    const char *username,
    int login_interface
);

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

















