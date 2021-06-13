# rules.bsp.mk - make rules
#
# Copyright 2015 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 10sep15,jmp  Removed lma adjustement for non LP64 config (V7PRO-2406).
# 27aug15,mze  switch to new __WRVX_BSP_POST_BUILD_RULE  (V7COR-3501)
# 02jul15,wyt  add image tag. (V7RAD-85) (F2518)
# 07jan15,syt  copied for rules.bsp.mk of qsp_ppc.(F2518)

# DESCRIPTION
# This file contains rules for building VxWorks for the PPC64 fsl_t2t4
#

# INTERNAL
# This file should only contain rules specific to the BSP.  Definitions
# specific to this BSP should be placed in the defs file (defs.bsp.mk)
#

__WRVX_BSP_POST_BUILD_RULE += $(CP) $@ $@_swap;

ifdef  _WRS_CONFIG_LP64
# adjust lma for all sections.

__WRVX_BSP_POST_BUILD_RULE += $(OBJCPY) --change-section-lma .*-$(LOAD_ADDR) \
                              --no-change-warnings $@ > /dev/null 2>&1;
endif

__WRVX_BSP_POST_BUILD_RULE += $(ENV_BIN)image-tag -tag $@;
