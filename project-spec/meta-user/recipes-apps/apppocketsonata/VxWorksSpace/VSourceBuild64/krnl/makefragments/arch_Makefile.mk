# Makefile - makefile for /arch, makefile for selecting
#	     architecture-specific portions of runtime
#
# Copyright 1996-2001, 2015 Wind River Systems, Inc.
#
# This Makefile is now generated -- DO NOT EDIT
#
# To change the boilerplate, edit Makefile.in
#
# To add CPU types or otherwise change the substance,
# edit vxworks-7/build/misc/architecturedb
#
# modification history
# --------------------
# 07feb15,mze  update comments
# 19sep11,mze  handle docs
# 12may08,pee  deprecating legacy top level libraries.
# 13nov03,c_c  Added PAL definition include.
# 21aug01,pch  Rename to Makefile.in, revise for use in generating
#		   Makefile from host/src/target/architecturedb
# 24jul01,scm  change XScale name to conform to coding standard...
# 16aug01,hdn  added PENTIUM2/3/4 support.
# 26apr00,lc   added MAPCA support.
# 17may99,mbh  added MAP1000 support.
# 04may01,scm  add STRONGARM support...
# 27oct00,s_m  rename PPC405 cpu types
# 07sep00,sm   added subdirs for PPC405GP and PPC405GF
# 11dec00,scm  replace references to ARMSA2 to XScale
# 31aug00,scm  add sa2 support to makefile
# 20jan99,cdp  removed support for old ARM libraries.
# 13nov98,cdp  added ARMARCH3, ARMARCH4, ARMARCH4_T support.
# 03mar00,zl   merged SH support into T2
# 19dec00,pes  Adapt to MIPS32/MIPS64 CPU architectures
# 20aug98,tpr  added PowerPC EC 603 support.
# 09apr98,hdn  added PENTIUM support.
# 06jan98,cym  added simnt support cleaned up modhist.
# 26mar97,cdp  added ARM7TDMI_T support.
# 16dec96,kkk  added R4650 support.
# 12dec96,cdp  added ARM support.
# 26nov96,dvs  added support for SIMSPARCSOLARIS
#             +pr
# 04nov96,p_m  added PPC860
# 17jun96,yp   written
#
# DESCRIPTION
# This file contains the makefile rules to launch builds in the subdirectories
# that are architecture specific. Given the CPU figure out the SUBDIR to build
#
#*/


SUBDIRS_MC68000=mc68k
SUBDIRS_MC68010=mc68k
SUBDIRS_MC68020=mc68k
SUBDIRS_MC68030=mc68k
SUBDIRS_MC68040=mc68k
SUBDIRS_MC68LC040=mc68k
SUBDIRS_MC68060=mc68k
SUBDIRS_CPU32=mc68k
SUBDIRS_SPARC=sparc
SUBDIRS_SPARClite=sparc
SUBDIRS_I960CA=i960
SUBDIRS_I960KA=i960
SUBDIRS_I960KB=i960
SUBDIRS_I960JX=i960
SUBDIRS_I960HX=i960
SUBDIRS_MIPS32=mips
SUBDIRS_MIPS64=mips
SUBDIRS_MIPSI2=mips
SUBDIRS_MIPSI3=mips
SUBDIRS_MIPSI32=mips
SUBDIRS_MIPSI32R2=mips
SUBDIRS_MIPSI64=mips
SUBDIRS_MIPSI64R2=mips
SUBDIRS_MIPS64_64=mips
SUBDIRS_AM29030=am29k
SUBDIRS_AM29200=am29k
SUBDIRS_AM29035=am29k
SUBDIRS_SIMSPARCSUNOS=simsparc
SUBDIRS_SIMSPARCSOLARIS=simsolaris
SUBDIRS_SIMHPPA=simhppa
SUBDIRS_I80386=i86
SUBDIRS_I80486=i86
SUBDIRS_PENTIUM=i86
SUBDIRS_PENTIUM2=i86
SUBDIRS_PENTIUM3=i86
SUBDIRS_PENTIUM4=i86
SUBDIRS_PENTIUM64=i86
SUBDIRS_CORE2=i86
SUBDIRS_X86_64=i86
SUBDIRS_SIMNT=simnt
SUBDIRS_ULTRASPARC=sparcv9
SUBDIRS_SH32=sh
SUBDIRS_SH7000=sh
SUBDIRS_SH7600=sh
SUBDIRS_SH7040=sh
SUBDIRS_SH7700=sh
SUBDIRS_SH7410=sh
SUBDIRS_SH7729=sh
SUBDIRS_SH7750=sh
SUBDIRS_MCORE10=mcore
SUBDIRS_MCORE15=mcore
SUBDIRS_MCORE200=mcore
SUBDIRS_MCORE300=mcore
SUBDIRS_MCF5200=coldfire
SUBDIRS_MCF5400=coldfire
SUBDIRS_FR500=frv
SUBDIRS_MAP1000=map
SUBDIRS_MAP1000A=map
SUBDIRS_MAPCA=map
SUBDIRS_SIMLINUX=simlinux
SUBDIRS_ATOM=i86
SUBDIRS_CORE=i86
SUBDIRS_NEHALEM=i86
SUBDIRS_WESTMERE=i86
SUBDIRS_SANDYBRIDGE=i86
SUBDIRS_IVYBRIDGE=i86
SUBDIRS_HASWELL=i86
SUBDIRS_BROADWELL=i86
SUBDIRS_SILVERMONT=i86
SUBDIRS_AIRMONT=i86
SUBDIRS_SKYLAKE=i86
SUBDIRS_GOLDMONT=i86
SUBDIRS_ARMARCH7=arm
SUBDIRS_ARMARCH7M=arm
SUBDIRS_ARMARCH8A=arm
SUBDIRS_PPCE500MC=ppc
SUBDIRS_PPCE500V2=ppc
SUBDIRS_PPCE6500=ppc
SUBDIRS_PPC603=ppc
SUBDIRS_PPC604=ppc

