/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

 
/* THIS IS GENERATED CODE. DO NOT MODIFY */

#ifndef INCsystem_info_types_h
#define INCsystem_info_types_h

#ifdef __cplusplus
extern "C" {
#endif
#define SYSTEM_INFO___SYSINFO_ROW_VT_DEF "S[sysinfo_row,k[key,s]v[value,s]]"
#define SYSTEM_INFO___SYSINFO_ROW_VT_REF "t[sysinfo_row]"

#define SYSTEM_INFO___WORKAREA_VT_DEF "S[system_info.workarea,v[sysname,s]v[release,s]v[version,s]v[properties,D[t[sysinfo_row]]]]"
#define SYSTEM_INFO___WORKAREA_VT_REF "t[system_info.workarea]"



#define SYSTEM_INFO___ALL_TYPE_DEFS \
    SYSTEM_INFO___SYSINFO_ROW_VT_DEF \
    SYSTEM_INFO___WORKAREA_VT_DEF

#define SYSTEM_INFO___ALL_TYPE_REFS \
    SYSTEM_INFO___SYSINFO_ROW_VT_REF \
    SYSTEM_INFO___WORKAREA_VT_REF

#ifndef SYSINFO_ROW_STRUCT_DEF
#define SYSINFO_ROW_STRUCT_DEF
struct sysinfo_row {
    char* key;  /* key */
    char* value; 
};
#endif /* SYSINFO_ROW_STRUCT_DEF */

#ifndef SYSTEM_INFO___WORKAREA_STRUCT_DEF
#define SYSTEM_INFO___WORKAREA_STRUCT_DEF
struct system_info___workarea {
    char* sysname; 
    char* release; 
    char* version; 
struct cafe_dict_struct properties; 
};
#endif /* SYSTEM_INFO___WORKAREA_STRUCT_DEF */

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* INCsystem_info_types_h */
