/* 10vxbus.cdf - Component configuration file */

/*
 * Copyright (c) 2013-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------
16jun17,mjn  text updates, as well as removal of hwif folder (F8862)
07oct16,mca  Make INCLUDE_VXBUS_IOCTL_USER component handle
             _WRS_CONFIG_CERT_KERNEL_OBJECT case.
07jun16,dlk  Make INCLUDE_VXBUS_PARAMS component handle
             _WRS_CONFIG_CERT_KERNEL_OBJECT case.
17may16,wap  Make the user mode ioctl component conditional on its
             corresponding VSB configuration setting
13may16,wap  Fix orphaned components, add linkage for user mode library,
             add component for parameter library
26apr16,emj  CERT: Update to produce partially linked objects
25apr16,pmr  make ISR deferral task stack size configurable (V7SP-978)
18feb16,l_z  add IOCTL component to FOLDER_HWIF. (V7PRO-2872)
06oct15,wap  Add the DMA32_LIB component when building for LP64 targets
02oct15,wap  Make vxbIoctlLib init routine name consistent with others
02oct15,wap  Change user-space component suffix name from RTP to USER
02oct15,wap  Add support for user-space VxBus interface (F2165)
23jan15,ggm  HYP-10148 - updated INIT_BEFORE for INCLUDE_VXBUS_IOCTL component
15dec14,to   US50371 - added missing PROTOTYPE for INCLUDE_VXBUS_IOCTL
02dec14,ggm  US50371 - added INCLUDE_VXBUS_IOCTL and INCLUDE_VXBUS_IOCTL_SHOW.
16oct13,x_z  fixed initialization order for INCLUDE_VXBUS.
20sep13,x_z  moved INCLUDE_ISR_DEFER from vxcore.
16jul13,l_z  created for VxBus GEN2
*/



Component INCLUDE_VXBUS {
        NAME            VxBus subsystem
        SYNOPSIS        This component provides a routines to initalize the VxBus subsystem.
        HDR_FILES       hwif/vxBus.h
        INIT_RTN        vxbLibInit ();
        _INIT_ORDER     usrRoot
        INIT_AFTER      usrIosCoreInit
        INIT_BEFORE     INCLUDE_DEFERRED_INTERRUPT_ENABLE
        _CHILDREN       FOLDER_SUBSYSTEM
}

Component INCLUDE_VXBUS_SHOW {
        NAME            VxBus subsystem show routines
        SYNOPSIS        This component provides a library which provides the interfaces used for displaying \
                        information about the elements in the VxBus subsystem.
        MODULES         vxbShowLib.o
        REQUIRES        INCLUDE_VXBUS
        LINK_SYMS       vxbDevShow vxbDrvShow
        _CHILDREN       FOLDER_SUBSYSTEM
}

Component INCLUDE_VXBUS_IOCTL {
        NAME            VxBus IOCTL traverse API
        SYNOPSIS        VxBus GEN2 was designed to hide the internal device tree structures whenever\
                        possible so as to avoid having external references to device node structures\
                        that might become stale if a device was removed from the tree. In some cases\
                        however, we would like for external applications to be able to walk the VxBus\
                        tree and perform certain operations while still maintaining an abstraction.\
                        This component implements an ioctl() interface to VxBus that allows device nodes\
                        and their resources to be enumerated without exporting device node pointers\
                        to application code.
        MODULES         vxbIoctlLib.o
        REQUIRES        INCLUDE_VXBUS
        HDR_FILES       hwif/vxbus/vxbIoctlLib.h
        INIT_RTN        vxbIoctlLibInit ();
        _INIT_ORDER     usrRoot
        INIT_AFTER      INCLUDE_VXBUS
        INIT_BEFORE     INCLUDE_DEFERRED_INTERRUPT_ENABLE \
                        INCLUDE_USER_APPL
        _CHILDREN       FOLDER_SUBSYSTEM
}

#ifdef _WRS_CONFIG_VXBUS_USER
Component INCLUDE_VXBUS_IOCTL_USER {
        NAME            VxBus RTP IOCTL API
        SYNOPSIS        This component provides the VxBus RTP IOCTL API which adds support for RTPs to \
                        claim kernel device nodes and bind their own drivers to them.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         vxbRtpIoctlLib.o
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
#ifdef _WRS_CONFIG_LP64
        REQUIRES        INCLUDE_VXBUS \
                        INCLUDE_CACHE_DMA32_LIB \
                        INCLUDE_RTP
#else /* _WRS_CONFIG_LP64 */
        REQUIRES        INCLUDE_VXBUS \
                        INCLUDE_RTP
#endif /* _WRS_CONFIG_LP64 */
        HDR_FILES       hwif/vxbus/vxbRtpIoctlLib.h
        INIT_RTN        vxbRtpIoctlLibInit ();
        _INIT_ORDER     usrRtpInit
        INIT_AFTER      INCLUDE_RTP
        INCLUDE_WHEN    INCLUDE_RTP
        _CHILDREN       FOLDER_SUBSYSTEM
}
#endif /* _WRS_CONFIG_VXBUS_USER */

Component INCLUDE_VXBUS_IOCTL_SHOW {
        NAME            VxBus IOCTL show routine
        SYNOPSIS        This component provides the VxBus show routine, which uses the virtual device "/vxbus" and dumps the device tree \
                        and resources used by each device.
        MODULES         vxbIoctlShow.o
        REQUIRES        INCLUDE_VXBUS_IOCTL
        LINK_SYMS       vxbIoctlShow
        _CHILDREN       FOLDER_SUBSYSTEM
}

Component INCLUDE_VXBUS_PARAMS {
        NAME            VxBus driver parameter utilities
        SYNOPSIS        This component provides the mechanism for drivers to obtain parameter \
                        values.  Driver parameters are values which have a useful default \
                        value which can be overridden by BSPs (DTS file). 
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         vxbParamLib.o
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_VXBUS
        HDR_FILES       hwif/util/vxbParamLib.h
        INIT_RTN        vxbParamLibInit ();
        _INIT_ORDER     usrRoot
        INIT_BEFORE     INCLUDE_VXBUS
        INCLUDE_WHEN    INCLUDE_VXBUS
        _CHILDREN       FOLDER_SUBSYSTEM
}

Component INCLUDE_ISR_DEFER {
        NAME            ISR deferral library
        SYNOPSIS        This component provides the ISR defferal library used by interrupt service routines to defer interrupt \
                        processing from interrupt context to task context.  Device drivers \
                        use this library by allocating a deferral task, and then enqueueing \
                        work on the task's work queue.  This library is designed to work with \
                        VxBus-compliant device drivers. 
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         vxbIsrDeferLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_KERNEL              \
                        INCLUDE_ANSI_STRCPY         \
                        INCLUDE_LSTLIB              \
                        INCLUDE_SEM_BINARY_CREATE   \
                        INCLUDE_SEM_BINARY          \
                        SELECT_MEM_ALLOC            \
                        INCLUDE_TASK_CREATE_DELETE  \
                        INCLUDE_VXBUS
        INIT_RTN        usrIsrDeferInit ();
        HDR_FILES       hwif/util/vxbIsrDeferLib.h
        CONFIGLETTES    usrIsrDefer.c
        CFG_PARAMS      ISR_DEFER_MODE              \
                        ISR_DEFER_TASK_STACK_SIZE
        _CHILDREN       FOLDER_SUBSYSTEM
}

Parameter ISR_DEFER_MODE {
    NAME                ISR deferral mode
    SYNOPSIS            This parameter specifies the interrupt service routines deferral handling global mode.
    TYPE                int
    DEFAULT             ISR_DEFER_MODE_PER_CPU
}

Parameter ISR_DEFER_TASK_STACK_SIZE {
    NAME                ISR deferral task stack size
    SYNOPSIS            This parameter specifies the interrupt service routines deferral task stack size.
    TYPE                int
    DEFAULT             8192
}
