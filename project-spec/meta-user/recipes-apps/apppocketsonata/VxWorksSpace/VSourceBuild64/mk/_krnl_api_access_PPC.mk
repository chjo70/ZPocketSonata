
ifndef __HEADER_ACCESS_PPC_INCLUDED
__HEADER_ACCESS_PPC_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_PPC = 



ifneq ($(wildcard $(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/PPC),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), PPC))
VSBL_LKH += $(OPTION_INCLUDE_DIR)$(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/PPC
endif
endif

endif

endif

