
ifndef __HEADER_ACCESS_OSTOOLS_INCLUDED
__HEADER_ACCESS_OSTOOLS_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_OSTOOLS = 



ifneq ($(wildcard $(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/OSTOOLS),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), OSTOOLS))
VSBL_LKH += $(OPTION_INCLUDE_DIR)$(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/OSTOOLS
endif
endif

endif

endif

