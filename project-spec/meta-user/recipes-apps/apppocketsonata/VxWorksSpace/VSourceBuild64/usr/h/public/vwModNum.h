/* vwModNum.h - VxWorks module numbers */

/*
 * Copyright (c) 1984-2007, 2009-2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16mar16,cma  change shift calculation to fixed numbers. (V7COR-3610)
25dec13,pad  Added M_userIdentLib
25nov13,pad  Added M_udbMgr
17oct13,rfr  Added M_condVarLib
04sep13,jxu  Added M_ftlLib
19oct12,jxu  Added M_ftlLib
25jul11,jlv  Added M_pwrPolicyLib
11jun10,pcs  added M_devMemLib
11dec09,zly  added M_tffsLib 
03feb09,cww  Added M_vxCpuLib
29jun07,gls  added M_spinLockLib
23jun07,bwa  added M_dshm.
17oct06,rlp  Added M_vxdbgLib.
13jul05,dlk  Added IPCOM module number (M_ipcom).
12aug05,pcm  M_hrfsLib, M_erfLib and M_taskPxLib are now unique
08jul05,jln  updated comment
28jun05,jln  add M_taskPxLib
03aug05,dbt  Added core dump errnos.
22jul05,jmt  Add M_erfLib
03feb05,pcm  added M_hrfsLib
22oct04,pch  SPR 92598: add M_excLib
07sep04,jyo  Fixing SPR 100119: Removing references to RT11.
24jun04,jn   Add loadFileLib
16may04,kk   added S_tlsLib mod num
30mar04,dms  Added SHL-specific errno class.
29mar04,jn   Rename rtpLoadLib -> loadRtpLib
16mar04,bpn  Updated errnoTbl.tcl location.
11dec03,gls  added M_sdLib
04dec03,als  removed M_snsLib (merged with M_salLib)
02dec03,bwa  removed M_msgCLib and M_msgSLib
24nov03,ann  added the module numbers for NFSv3
26nov03,bwa  merged M_unLib and M_unCompLib definitions
21nov03,bwa  added M_unLib and M_unCompLib definitions;
	     added M_salLib and M_snsLib
14oct03,gls  added M_pgMgrLib
18nov03,yvp  Added M_hookLib.
28oct03,jn   Add M_rtpLoadLib
18sep03,vvv  added M_ipRouteLib
11aug03,yp   adding M_adrSpaceLib and M_pgPoolLib
26aug03,dbs  added ED&R modules M_edrLib, M_pmLib, M_memLogLib
26aug03,yvp  Added M_syscallLib
11apr03,pes  PAL Coprocessor Abstraction: Added M_coprocLib
01jul03,nrj  added RTP support
15jul03,kam  rebased to Base6 integration branch
20jun03,t_m  added module number for Card and Socket services (pccard)
04jun03,bwa  Added M_msgCLib and M_msgSLib definitions.
04jun03,kam  added M_isrLib
18feb03.bpn  Added M_shellLib and M_shellCmdLib.
01nov02,vvv  added M_fastUdpLib
20jun02,jws  Added HA related numbers. This creates a gap.
14mar02,elr  Added M_ftpDrv
12oct01,rae  Added M_fastPathLib
09oct01,bwa  Added M_eventLib
24sep01,jkf  added M_cbioLib.
02may01,wef  changed usb error codes to M_usbHostLib and M_usbTargLib
05dec00,wef  added usb error codes
04may01,dlk  Added M_qPriMaskLib.
12dec00,agf  Adding #define for M_devCfgLib, required as part of the
	     es.coretools merge
24apr00,gnn  merged in from tor2_0.open_stack
28mar00,rae  merging in IGMPv2 changes
14jan00,brx  added M_rarpLib definition 
03sep99,mas  removed dmsObjLib following merge of it with dmsLib.
08jul99,mas  added M_poolLib, M_setLib, M_dmsObjLib, M_dmsLib
14jun99,cn   added M_miiLib.
05oct98,jmp  added M_if_ul definition (SPR #22585).
19may98,drm  merged 3rd party changes for distributed message queues
	     - added M_msgQDistLib, M_distNameLib, M_msgQDistGrpLib,
	       and M_distLib
	     - merged code was originally based on version 03s
04May98,cym  added M_loadPecoffLib
13nov97,vin  added M_netBufLib
15jul97,spm  added M_sntpcLib and M_sntpsLib
16may97,vin  added M_dhcpsLib.
27apr97,rjc  added M_ospfLib.
07apr97,gnn  added M_endLib, M_muxLib, and M_m2RipLib.
14feb97,rjc  added M_snmpdLib
13dec96,jag  added M_resolvLib 
17oct96,spm  added M_dhcpcLib
02jul97,ms   moved M_cdromFs here from cdromFsLib.h
29nov96,p_m  added to a comment to tell people to go edit errnoTbl.tcl
01nov96,hdn  added M_pcmciaLib.
22aug95,jds  added M_tapeFsLib
23may96,rjc  added M_snmpdLib
30nov95,vin  added M_pppHookLib.
09may95,dzb  added M_pppSecretLib.
29mar95,sgv  added M_strmLib.
04nov94,dzb  added M_mbufLib and M_pingLib.
15oct93,cd   added M_loadElfLib.
04nov93,yao  added M_loadSomCoffLib.
22apr94,jmm  added M_nfsdLib and M_mountLib
14feb94,jag  added M_ for MIB-II library.
22sep92,rrr  added support for c++
01aug92,srh  added M_cxxLib
19jul92,pme  added M_smObjLib and M_smNameLib.
15jul92,jmm  added M_moduleLib and M_unldLib.
08jul92,rdc  added M_vmLib and M_mmuLib.
30jun92,wmd  added M_loadCoffLib.
09jun92,ajm  added M_loadEcoffLib, M_loadAoutLib, M_loadBoutLib,
	     and M_bootLoadLib
02jun92,elh  added M_smPktLib, and M_smUtilLib, renamed M_shMemLib
	     to M_smLib.
26may92,rrr  the tree shuffle
28feb92,elh  added M_bootpLib, M_tftpLib, and M_icmpLib
04feb92,elh  added M_shMemLib, changed year on copyright
07jan92,elh  added M_arpTblLib
04oct91,rrr  passed through the ansification filter
	     -changed copyright notice
05oct90,shl  added copyright notice.
	     made #endif ANSI style.
02oct90,kdl  added M_rawFsLib.
09aug90,kdl  changed M_msdosLib to M_dosFsLib, changed M_rt11Lib to
	     M_rt11FsLib.
18jul90,jcf  added M_cacheLib
26jun90,jcf  removed M_semCore, M_semILib. added M_semLib.
04may90,kdl  added M_dirLib.
18mar90,jcf  added M_hashLib, M_qLib, M_tickLib, M_objLib,
	     M_qPriHeapLib, M_qPriBMapLib, M_bufLib,
	     M_msgQLib, M_classLib
16mar90,kdl  added M_scsiLib, M_msdosLib.
        rdc  added M_selectLib.
13mar90,shl  added M_loginLib.
27jul89,hjb  added M_if_sl.
25may89,gae  added M_ftnLib.
04jun88,dnw  changed ldLib->loadLib, rtLib->rt11Lib, stsLib->errnoLib.
	     changed M_errno, M_taskLib, M_vrtx, M_psos.
29may88,dnw  added M_sigLib.
	     deleted some obsolete modules.
28may88,dnw  added M_hostLib.
29apr88,gae  added M_stsLib.
19apr88,llk  added M_nfsDrv, M_nfsLib, M_rpcClntStat, M_nfsStat.
25jan88,jcf  added M_taskLib.
01nov87,llk  added M_inetLib and M_routeLib.
...pre 1987 mod history removed.  See RCS.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCvwModNumh
#define __INCvwModNumh

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ASMLANGUAGE
#define MODNUM_TO_ERRNO(modNum)   (modNum << 16)
#else
#define MODNUM_TO_ERRNO(modNum)   (modNum##U << 16)
#endif

/* module numbers - DO NOT CHANGE NUMBERS! Add or delete only! */
#define M_errno			MODNUM_TO_ERRNO (0)	/* THIS MUST BE ZERO! */
#define M_kernel		MODNUM_TO_ERRNO (1)
#define M_taskLib		MODNUM_TO_ERRNO (3)
#define M_dbgLib		MODNUM_TO_ERRNO (4)
#define M_vxdbgLib		MODNUM_TO_ERRNO (5)
#define M_dsmLib		MODNUM_TO_ERRNO (7)
#define M_fioLib		MODNUM_TO_ERRNO (9)
#define M_ioLib			MODNUM_TO_ERRNO (12)
#define M_iosLib		MODNUM_TO_ERRNO (13)
#define M_loadLib		MODNUM_TO_ERRNO (14)
#define M_lstLib		MODNUM_TO_ERRNO (15)
#define M_memLib		MODNUM_TO_ERRNO (17)
#define M_rngLib		MODNUM_TO_ERRNO (19)

#define M_semLib		MODNUM_TO_ERRNO (22)
#define M_vwModNum		MODNUM_TO_ERRNO (27)
#define M_symLib		MODNUM_TO_ERRNO (28)
#define M_tyLib			MODNUM_TO_ERRNO (31)
#define M_wdLib			MODNUM_TO_ERRNO (34)
#define M_usrLib		MODNUM_TO_ERRNO (35)
#define M_remLib		MODNUM_TO_ERRNO (37)
#define M_netDrv		MODNUM_TO_ERRNO (41)
#define M_inetLib		MODNUM_TO_ERRNO (43)
#define M_routeLib		MODNUM_TO_ERRNO (44)
#define M_nfsDrv		MODNUM_TO_ERRNO (45)
#define M_nfsLib		MODNUM_TO_ERRNO (46)
#define M_rpcClntStat		MODNUM_TO_ERRNO (47)
#define M_nfsStat		MODNUM_TO_ERRNO (48)
#define M_errnoLib		MODNUM_TO_ERRNO (49)
#define M_hostLib		MODNUM_TO_ERRNO (50)
#define M_sigLib		MODNUM_TO_ERRNO (51)
#define M_ftnLib		MODNUM_TO_ERRNO (52)
#define M_if_sl			MODNUM_TO_ERRNO (53)
#define M_loginLib		MODNUM_TO_ERRNO (54)
#define M_scsiLib		MODNUM_TO_ERRNO (55)
#define M_dosFsLib		MODNUM_TO_ERRNO (56)
#define M_selectLib		MODNUM_TO_ERRNO (57)
#define M_hashLib		MODNUM_TO_ERRNO (58)
#define M_qLib			MODNUM_TO_ERRNO (59)
#define M_tickLib		MODNUM_TO_ERRNO (60)
#define M_objLib		MODNUM_TO_ERRNO (61)
#define M_qPriHeapLib		MODNUM_TO_ERRNO (62)
#define M_qPriBMapLib		MODNUM_TO_ERRNO (63)
#define M_bufLib		MODNUM_TO_ERRNO (64)
#define M_msgQLib		MODNUM_TO_ERRNO (65)
#define M_classLib		MODNUM_TO_ERRNO (66)
#define M_intLib		MODNUM_TO_ERRNO (67)
#define M_dirLib		MODNUM_TO_ERRNO (68)
#define M_cacheLib		MODNUM_TO_ERRNO (69)
#define M_rawFsLib		MODNUM_TO_ERRNO (70)
#define M_arpLib		MODNUM_TO_ERRNO (71)
#define M_smLib			MODNUM_TO_ERRNO (72)
#define M_bootpLib		MODNUM_TO_ERRNO (73)
#define M_icmpLib		MODNUM_TO_ERRNO (74)
#define M_tftpLib		MODNUM_TO_ERRNO (75)
#define M_proxyArpLib		MODNUM_TO_ERRNO (76)
#define M_smUtilLib		MODNUM_TO_ERRNO (77)
#define M_smPktLib		MODNUM_TO_ERRNO (78)
#define M_loadEcoffLib		MODNUM_TO_ERRNO (79)
#define M_loadAoutLib		MODNUM_TO_ERRNO (80)
#define M_loadBoutLib		MODNUM_TO_ERRNO (81)
#define M_bootLoadLib		MODNUM_TO_ERRNO (82)
#define M_loadCoffLib		MODNUM_TO_ERRNO (83)
#define M_vmLib			MODNUM_TO_ERRNO (84)
#define M_mmuLib		MODNUM_TO_ERRNO (85)
#define M_moduleLib		MODNUM_TO_ERRNO (86)
#define M_unldLib		MODNUM_TO_ERRNO (87)
#define M_smObjLib		MODNUM_TO_ERRNO (88)
#define M_smNameLib		MODNUM_TO_ERRNO (89)
#define M_cplusLib		MODNUM_TO_ERRNO (90)
#define M_m2Lib			MODNUM_TO_ERRNO (91)
#define M_aioPxLib		MODNUM_TO_ERRNO (92)
#define M_loadAoutHppaLib	MODNUM_TO_ERRNO (93)
#define M_mountLib		MODNUM_TO_ERRNO (94)
#define M_nfsdLib		MODNUM_TO_ERRNO (95)
#define M_loadSomCoffLib	MODNUM_TO_ERRNO (96)
#define M_loadElfLib		MODNUM_TO_ERRNO (97)
#define M_mbufLib		MODNUM_TO_ERRNO (98)
#define M_pingLib		MODNUM_TO_ERRNO (99)
#define M_strmLib		MODNUM_TO_ERRNO (100)
#define M_pppSecretLib		MODNUM_TO_ERRNO (101)
#define M_pppHookLib		MODNUM_TO_ERRNO (102)
#define M_tapeFsLib		MODNUM_TO_ERRNO (103)
#define M_snmpdLib		MODNUM_TO_ERRNO (104)
#define M_pcmciaLib		MODNUM_TO_ERRNO (105)
#define M_dhcpcLib		MODNUM_TO_ERRNO (106)
#define M_resolvLib		MODNUM_TO_ERRNO (107)
#define M_endLib		MODNUM_TO_ERRNO (108)
#define M_muxLib		MODNUM_TO_ERRNO (109)
#define M_m2RipLib		MODNUM_TO_ERRNO (110)
#define M_ospfLib		MODNUM_TO_ERRNO (111)
#define M_dhcpsLib		MODNUM_TO_ERRNO (112)
#define M_sntpcLib		MODNUM_TO_ERRNO (113)
#define M_sntpsLib		MODNUM_TO_ERRNO (114)
#define M_netBufLib		MODNUM_TO_ERRNO (115)
#define M_cdromFsLib		MODNUM_TO_ERRNO (116)
#define M_loadPecoffLib		MODNUM_TO_ERRNO (117)
#define M_distLib		MODNUM_TO_ERRNO (118)
#define M_distNameLib		MODNUM_TO_ERRNO (119)
#define M_msgQDistGrpLib	MODNUM_TO_ERRNO (120)
#define M_msgQDistLib		MODNUM_TO_ERRNO (121)
#define M_if_ul			MODNUM_TO_ERRNO (122)
#define M_miiLib                MODNUM_TO_ERRNO (123)
#define M_poolLib		MODNUM_TO_ERRNO (124)
#define M_setLib		MODNUM_TO_ERRNO (125)
#define M_dmsLib		MODNUM_TO_ERRNO (126)
#define M_rarpLib		MODNUM_TO_ERRNO (127)
#define M_igmpRouterLib         MODNUM_TO_ERRNO (128)
#define M_devCfgLib             MODNUM_TO_ERRNO (129)
#define M_qPriMaskLib		MODNUM_TO_ERRNO (130)
#define M_usbHostLib		MODNUM_TO_ERRNO (131)
#define M_usbPeriphLib		MODNUM_TO_ERRNO (132)
#define M_cbioLib		MODNUM_TO_ERRNO (133)
#define M_eventLib		MODNUM_TO_ERRNO (134)
#define M_fastPathLib           MODNUM_TO_ERRNO (135)
#define M_ftpLib           	MODNUM_TO_ERRNO (136)
#define M_fastUdpLib            MODNUM_TO_ERRNO (137)
#define M_edrLib           	MODNUM_TO_ERRNO (138)
#define M_pmLib           	MODNUM_TO_ERRNO (139)
#define M_memLogLib           	MODNUM_TO_ERRNO (140)
#define M_ipRouteLib            MODNUM_TO_ERRNO (141)
#define M_nfs3Stat              MODNUM_TO_ERRNO (142)

#define M_alarmLib              MODNUM_TO_ERRNO (153)
#define M_amsLib                MODNUM_TO_ERRNO (154)
#define M_fmsLib                MODNUM_TO_ERRNO (155)
#define M_hsiLib                MODNUM_TO_ERRNO (156)
#define M_hsmsLib               MODNUM_TO_ERRNO (157)
#define M_omsLib                MODNUM_TO_ERRNO (158)
#define M_rpmLib                MODNUM_TO_ERRNO (159)
#define M_umsLib                MODNUM_TO_ERRNO (160)
#define M_cmsLib                MODNUM_TO_ERRNO (161)
#define M_mmsLib                MODNUM_TO_ERRNO (162)
#define M_pspLib                MODNUM_TO_ERRNO (163)
#define M_xcomLib               MODNUM_TO_ERRNO (164)
#define M_ipsLib                MODNUM_TO_ERRNO (165)
#define M_rdsLib                MODNUM_TO_ERRNO (166)
#define M_grmLib                MODNUM_TO_ERRNO (167)
#define M_mtpLib                MODNUM_TO_ERRNO (168)
#define M_exEngLib              MODNUM_TO_ERRNO (169)
#define M_tplLib		MODNUM_TO_ERRNO (170)
#define M_smmLib		MODNUM_TO_ERRNO (171)
#define M_graLib		MODNUM_TO_ERRNO (172)
#define M_shellLib		MODNUM_TO_ERRNO (173)
#define M_shellInterpCmdLib	(174 << 16)
#define M_isrLib                MODNUM_TO_ERRNO (175)

#define M_rtpLib                MODNUM_TO_ERRNO (178)
#define M_coprocLib             MODNUM_TO_ERRNO (179)
#define M_adrSpaceLib		MODNUM_TO_ERRNO (180)
#define M_pgPoolLib		MODNUM_TO_ERRNO (181)
#define M_pgPoolPhysLib		MODNUM_TO_ERRNO (182)
#define M_pgPoolVirtLib		MODNUM_TO_ERRNO (183)
#define M_syscallLib		MODNUM_TO_ERRNO (184)
#define M_pgMgrLib		MODNUM_TO_ERRNO (185)
#define M_loadRtpLib            MODNUM_TO_ERRNO (186)
#define M_hookLib		MODNUM_TO_ERRNO (187)
#define M_unLib                 MODNUM_TO_ERRNO (188)
#define M_salLib                MODNUM_TO_ERRNO (189)
#define M_sdLib                 MODNUM_TO_ERRNO (190)
#define M_shlLib                MODNUM_TO_ERRNO (191)
#define M_tlsLib                MODNUM_TO_ERRNO (192)
#define M_loadFileLib           MODNUM_TO_ERRNO (193)

#define M_excLib		MODNUM_TO_ERRNO (194)
#define M_hrfsLib               MODNUM_TO_ERRNO (195)
#define M_erfLib                MODNUM_TO_ERRNO (196)
#define M_coreDumpLib		MODNUM_TO_ERRNO (197)
#define M_taskPxLib	        MODNUM_TO_ERRNO (198)

#define M_ipcom			MODNUM_TO_ERRNO (199)
#define M_dshm                  MODNUM_TO_ERRNO (200)
#define M_spinLockLib		MODNUM_TO_ERRNO (201)
#define M_vxCpuLib		MODNUM_TO_ERRNO (202)

#define M_tffsLib		MODNUM_TO_ERRNO (203)
#define M_devMemLib		MODNUM_TO_ERRNO (204)
#define M_pwrPolicyLib          MODNUM_TO_ERRNO (205)
#define M_ftlLib                MODNUM_TO_ERRNO (206)
#define M_condVarLib		MODNUM_TO_ERRNO (207)
#define M_udbMgr                MODNUM_TO_ERRNO (208)
#define M_userIdentLib          MODNUM_TO_ERRNO (209)

/*
 * The host file that contains VxWorks errnos for the host shell is now 
 * created automatically. Building the target directory target/src/usr will
 * force a recreate of the file host/resource/tcl/VxWorksErrnoTbl.tcl
 */

#ifdef __cplusplus
}
#endif

#endif /* __INCvwModNumh */

