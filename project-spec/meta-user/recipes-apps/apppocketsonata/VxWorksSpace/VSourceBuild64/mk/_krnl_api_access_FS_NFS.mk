
ifndef __HEADER_ACCESS_FS_NFS_INCLUDED
__HEADER_ACCESS_FS_NFS_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_FS_NFS = 



ifneq ($(wildcard $(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/FS_NFS),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), FS_NFS))
VSBL_LKH += $(OPTION_INCLUDE_DIR)$(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/FS_NFS
endif
endif

endif

endif

