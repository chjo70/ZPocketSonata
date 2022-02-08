/* vxmux_pkt.h - vxmux packet handling API */

/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef VXMUX_PKT_H
#define VXMUX_PKT_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * VXMUX packet manipulation routines.  Used by VxWorks MUX2/END2 code
 * to enable selection between full ipnet_pkt_pool library when IPNET
 * is configured in the image, and the more restricted vxmux_pkt_pool_min
 * library, supporting END2 drivers when IPNET is not included in the
 * VxWorks image.
 */

/*
DESCRIPTION
This library contains the API for IPCOM packets, used by VxWorks MUX2/END2
code to enable selection between full ipnet_pkt_pool library when IPNET
is configured in the image, and the more restricted vxmux_pkt_pool_min
library, supporting END2 drivers when IPNET is not included in the
VxWorks image.
INCLUDE FILES: ipcom_atomic.h, ipcom_cstyle.h, ipcom_type.h
*/

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include <vxmux_config.h>

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_pkt.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         Ipcom_pkt_done_func
 *===========================================================================
 * Function to free a packet from VxWorks code, possibly calling an output
 * done function.
 */
#ifdef IP_DEBUG

#define VXIPCOM_PKT_DONE(p) \
    do  { \
        Ipcom_port_pkt * p_ = (Ipcom_port_pkt *)(p);	\
	p_->pkt.done (&p_->pkt, __FILE__, __LINE__); \
    } while ((0))
#define VXIPCOM_PKT_FREE vxipcom_pkt_dfree
#else

#define VXIPCOM_PKT_DONE(p) \
    do  { \
        Ipcom_port_pkt * p_ = (Ipcom_port_pkt *)(p);	\
	p_->pkt.done (&p_->pkt); \
    } while ((0))
#define VXIPCOM_PKT_FREE vxipcom_pkt_free
#endif /* IP_DEBUG */


/*
 * The vxipcom* macros are the APIs called by MUX2/END2 code.
 * They expand either to the vxmux_* functions or the ipcom_*
 * functions.  The corresponding functions must be declared
 * equivalently.
 */

#ifdef VXMUX_USE_PKT_POOL_MIN
#define vxipcom_pkt_create vxmux_pkt_create
#define vxipcom_pkt_malloc vxmux_pkt_malloc
#define vxipcom_pkt_free   vxmux_pkt_free
#define vxipcom_pkt_dfree  vxmux_pkt_dfree
#define vxipcom_pktbuf_free vxmux_pktbuf_free
#define vxipcom_conf_pkt_pool_buffer_alignment \
    vxmux_conf_pkt_pool_buffer_alignment
#define vxipcom_conf_pkt_pool_buffer_extra_space \
    vxmux_conf_pkt_pool_buffer_extra_space
#define vxipcom_pkt_stack_malloc(mtu, fcflags, idx) \
    vxmux_pkt_malloc(mtu, fcflags)
#define vxipcom_pkt_stack_free(pkt, idx) \
    vxmux_pkt_free(pkt)
#else
#define vxipcom_pkt_create ipcom_pkt_create
#define vxipcom_pkt_malloc ipcom_pkt_malloc
#define vxipcom_pkt_free   ipcom_pkt_free
#define vxipcom_pkt_dfree  ipcom_pkt_dfree
#define vxipcom_pktbuf_free ipcom_pktbuf_free
#define vxipcom_conf_pkt_pool_buffer_alignment \
    ipcom_conf_pkt_pool_buffer_alignment
#define vxipcom_conf_pkt_pool_buffer_extra_space \
    ipcom_conf_pkt_pool_buffer_extra_space
#define vxipcom_pkt_stack_malloc(mtu, fcflags, idx) \
    ipcom_pkt_stack_malloc(mtu, fcflags, idx)
#define vxipcom_pkt_stack_free(pkt, idx) \
    ipcom_pkt_stack_free(pkt, idx)
#endif

IP_EXTERN Ip_size_t vxmux_conf_pkt_pool_buffer_alignment;
IP_EXTERN Ip_size_t vxmux_conf_pkt_pool_buffer_extra_space;

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/******************************************************************************
*
* vxmux_pktbuf_free - free packet buffer disassociated from Ipcom_pkt packet
*
* This routine frees a buffer that was previously allocated along with
* an Ipcom_pkt structure using a vxmux_pkt_malloc() call with non-zero
* <mtu> argument.
*
* The <buf> argument to this routine is the <data> member from the previously
* allocated Ipcom_pkt packet, and the <cookie> argument is the packet's
* <data_freefunc_cookie> member.  After recording the original packet's
* <data> and <data_freefunc_cookie> members, the packet's <data> member
* should be cleared to disassociate it from the packet buffer and prevent a
* double-free of the buffer when the original Ipcom_pkt is freed using
* vxmux_pkt_free().
*
* This function is intended to support limited cases in which it is
* convenient to allocate both an Ipcom_pkt packet header and a packet buffer
* in an vxmux_pkt_malloc() call, but to separate the parts for different
* uses with different lifetimes.  This kind of separation can increase
* cache efficiency in some network drivers that allocate RX packets out of
* the ipnet packet pool; the disassociated buffer can be put into the device's
* RX ring to receive a packet off the wire at some time in the future,
* while the disassociated and still cache-hot Ipcom_pkt can be reassociated
* with a filled buffer that holds a received packet for immediate delivery to
* the stack.
*
* Parameters:
* \is
* \i <pkt>
* A pointer to the packet to free.
* \ie
*
* RETURNS: \&N/A.
*
* ERRNO:
*/
IP_PUBLIC void vxmux_pktbuf_free
(
    Ip_u8 *buf,
    void * cookie
);

#ifdef IP_DEBUG
/*
 *===========================================================================
 *                    vxmux_pkt_dfree
 *===========================================================================
 * Description: Frees a packet that was allocated with vxmux_pkt_malloc().
 * Parameters:  pkt - The packet to free.
 *              file - The file the packet was freed in.
 *              line - The line the packet was freed at.
 * Returns:
 *
 */
IP_PUBLIC void vxmux_pkt_dfree(Ipcom_pkt *pkt, char *file, int line);
#define vxmux_pkt_free(pkt) vxmux_pkt_dfree(pkt, __FILE__, __LINE__)

/*
 *===========================================================================
 *                    vxmux_pkt_dmalloc
 *===========================================================================
 * Description: Allocates the requested amount of MTU data. MTU data is
 *              defined as IP + transport + application (not link header).
 * Parameters:  size  - The size of the data MTU in bytes.
 *              fcflags - function call flags (see ipcom_cstyle.h)
 *              file - The file the packet was allocated in.
 *              line - The line the packet was allocated at.
 * Returns:     A IPCOM packet.
 *
 */
IP_PUBLIC Ipcom_pkt *vxmux_pkt_dmalloc(Ip_size_t size, int fcflags, char *file, int line);
#define vxmux_pkt_malloc(size, fcflags) vxmux_pkt_dmalloc(size, fcflags, __FILE__, __LINE__)

#else /* ifndef IP_DEBUG */

/*******************************************************************************
*
* vxmux_pkt_free - free memory used by the 'Ipcom_pkt' structure
*
* This routine frees the memory used by the 'Ipcom_pkt' structure. The packet
* data buffer freefunc() function is called, if the packet was allocated with
* vxmux_pkt_create().
*
* Parameters:
* \is
* \i <pkt>
* A pointer to the packet to free.
* \ie
*
* RETURNS: \&N/A.
*
* ERRNO:
*/
IP_FASTTEXT IP_PUBLIC void vxmux_pkt_free
(
    Ipcom_pkt *pkt
);


/******************************************************************************
*
* vxmux_pkt_malloc - allocate memory for 'Ipcom_pkt' structures
*
* This routine is used to allocate memory for 'Ipcom_pkt' structures and
* associated packet buffers. The <size> parameter specifies the number of
* octets to allocate in the buffer for the IP header, transport header and
* application data. The TCP/IP stack adds space for the link-layer header, and
* reserves additional space for additional headers and alignment. This means
* that the full size of the data buffer will be greater than <size>.
*
* The total amount of memory allocated by vxipcom_pkt_malloc() can never exceed
* the predefined TCP/IP stack packet buffer pool <maxsize>.
*
* The <fcflags> parameter must be set based on blocking mode and the context of
* the process that calls ipcom_pkt_malloc(). Available flags are:
* \is
* \i 'IP_FLAG_FC_BLOCKOK'
* Ok for function call to block (used when default is non-blocking).
* \i 'IP_FLAG_FC_NOBLOCK'
* Function call may not block (used when default is blocking).
* \ie
*
* Parameters:
* \is
* \i <size>
* Size of the packet data buffer in bytes.
* \i <fcflags>
* Function call flags.
* \ie
*
* RETURNS: A pointer to a newly allocated packet structure, or 'IP_NULL', if no
* buffer was available.
*
* ERRNO:
*/
IP_FASTTEXT IP_PUBLIC Ipcom_pkt *vxmux_pkt_malloc
(
    Ip_size_t size,
    int fcflags
);

#endif /* IP_DEBUG */


/******************************************************************************
*
* vxipcom_pkt_create - create a valid 'ipcom_pkt' structure from user allocated
* memory
*
* This routine creates a valid 'Ipcom_pkt' structure from user allocated
* memory. This routine can be used to avoid doing memory copy of data from
* a device driver buffer into an 'Ipcom_pkt' structure.
*
* Parameters:
* \is
* \i <pkt>
* Pointer to a buffer which is large enough to hold an 'ipcom_pkt' structure.
* \i <data>
* Pointer to the buffer which contains the packet <data>.
* \i <data_len>
* The length of the data buffer.
* \i <freefunc>
* A routine that is called when the stack is finished using the packet.
* \i <cookie>
* User-defined data that is passed as the second argument to <freefunc>.
* \ie
*
* RETURNS: \&N/A.
*
* ERRNO:
*/
IP_FASTTEXT IP_PUBLIC void vxmux_pkt_create
(
    Ipcom_pkt *pkt,
    void *data,
    Ip_size_t data_len,
    Ipcom_pkt_freefunc freefunc,
    void *cookie
);

#ifdef IPCOM_USE_HW_CHECKSUM_TX
/***************************************************************************
*
* vxmux_calculate_transport_checksum - complete transport checksum on packet
*
* This routine may be called by IPNET-native drivers that support transport
* checksum offload on transmit, but for one reason or another cannot enable
* TX checksum offload on the current packet, for which it is requested.
* (For example, some devices cannot support transmit checksum offload
* over IPv4 for packets with IP options.)  Instead, this routine may
* be called to complete the transport layer checksum on the packet.
* This routine also clears the IPCOM_PKT_FLAG_HW_CHECKSUM flag, to mark
* the checksum as already complete, in case the driver send routine returns
* -IP_ERRNO_EWOULDBLOCK, the packet
*
* RETURNS: N/A
*
* ERRNO: None
*/
IP_PUBLIC void vxmux_calculate_transport_checksum
(
    Ipcom_pkt *pkt
);
#endif /* IPCOM_USE_HW_CHECKSUM_TX */


/*
 ****************************************************************************
 * 8                    VARIABLES
 ****************************************************************************
 */

#ifdef __cplusplus
}
#endif

#endif /* VXMUX_PKT_H */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
