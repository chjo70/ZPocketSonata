
ifndef __HEADER_ACCESS_CORE_RTP_INCLUDED
__HEADER_ACCESS_CORE_RTP_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_CORE_RTP = 



ifneq ($(wildcard $(VSB_USER_PROTECTED_INCLUDE_DIR)/CORE_RTP),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), CORE_RTP))
VSBL_LUH += $(OPTION_INCLUDE_DIR)$(VSB_USER_PROTECTED_INCLUDE_DIR)/CORE_RTP
endif
endif

endif

endif

