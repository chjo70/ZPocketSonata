
ifndef __HEADER_ACCESS_PPC_E500_INCLUDED
__HEADER_ACCESS_PPC_E500_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_PPC_E500 = 



ifneq ($(wildcard $(VSB_USER_PROTECTED_INCLUDE_DIR)/PPC_E500),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), PPC_E500))
VSBL_LUH += $(OPTION_INCLUDE_DIR)$(VSB_USER_PROTECTED_INCLUDE_DIR)/PPC_E500
endif
endif

endif

endif

