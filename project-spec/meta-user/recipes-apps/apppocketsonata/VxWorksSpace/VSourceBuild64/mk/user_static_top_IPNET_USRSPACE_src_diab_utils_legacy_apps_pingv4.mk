
#
# This file is automatically generated by mk/usr/defs.fastlibgen.mk.
#
# build configuration :
#	VSB : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64
#	CPU : PPCE6500
#	TOOL : diab
#	FP : hard
# 	ENDIAN : big
#	LIB_DIR_TAG = 
#	LIBDIRBASE = common
#	LIBDIRBASE = $(TOOL_COMMON_DIR)$(LIB_DIR_TAG)






ifeq (,)



endif


# DEP_OBJS = (DEP_OBJS)

# LIB_BASE_NAMES = net

 
_STATIC_LIBOBJS_common_net_user_static_top_IPNET_USRSPACE_src_diab_utils_legacy_apps_pingv4 = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common/objnet/pingLib.o

_usrstarcmdfile_common_net : $(_STATIC_LIBOBJS_common_net_user_static_top_IPNET_USRSPACE_src_diab_utils_legacy_apps_pingv4)

_STATIC_LIBOBJS_common_net += $(_STATIC_LIBOBJS_common_net_user_static_top_IPNET_USRSPACE_src_diab_utils_legacy_apps_pingv4)

__OBJS_TO_CLEAN_IPNET_USRSPACE += $(_STATIC_LIBOBJS_common_net_user_static_top_IPNET_USRSPACE_src_diab_utils_legacy_apps_pingv4)

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common/libnet.a : $(_STATIC_LIBOBJS_common_net_user_static_top_IPNET_USRSPACE_src_diab_utils_legacy_apps_pingv4)

ifndef _DONEBASE_USRST_LIB_common_net

_DONEBASE_USRST_LIB_common_net = TRUE

# LIBBASES += net

# D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common:
#	mkdir -p $@

# D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common/objnet :
#	mkdir -p $@

usrstlib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common/libnet.a

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common/libnet.a : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common

__STATIC_BUILT_LIBS += common_net

__STLIB_common_net = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common/libnet.a

arcmdfiles : _usrstarcmdfile_common_net

_usrstarcmdfile_common_net :
	$(file >$@,$(sort $(_STATIC_LIBOBJS_common_net)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common/libnet.a : _usrstarcmdfile_common_net | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @_usrstarcmdfile_common_net

clean  _layer_clean_IPNET_USRSPACE : _clean_USRST_LIB_BASE_common_net

_clean_USRST_LIB_BASE_common_net :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/lib/common/libnet.a

endif


 

 

################
# rules defined locally in Makefile
##





################

objs : $(LIBOBJS)
 
# this is the end of the file 
