
ifndef __HEADER_ACCESS_IPNET_COREIP_INCLUDED
__HEADER_ACCESS_IPNET_COREIP_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_IPNET_COREIP = 



ifneq ($(wildcard $(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/IPNET_COREIP),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), IPNET_COREIP))
VSBL_LKH += $(OPTION_INCLUDE_DIR)$(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/IPNET_COREIP
endif
endif

endif

endif

