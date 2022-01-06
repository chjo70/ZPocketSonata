/* 02comp_ipnet_ldapc.cdf - IPNet LDAPC configuration file */

/*
 * Copyright (c) 2006, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
02feb17,jbm  Editing name and synopsis
27sep06,kch  created.
*/

Component INCLUDE_IPLDAPC {
    NAME            LDAPC
    SYNOPSIS        This component includes support for the Lightweight Directory \
                    Access Protocol (LDAP) client.
    MODULES         ipldapc.o ipldapc_example.o ipldapc_filter.o \
                    ipldapc_srvcall.o ipldapc_util.o
    CONFIGLETTES    ipldapc_config.c
}

Component INCLUDE_IPLDAPC_ADD_CMD {
    NAME            IPCOM ldapadd commands
    SYNOPSIS        This component includes the shell command, ldapadd, which is \
                    used to add entries to a Lightweight Directory Access \
                    Protocol (LDAP) directory.
    MODULES         ipldapc_cmd_add.o
    REQUIRES        INCLUDE_IPLDAPC INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPLDAPC_COMPARE_CMD {
    NAME            IPCOM ldapcompare commands
    SYNOPSIS        This component includes the shell command, ldapcompare, which \
                    is used to compare the attributes of an entry with the \
                    attributes specified at the command line. The command \
                    writes "true" or "false" to standard out to show the outcome \
                    of the comparison.
    MODULES         ipldapc_cmd_compare.o
    REQUIRES        INCLUDE_IPLDAPC INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPLDAPC_DELETE_CMD {
    NAME            IPCOM ldapdelete commands
    SYNOPSIS        This component includes the shell command, ldapdelete, which \
                    is used to delete entries from a Lightweight Directory Access \
                    Protocol (LDAP) directory.
    MODULES         ipldapc_cmd_delete.o
    REQUIRES        INCLUDE_IPLDAPC INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPLDAPC_MODIFY_CMD {
    NAME            IPCOM ldapmodify commands
    SYNOPSIS        This component includes the shell command, ldapmodify, which \
                    is used to change the attribute value(s) of an entry.
    MODULES         ipldapc_cmd_modify.o
    REQUIRES        INCLUDE_IPLDAPC INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPLDAPC_MODIFYDN_CMD {
    NAME            IPCOM ldapmodifydn commands
    SYNOPSIS        This component includes the shell command, ldapmodifydn, \
                    which is used to change the relative distinguished name of \
                    an entry.
    MODULES         ipldapc_cmd_modifydn.o
    REQUIRES        INCLUDE_IPLDAPC INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPLDAPC_SEARCH_CMD {
    NAME            IPCOM ldapsearch commands
    SYNOPSIS        This component includes the shell command, ldapsearch, which \
                    searches a part of the Lightweight Directory Access Protocol \
                    (LDAP) directory and returns all entries that match the search \
                    filter. The syntax for search filters is specified in RFC 2254. \
                    The command can connect to the LDAP server using SSL. All \
                    matching entries are printed to stdout.
    MODULES         ipldapc_cmd_search.o
    REQUIRES        INCLUDE_IPLDAPC INCLUDE_IPCOM_SHELL_CMD
}

