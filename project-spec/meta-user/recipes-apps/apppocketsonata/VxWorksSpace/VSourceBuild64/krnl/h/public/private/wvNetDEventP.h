/* wvNetDEventP.h - header file for WindView WindNet IPv6/IPv4 event ids */

/* Copyright 2003,2004,2008,2010, 2012, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07sep15,wzc  _WRS_CONFIG_SV_INSTRUMENTATION is enough.(V7COR-3476)
13jul12,h_x  Fix warnings.
30dec10,vhe  Changed pWvNetEventMap to pWvNetEvtMap (CQ:WIND00237112)
06oct08,tcr  fix Coverity warnings
10sep08,tcr  Fix WIND00133631 (exception dereferencing pWvNetEventMap if
             INCLUDE_WV_NETD not present)
15aug08,tcr  temproary build fix
31jul08,tcr  code review changes
09may08,tcr  change name of event_point_handler
25apr08,tcr  change WV to use eventpoints
27may08,jpb  Modifications for source build.  Renamed WV_INSTRUMENTATION
             to _WRS_CONFIG_SV_INSTRUMENTATION.
07jul04,vvv  fixed warnings (statement not reached)
02apr04,spm  fixed virtual stack build: enabled required values
24feb04,syy  Update wvNetDEventInfo structure
23jan04,syy  Added WV class check to macros
17dec03,syy  Remove evtLogOBinary() workaround
16dec03,syy  Fixed a typo that caused build problem
11dec03,syy  Code adjustment and clean up
08dec03,syy  Networking WindView instrumentation merge
04nov03,syy  WV Instrumentation changes
20oct03,syy  Added #ifdef WV_INSTRUMENTATION
04sep03,tar  Windview instrumentation codereview changes
05aug03,tar  written
*/

#ifndef __INCwvNetDEventPh
#define __INCwvNetDEventPh

#ifdef __cplusplus
extern "C" {
#endif

typedef struct eventmask
    {
    UCHAR bitmap [8];     /* Map indicating selection status of events. */
    }
EVENT_MASK;

IMPORT EVENT_MASK * pWvNetEvtMap;

#define MIN_WVNET_EVENTID 	20000  
#define MAX_WVNET_EVENTID 	24999

#define WVNET_EVENT(id) 	(MIN_WVNET_EVENTID + id)

#define WVNET_MASKSIZE 	8 	/* Allows 57 to 64 events per level. */

#ifdef IPCOM_WV_INSTRUMENTATION
static char wvNetDEventBlob [8];
#endif


/*
 * The WV_BLOCK_START macro prevents wasted cycles by determining if
 * WindView is running and if the given class has been selected. It
 * provides initial screening for reporting network events to WindView.
 * WV_CLASS_3 is for "Additional Instrumentation" selection.
 * The classId is NETD_IP4_DATAPATH_EVENT, NETD_IP4_CTRLPATH_EVENT,
 * NETD_IP6_DATAPATH_EVENT or NETD_IP6_CTRLPATH_EVENT.
 */

#define WV_BLOCK_START(classId)    \
    if (ACTION_IS_SET && (pWvNetEvtMap != NULL))    \
        {
/*
 * The WV_NETD_EVENT_TEST macro evaluates to TRUE if the event is selected
 * for inclusion in the WindView updates sent to the host. The event
 * selection status is stored in a bitmap accessed by priority level.
 * This macro is only valid within a test conditional after the
 * WV_BLOCK_START macro verifies that the class is active. The eventLevel
 * parameter has values determined by the constants defined below, and
 * the offset indicates the ordinal number of the event for the given
 * level (ranging from 0 upward).
 */

#define WV_NETD_EVENT_TEST(eventLevel, offset) \
 pWvNetEvtMap [eventLevel - 1].bitmap [WVNET_MASKSIZE - 1 - (offset / 8)] & \
                                                           (1 << (offset % 8))

/*
 * The WV_BLOCK_END provides a footer for all code which reports network
 * events to WindView. It closes the open scopes caused by WV_BLOCK_START.
 * The classId parameter is not used, but is included for symmetry.
 */

#define WV_BLOCK_END(classId)    \
        }

#if defined (_WRS_CONFIG_SV_INSTRUMENTATION) 

/*
 * The macros stores all the arguments and the string into a structure to pass
 * to the logging routine. The eventId is also stored in the structure, and a
 * fixed eventId is passed to the eventpoint. The data collector will extract
 * the eventId from the arguments, and pass it to the logging routines. This
 * means that a single data collector can be used for all the network events.
 */
    
#define WV_EVT_LOG_OBIN(EVTID, NARGS, INFO, ARG1, ARG2, ARG3, ARG4, ARG5, SIZE, PAYLOAD) \
do { \
        EVT_STR_NET_T evt_wv_net; \
        evt_wv_net.args [0] = INFO; \
        evt_wv_net.args [1] = ARG1; \
        evt_wv_net.args [2] = ARG2; \
        evt_wv_net.args [3] = ARG3; \
        evt_wv_net.args [4] = ARG4; \
        evt_wv_net.evtId = EVTID; \
        evt_wv_net.nParams = NARGS; \
        evt_wv_net.length = SIZE; \
        evt_wv_net.pData = PAYLOAD; \
        eventPointSwHandle (WV_NETD_BASE_EVENT, &evt_wv_net, sizeof(evt_wv_net) ); \
} while (0)

/*
 * Event data binary block consists of three parts: the data format ID,
 * two optional parameters, each can be either non IP address or IP address.
 * The interpretation of the event data is governed by the format ID (the
 * first byte). Various formats are defined in the section below.
 *
 *   wvNetDEventBlob [0]   - event data format 
 *   wvNetDEventBlob [1-4] - first event data in UINT32 (optional)
 *   wvNetDEventBlob [5-8] - second event data in UINT32 (optional)
 */
    
/*
 * Event data format indicator bit definitions
 */
#define WV_NETD_EVT_PARAM_ONE    0x01
#define WV_NETD_EVT_PARAM_TWO    0x02
#define WV_NETD_EVT_V4_ADDR      0x04
#define WV_NETD_EVT_V6_ADDR      0x08

/*
 * List of allowed event data formats:
 *
 * WV_NETD_EVT_FMT_1P: one non- IP address parameter;
 * WV_NETD_EVT_FMT_2P: two  that non- IP address parameters;
 * WV_NETD_EVT_FMT_1P_V4: one non- IP address parameter and one IPv4 address;
 * WV_NETD_EVT_FMT_1P_V6: one non- IP address parameter and one ptr to the 
 *                        IPv6 address structure;
 * WV_NETD_EVT_FMT_V4: two IPv4 addresses;
 * WV_NETD_EVT_FMT_V6: two ptr's to the IPv6 addresse structures;
 */
#define WV_NETD_EVT_FMT_1P       WV_NETD_EVT_PARAM_ONE
#define WV_NETD_EVT_FMT_2P       WV_NETD_EVT_PARAM_ONE | WV_NETD_EVT_PARAM_TWO
#define WV_NETD_EVT_FMT_1P_V4    WV_NETD_EVT_PARAM_ONE | WV_NETD_EVT_V4_ADDR
#define WV_NETD_EVT_FMT_1P_V6    WV_NETD_EVT_PARAM_ONE | WV_NETD_EVT_V6_ADDR
#define WV_NETD_EVT_FMT_V4       WV_NETD_EVT_V4_ADDR
#define WV_NETD_EVT_FMT_V6       WV_NETD_EVT_V6_ADDR
    
/*
 * The following macros accept an argument of struct sockaddr type and return the
 * sockaddr_in for IPv4 and return the address of the struct for IPv6.
 */   
#define WV_SOCKADDR_IN(s)  (((struct sockaddr_in *)(s))->sin_addr.s_addr)
    
#ifdef INET6
    
#else
#define WV_ADDR_GET(pAddr) (pAddr == NULL ? 0 : \
   (((struct sockaddr *)pAddr)->sa_family == AF_INET ? \
    (((struct sockaddr_in *)pAddr)->sin_addr.s_addr) : 0))

#define WV_ADDR_FAMILY_GET(pAddr)  (pAddr == NULL ? 0 : \
   (((struct sockaddr *)pAddr)->sa_family == AF_INET ? \
    WV_NETD_EVT_V4_ADDR : 0))
#endif /* INET6 */    

/*
 * The WV_EVT_INFO_SET_ALL macro constructs the WindView event information
 * field in the event data using the following structure:
 *
 * <Component ID>:<Status>:<Filter ID>:<Entity ID>:<Module ID>:<Event Tag>
 *    (2 bits)    (2 bits)   (4 bits)   (8 bits)     (8 bits)   (8 bits)
 *
 * The component ID is a fixed value for all WindNet IPv6/IPv4 stack code, The
 * values of other fields, except Event Tag, use the constants defined
 * below. The packet filter type (Filter ID), Entity ID and Module ID are
 * assigned using local #defin'se within each module. The final field (Event
 * Tag) is a unique identifier for each event within a given module.
 *
 * Currently, the packet filter is not used. But it may be used for refined
 * event filtering someday.
 *
 * The resulting event information is stored in the ULONG variable
 * wvNetDEventInfo, local to the file module.
 */

#define WV_EVT_INFO_SET_ALL(eventLevel, eventTag, status)                  \
do { \
    wvNetDEventInfo = ((UINT32)(WV_NET_DUAL_ID << 30)) | (status << 28)             \
                      | (wvNetDLocalFilter << 24) | (wvNetDEntityId << 16) \
                      |  (wvNetDModuleId << 8) | eventTag; \
} while (0)

/* Macro sets evenInfo fields, except "Status" */    
#define WV_EVT_INFO_SET(eventLevel, eventTag)                              \
do { \
    wvNetDEventInfo = ((UINT32)(WV_NET_DUAL_ID << 30)) | (wvNetDLocalFilter << 24)  \
                      | (wvNetDEntityId << 16) | (wvNetDModuleId << 8)     \
                      | eventTag; \
} while (0)

    /* Store the 4 bytes of an UINT32 into blob */
#define WV_ASSIGN_BLOB(blob, arg) \
do { \
     *(&(blob)) = (UCHAR)((((UINT32) arg) >> 24) & 0xff); \
     *(&(blob) + 1) = (UCHAR)((((UINT32) arg) >> 16) & 0xff); \
     *(&(blob) + 2) = (UCHAR)((((UINT32) arg) >>  8) & 0xff); \
     *(&(blob) + 3) = (UCHAR)((((UINT32) arg) >>  0) & 0xff); \
     *(&(blob) + 4) = '\n'; \
} while (0)
 
/*
 * To minimize the size of the log, for V6 address, only the ptr to struct
 * sockadd will be logged.
 *
 * format: 0x1 - one parameter; 0x3 - two parameters; 
 */

#define WV_EVT_BLOB_SET0(format, arg1, arg2)                 \
  do {                                                       \
       wvNetDEventBlob[0] = (UCHAR) format;                  \
       if ((format) & WV_NETD_EVT_PARAM_ONE)                 \
           WV_ASSIGN_BLOB(wvNetDEventBlob[1], arg1);         \
       if ((format) & WV_NETD_EVT_PARAM_TWO)                 \
           WV_ASSIGN_BLOB(wvNetDEventBlob[5], arg2);         \
      } while (0)

/*
 * The WindView for networking marker events handles cases which do not
 * involve data transfer. The transmission direction (i.e. - status) field
 * in the event identifier is always 0. Up to four additional parameters
 * may be sent to the host.
 */
    
#define WV_NET_MARKER_1(classId, eventLevel, eventOffset, eventTag, eventId, arg1) \
    WV_BLOCK_START (classId) \
    if (WV_NETD_EVENT_TEST (eventLevel, eventOffset)) \
        {    \
        UINT32 wvNetDEventInfo;  \
        WV_EVT_INFO_SET (eventLevel, eventTag); \
        WV_EVT_LOG_OBIN (eventId, 3, wvNetDEventInfo, (_Vx_usr_arg_t)arg1, 0, 0, 0, 0, 0, NULL); \
        } \
    WV_BLOCK_END (classId)

#define WV_NET_MARKER_2(classId, eventLevel, eventOffset, eventTag, eventId, arg1, arg2) \
    WV_BLOCK_START (classId) \
    if (WV_NETD_EVENT_TEST (eventLevel, eventOffset)) \
        {    \
        UINT32 wvNetDEventInfo;  \
        WV_EVT_INFO_SET (eventLevel, eventTag); \
        WV_EVT_LOG_OBIN (eventId, 3, wvNetDEventInfo, (_Vx_usr_arg_t)arg1, (_Vx_usr_arg_t)arg2, 0, 0, 0, 0, NULL); \
        } \
    WV_BLOCK_END (classId)

/* when the last argument is a parameter */
#define WV_NET_MARKER_3(classId, eventLevel, eventOffset, eventTag, eventId, arg1, arg2, arg3) \
    WV_BLOCK_START (classId) \
    if (WV_NETD_EVENT_TEST (eventLevel, eventOffset)) \
        {    \
        UCHAR wvNetDEventBlob[12]; \
        UINT32 wvNetDEventInfo;  \
        WV_EVT_INFO_SET (eventLevel, eventTag); \
        WV_EVT_BLOB_SET0 (WV_NETD_EVT_FMT_1P, arg3, 0); \
        WV_EVT_LOG_OBIN (eventId, 3, wvNetDEventInfo, (_Vx_usr_arg_t)arg1, (_Vx_usr_arg_t)arg2, 0, 0, 0, \
                         sizeof (wvNetDEventBlob), (char *)wvNetDEventBlob); \
        } \
    WV_BLOCK_END (classId)



/* when the last two arguments are parameters */
#define WV_NET_MARKER_4(classId, eventLevel, eventOffset, eventTag, eventId, arg1, arg2, arg3, arg4) \
    WV_BLOCK_START (classId) \
    if (WV_NETD_EVENT_TEST (eventLevel, eventOffset)) \
        {    \
        UINT32 wvNetDEventInfo;  \
        UCHAR wvNetDEventBlob[12]; \
        WV_EVT_INFO_SET (eventLevel, eventTag); \
        WV_EVT_BLOB_SET0 (WV_NETD_EVT_FMT_2P, arg3, arg4); \
        WV_EVT_LOG_OBIN (eventId, 3, wvNetDEventInfo, (_Vx_usr_arg_t)arg1, (_Vx_usr_arg_t)arg2, 0, 0, 0, \
                         sizeof (wvNetDEventBlob), (char *)wvNetDEventBlob); \
        } \
    WV_BLOCK_END (classId)

/*
 * The WindView for networking data transfer events store a transmission
 * direction in the status field of the event identifier. Valid values are
 * WV_NET_SEND and WV_NET_RECV. Up to four additional parameters may be sent
 * to the host.
 */

#define WV_NET_EVENT_1(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1) \
    WV_BLOCK_START (classId) \
    if (WV_NETD_EVENT_TEST (eventLevel, eventOffset)) \
        {    \
        UINT32 wvNetDEventInfo;  \
        WV_EVT_INFO_SET_ALL (eventLevel, eventTag, status); \
        WV_EVT_LOG_OBIN (eventId, 3, wvNetDEventInfo, (_Vx_usr_arg_t)arg1, 0, 0, 0, 0, 0, NULL); \
        } \
    WV_BLOCK_END (classId)

#define WV_NET_EVENT_2(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1, arg2) \
    WV_BLOCK_START (classId) \
    if (WV_NETD_EVENT_TEST (eventLevel, eventOffset)) \
        {    \
        UINT32 wvNetDEventInfo;  \
        WV_EVT_INFO_SET_ALL (eventLevel, eventTag, status); \
        WV_EVT_LOG_OBIN (eventId, 3, wvNetDEventInfo, (_Vx_usr_arg_t)arg1, (_Vx_usr_arg_t)arg2, 0, 0, 0, 0, NULL); \
        } \
    WV_BLOCK_END (classId)

#define WV_NET_EVENT_3(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1, arg2, arg3) \
    WV_BLOCK_START (classId) \
    if (WV_NETD_EVENT_TEST (eventLevel, eventOffset)) \
        {    \
	int format = WV_NETD_EVT_FMT_1P; \
        UINT32 wvNetDEventInfo;  \
        UCHAR wvNetDEventBlob[12]; \
        WV_EVT_INFO_SET_ALL (eventLevel, eventTag, status); \
        WV_EVT_BLOB_SET0 (format, arg3, 0); \
        WV_EVT_LOG_OBIN (eventId, 3, wvNetDEventInfo, (_Vx_usr_arg_t)arg1, (_Vx_usr_arg_t)arg2, 0, 0, 0, \
                         sizeof (wvNetDEventBlob), (char *)wvNetDEventBlob); \
        } \
    WV_BLOCK_END (classId)

#define WV_NET_EVENT_4(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1, arg2, arg3, arg4) \
    WV_BLOCK_START (classId) \
    if (WV_NETD_EVENT_TEST (eventLevel, eventOffset)) \
        {    \
        UINT32 wvNetDEventInfo;  \
        UCHAR wvNetDEventBlob[12]; \
        WV_EVT_INFO_SET_ALL (eventLevel, eventTag, status); \
        WV_EVT_BLOB_SET0 (WV_NETD_EVT_FMT_2P, arg3, arg4); \
        WV_EVT_LOG_OBIN (eventId, 3, wvNetDEventInfo, (_Vx_usr_arg_t)arg1, (_Vx_usr_arg_t)arg2, 0, 0, 0, \
                         sizeof (wvNetDEventBlob), (char *)wvNetDEventBlob); \
        } \
    WV_BLOCK_END (classId)

#else  /* when system viewer is excluded */

#define WV_ADDR_GET(pAddr) {}    
#define WV_NET_MARKER_1(classId, eventLevel, eventOffset, eventTag, eventId, arg1) {}
#define WV_NET_MARKER_2(classId, eventLevel, eventOffset, eventTag, eventId, arg1, arg2) {}
#define WV_NET_MARKER_3(classId, eventLevel, eventOffset, eventTag, eventId, arg1, arg2, arg3) {}
#define WV_NET_MARKER_4(classId, eventLevel, eventOffset, eventTag, eventId, arg1, arg2, arg3, arg4) {}
#define WV_NET_EVENT_1(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1) {}
#define WV_NET_EVENT_2(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1, arg2) {}
#define WV_NET_EVENT_3(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1, arg2, arg3) {}
#define WV_NET_EVENT_4(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1, arg2, arg3, arg4) {}
#endif /* _WRS_CONFIG_SV_INSTRUMENTATION */

#ifdef __cplusplus
}
#endif

#endif /* __INCwvNetDEventPh */
