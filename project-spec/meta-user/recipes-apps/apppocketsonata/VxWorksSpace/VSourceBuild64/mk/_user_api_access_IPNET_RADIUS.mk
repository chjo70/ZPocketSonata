
ifndef __HEADER_ACCESS_IPNET_RADIUS_INCLUDED
__HEADER_ACCESS_IPNET_RADIUS_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_IPNET_RADIUS = 



ifneq ($(wildcard $(VSB_USER_PROTECTED_INCLUDE_DIR)/IPNET_RADIUS),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), IPNET_RADIUS))
VSBL_LUH += $(OPTION_INCLUDE_DIR)$(VSB_USER_PROTECTED_INCLUDE_DIR)/IPNET_RADIUS
endif
endif

endif

endif

