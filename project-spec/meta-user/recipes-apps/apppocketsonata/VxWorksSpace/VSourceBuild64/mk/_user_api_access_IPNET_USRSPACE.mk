
ifndef __HEADER_ACCESS_IPNET_USRSPACE_INCLUDED
__HEADER_ACCESS_IPNET_USRSPACE_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_IPNET_USRSPACE = 



ifneq ($(wildcard $(VSB_USER_PROTECTED_INCLUDE_DIR)/IPNET_USRSPACE),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), IPNET_USRSPACE))
VSBL_LUH += $(OPTION_INCLUDE_DIR)$(VSB_USER_PROTECTED_INCLUDE_DIR)/IPNET_USRSPACE
endif
endif

endif

endif

