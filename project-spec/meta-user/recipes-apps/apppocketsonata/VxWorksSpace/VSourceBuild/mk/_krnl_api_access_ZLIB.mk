
ifndef __HEADER_ACCESS_ZLIB_INCLUDED
__HEADER_ACCESS_ZLIB_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_ZLIB = 



ifneq ($(wildcard $(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/ZLIB),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), ZLIB))
VSBL_LKH += $(OPTION_INCLUDE_DIR)$(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/ZLIB
endif
endif

endif

endif

