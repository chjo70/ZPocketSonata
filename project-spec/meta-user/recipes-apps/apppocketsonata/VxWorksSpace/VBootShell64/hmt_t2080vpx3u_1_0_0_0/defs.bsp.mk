# defs.bsp.mk - make variable definitions
#
# Copyright 2014 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 26jan15,y_y  fix LOAD_ADDR issue in LP32 mode.
# 07jan15,syt  added bootapp support. (US15027)
# 18jul14,x_z  added multipile FMAN microcode support. (US40507)
# 14may14,ylu  added C99 option for sysLib.o. (US35954)
# 07mar14,fao  create

# DESCRIPTION
# This file contains definitions for building VxWorks for the FREESCALE T2080
# board
#

CFLAGS_sysLib.o += $(C_COMPILER_FLAGS_C99)

ifdef _WRS_CONFIG_STANDALONE_DTB
## The following microcode patch is required for the
## frame manager in the T2080.
 
subststring =$(join $(subst x,$(subst :,_,$(subst -,_,$(subst .,_,$(subst /,_,$(1))))),_binary_x_),$(2))

fsl_fman_ucode_t4240_r2.0_106_4_14.obj:$(BSP_DIR)/fsl_fman_ucode_t4240_r2.0_106_4_14.bin
	$(OBJCPY) -I binary -O elf32-powerpc-vxworks \
	--redefine-sym $(call subststring,$<,start)=fman_ucode_t4240_r2_0_start \
	-B powerpc:603 $< $@

UCODE_BINLIST = $(notdir $(BSP_DIR)/fsl_fman_ucode_t4240_r2.0_106_4_14.bin)
UCODE_OBJLIST = $(UCODE_BINLIST:.bin=.obj)

ucode.a: $(UCODE_OBJLIST)
	- @ $(RM) $@
	@echo Generating FMAN microcode Object Library...
	$(AR) r $@ $^

POSTLINK_MODULES = ucode.a
endif

# note: this value must match KERN_SYS_MEM_RGN_BASE

ifndef  _WRS_CONFIG_LP64 
LOAD_ADDR       = 0
else
LOAD_ADDR       = 0xffffffff80000000
endif

vxWorks.bin:    vxWorks
		- @ $(RM) $@
		$(EXTRACT_BIN) vxWorks_swap $@
		

