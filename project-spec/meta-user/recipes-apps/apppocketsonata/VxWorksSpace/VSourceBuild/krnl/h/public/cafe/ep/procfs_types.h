/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

 
/* THIS IS GENERATED CODE. DO NOT MODIFY */

#ifndef INCprocfs_types_h
#define INCprocfs_types_h

#ifdef __cplusplus
extern "C" {
#endif
#define PROCFS___NET_STATS_ROW_VT_DEF "S[net_stats_row,k[key,s]v[value,t[net_device_stats]]]"
#define PROCFS___NET_STATS_ROW_VT_REF "t[net_stats_row]"

#define PROCFS___STAT_INFO_VT_DEF "S[stat_info,v[cpu_avg,t[cpu_stat]]v[cpus,D[t[cpu_dict_row]]]v[ctxt_switch,Q]v[interrupt,Q]v[page_in,L]v[page_out,L]v[swap_in,L]v[swap_out,L]v[boot_time,I]v[boot_procs,I]v[procs_running,I]v[procs_blocked,I]]"
#define PROCFS___STAT_INFO_VT_REF "t[stat_info]"

#define PROCFS___CPU_DICT_ROW_VT_DEF "S[cpu_dict_row,k[key,s]v[value,t[cpu_stat]]]"
#define PROCFS___CPU_DICT_ROW_VT_REF "t[cpu_dict_row]"

#define PROCFS___MEM_INFO_VT_DEF "S[mem_info,v[kb_active,L]v[kb_anon_pages,L]v[kb_bounce,L]v[kb_main_buffers,L]v[kb_main_cached,L]v[kb_commit_limit,L]v[kb_committed_as,L]v[kb_dirty,L]v[kb_high_free,L]v[kb_high_total,L]v[kb_inactive,L]v[kb_low_free,L]v[kb_low_total,L]v[kb_mapped,L]v[kb_main_free,L]v[kb_main_total,L]v[kb_pagetables,L]v[kb_swap_reclaimable,L]v[kb_swap_unreclaimable,L]v[kb_slab,L]v[kb_swap_cached,L]v[kb_swap_free,L]v[kb_swap_total,L]v[kb_vmalloc_chunk,L]v[kb_vmalloc_total,L]v[kb_vmalloc_used,L]v[kb_writeback,L]]"
#define PROCFS___MEM_INFO_VT_REF "t[mem_info]"

#define PROCFS___NET_DEVICE_STATS_VT_DEF "S[net_device_stats,v[rx_bytes,L]v[rx_packets,L]v[rx_errs,L]v[rx_drops,L]v[rx_fifo,L]v[rx_frame,L]v[rx_compressed,L]v[rx_multi,L]v[tx_bytes,L]v[tx_packets,L]v[tx_errs,L]v[tx_drops,L]v[tx_fifo,L]v[tx_colls,L]v[tx_carrier,L]v[tx_compressed,L]]"
#define PROCFS___NET_DEVICE_STATS_VT_REF "t[net_device_stats]"

#define PROCFS___CPU_STAT_VT_DEF "S[cpu_stat,v[time_user,Q]v[time_low,Q]v[time_sys,Q]v[time_idle,Q]v[time_iowait,Q]v[time_irq,Q]v[time_softirq,Q]v[time_steal,Q]]"
#define PROCFS___CPU_STAT_VT_REF "t[cpu_stat]"

#define PROCFS___LOADAVG___INFO_VT_DEF "S[loadavg.info,v[avg1,d]v[avg5,d]v[avg15,d]]"
#define PROCFS___LOADAVG___INFO_VT_REF "t[loadavg.info]"

#define PROCFS___UPTIME___INFO_VT_DEF "S[uptime.info,v[up,d]v[idle,d]]"
#define PROCFS___UPTIME___INFO_VT_REF "t[uptime.info]"

#define PROCFS___NET_STATS_VT_DEF "S[net_stats,v[stats,D[t[net_stats_row]]]]"
#define PROCFS___NET_STATS_VT_REF "t[net_stats]"



#define PROCFS___ALL_TYPE_DEFS \
    PROCFS___NET_STATS_ROW_VT_DEF \
    PROCFS___STAT_INFO_VT_DEF \
    PROCFS___CPU_DICT_ROW_VT_DEF \
    PROCFS___MEM_INFO_VT_DEF \
    PROCFS___NET_DEVICE_STATS_VT_DEF \
    PROCFS___CPU_STAT_VT_DEF \
    PROCFS___LOADAVG___INFO_VT_DEF \
    PROCFS___UPTIME___INFO_VT_DEF \
    PROCFS___NET_STATS_VT_DEF

#define PROCFS___ALL_TYPE_REFS \
    PROCFS___NET_STATS_ROW_VT_REF \
    PROCFS___STAT_INFO_VT_REF \
    PROCFS___CPU_DICT_ROW_VT_REF \
    PROCFS___MEM_INFO_VT_REF \
    PROCFS___NET_DEVICE_STATS_VT_REF \
    PROCFS___CPU_STAT_VT_REF \
    PROCFS___LOADAVG___INFO_VT_REF \
    PROCFS___UPTIME___INFO_VT_REF \
    PROCFS___NET_STATS_VT_REF

#ifndef NET_STATS_ROW_STRUCT_DEF
#define NET_STATS_ROW_STRUCT_DEF
struct net_stats_row {
    char* key;  /* key */
struct net_device_stats value; 
};
#endif /* NET_STATS_ROW_STRUCT_DEF */

#ifndef STAT_INFO_STRUCT_DEF
#define STAT_INFO_STRUCT_DEF
struct stat_info {
struct cpu_stat cpu_avg; 
struct cafe_dict_struct cpus; 
    unsigned long long ctxt_switch; 
    unsigned long long interrupt; 
    unsigned long page_in; 
    unsigned long page_out; 
    unsigned long swap_in; 
    unsigned long swap_out; 
    unsigned int boot_time; 
    unsigned int boot_procs; 
    unsigned int procs_running; 
    unsigned int procs_blocked; 
};
#endif /* STAT_INFO_STRUCT_DEF */

#ifndef CPU_DICT_ROW_STRUCT_DEF
#define CPU_DICT_ROW_STRUCT_DEF
struct cpu_dict_row {
    char* key;  /* key */
struct cpu_stat value; 
};
#endif /* CPU_DICT_ROW_STRUCT_DEF */

#ifndef MEM_INFO_STRUCT_DEF
#define MEM_INFO_STRUCT_DEF
struct mem_info {
    unsigned long kb_active; 
    unsigned long kb_anon_pages; 
    unsigned long kb_bounce; 
    unsigned long kb_main_buffers; 
    unsigned long kb_main_cached; 
    unsigned long kb_commit_limit; 
    unsigned long kb_committed_as; 
    unsigned long kb_dirty; 
    unsigned long kb_high_free; 
    unsigned long kb_high_total; 
    unsigned long kb_inactive; 
    unsigned long kb_low_free; 
    unsigned long kb_low_total; 
    unsigned long kb_mapped; 
    unsigned long kb_main_free; 
    unsigned long kb_main_total; 
    unsigned long kb_pagetables; 
    unsigned long kb_swap_reclaimable; 
    unsigned long kb_swap_unreclaimable; 
    unsigned long kb_slab; 
    unsigned long kb_swap_cached; 
    unsigned long kb_swap_free; 
    unsigned long kb_swap_total; 
    unsigned long kb_vmalloc_chunk; 
    unsigned long kb_vmalloc_total; 
    unsigned long kb_vmalloc_used; 
    unsigned long kb_writeback; 
};
#endif /* MEM_INFO_STRUCT_DEF */

#ifndef NET_DEVICE_STATS_STRUCT_DEF
#define NET_DEVICE_STATS_STRUCT_DEF
struct net_device_stats {
    unsigned long rx_bytes; 
    unsigned long rx_packets; 
    unsigned long rx_errs; 
    unsigned long rx_drops; 
    unsigned long rx_fifo; 
    unsigned long rx_frame; 
    unsigned long rx_compressed; 
    unsigned long rx_multi; 
    unsigned long tx_bytes; 
    unsigned long tx_packets; 
    unsigned long tx_errs; 
    unsigned long tx_drops; 
    unsigned long tx_fifo; 
    unsigned long tx_colls; 
    unsigned long tx_carrier; 
    unsigned long tx_compressed; 
};
#endif /* NET_DEVICE_STATS_STRUCT_DEF */

#ifndef CPU_STAT_STRUCT_DEF
#define CPU_STAT_STRUCT_DEF
struct cpu_stat {
    unsigned long long time_user; 
    unsigned long long time_low; 
    unsigned long long time_sys; 
    unsigned long long time_idle; 
    unsigned long long time_iowait; 
    unsigned long long time_irq; 
    unsigned long long time_softirq; 
    unsigned long long time_steal; 
};
#endif /* CPU_STAT_STRUCT_DEF */

#ifndef LOADAVG___INFO_STRUCT_DEF
#define LOADAVG___INFO_STRUCT_DEF
struct loadavg___info {
    double avg1; 
    double avg5; 
    double avg15; 
};
#endif /* LOADAVG___INFO_STRUCT_DEF */

#ifndef UPTIME___INFO_STRUCT_DEF
#define UPTIME___INFO_STRUCT_DEF
struct uptime___info {
    double up; 
    double idle; 
};
#endif /* UPTIME___INFO_STRUCT_DEF */

#ifndef NET_STATS_STRUCT_DEF
#define NET_STATS_STRUCT_DEF
struct net_stats {
struct cafe_dict_struct stats; 
};
#endif /* NET_STATS_STRUCT_DEF */

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* INCprocfs_types_h */
