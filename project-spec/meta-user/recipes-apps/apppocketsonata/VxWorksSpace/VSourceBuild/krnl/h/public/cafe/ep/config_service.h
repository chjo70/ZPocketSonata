/* cafe_config_service - TCF service for controlling Cafe Configurations */

/*
 * Copyright (c) 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


#if !defined(__cafe_config_service_h)
#define __cafe_config_service_h

#if defined(__cplusplus)
extern "C" {
#endif

#if 0
#  include <framework/protocol.h>
#else
/* This is a workaround for TCF's namespace pollution.  The issue is that
   including protocol.h globally defines "LINK" which is also defined, for
   example in VxWorks' usb/usbListLib.h header.  This change can be reverted
   once either TCF or VxWorks have been fixed to define less generic names. */
struct Protocol;
struct Channel;
#endif


/**
 * Initialize Configuration control service.
 */
extern void ini_cafe_config_service(struct Protocol *);


extern void *cafe_event_thread(void *unused);


extern struct Channel *cafe_config_channel_up;
extern struct Channel *cafe_config_channel_down;


#if !defined(__VXWORKS__)
/**
 *  Register all common Cafe EP specifications.  This isn't necessary for
 * VxWorks targets because they toggle availability and initialization of
 * individual specifications using its own component system.
 */
extern void register_common_EPs(void);
#endif


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif  /* if !defined(__cafe_config_service_h) */
