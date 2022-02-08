/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_FORWARDER_H_H
#define IPCOM_FORWARDER_H_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

#ifdef IPCOM_SYSLOG_ENABLE
#undef IPCOM_SYSLOG_ENABLE
#define IPCOM_SYSLOG_ENABLE(x) (1)
#endif

#define IPCOM_SYSLOG_FACILITY    IPCOM_LOG_IPFORWARDER
#define IPCOM_SYSLOG_PRIORITY    IPCOM_LOG_WARNING

/* #define IPCOM_SHARED_DEBUG */

#ifdef IPCOM_SHARED_DEBUG
typedef struct shared_debug_s
{
	Ip_u32 fw_id;
	Ip_u32 flag;
	Ip_u64 pkt[1];
	Ip_u64 align[256 / sizeof(Ip_u64) - 2];

} shared_debug_t;

typedef struct seq_pkt_s
{
	void *p;
	Ip_u16 pos;
	Ip_u16 seq;
} seq_pkt_t;


typedef struct pkt_tag_s
{
	Ip_u32 seq;
	Ip_u8 bid;
	Ip_u8 bpid;
	Ip_u16 cpu;
	Ip_u32 loc;
	Ip_u32 cnt;

} pkt_tag_t;

#define PKT_TAG_LOC(v) ((pkt_tag_t *) (((Ip_u32)(v) & ~(0x800 - 1)) + 0x800 - sizeof(pkt_tag_t)) )
#define PKT_TAG_NEXT(v) PKT_TAG_LOC(v) + 0x800/sizeof(pkt_tag_t)
#define PKT_ADDR(v) ((void *)((Ip_u32)(v) & ~(0x800 - 1)))

#define SHARED_PKT(a) (shared_debug->pkt[a]++)
#define SHARED_POS(a)
#define SHARED_FAIL(a) (seq_pkt[a].pos++)
#define SHARED_PKT_INIT(v, bp) do {PKT_TAG_LOC(v)->bpid = bp;} while(0)
#define SHARED_PKT_SET(v, s, b, c, l) do {PKT_TAG_LOC(v)->bid = b; PKT_TAG_LOC(v)->loc = l; PKT_TAG_LOC(v)->seq = s; PKT_TAG_LOC(v)->cpu = c;} while(0)
#define SHARED_PKT_GET(v) PKT_TAG_LOC(v)
#define SHARED_PKT_INC(v) do {PKT_TAG_LOC(v)->cnt++;} while(0)
#define SHARED_PKT_LOC(a, b) do {PKT_TAG_LOC(a)->loc = b;} while(0)

#define GET_POOLS() get_pools()

#define PKT_RX (1)
#define PKT_TX1 (2)
#define PKT_TX2 (3)
#define PKT_FW1 (4)
#define PKT_FW2 (5)
#define PKT_SP1 (6)
#define PKT_SP2 (7)
#define PKT_SP3 (8)


#else
#define SHARED_PKT(a)
#define SHARED_POS(a)
#define SHARED_FAIL(a)
#define SHARED_PKT_INIT(v, bpid)
#define SHARED_PKT_SET(v, seq, bid, cpu, loc)
#define SHARED_PKT_GET(v)
#define SHARED_PKT_INC(v)
#define SHARED_PKT_LOC(a, b)
#define GET_POOLS()
#endif

#endif /* IPCOM_FORWARDER_H_H */
/*
 ****************************************************************************
 *  End of file
 ****************************************************************************
 */

