/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef IPCOM_FORWARDER_H
#define IPCOM_FORWARDER_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
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
#include <ipcom_cstyle.h>
#include <ipcom_sock.h>
#include <ipcom_ipc_spinlock.h>
#include "ipcom_netif.h"

/* #include "ipcom_mipc.h" */

#ifdef IPCOM_USE_FORWARDER_VLAN_STACKING
#include <ipnet_netif.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* Uncomment for debug printfs */
/* #define FW_DEBUG 1 */
/* #define FW_IPSEC_DEBUG 1 */

#define IP_FORWARDER_TASK_NAME  "ipfwdr"
#define IPCOM_FORWARDER_MAX_TASKNAME_LEN (10)

#define IPCOM_FORWARDER_PACKET_TYPE_IPV4 (0)
#define IPCOM_FORWARDER_PACKET_TYPE_IPV6 (1)
#define IPCOM_FORWARDER_PACKET_TYPE_NONE (2)
#define IPCOM_FORWARDER_PACKET_TYPE_IPV4_VLAN (3)
#define IPCOM_FORWARDER_PACKET_TYPE_IPV6_VLAN (4)
#define IPCOM_FORWARDER_PACKET_DROP_PKT  (5)
#define IPCOM_FORWARDER_PACKET_TYPE_VLAN (6)

#define IPV4 (4)
#define IPV6 (6)
#define IP_IPv4 (0x0800)
#define IP_IPv6 (0x86dd)
#define IP_VLAN (0x8100)
#define VLAN_STACKING (0x88a8)     /* represent VLAN stacking pkt type id, */
                                   /* not necessary same as service TPID */

/* Frame type */
#define ETH_FRAME_C_VLAN        ip_htons(IP_VLAN)

#define LL_ETH_HDR_SZ (14)
#define LL_ETH_HDR_VLAN_SZ    (18)
#define LL_ETH_ADDR_SZ (6)
#define LL_ETH_ADDRS_SZ       (12)
#define LL_ETH_ADDRS_VLAN_SZ  (16)
#define MAX_FW_LL_HDR_SZ (24)
#define IPCOM_FW_FLOW_SZ (256)
#define LL_ETH_VLAN_ADD (4)
#define LL_ETH_VLAN_TYPE_SZ (2)

#ifdef IPCOM_USE_NEHALEM_FORWARDER

#define IPCOM_FORWARDER_MAC_HDR_ALIGN  /* align the MAC header, not the IP */
#define IPCOM_FW_MACBITS0_16(x) ((x >> 16U))

#define MAX_FW_PORTS (20)

#ifdef IPCOM_USE_NEHALEM_HYPERTHREAD

#define MAX_FW (15)             /* limited by number of TX queues on 82576 */
#define PAUSE() do {_WRS_ASM("pause");} while ((0))

#else

#define MAX_FW (11)
#define PAUSE() do {} while ((0))

#endif /* IPCOM_USE_NEHALEM_HYPERTHREAD */

#else
#define MAX_FW_PORTS (35)
#define MAX_FW (14)
#define PAUSE() do {} while ((0))

#endif /* IPCOM_USE_NEHALEM_FORWARDER */

#define FW_MSG(a)            ((a)->tbl[1])
#define IS_CONTROL_MSG_FW(m) (m->tbl[0] == IPCOM_FORWARDER_PACKET_TYPE_NONE && m->tbl[1] > FW_MSG_CONTROL_BASE)
#define IS_DROP_MSG_FW(m)    (m->tbl[0] == IPCOM_FORWARDER_PACKET_DROP_PKT)

#define IPCOM_FWD_IPSEC_CLEARTXT (0x0)
#define IPCOM_FWD_IPSEC_ENCRYPT  (0x1)
#define IPCOM_FWD_IPSEC_DECRYPT  (0x2)
#define IPCOM_FWD_IPSEC_NOCACHE  (0x3)

/* Supported algorithms */
#define IPCOM_FORWARDER_IPSEC_3DES_MD5    0
#define IPCOM_FORWARDER_IPSEC_3DES_SHA1   1
#define IPCOM_FORWARDER_IPSEC_AES_MD5     2
#define IPCOM_FORWARDER_IPSEC_AES_SHA1    3
#define IPCOM_FORWARDER_IPSEC_NULL_NULL   4
#define IPCOM_FORWARDER_IPSEC_ALG_MAX     5

#define IPCOM_FORWARDER_IPSEC_HMAC_LEN    12
#define IPCOM_FORWARDER_IPSEC_ESP_HLEN     8

#ifndef IPCOM_USE_NEHALEM_FORWARDER
#define IPCOM_USE_PER_PACKET_SRC_MAC         1
#endif /* IPCOM_USE_NEHALEM_FORWARDER */

/* port number 1-3 are reserved for MSD/WDB/IPCOM */
#define IPCOM_FORWARDER_MIPC_PORT    4

/* Allocation flags for ipcom_fw_cpu_mem_alloc() */
#define IPCOM_FW_CPU_MEM_ALLOC_DMA      1
#define IPCOM_FW_CPU_MEM_ALLOC_SHARED   2
#define IPCOM_FW_CPU_MEM_ALLOC_ZEROED   4

#ifdef IPCOM_USE_FORWARDER_VLAN_STACKING
/* port action flags */
#define IPCOM_FWD_VLAN_ADD_SVLAN          (1 << 0)
#define IPCOM_FWD_VLAN_DEL_SVLAN          (1 << 1)
#define IPCOM_FWD_VLAN_ADD_CVLAN          (1 << 2)
#define IPCOM_FWD_VLAN_PRI_REMAP          (1 << 3)
#define IPCOM_FWD_VLAN_DROP_NO_VID        (1 << 4)
#define IPCOM_FWD_VLAN_DROP_VID           (1 << 5)

/* pkt flags */
#define IPCOM_FWD_VLAN_PKT_SVTAG          (1 << 0)
#define IPCOM_FWD_VLAN_PKT_CVTAG          (1 << 1)
#define IPCOM_FWD_VLAN_PKT_BCAST          (1 << 2)
#define IPCOM_FWD_VLAN_PKT_MCAST          (1 << 3)
#define IPCOM_FWD_VLAN_PKT_MAPED          (1 << 4)

#define IPCOM_FWD_VLAN_PKT_BMCAST  (IPCOM_FWD_VLAN_PKT_BCAST|IPCOM_FWD_VLAN_PKT_MCAST)

/* port type flags */
#define IPCOM_FWD_VLAN_PORT_CS            (1 << 0)
#define IPCOM_FWD_VLAN_PORT_SC            (1 << 1)
#define IPCOM_FWD_VLAN_PORT_S             (1 << 2)

#define IPCOM_FWD_VLAN_PORT_PR  (IPCOM_FWD_VLAN_PORT_SC|IPCOM_FWD_VLAN_PORT_S)
#define IPCOM_FWD_VLAN_PORT_STACKING  (IPCOM_FWD_VLAN_PORT_CS|IPCOM_FWD_VLAN_PORT_SC|IPCOM_FWD_VLAN_PORT_S)
#endif


#ifdef IPCOM_CHK_DEBUG
#define IPCOM_NAE_VERIFY_ATOMIC(t) ipcom_nae_tag_atomic(t)
#else
#define IPCOM_NAE_VERIFY_ATOMIC(t)
#endif

#define IPCOM_USE_FWD_TRACE
#ifdef IPCOM_USE_FWD_TRACE
extern const char *ipcom_fwd_trace_file;
extern int ipcom_fwd_trace_line;
#define IPCOM_FWD_TRACE     { ipcom_fwd_trace_file = __FILE__; ipcom_fwd_trace_line = __LINE__; }
#define IPCOM_FWD_PRINT(x)  { printf x; }
#else
#define IPCOM_FWD_TRACE IP_NOOP
#endif


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

typedef struct port_stats_s
{
    Ip_u32      octets_lw;
    Ip_u32      octets_hw;
    Ip_u32      packets;

    Ip_u32  fw_frames;
    Ip_u32  fw_bytes;

    Ip_u32      multicast_packets;
    Ip_u32      broadcast_packets;

    Ip_u32      len_64_packets;
    Ip_u32      len_65_127_packets;
    Ip_u32      len_128_255_packets;
    Ip_u32      len_256_511_packets;
    Ip_u32      len_512_1023_packets;
    Ip_u32      len_1024_1518_packets;
    Ip_u32      len_1519_max_packets;

    Ip_u32      runt_packets;
    Ip_u32      runt_crc_packets;

    Ip_u32      oversize_packets;
    Ip_u32      oversize_crc_packets;

    Ip_u32  dropped_octets;
    Ip_u32  dropped_packets;

    Ip_u32  tx_packets;
    Ip_u32  tx_octets_lw;
    Ip_u32  tx_octets_hw;

} port_stats_t;

typedef struct port_statistics_s
{
    Ip_u32      dropped_octets;
    Ip_u32      dropped_packets;
    Ip_u32      pci_raw_packets;
    Ip_u32      octets;
    Ip_u32      packets;
    Ip_u32      multicast_packets;
    Ip_u32      broadcast_packets;
    Ip_u32      len_64_packets;
    Ip_u32      len_65_127_packets;
    Ip_u32      len_128_255_packets;
    Ip_u32      len_256_511_packets;
    Ip_u32      len_512_1023_packets;
    Ip_u32      len_1024_1518_packets;
    Ip_u32      len_1519_max_packets;
    Ip_u32      fcs_align_err_packets;
    Ip_u32      runt_packets;
    Ip_u32      runt_crc_packets;
    Ip_u32      oversize_packets;
    Ip_u32      oversize_crc_packets;
    Ip_u32  inb_packets;
    Ip_u64  inb_octets;
    Ip_u64      inb_errors;

    Ip_u32  non_fw_frames;
    Ip_u32  non_fw_bytes;

    Ip_u32  tx_packets;
    Ip_u64  tx_octets;

} port_statistics_t;

struct Ip_fwreq
{
    char    eth_name[IP_IFNAMSIZ];    /* if name, e.g. "eth0" */

    union {

        port_stats_t ps;
    }u;

};

#include "ipcom_align16.h"
typedef IP_PACKED1 struct Ipcom_fw_ipsec_sa_s
{
    /* offset 0 */
    Ip_u32 spi;      /* Network endian */
    /* offset 4 */
    Ip_u32 seq;
    /* offset 8 */
    Ip_u8 domain;
    Ip_u8 proto;
    Ip_u8 algid;
    Ip_u8 replay;
    /* offset 12 */
    Ip_u8 ivlen;
    Ip_u8 akeylen;
    Ip_u8 ekeylen;
    Ip_u8 blocklen;
    /* offset 16 */
    Ip_u32 src[4];   /* Network endian */
    /* offset 32 */
    Ip_u32 dst[4];   /* Network endian */
    /* offset 48 */
    Ip_u8 ekey[32];  /* Max encryption key is 32 bytes (AES) */
    /* offset 80 */
    Ip_u64 iv[2];    /* Max IV is 16 bytes (AES) */
    /* offset 96 */
    Ip_u8  akey[20]; /* Max authentication key is 20 bytes (SHA1) */
    /* offset 116 */
    Ip_u32 cache_id;
    /* offset 120 */
    Ip_u32 replay_counter;
    /* offset 124 */
    Ip_u32 replay_bitmap;
    /* total 128 bytes */
    Ip_u8 ictx[64];  /* HMAC IPAD context */
    Ip_u8 octx[64];  /* HMAC OPAD context */
    /* total 256 bytes */
}
IP_PACKED2 Ipcom_fw_ipsec_sa_t;
#include "ipcom_align16.h"

#ifdef IPCOM_USE_FORWARDER_VLAN_STACKING
typedef struct fw_cache_entry_vlan_stacking_s
{
    Ip_u16      s_vlan_id;
    Ip_u8       port_egress_tagged;
    /* A bit map structure to represent all tx ports. */
    /* The most significant bit represents (the highest port number plus 1) */
    /* Thus, each port is represented by a single bit. If that bit has a */
    /* value of 1, then this port is a tx port. */
    /* The represented port number range is [0,63]. */
    Ip_u8       tx_ports_num;                 /* number of tx ports */
    Ip_u32      tx_ports[2];
    Ip_u8       pri_mapping[8];
    Ip_u32      c_vlan_tag;
    Ip_u32      s_vlan_tag;
} fw_cache_entry_vlan_stacking_t;
#endif

#ifdef IPCOM_USE_P4080_FORWARDER
#define FW_WIDE_HASH
#endif

typedef struct fw_msg_ipsec_s
{
    /* Keep size a multiple of Ip_u32 */
    void  *fw_cookie;
    Ip_u16 len;
    Ip_u16 hlen;
    Ip_u16 headers;
    Ip_u16 trailers;
    Ip_u16 offset;
    Ip_u16 key;
    Ip_u8  dec;
    Ip_u8  kept;
    Ip_u8  async_encrypt;
    Ip_u8  async_decrypt;
    void  *fw_cache_entry;
    Ip_u32 hmac[3];
    Ip_u64 hw_spec;
} fw_msg_ipsec_t;

typedef struct fw_msg_s
{
    Ip_u8 tbl[2];
#ifdef FW_WIDE_HASH
    Ip_u32 fw_key;
#else
    Ip_u16 fw_key;
#endif
    Ip_u8 *packet;
#ifdef IPCOM_USE_FORWARDER_IPSEC
    fw_msg_ipsec_t ipsec;
#endif
#ifdef IPCOM_USE_FORWARDER_VLAN
    Ip_u16 vlan_id;
#endif

#ifdef IPCOM_USE_FORWARDER_VLAN_STACKING
    fw_cache_entry_vlan_stacking_t *evlan;  /* forwarder cache entry */
    Ip_u8  pkt_flags;
    Ip_s8  len_mod;
    Ip_u16 ctci, stci;
    Ip_u8  spri;             /* re-mapped S-VLAN priority */
    Ip_u64 orig_pkt;
#endif

    int ipprt;          /* incoming port id */
} fw_msg_t;

typedef struct fw_ip4_s
{
    Ip_u32 addr;
    Ip_u32 rci;

} fw_ip4_t;

typedef struct fw_ip6_s
{
    Ip_u64 addr[2];
    Ip_u32 rci;
#ifdef IPCOM_USE_FORWARDER_VLAN
    Ip_u16 type;
    Ip_u16 vlan_id;
#endif
} fw_ip6_t;

typedef struct fw_ip_vlan_s
{
    union {
        Ip_u32 addr_v4;
        Ip_u64 addr_v6[2];
    } a;
    Ip_u32 rci;
    Ip_u16 type;
    Ip_u16 vlan_id;

} fw_ip_vlan_t;

typedef union fw_mac_if_u
{
    Ip_u64 dst_mac64;
    Ip_u32 dst_mac[2];
    Ip_u16 dst_mac_u16[4];
    Ip_u8  dst_mac_u8[8];
    Ip_u8  ix[8];
    Ip_u8  enc[8];

} fw_mac_if_t;

/*
 * IPCOM_FW_NBR_STALE is the high-order bit of fw_mac_if_t.ix[1],
 * but made for masking against fw_mac_if_t.dst_mac[0].
 * When this bit is set, in a forwarding cache entry, it indicates
 * that the management OS neigbor cache entry corresponding to the
 * forwarding cache entry has gone stale, and a packet needs to take
 * the slow path to drive the STALE -> DELAY Neighbor Unreachability
 * Detection transition.
 */

#ifdef IP_BIG_ENDIAN
#define IPCOM_FW_NBR_STALE (0x00800000)
#else
#define IPCOM_FW_NBR_STALE (0x00008000)
#endif

typedef struct fw_ipsec_s
{
    Ip_u16 key;
    Ip_u16 mtu;
    Ip_u32 cache_id;
} fw_ipsec_t;

typedef struct fw_cache_entry_v4_s
{
    fw_mac_if_t mac_if;
    fw_ip4_t ip4;
#ifdef IPCOM_USE_FORWARDER_IPSEC
    fw_ipsec_t ipsec;
#endif

} fw_cache_entry_v4_t;

typedef struct fw_cache_entry_v6_s
{
    fw_mac_if_t mac_if;
    fw_ip6_t ip6;
#ifdef IPCOM_USE_FORWARDER_IPSEC
    fw_ipsec_t ipsec;
#endif

} fw_cache_entry_v6_t;

typedef struct fw_cache_entry_vlan_s
{
    fw_mac_if_t mac_if;
    fw_ip_vlan_t ipvlan;
#ifdef IPCOM_USE_FORWARDER_IPSEC
    fw_ipsec_t ipsec;
#endif

} fw_cache_entry_vlan_t;


typedef struct fw_port_s
{
    union {
        Ip_u64 align; /* The 'fw_port' array must be 64-bit aligned */
        Ip_u32 s_t[2];
    } u;
#define src_type u.s_t
    void *fwd;
    Ip_u32 mtu;
#if defined(IPCOM_FORWARDER_NAE)
    /* TODO: move to NAE-private memory */
    void *netif[MAX_FW]; /* Corresponding netif */
#endif
    int port;

    /* The same if_index value is used by the NAEs and by
       the management OS for the corresponding proxy interface. */
    int if_index;
} fw_port_t;

typedef struct Ipcom_fw_s
{
    volatile int *rt_cache_id;

    fw_cache_entry_v4_t *fw_cache_tbl_v4;
    fw_cache_entry_v6_t *fw_cache_tbl_v6;
    int fw_v4_entries;
    int fw_v6_entries;
#ifdef IPCOM_USE_FORWARDER_IPSEC
    Ipcom_fw_ipsec_sa_t *fw_cache_tbl_enc;
    Ipcom_fw_ipsec_sa_t *fw_cache_tbl_dec;
    int fw_ipsec_entries;
    struct
    {
        Ip_u64 out_ok;
        Ip_u64 out_async;
        Ip_u64 out_skip;
        Ip_u64 out_fail;
        Ip_u64 in_ok;
        Ip_u64 in_async;
        Ip_u64 in_skip;
        Ip_u64 in_fail;
        Ip_u64 in_hmac_fail;
    } ipsec_stats;
#endif /* IPCOM_USE_FORWARDER_IPSEC */

    fw_port_t fw_port[MAX_FW_PORTS];

#ifdef IPCOM_FORWARDER_SMP
    Ipcom_pipe *fw_pipe;                        /* SMP only */
    Ipcom_pipe *control_pipe[MAX_FW];           /* SMP only */
#endif

#ifdef IPCOM_FORWARDER_USE_UPPER_TAG_BITS
    int fw_key_shift;
#endif

#ifdef IPCOM_USE_FORWARDER_VLAN_STACKING
    fw_cache_entry_vlan_stacking_t *fw_cache_tbl_vlan[MAX_FW_PORTS];
    Ip_u8   port_type[MAX_FW_PORTS];
    Ip_u8   rule_flags[MAX_FW_PORTS];
    Ip_u16  hw_pvid[MAX_FW_PORTS];
    Ip_u16  vlan_s_tpid_net, vlan_s_tpid;
    Ip_u8   hw_mac[MAX_FW_PORTS][6];
#endif

    int fw_tick_cnt;
    int fw_map;           /* bitmap of cores with running forwarders */

} Ipcom_fw_t;



enum Ipcom_forward_sig
{
    IPCOM_SIG_ETH_PKT = 0x8833,
    IPCOM_SIG_STOP_FW,
    IPCOM_SIG_START_FW,
    IPCOM_SIG_ACK_FW
};

/*
 * TODO: remove or at least clean up this structure.
 */
#if 0
typedef struct Ipcom_pipe_msg_s
{
    int msg_id;
    union {
            char * packet;                      /* Used for raw packet */
            Ipcom_pkt * pkt;            /* Forward an Ipcom_pkt */
    } p;
    union {
            void *nif;
            Ipcom_netif *netif;
    } n;
    unsigned int fw_key;
    void *priv;
    Ip_u32 tag_seed;
    Ip_pid_t pid;
    int nix;                   /* index of input interface */

} Ipcom_pipe_msg_t;
#endif

typedef unsigned long fw_lock_key_t;


#define IPCOM_FWD_V4 (0x1)
#define IPCOM_FWD_V6 (0x2)
#define IPCOM_FWD_V4_V6 (IPCOM_FWD_V4 | IPCOM_FWD_V6)


/*
 ****************************************************************************
 * 5                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_EXTERN Ipcom_fw_t *ipcom_fw;

IP_EXTERN int ipcom_forwarder_fw_enable;
IP_EXTERN int ipcom_forwarder_fw_started;
IP_EXTERN Ip_u32 ipcom_forwarder_seed;

#ifdef IPCOM_FORWARDER_C
#ifdef IPCOM_USE_CALCULATE_KEY
IP_PUBLIC Ip_u16 ipcom_forwarder_calculate_pkt_key(Ipcom_pkt *pkt);
IP_PUBLIC Ip_u16 ipcom_forwarder_calculate_packet_key(void *packet);
#endif
#endif /* IPCOM_FORWARDER_C */


/*
 ****************************************************************************
 * 6                    EXTERNAL FUNCTIONS
 ****************************************************************************
 */

#ifndef ipcom_forwarder_create_cf
IP_EXTERN int ipcom_forwarder_create_cf(void);
#endif
#ifndef ipcom_forwarder_transmit_pkt_cf
IP_EXTERN int ipcom_forwarder_transmit_pkt_cf(void *pkt, void *netif);
#endif

IP_EXTERN void ipcom_forwarder_master_tick_cf(void);
IP_EXTERN void ipcom_forwarder_cmd_add(void);
IP_EXTERN void ipcom_forwarder_master_tick_cf(void);

/*
 ****************************************************************************
 * 7                    PUBLIC FUNCTIONS
 ****************************************************************************
 */

/* ipcom_<os/hw>_forwarder.c */

/* HW specific functions */
IP_PUBLIC fw_lock_key_t ipcom_forwarder_atomic_lock(int index);
IP_PUBLIC void   ipcom_forwarder_atomic_unlock(int index, fw_lock_key_t key);

#ifdef IPCOM_USE_FORWARDER_IPSEC
IP_PUBLIC Ip_u16 ipcom_forwarder_hw_crc16(Ip_u32 *buf, Ip_u32 num);
IP_PUBLIC Ip_u32 ipcom_forwarder_hw_crc32(Ip_u32 *buf, Ip_u32 num);
#endif

IP_PUBLIC void  *ipcom_forwarder_init_rx(int fw_id);
IP_PUBLIC void  *ipcom_forwarder_get_fw_cookie(int fw_id);

IP_PUBLIC void   ipcom_forwarder_backend_setup(void);
IP_PUBLIC void   ipcom_forwarder_backend_create(void);

IP_PUBLIC void   ipcom_forwarder_free_trigger_msg(fw_msg_t *msg, void *fw_cookie);
IP_PUBLIC void * ipcom_fw_cpu_mem_alloc(unsigned int cpu, Ip_size_t size,
                                        Ip_size_t align, unsigned int flags);

IP_PUBLIC void   ipcom_fw_cpu_mem_free(void * ptr);
IP_PUBLIC int    ipcom_forwarder_cpuid_get(int fw_id);
IP_PUBLIC void   ipcom_forwarder_drop_fw_msg(fw_msg_t *msg, void *fw_cookie);

IP_PUBLIC void   ipcom_forwarder_enter_poll(void);
IP_PUBLIC void   ipcom_forwarder_exit_poll(void);

IP_PUBLIC int    ipcom_forwarder_get_fw_cnt(void);

IP_PUBLIC void   ipcom_forwarder_get_statistics(void *port_cookie, port_statistics_t *ps);


IP_PUBLIC int    ipcom_forwarder_ipnet_msg_len(fw_msg_t *msg);
IP_PUBLIC Ip_u8 *ipcom_forwarder_ipnet_msg_packet(fw_msg_t *msg);

IP_PUBLIC int    ipcom_forwarder_port_name_get(void *port_cookie,
                                               char ifname[IP_IFNAMSIZ]);
IP_PUBLIC void   ipcom_forwarder_reset_statistics(void *port_cookie);

IP_PUBLIC fw_msg_t *ipcom_forwarder_rx(void *fw_cookie);
IP_PUBLIC int    ipcom_forwarder_tx(int port_index, fw_msg_t *msg, void *fw_cookie);
IP_PUBLIC int    ipcom_forwarder_tx_fw(int port_index, fw_msg_t *msg, void *fw_cookie);

IP_PUBLIC void   ipcom_forwarder_set_tag_seed(Ip_u32 seed);
IP_PUBLIC void   ipcom_forwarder_slow_path(fw_msg_t *fw_msg, void *fw_cookie);
IP_PUBLIC void   ipcom_forwarder_queue_pkt(fw_msg_t *fw_msg, void *fw_cookie);
#ifdef IPCOM_FORWARDER_NAE
IP_PUBLIC void   ipcom_forwarder_mipc_send_slow_path(fw_msg_t *fw_msg);
#endif

IP_PUBLIC void   ipcom_forwarder_trigger_pipe_read(int fw_id);

IP_PUBLIC void   ipcom_forwarder_wait_for_master(void);

/* OS specific functions */
IP_PUBLIC void   ipcom_forwarder_setup_hw(void);
IP_PUBLIC void   *ipcom_forwarder_alloc_aligned(unsigned alignment, unsigned size);

/* ipcom_forwarder_ctrl.c */
IP_PUBLIC int    ipcom_forwarder_cache_util(int v4_v6);
IP_PUBLIC int    ipcom_forwarder_create(void);
IP_PUBLIC int    ipcom_forwarder_get_fw_enable(void);
IP_PUBLIC int    ipcom_forwarder_get_fw_started(void);
IP_PUBLIC int    ipcom_forwarder_get_fwdebug_mask(void);
IP_PUBLIC void  *ipcom_forwarder_get_port_cookie(int port);
IP_PUBLIC Ip_u32 ipcom_forwarder_get_seed(void);
IP_PUBLIC unsigned int ipcom_forwarder_init(void);
#ifndef IP_PORT_LKM
IP_PUBLIC Ip_err ipcom_forwarder_ioctl(Ipcom_netif *netif, int code, struct Ip_fwreq *fwreq);
#endif
IP_PUBLIC void   ipcom_forwarder_invalidate(int id, int v4_v6);
IP_PUBLIC void   ipcom_forwarder_port_mac_update(int port_index, Ip_u8 *hwaddr);
IP_PUBLIC void   ipcom_forwarder_port_mtu_update(int port, Ip_u32 mtu);
IP_PUBLIC void   ipcom_forwarder_print_cache(int v);
IP_PUBLIC void   ipcom_forwarder_register_port(int port, void *port_cookie,
                                               Ip_u32 mtu, const Ip_u8 *hwaddr);
IP_PUBLIC void   ipcom_forwarder_route_cache_invalidate(void);
IP_PUBLIC void   ipcom_forwarder_set_port_cookie(int port, void *port_cookie);
IP_PUBLIC void   ipcom_forwarder_set_seed(Ip_u32 seed);

IP_PUBLIC void   ipcom_forwarder_start_stop_fw(int sig);
IP_PUBLIC int    ipcom_forwarder_transmit_pkt(Ipcom_pkt *pkt, Ipcom_netif *netif);
IP_PUBLIC int    ipcom_forwarder_transmit_pkt_ext(Ipcom_pkt *pkt, int port_index);

/* ipcom_forwarder_data.c */
IP_PUBLIC void   ipcom_forwarder_loop(int fw_id, void * fw_cookie, void * pipe);

/* ipcom_config.c */
IP_PUBLIC int    ipcom_forwarder_config_cache_size(void);
IP_PUBLIC int    ipcom_forwarder_config_fw_max(void);
IP_PUBLIC unsigned int ipcom_forwarder_current_core(void);
IP_PUBLIC int    ipcom_forwarder_fw_per_port(void);
IP_PUBLIC void *ipcom_forwarder_get_tx_queue(void *end);
IP_PUBLIC void   ipcom_forwarder_get_nonfw_stats(void *end, Ip_u32 *frames, Ip_u32 *bytes, int reset);
IP_PUBLIC Ip_u32 ipcom_forwarder_get_ports_for_interface (Ip_u32 iface);
IP_PUBLIC unsigned int ipcom_nae_extra_packets(void);

IP_PUBLIC int    ipcom_forwarder_get_key_shift(void);
IP_PUBLIC Ip_bool ipcom_forwarder_is_master(void);
IP_PUBLIC int ipcom_forwarder_create_slave(void);
IP_PUBLIC unsigned int ipcom_forwarder_master_core(void);
IP_PUBLIC Ip_err ipcom_forwarder_load_and_boot(Ip_bool first, char **cpuctx, char **imagectx);
IP_PUBLIC int ipcom_forwarder_get_hw_ix(void *end);
IP_PUBLIC int ipcom_forwarder_get_mac_cf(void *pDrv, void *mac);
IP_PUBLIC int ipcom_forwarder_set_mac_cf(void *pDrv, void *mac);


/* ipcom_forwarder_<hw>.c */

IP_PUBLIC int ipcom_nae_tx(Ipcom_netif *netif, Ipcom_pkt *pkt);
IP_PUBLIC int ipcom_forwarder_get_mac_addr(int port, void *mac);
IP_PUBLIC int ipcom_forwarder_set_mac_addr(int port, void *mac);
IP_PUBLIC int ipcom_forwarder_port_status(int port, int *running, int *speed);

IP_PUBLIC void ipcom_forwarder_tick(fw_msg_t *msg, void *fw_cookie);
#if defined(IPCOM_FORWARDER_NAE)
IP_PUBLIC int ipcom_forwarder_nae_id(void);
#endif

#if defined(IPCOM_FORWARDER_AMP)
IP_EXTERN Ip_u32 ipcom_fw_atomic_and(Ip_u32 *addr, Ip_u32 val);
#endif

/* OS specific functions */

/* ipcom_<os>_mipc.c */
IP_PUBLIC int ipcom_mipc_get_shared_data(void);
IP_PUBLIC void ipcom_mipc_ctrl_msg(void *msg, void *fw_cookie);
IP_PUBLIC int ipcom_mipc_printf(const char *fmt, ...);
IP_PUBLIC void ipcom_mipc_syslog(Ip_u32 priority, const char *fmt, ...);


/* ipcom_forwarder.c */
IP_PUBLIC void ipcom_forwarder_set_seed(Ip_u32 seed);
IP_PUBLIC void ipcom_forwarder_set_tx_port(int port, void *txqueue);
IP_PUBLIC Ip_err ipcom_create_rx_fw_tx(int fw_i);


/* port/<os>/src/ipcom_os.c */
IP_PUBLIC int    ipcom_mipc_get_node_id(void);
IP_PUBLIC int    ipcom_mipc_listen(char *busname, int port, int backlog);
IP_PUBLIC void   ipcom_mipc_close(int s);
IP_PUBLIC int    ipcom_mipc_recv(int s, void *buf, int buflen);
IP_PUBLIC Ip_err ipcom_mipc_send(char *busname, int node, int port, void *buf, int buflen);
IP_PUBLIC unsigned long ipcom_mipc_addr2offset(void *p);
IP_PUBLIC void  *ipcom_mipc_offset2addr(unsigned long offset);

/* ipcom_forwarder_ipsec.c */
IP_PUBLIC int    ipcom_forwarder_ipsec_input_done(fw_msg_t *fw_msg, Ip_bool async, Ip_bool check_hmac);

IP_PUBLIC void   ipcom_forwarder_ipsec_output_done(fw_msg_t *fw_msg, Ip_bool async);

IP_PUBLIC int    ipcom_forwarder_ipsec_input(fw_msg_t *fw_msg,Ip_u8 *domain, Ip_u8 *p, unsigned int length);

IP_PUBLIC int    ipcom_forwarder_ipsec_output(fw_msg_t *fw_msg, fw_ipsec_t *ipsec, Ip_u8 *p, unsigned int length);

IP_PUBLIC void   ipcom_forwarder_ipsec_sprint_sa(Ip_bool in, char *buf, Ipcom_fw_ipsec_sa_t *fw_ipsec_sa);

IP_PUBLIC int    ipcom_forwarder_ipsec_check_replay_window(Ipcom_fw_ipsec_sa_t *fw_ipsec_sa, Ip_u32 seq);
IP_PUBLIC Ip_u8  ipcom_forwarder_ipsec_set_fw_if(Ip_u8 *p, Ipcom_pkt *pkt,
                                                 Ip_u32 mtu, fw_ipsec_t *fw_ipsec);

/* ipcom_xxx_yyy_forwarder_ipsec.c */
IP_PUBLIC int    ipcom_forwarder_ipsec_esp_encrypt(fw_msg_t *fw_msg,
                                                   Ip_u16 sa_index,
                                                   Ip_u32 seq_no,
                                                   Ip_u8 *iv,
                                                   Ip_u8 *pkt,
                                                   Ip_u16 pktlen,
                                                   Ip_u8 *out);

IP_PUBLIC int    ipcom_forwarder_ipsec_esp_decrypt(fw_msg_t *fw_msg,
                                                   Ip_u16 sa_index,
                                                   Ip_u8 *pkt,
                                                   Ip_u16 pktlen,
                                                   Ip_u8 *out);

IP_PUBLIC fw_msg_t *ipcom_forwarder_ipsec_poll(void);
IP_PUBLIC int    ipcom_forwarder_ipsec_populate_specific_sa(Ipcom_fw_ipsec_sa_t *fw_ipsec_sa, Ip_u16 sa_index, int enc);
IP_PUBLIC void   ipcom_forwarder_ipsec_init(void);

#ifdef IPCOM_USE_FORWARDER_VLAN_STACKING
IP_PUBLIC void   ipcom_forwarder_reset_stpid(Ip_u16 stpid);
IP_PUBLIC void  ipcom_forwarder_svlan_time(unsigned long ticks, unsigned hz);
IP_PUBLIC __inline__ void ipcom_forwarder_sc_fwd_entry(fw_msg_t *msg);
IP_PUBLIC int ipcom_forwarder_if_set_vlan_stacking(Ipnet_netif *netif);
IP_PUBLIC void ipcom_forwarder_if_clr_vlan_stacking(Ipnet_netif *netif);
IP_PUBLIC int ipcom_forwarder_svlan_add_cache_entry(Ipnet_netif *in_netif,
                                Ip_u16 vid, Ip_u16 svid, Ip_u8 *pri_mapping,
                                Ipnet_netif *out_netif);
IP_PUBLIC int ipcom_forwarder_svlan_del_cache_entry(Ipnet_netif *in_netif,
                                Ip_u16 vid, Ip_u16 svid,
                                Ipnet_netif *out_netif);
IP_PUBLIC int ipcom_forwader_svlan_update_config(unsigned long request,
                                struct Ip_vlanreq *vlan_req, Ip_u8 old_rule,
                                Ipnet_netif *netif);
IP_GLOBAL void ipcom_svlan_forwarder_cmd_add(void);
#endif

#ifdef __cplusplus
}
#endif

#endif
/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
