#ifndef IPCOM_NETLINK_XFRM_H
#define IPCOM_NETLINK_XFRM_H

typedef union Ip_xfrm_address
{
    Ip_u32      a4;
    Ip_u32      a6[4];
} Ip_xfrm_address_t;

struct Ip_xfrm_id 
{
    Ip_xfrm_address_t   daddr;
    Ip_u32              spi;
    Ip_u8               proto;
};

struct Ip_xfrm_sec_ctx 
{
    Ip_u8   ctx_doi;
    Ip_u8   ctx_alg;
    Ip_u16  ctx_len;
    Ip_u32  ctx_sid;
    char    ctx_str[4];
};

#define IP_XFRM_SC_DOI_RESERVED 0
#define IP_XFRM_SC_DOI_LSM 1

#define IP_XFRM_SC_ALG_RESERVED 0
#define IP_XFRM_SC_ALG_SELINUX 1

struct Ip_xfrm_selector 
{
    Ip_xfrm_address_t   daddr;
    Ip_xfrm_address_t   saddr;
    Ip_u16              dport;
    Ip_u16              dport_mask;
    Ip_u16              sport;
    Ip_u16              sport_mask;
    Ip_u16              family;
    Ip_u8               prefixlen_d;
    Ip_u8               prefixlen_s;
    Ip_u8               proto;
    int	                ifindex;
    Ip_u32              user;
};

#define IP_XFRM_INF (~(Ip_u64)0)

struct Ip_xfrm_lifetime_cfg 
{
    Ip_u64  soft_byte_limit;
    Ip_u64  hard_byte_limit;
    Ip_u64  soft_packet_limit;
    Ip_u64  hard_packet_limit;
    Ip_u64  soft_add_expires_seconds;
    Ip_u64  hard_add_expires_seconds;
    Ip_u64  soft_use_expires_seconds;
    Ip_u64  hard_use_expires_seconds;
};

struct Ip_xfrm_lifetime_cur 
{
    Ip_u64  bytes;
    Ip_u64  packets;
    Ip_u64  add_time;
    Ip_u64  use_time;
};

struct Ip_xfrm_replay_state 
{
    Ip_u32  oseq;
    Ip_u32  seq;
    Ip_u32  bitmap;
};

struct Ip_xfrm_algo 
{
    char            alg_name[64];
    unsigned int    alg_key_len;    /* in bits */
    char            alg_key[4];
};

struct Ip_xfrm_algo_auth 
{
    char            alg_name[64];
    unsigned int    alg_key_len;    /* in bits */
    unsigned int    alg_trunc_len;  /* in bits */
    char            alg_key[4];
};

struct Ip_xfrm_algo_aead 
{
    char            alg_name[64];
    unsigned int    alg_key_len;	/* in bits */
    unsigned int    alg_icv_len;	/* in bits */
    char            alg_key[4];
};

struct Ip_xfrm_stats 
{
    Ip_u32  replay_window;
    Ip_u32  replay;
    Ip_u32  integrity_failed;
};

enum 
{
    IP_XFRM_POLICY_TYPE_MAIN    = 0,
    IP_XFRM_POLICY_TYPE_SUB     = 1,
    IP_XFRM_POLICY_TYPE_MAX     = 2,
    IP_XFRM_POLICY_TYPE_ANY     = 255
};

enum 
{
    IP_XFRM_POLICY_IN   = 0,
    IP_XFRM_POLICY_OUT  = 1,
    IP_XFRM_POLICY_FWD  = 2,
    IP_XFRM_POLICY_MASK = 3,
    IP_XFRM_POLICY_MAX  = 3
};

enum 
{
    IP_XFRM_SHARE_ANY,
    IP_XFRM_SHARE_SESSION,
    IP_XFRM_SHARE_USER,
    IP_XFRM_SHARE_UNIQUE
};

#define IP_XFRM_MODE_TRANSPORT          0
#define IP_XFRM_MODE_TUNNEL             1
#define IP_XFRM_MODE_ROUTEOPTIMIZATION  2
#define IP_XFRM_MODE_IN_TRIGGER         3
#define IP_XFRM_MODE_BEET               4
#define IP_XFRM_MODE_MAX                5

enum 
{
    IP_XFRM_MSG_BASE = 0x10,

    IP_XFRM_MSG_NEWSA = 0x10,
    IP_XFRM_MSG_DELSA,
	IP_XFRM_MSG_GETSA,

	IP_XFRM_MSG_NEWPOLICY,
	IP_XFRM_MSG_DELPOLICY,
	IP_XFRM_MSG_GETPOLICY,

	IP_XFRM_MSG_ALLOCSPI,
	IP_XFRM_MSG_ACQUIRE,
	IP_XFRM_MSG_EXPIRE,

	IP_XFRM_MSG_UPDPOLICY,
	IP_XFRM_MSG_UPDSA,

	IP_XFRM_MSG_POLEXPIRE,

	IP_XFRM_MSG_FLUSHSA,
	IP_XFRM_MSG_FLUSHPOLICY,

	IP_XFRM_MSG_NEWAE,
	IP_XFRM_MSG_GETAE,

	IP_XFRM_MSG_REPORT,

	IP_XFRM_MSG_MIGRATE,

	IP_XFRM_MSG_NEWSADINFO,
	IP_XFRM_MSG_GETSADINFO,

	IP_XFRM_MSG_NEWSPDINFO,
	IP_XFRM_MSG_GETSPDINFO,

	IP_XFRM_MSG_MAPPING,
	__IP_XFRM_MSG_MAX
};
#define IP_XFRM_MSG_MAX (__IP_XFRM_MSG_MAX - 1)

#define IP_XFRM_NR_MSGTYPES (IP_XFRM_MSG_MAX + 1 - IP_XFRM_MSG_BASE)

struct Ip_xfrm_user_sec_ctx 
{
    Ip_u16          len;
    Ip_u16          exttype;
    Ip_u8           ctx_alg;
    Ip_u8           ctx_doi;
    Ip_u16          ctx_len;
};

struct Ip_xfrm_user_tmpl 
{
    struct Ip_xfrm_id       id;
    Ip_u16                  family;
    Ip_xfrm_address_t       saddr;
    Ip_u32                  reqid;
    Ip_u8                   mode;
    Ip_u8                   share;
    Ip_u8                   optional;
    Ip_u32                  aalgos;
    Ip_u32                  ealgos;
    Ip_u32                  calgos;
};

struct Ip_xfrm_encap_tmpl 
{
    Ip_u16              encap_type;
    Ip_u16              encap_sport;
    Ip_u16              encap_dport;
    Ip_xfrm_address_t   encap_oa;
};

enum Ip_xfrm_ae_ftype_t 
{
	IP_XFRM_AE_UNSPEC,
	IP_XFRM_AE_RTHR     =1,
	IP_XFRM_AE_RVAL     =2,
	IP_XFRM_AE_LVAL     =4,
	IP_XFRM_AE_ETHR     =8,
	IP_XFRM_AE_CR       =16,
	IP_XFRM_AE_CE       =32,
	IP_XFRM_AE_CU       =64,
	__IP_XFRM_AE_MAX
};

#define IP_XFRM_AE_MAX (__IP_XFRM_AE_MAX - 1)

struct Ip_xfrm_userpolicy_type 
{
    Ip_u8       type;
    Ip_u16      reserved1;
    Ip_u8       reserved2;
};

enum Ip_xfrm_attr_type_t 
{
	IP_XFRMA_UNSPEC,
	IP_XFRMA_ALG_AUTH,
	IP_XFRMA_ALG_CRYPT,
	IP_XFRMA_ALG_COMP,
	IP_XFRMA_ENCAP,
	IP_XFRMA_TMPL,
	IP_XFRMA_SA,
	IP_XFRMA_POLICY,
	IP_XFRMA_SEC_CTX,
	IP_XFRMA_LTIME_VAL,
	IP_XFRMA_REPLAY_VAL,
	IP_XFRMA_REPLAY_THRESH,
	IP_XFRMA_ETIMER_THRESH,
	IP_XFRMA_SRCADDR,
	IP_XFRMA_COADDR,
	IP_XFRMA_LASTUSED,
	IP_XFRMA_POLICY_TYPE,
	IP_XFRMA_MIGRATE,
	IP_XFRMA_ALG_AEAD,
	IP_XFRMA_KMADDRESS,
	IP_XFRMA_ALG_AUTH_TRUNC,
	IP_XFRMA_MARK,
	__IP_XFRMA_MAX
};
#define IP_XFRMA_MAX (__IP_XFRMA_MAX - 1)

struct Ip_xfrm_mark 
{
    Ip_u32          v;
    Ip_u32          m;
};

enum Ip_xfrm_sadattr_type_t 
{
	IP_XFRMA_SAD_UNSPEC,
	IP_XFRMA_SAD_CNT,
	IP_XFRMA_SAD_HINFO,
	__IP_XFRMA_SAD_MAX
};
#define IP_XFRMA_SAD_MAX (__IP_XFRMA_SAD_MAX - 1)

struct Ip_xfrmu_sadhinfo 
{
    Ip_u32  sadhcnt; /* current hash bkts */
    Ip_u32  sadhmcnt; /* max allowed hash bkts */
};

enum Ip_xfrm_spdattr_type_t 
{
	IP_XFRMA_SPD_UNSPEC,
	IP_XFRMA_SPD_INFO,
	IP_XFRMA_SPD_HINFO,
	__IP_XFRMA_SPD_MAX
};

#define IP_XFRMA_SPD_MAX (__IP_XFRMA_SPD_MAX - 1)

struct Ip_xfrmu_spdinfo 
{
    Ip_u32 incnt;
    Ip_u32 outcnt;
    Ip_u32 fwdcnt;
    Ip_u32 inscnt;
    Ip_u32 outscnt;
    Ip_u32 fwdscnt;
};

struct Ip_xfrmu_spdhinfo 
{
    Ip_u32 spdhcnt;
    Ip_u32 spdhmcnt;
};

struct Ip_xfrm_usersa_info 
{
    struct Ip_xfrm_selector     sel;
    struct Ip_xfrm_id           id;
    Ip_xfrm_address_t           saddr;
    struct Ip_xfrm_lifetime_cfg lft;
    struct Ip_xfrm_lifetime_cur curlft;
    struct Ip_xfrm_stats        stats;
    Ip_u32                      seq;
    Ip_u32                      reqid;
    Ip_u16                      family;
    Ip_u8                       mode;
    Ip_u8                       replay_window;
    Ip_u8                       flags;
};

#define IP_XFRM_STATE_NOECN	        1
#define IP_XFRM_STATE_DECAP_DSCP    2
#define IP_XFRM_STATE_NOPMTUDISC    4
#define IP_XFRM_STATE_WILDRECV      8
#define IP_XFRM_STATE_ICMP          16
#define IP_XFRM_STATE_AF_UNSPEC     32

struct Ip_xfrm_usersa_id 
{
    Ip_xfrm_address_t   daddr;
    Ip_u32              spi;
    Ip_u16              family;
    Ip_u8               proto;
};

struct Ip_xfrm_aevent_id 
{
    struct Ip_xfrm_usersa_id    sa_id;
    Ip_xfrm_address_t           saddr;
    Ip_u32                      flags;
    Ip_u32                      reqid;
};

struct Ip_xfrm_userspi_info 
{
    struct Ip_xfrm_usersa_info  info;
    Ip_u32                      min;
    Ip_u32                      max;
};

struct Ip_xfrm_userpolicy_info 
{
    struct Ip_xfrm_selector     sel;
    struct Ip_xfrm_lifetime_cfg lft;
    struct Ip_xfrm_lifetime_cur curlft;
    Ip_u32                      priority;
    Ip_u32                      index;
    Ip_u8                       dir;
    Ip_u8                       action;
    Ip_u8                       flags;
    Ip_u8                       share;
};
#define IP_XFRM_POLICY_ALLOW	0
#define IP_XFRM_POLICY_BLOCK	1

#define IP_XFRM_POLICY_LOCALOK	1
#define IP_XFRM_POLICY_ICMP	2

struct Ip_xfrm_userpolicy_id 
{
    struct Ip_xfrm_selector     sel;
    Ip_u32                      index;
    Ip_u8                       dir;
};

struct Ip_xfrm_user_acquire 
{
    struct Ip_xfrm_id               id;
    Ip_xfrm_address_t               saddr;
    struct Ip_xfrm_selector         sel;
    struct Ip_xfrm_userpolicy_info  policy;
    Ip_u32                          aalgos;
    Ip_u32                          ealgos;
    Ip_u32                          calgos;
    Ip_u32                          seq;
};

struct Ip_xfrm_user_expire 
{
    struct Ip_xfrm_usersa_info	    state;
    Ip_u8                           hard;
};

struct Ip_xfrm_user_polexpire 
{
    struct Ip_xfrm_userpolicy_info  pol;
    Ip_u8                           hard;
};

struct Ip_xfrm_usersa_flush 
{
    Ip_u8                           proto;
};

struct Ip_xfrm_user_report 
{
    Ip_u8				            proto;
    struct Ip_xfrm_selector         sel;
};

struct Ip_xfrm_user_kmaddress 
{
    Ip_xfrm_address_t   local;
    Ip_xfrm_address_t   remote;
    Ip_u32              reserved;
    Ip_u16              family;
};

struct Ip_xfrm_user_migrate 
{
    Ip_xfrm_address_t   old_daddr;
    Ip_xfrm_address_t   old_saddr;
    Ip_xfrm_address_t   new_daddr;
    Ip_xfrm_address_t   new_saddr;
    Ip_u8               proto;
    Ip_u8               mode;
    Ip_u16              reserved;
    Ip_u32              reqid;
    Ip_u16              old_family;
    Ip_u16              new_family;
};

struct Ip_xfrm_user_mapping 
{
    struct Ip_xfrm_usersa_id    id;
    Ip_u32                      reqid;
    Ip_xfrm_address_t           old_saddr;
    Ip_xfrm_address_t           new_saddr;
    Ip_u16                      old_sport;
    Ip_u16                      new_sport;
};

#define IP_XFRMGRP_ACQUIRE		1
#define IP_XFRMGRP_EXPIRE		2
#define IP_XFRMGRP_SA		    4
#define IP_XFRMGRP_POLICY		8
#define IP_XFRMGRP_REPORT		0x20

enum Ip_xfrm_nlgroups 
{
    IP_XFRMNLGRP_NONE,
    IP_XFRMNLGRP_ACQUIRE,
    IP_XFRMNLGRP_EXPIRE,
    IP_XFRMNLGRP_SA,
    IP_XFRMNLGRP_POLICY,
    IP_XFRMNLGRP_AEVENTS,
    IP_XFRMNLGRP_REPORT,
    IP_XFRMNLGRP_MIGRATE,
    IP_XFRMNLGRP_MAPPING,
    __IP_XFRMNLGRP_MAX
};
#define IP_XFRMNLGRP_MAX	(__IP_XFRMNLGRP_MAX - 1)



#endif /* IPCOM_NETLINK_XFRM_H */
